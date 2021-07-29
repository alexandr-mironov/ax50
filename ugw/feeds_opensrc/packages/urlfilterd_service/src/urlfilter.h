/********************************************************************************

  Copyright (c) 2016
  Lantiq Beteiligungs-GmbH & Co. KG
  Lilienthalstrasse 15, 85579 Neubiberg, Germany 
  For licensing information, see the file 'LICENSE' in the root folder of
  this software module.

 ********************************************************************************/

/*  ***************************************************************************** 
 *         File Name    : urlfilter.h                                          *
 *         Description  : urlfilter related struct,defs, prototyps * 
 *  *****************************************************************************/

/*! \file urlfilter.h
  \brief This File contains the Constants, enumerations, related Data
  structures and API's.
  */

#ifndef _URLFILTER_H
#define _URLFILTER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <linux/types.h>
#include <linux/netfilter.h>	/* for NF_ACCEPT */
#include <libnetfilter_queue/libnetfilter_queue.h>
#include <string.h>		/* strncpy() */
#include <sys/socket.h>
#include <time.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <regex.h>
#include <list.h>
#include <libubox/blobmsg_json.h>
#include <libubox/avl-cmp.h>
#include <libubox/uloop.h>

#define MAX_LEN_VALID_VALUE 1024 /*!< Parameter valid value string length */

#ifndef OUT
/*!
	\brief 
*/
#define OUT /*!< Macro for OUT null */
#endif 

#ifndef INOUT
/*! 
	\brief 
*/
#define INOUT /*!< Macro INOUT null */
#endif 

#ifndef IN 
/*! 
	\brief 
*/
#define IN /*!< Macro for IN null */
#endif

/*!  \brief  This function is used to Add the URL node to global list
  \param[in] pxURLChain Global list
  \param[in] pcURL URL to be added to list
  \return EXIT_SUCCESS/-EXIT_FAILURE 
  */
static struct url_list *URLFilter_addURLNode(IN struct url_list *pxURLChain, IN char *pcURL);

/*!  \brief  This function reads the urls from the /tmp/url_list and update to glist 
  \return EXIT_SUCCESS/-EXIT_FAILURE 
  */
int32_t URLFilter_readURLConfig(void);

/*!  \brief This function is used to parse the hostname from the DNS packet
 \param[in] pcData Ponter to the packet data 
 \param[out] pcHostname Pointer to the string to be updated
 \return EXIT_SUCCESS /-EXIT_FAILURE
 */
static int32_t URLFilter_parseDNSHeader(IN const char *pcData, OUT char *pcHostname);

/*!  \brief  This function is used to match the dns host name with Configured URL
  \param[in] pHostName Contains the host name extracted from DNS query.
  \param[in] pPattern Contains the user configured URL
  \return true/false 
  */
bool regMatch(IN const char *pHostName, IN const char *pPattern);

/*!  \brief  This function is used to search the hostname in the list
  \param[in] pHostName Pointer to the Host name to be searched
  \return EXIT_SUCCESS / -EXIT_FAILURE
 */

int32_t URLFilter_searchURLList(IN char *pHostName);

/*!  \brief  This function is used to process the DNS packet received
  on the queue 1. 
  \param[in] pxQueue Pointer to the nfq_q_handle structure
  \param[in] pxPkt Pointer to the nfq_data structure
  \return EXIT_SUCCESS / -EXIT_FAILURE
 */
int32_t URLFilter_processDNSPkt(IN struct nfq_data *pxPkt, IN struct nfq_q_handle *pxQueue);

/*!  \brief  This function will be invoked when  a packet is received on the queue 1. 
  \param[in] pxQueue Pointer to the nfq_q_handle structure
  \param[in] pxMsg Pointer to the nfgenmsg structure
  \param[in] pxPkt Pointer to the nfq_data structure
  \param[in] pCbData Pointer to the Call back data
  \return EXIT_SUCCESS / -EXIT_FAILURE
 */
static int32_t URLFilter_processPktCallback(IN struct nfq_q_handle *pxQueue, IN struct nfgenmsg *pxMsg, IN struct nfq_data *pxPkt, IN void *pCbData);

/*!  \brief  This function will be invoked when  a packet is received on the socket. 
  \param[in] pxSock Pointer to the socket
  \param[in] nEvents Events registered for this socket
  \param[in] pCbData Pointer to the Call back data
  \return
 */
static void URLFilter_handleRcvData(IN struct uloop_fd *pxSock, IN unsigned int nEvents);

/*!	 \brief Macros definitions
*/
#define URL_LIST "/tmp/url_list"	/* File to store the URLs configured */

/*!	 \strucuture url_list
*/
typedef struct url_list {
	char sURL[MAX_LEN_VALID_VALUE];
	struct list_head pxURLEntries;	/* List. */
} url_list;

url_list glist;

#define UNUSED_PARAM(x) (void)(x)
/* IP header */
struct url_sniffIP {
	unsigned char ucIPVerHdrLen;	/*version<<4|header length>>2 */
	unsigned char ucIPTos;	/*type of service */
	unsigned char ucIPLen;	/* total length */
	unsigned char ucIPId;	/* identification */
	unsigned char ucIPOff;	/* fragment offset field */
#define IP_RESFRAG 0x8000	/* reserved fragment flag */
#define IP_DONTFRAG 0x4000	/* dont fragment flag */
#define IP_MOREFRAG 0x2000	/* more fragments flag */
#define IP_OFFMASKFRAG 0x1fff	/* mask for fragmenting bits */
	unsigned char ucIPTTL;	/* time to live */
	unsigned char ucIPProto;	/* protocol */
	unsigned short usIPCheckSum;	/* checksum */
	struct in_addr xIPSrc, xIPDest;	/* source and dest address */
};
#define IP_HDRLEN(ip)               (((ip)->ucIPVerHdrLen) & 0x0f)

struct ipv6hdr {
        __u8 version:4, priority:4;
        __u8 flow_lbl[3];

        __u16 payload_len;
        __u8 nexthdr;
        __u8 hop_limit;

        struct in6_addr saddr;
        struct in6_addr daddr;
};

/* TCP header */
typedef u_int tcp_seq;

/* UDP Header*/
struct UDP_hdr {
	u_short uh_sport;	/* source port */
	u_short uh_dport;	/* destination port */
	u_short uh_ulen;	/* datagram length */
	u_short uh_sum;		/* datagram checksum */
};

/* DNS header definition */
struct dnshdr {
	char id[2];
	char flags[2];
	char qdcount[2];
	char ancount[2];
	char nscount[2];
	char arcount[2];
};

#endif
