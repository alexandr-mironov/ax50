#ifndef __PPA_API_SW_ACCEL_H__20130913
#define __PPA_API_SW_ACCEL_H__20130913
/*******************************************************************************
 **
 ** FILE NAME    : ppa_api_sw_accel.h
 ** PROJECT      : PPA
 ** MODULES      : PPA API (Software Fastpath Implementation)
 **
 ** DATE         : 12 Sep 2013
 ** AUTHOR       : Lantiq
 ** DESCRIPTION  : Function to bypass the linux stack for packets belonging to the PPA sessions which are not in PPE firmware.
 ** COPYRIGHT    :              Copyright (c) 2013
 **                          Lantiq Deutschland GmbH
 **                   Am Campeon 3; 85579 Neubiberg, Germany
 **
 **   For licensing information, see the file 'LICENSE' in the root folder of
 **   this software module.
 **
 ** HISTORY
 ** $Date        $Author                $Comment
 ** 12 Sep 2013  Kamal Eradath          Initiate Version
 *******************************************************************************/
#include "ppa_stack_al.h"

/*! \file ppa_api_sw_accel.h
  \brief This file contains es.
  software fastpath function declarations
 */

/*@{*/

/*
 * ####################################
 *              Definition
 * ####################################
 */

/*
 * ####################################
 *              Data Type
 * ####################################
 */
extern volatile u_int8_t g_sw_fastpath_enabled;

typedef enum {
  SW_ACC_TYPE_IPV4,
  SW_ACC_TYPE_IPV6,
  SW_ACC_TYPE_6RD,
  SW_ACC_TYPE_DSLITE,
  SW_ACC_TYPE_BRIDGED,
#if defined(CONFIG_LTQ_PPA_TCP_LITEPATH) && CONFIG_LTQ_PPA_TCP_LITEPATH
  SW_ACC_TYPE_LTCP,
#if defined(CONFIG_LTQ_PPA_LRO) && CONFIG_LTQ_PPA_LRO
  SW_ACC_TYPE_LTCP_LRO,
#endif
#endif
#if defined(CONFIG_PPTP_MODULE) || defined(CONFIG_PPTP)
  SW_ACC_TYPE_PPTP,
#endif
  SW_ACC_TYPE_MAX
}sw_acc_type;

typedef struct sw_header {
  uint16_t tot_hdr_len;		/* Total length of outgoing header (for future use) */
  uint16_t transport_offset;	/* Transport header offset - from beginning of MAC header  */
  uint16_t network_offset; 	/* Network header offset - from beginning of MAC header  */
  uint32_t extmark; 		/* marking */
#ifdef CONFIG_PPA_PUMA7	
  uint32_t queue; 		/* port egress queue */
#endif
  sw_acc_type type;  		/* Software acceleration type */
  PPA_NETIF *tx_if;   		/* Out interface */
  int (*tx_handler)(PPA_SKBUF *skb); /* tx handler function */
#if defined(CONFIG_LTQ_PPA_TCP_LITEPATH) && CONFIG_LTQ_PPA_TCP_LITEPATH
  struct dst_entry *dst; 	/* route entry */
#endif
  uint8_t hdr[0];		/* Header to be copied */

} t_sw_hdr;
/*
 * ####################################
 *             Declaration
 * ####################################
 */
/* @} */
/*
   int32_t ppa_sw_fastpath_enable(uint32_t f_enable, uint32_t flags);
   int32_t ppa_get_sw_fastpath_status(uint32_t *f_enable, uint32_t flags);
   int32_t ppa_sw_fastpath_send(struct sk_buff *skb);
 */
#ifdef CONFIG_NET_CLS_ACT
extern struct sk_buff *handle_ing(struct sk_buff *skb, struct packet_type **pt_prev, int *ret, struct net_device *orig_dev);
extern int check_ingress(struct sk_buff *skb);
#endif


extern int32_t (*ppa_sw_fastpath_enable_hook)(uint32_t, uint32_t);
extern int32_t (*ppa_get_sw_fastpath_status_hook)(uint32_t *, uint32_t);
extern int32_t (*ppa_sw_fastpath_send_hook)(PPA_SKBUF *);
#if defined(CONFIG_LTQ_PPA_TCP_LITEPATH) && CONFIG_LTQ_PPA_TCP_LITEPATH
extern int32_t (*ppa_tcp_litepath_enable_hook)(uint32_t, uint32_t);
extern int32_t (*ppa_get_tcp_litepath_status_hook)(uint32_t *, uint32_t);
extern int32_t (*ppa_sw_litepath_tcp_send_hook)(PPA_SKBUF *);
#endif

extern int32_t (*ppa_sw_add_session_hook)(PPA_BUF *skb, struct session_list_item *p_item);
extern int32_t (*ppa_sw_update_session_hook)(PPA_BUF *skb, struct session_list_item *p_item,struct netif_info *tx_ifinfo);
extern void (*ppa_sw_del_session_hook)(struct session_list_item *p_item);
extern int32_t (*ppa_sw_session_enable_hook)(struct session_list_item *p_item, uint32_t, uint32_t);
extern int32_t (*ppa_get_sw_session_status_hook)(struct session_list_item *p_item, uint32_t *, uint32_t);

extern int32_t sw_update_session(PPA_BUF *skb, struct session_list_item *p_item, struct netif_info *tx_ifinfo);
extern int32_t sw_add_session(PPA_BUF *skb, struct session_list_item *p_item);
extern void sw_del_session(struct session_list_item *p_item);

extern int32_t sw_fastpath_send(PPA_SKBUF *skb);
extern int32_t get_sw_fastpath_status(uint32_t *f_enable, uint32_t flags);
extern int32_t sw_fastpath_enable(uint32_t f_enable, uint32_t flags);
#if defined(CONFIG_LTQ_PPA_TCP_LITEPATH) && CONFIG_LTQ_PPA_TCP_LITEPATH
extern int ppa_sw_litepath_local_deliver(struct sk_buff *skb);
#endif
#endif  // __PPA_API_SW_ACCEL_H__20130913
