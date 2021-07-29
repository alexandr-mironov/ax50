/********************************************************************************

  Copyright (c) 2016
  Lantiq Beteiligungs-GmbH & Co. KG
  Lilienthalstrasse 15, 85579 Neubiberg, Germany 
  For licensing information, see the file 'LICENSE' in the root folder of
  this software module.

 ********************************************************************************/

/*  ***************************************************************************** 
 *         File Name    : urlfilter.c                                           *
 *         Description  : urlfilterd daemon is used to block the urls specified  * 
 *			  in the /tmp/url_list				 	*
 *                                                                              *
 *  *****************************************************************************/

#include "urlfilter.h"
#include <syslog.h>
#include <linux/ip.h>

struct nfq_handle *gpxNfqHandle = NULL;
int32_t gNfqFd = 0;

/*!  \brief  This function is used to Add the URL node to global list
  \param[in] pxURLChain Global list
  \param[in] pcURL URL to be added to list
  \return EXIT_SUCCESS/-EXIT_FAILURE 
  */
static struct url_list *URLFilter_addURLNode(IN struct url_list *pxURLChain, IN char *pcURL)
{

	struct url_list *pxTmp;
	/* Create a temporary node */
	pxTmp = (struct url_list *)malloc(sizeof(struct url_list));
	if (!pxTmp) {
		syslog(LOG_ERR,"Node creation failed \n");
		return NULL;
	}

	memset(pxTmp, 0, sizeof(struct url_list));
	/* Copy the pcURL to pxTmp->sURL */
	strncpy(pxTmp->sURL, pcURL, MAX_LEN_VALID_VALUE);
	/* Add the temporary node to pxURLChain */
	list_add_tail(&(pxTmp->pxURLEntries), &(pxURLChain->pxURLEntries));
	return pxTmp;

}

/*!  \brief  This function reads the urls from the /tmp/url_list and update to glist 
  \return EXIT_SUCCESS/-EXIT_FAILURE 
  */
int32_t URLFilter_readURLConfig()
{
	FILE *pFd;
	char sBuf[MAX_LEN_VALID_VALUE] = { 0 };
	char sURL[MAX_LEN_VALID_VALUE] = { 0 };
	char *pcTmp1 = NULL;
	char *pcTmp2 = NULL;

	INIT_LIST_HEAD(&glist.pxURLEntries);
	/* Open the URL_LIST file */
	pFd = fopen(URL_LIST, "r");
	if (pFd == NULL) {
		/* failed to open a file */
		syslog(LOG_ERR,"Failed to open a URL_LIST file \n");
		return -EXIT_FAILURE;
	}
	/* Get all the URLSs from URL_LIST file and add to the global list */
	while (fgets(sBuf, MAX_LEN_VALID_VALUE, pFd) != NULL) {
		if (strncmp(sBuf, "http://", 7) == 0) {
			pcTmp1 = sBuf + 7;
		} else if (strncmp(sBuf, "https://", 8) == 0) {
			pcTmp1 = sBuf + 8;
		} else {
			pcTmp1 = sBuf;
		}
		if ((pcTmp2 = strchr(pcTmp1, '\n')) != NULL) {
			*pcTmp2 = '\0';
		}
		strncpy(sURL, pcTmp1, MAX_LEN_VALID_VALUE);
		/* Add the URL to the global list */
		syslog(LOG_DEBUG,"Adding URL [%s] to Global list\n", sURL);
		URLFilter_addURLNode(&glist, sURL);

	}
	fclose(pFd);
	return EXIT_SUCCESS;
}

/*!  \brief This function is used to parse the hostname from the http packet
 \param[in] pcData Ponter to the packet data 
 \param[out] pcHostname Pointer to the string to be updated
 \return EXIT_SUCCESS /-EXIT_FAILURE
 */

static int32_t URLFilter_parseDNSHeader(IN const char *pcData, OUT char *pcHostname)
{

/*
 * Extracts the request from a dns query
 * pcData will be in this format: [3]www[7]example[3]com[0]
 * pcHostname will be this: www.example.com
 */

	unsigned int i, j, k;
	const char *pcCurr = pcData;
	unsigned int nSize;

	nSize = pcCurr[0];

	j = 0;
	i = 1;
	while (nSize > 0) {
		for (k = 0; k < nSize; k++) {
			pcHostname[j++] = pcCurr[i + k];
		}
		pcHostname[j++] = '.';
		i += nSize;
		nSize = pcCurr[i++];
	}
	pcHostname[--j] = '\0';
	return EXIT_SUCCESS;
}

/*!  \brief  This function is used to match the dns host name with Configured URL
  \param[in] pHostName Contains the host name extracted from DNS query.
  \param[in] pPattern Contains the user configured URL
  \return true/false 
  */
bool regMatch(IN const char *pHostName, IN const char *pPattern)
{
	regex_t re;
	int32_t nRet;

	if (regcomp(&re, pPattern, REG_EXTENDED) != 0)
		return false;

	nRet = regexec(&re, pHostName, (size_t) 0, NULL, 0);
	regfree(&re);

	if (nRet == 0)
		return true;

	return false;
}

/*!  \brief  This function is used to search the hostname in the list
  \param[in] pHostName Pointer to the Host name to be searched
  \return EXIT_SUCCESS / -EXIT_FAILURE
 */

int32_t URLFilter_searchURLList(IN char *pHostName)
{

	struct list_head *node;
	struct url_list *pxURLNode;
	if (!list_empty(&glist.pxURLEntries)) {
		list_for_each(node, &glist.pxURLEntries) {
			pxURLNode = list_entry(node, struct url_list, pxURLEntries);

			if (regMatch(pHostName, pxURLNode->sURL) == true) {
				syslog(LOG_DEBUG,"Received Request [%s] is in configured list [%s] \n", pHostName, pxURLNode->sURL);
				return EXIT_SUCCESS;
			}
		}
	}
	return -EXIT_FAILURE;
}

/*!  \brief  This function is used to process the DNS packet received
  on the queue 1. 
  \param[in] pxQueue Pointer to the nfq_q_handle structure
  \param[in] pxPkt Pointer to the nfq_data structure
  \return EXIT_SUCCESS / -EXIT_FAILURE
 */
int32_t URLFilter_processDNSPkt(IN struct nfq_data * pxPkt, IN struct nfq_q_handle * pxQueue)
{
	struct nfqnl_msg_packet_hdr *pxHeader = NULL;
	uint32_t unIpHdrLen = 0;
	uint32_t unId = 0;
	int32_t nRet = EXIT_SUCCESS;
	int32_t nLen = 0;
	unsigned char *pucPktData = NULL;
	const struct UDP_hdr *pxUDPHdr = NULL;	/* The UDP header */
	unsigned char *pucPayload = NULL;
	char pcHostname[MAX_LEN_VALID_VALUE] = { 0 };
	unsigned char version = 0;
	struct iphdr *iph = NULL;

	if ((pxHeader = nfq_get_msg_packet_hdr(pxPkt))) {
		unId = ntohl(pxHeader->packet_id);
	}
	/* Print the payload; in copy meta mode, only headers will be included;
	   in copy packet mode, whole packet will be returned. */
	nLen = nfq_get_payload(pxPkt, &pucPktData);
	if (pucPktData == NULL) {
		syslog(LOG_ERR,"Failed to get Payload\n");
		nRet = -EXIT_FAILURE;
		goto end;
	}

	if (nLen) {
		/* define/compute ip header offset */
		iph = (struct iphdr *)pucPktData;
		version = iph->version;
		if (version == 4) {
			unIpHdrLen = iph->ihl * 4;
			if (unIpHdrLen < 20) {
				syslog(LOG_ERR,"   * Invalid IP header length: %u bytes\n", unIpHdrLen);
				nRet = -EXIT_FAILURE;
				goto end;
			}
		}
		if (version == 6) {
			unIpHdrLen = sizeof(struct ipv6hdr);
		}
	}
	/* define/compute UDP header offset */
	pxUDPHdr = (struct UDP_hdr *)(pucPktData + unIpHdrLen);
	/* define/compute UDP payload (segment) offset */
	pucPayload = (pucPktData + unIpHdrLen + sizeof(struct UDP_hdr) + sizeof(struct dnshdr));

	if  (ntohs(pxUDPHdr->uh_dport) == 53) {
		URLFilter_parseDNSHeader((const char *)pucPayload, pcHostname);
		syslog(LOG_DEBUG,"Received Host name in DNS query [%s] \n", pcHostname);
	}
	if (pcHostname[0] != '\0') {
		if (URLFilter_searchURLList(pcHostname) == EXIT_SUCCESS) {

			if ((nRet = nfq_set_verdict(pxQueue, unId, NF_DROP, 0, NULL)) == -EXIT_FAILURE) {
				perror("Failed to set verdict");
				syslog(LOG_ERR,"Failed to set verdict for packet id [%d]\n", unId);
			}
			nRet = EXIT_SUCCESS;
			goto end;

		}
	}
	if ((nRet = nfq_set_verdict(pxQueue, unId, NF_ACCEPT, 0, NULL)) == -EXIT_FAILURE) {
		perror("Failed to set verdict");
		syslog(LOG_ERR,"Failed to set verdict for packet id [%d]\n", unId);
	} else {
		nRet = EXIT_SUCCESS;
	}
 end:
	return nRet;
}

/*!  \brief  This function will be invoked when  a packet is received on the queue 1. 
  \param[in] pxQueue Pointer to the nfq_q_handle structure
  \param[in] pxMsg Pointer to the nfgenmsg structure
  \param[in] pxPkt Pointer to the nfq_data structure
  \param[in] pCbData Pointer to the Call back data
  \return EXIT_SUCCESS / -EXIT_FAILURE
 */

static int32_t URLFilter_processPktCallback(IN struct nfq_q_handle *pxQueue, IN struct nfgenmsg *pxMsg, IN struct nfq_data *pxPkt, IN void *pCbData)
{
	UNUSED_PARAM(pxMsg);
	UNUSED_PARAM(pCbData);
	int32_t nRet = EXIT_SUCCESS;
	/* Process DNS Packet */
	nRet = URLFilter_processDNSPkt(pxPkt, pxQueue);
	return nRet;

	/* end URLFilter_processPktCallback */
}

/*!  \brief  This function will be invoked when  a packet is received on the socket. 
  \param[in] pxSock Pointer to the socket
  \param[in] nEvents Events registered for this socket
  \param[in] pCbData Pointer to the Call back data
  \return
 */
static void URLFilter_handleRcvData(struct uloop_fd *pxSock, unsigned int nEvents)
{
	int32_t nBytes;
	char buf[4096];
	UNUSED_PARAM(nEvents);
	struct uloop_fd xNfqFd;

	memset(&xNfqFd, 0, sizeof(struct uloop_fd));
	nBytes = read(pxSock->fd, (char *)buf, sizeof(buf));
	if (nBytes >= 0) {
		nfq_handle_packet(gpxNfqHandle, buf, nBytes);
	}

	if (gNfqFd > 0) {
		xNfqFd.fd = gNfqFd;
		xNfqFd.cb = URLFilter_handleRcvData;
		uloop_fd_add(&xNfqFd, ULOOP_BLOCKING | ULOOP_READ);
		syslog(LOG_DEBUG,"Added xNfqFd in FD Set \n");
	}

}

/*!  \brief  This function is will be invoked when urlfilterd daemon is started.
  \return EXIT_SUCCESS / -EXIT_FAILURE
 */

int main(void)
{
	struct nfq_q_handle *pxQueue = NULL;
	struct uloop_fd xNfqFd;

	memset(&xNfqFd, 0, sizeof(struct uloop_fd));

	int32_t nRet = EXIT_SUCCESS;

	/* read the configuration file */
	URLFilter_readURLConfig();

	syslog(LOG_DEBUG,"URLFilterd started\n");

	/* Ubus Socket Init */
	if (uloop_init() != EXIT_SUCCESS) {
		syslog(LOG_ERR,"ULoop Init Failed.\n");
	}

	/* Get a queue connection handle from the module */
	if (!(gpxNfqHandle = nfq_open())) {
		perror("nfq_open");
		syslog(LOG_ERR,"error during nfq_open(), nfnetlink.ko and nfnetlink_queue.ko should be installed to make urlfilter work\n");
		nRet = -EXIT_FAILURE;
		goto end;
	}

	/* Unbind the handler from processing any IP packets */
	if (nfq_unbind_pf(gpxNfqHandle, AF_INET) < 0) {
		syslog(LOG_ERR,"error during nfq_unbind_pf()\n");
		nRet = -EXIT_FAILURE;
		goto end;
	}
	if (nfq_unbind_pf(gpxNfqHandle, AF_INET6) < 0) {
		syslog(LOG_ERR,"error during nfq_unbind_pf()\n");
		nRet = -EXIT_FAILURE;
		goto end;
	}

	/* Bind this handler to process IP packets... */
	if (nfq_bind_pf(gpxNfqHandle, AF_INET) < 0) {
		syslog(LOG_ERR,"error during nfq_bind_pf()\n");
		nRet = -EXIT_FAILURE;
		goto end;
	}

	if (nfq_bind_pf(gpxNfqHandle, AF_INET6) < 0) {
		syslog(LOG_ERR,"error during AF_INET6 nfq_bind_pf()\n");
		nRet = -EXIT_FAILURE;
		goto end;
	}
	/* Install a URLFilter_processPktCallback on queue 1 */
	if (!(pxQueue = nfq_create_queue(gpxNfqHandle, 1, &URLFilter_processPktCallback, NULL))) {
		syslog(LOG_ERR,"error during nfq_create_queue()\n");
		nRet = -EXIT_FAILURE;
		goto end;
	}

	/* Turn on packet copy mode */
	if (nfq_set_mode(pxQueue, NFQNL_COPY_PACKET, 0xffff) < 0) {
		syslog(LOG_ERR,"Could not set packet copy mode\n");
		nRet = -EXIT_FAILURE;
		goto end;
	}
	gNfqFd = nfq_fd(gpxNfqHandle);

	if (gNfqFd > 0) {
		xNfqFd.fd = gNfqFd;
		xNfqFd.cb = URLFilter_handleRcvData;
		uloop_fd_add(&xNfqFd, ULOOP_BLOCKING | ULOOP_READ);
		syslog(LOG_DEBUG,"Added xNfqFd in FD Set \n");
	}
	uloop_run();

 end:
	if (pxQueue != NULL) {
		syslog(LOG_DEBUG,"unbinding from queue 1\n");
		nfq_destroy_queue(pxQueue);
	}

	if (gpxNfqHandle != NULL) {
		syslog(LOG_DEBUG,"closing library handle\n");
		nfq_close(gpxNfqHandle);
	}

	return nRet;
}
