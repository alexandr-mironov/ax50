#ifndef __GUARDcfg_const_D5
#define __GUARDcfg_const_D5

#if defined(PROCESSOR_AMAZON_S)
	#define	__FW_VER_ID_HWORD						0x5503
	#define	__FW_VER_ID_LWORD						0x0200
	
    #define __FW_FEATURE_HWORD                      0x0F80
	#define __FW_FEATURE_LWORD                      0x0000
#endif

#if defined(PROCESSOR_AR10)
	#include "inc/AR10_D5_Version.inc"
#endif

#if defined(PROCESSOR_GRX390)
	#include "inc/GRX390_D5_Version.inc"
#endif
	
 //---------------------------------------------
	// CAPWAP TUNNELLING IPV4 Table Configuration
	//	0x1F00 - 0x1F7F
	// 	Size = 5 * 18 = 90 dwords
	//---------------------------------------------
	#define __CAPWAP_CONFIG_TABLE_BASE            0x1f00
	#define xLDI_CAPWAP_CONFIG_TABLE_BASE(__rd)	ldi __rd 0 __CAPWAP_CONFIG_TABLE_BASE
	//=============================================
	
  //---------------------------------------------
	// 6RD TUNNELLING IPV4 Header Table Configuration
	//	0x2f00 - 0x2f13
	// 	Size = 4 * 5 = 20 dwords
	//---------------------------------------------
	#define __TUNNEL_IPV4_HDR_TABLE_BASE            0x2f00
	#define xLDI_TUNNEL_IPV4_HDR_TABLE_BASE(__rd)	ldi __rd 0 __TUNNEL_IPV4_HDR_TABLE_BASE
	//=============================================
	 
    //---------------------------------------------
	// 6RD TUNNELLING IPV4 Header Table Configuration
	//	0x2f20 - 0x2f47
	// 	Size = 4 * 10 = 40 dwords
	//---------------------------------------------
	#define __TUNNEL_IPV6_HDR_TABLE_BASE            0x2f20
	#define xLDI_TUNNEL_IPV6_HDR_TABLE_BASE(__rd)	ldi __rd 0 __TUNNEL_IPV6_HDR_TABLE_BASE
    //=============================================
    
	//---------------------------------------------
	// IPV4 Routing Forward Table Action Table HASH Table -WAN
	// 	0x4000 - 0x4BFF
	// 	Size = 6 * 512 = 3072 dwords
	//---------------------------------------------
	#define __IPV4_WAN_HASH_ROUT_FWDA_TABLE_BASE	0x4000
	#define __IPV4_WAN_HASH_ROUT_FWDA_TABLE_SIZE	3072
	#define __IPV4_WAN_HASH_ROUT_FWDA_TABLE_SIZE_ipv6_en	1536

#if (defined (PROCESSOR_GRX390))	
	//---------------------------------------------
	// IPV4 Routing Forward Table Action Table HASH Table -LAN
	// 	0x5000 - 0x5BFF
	// 	Size = 6 * 512 = 3072 dwords
	//---------------------------------------------
	#define __IPV4_LAN_HASH_ROUT_FWDA_TABLE_BASE	0x5000
	#define __IPV4_LAN_HASH_ROUT_FWDA_TABLE_SIZE	3072
	#define __IPV4_LAN_HASH_ROUT_FWDA_TABLE_SIZE_ipv6_en	1536
	//---------------------------------------------

	// IPV4 Routing Forward Table Action Table COLLISION Table - WAN 
	// 	0x4C00 - 0x4D7F
	// 	Size = 6 * 64 = 384 dwords
	//---------------------------------------------
	#define __IPV4_WAN_COLLISION_ROUT_FWDA_TABLE_BASE	0x4C00
	#define __IPV4_WAN_COLLISION_ROUT_FWDA_TABLE_SIZE	384
    #define __xGET_wan_coll_action_tbl(__r_base, __r_ipv6_en)               \
        xLDI(__r_base, __IPV4_WAN_COLLISION_ROUT_FWDA_TABLE_BASE)           

	// IPV4 Routing Forward Table Action Table COLLISION Table 
	// 	0x4D80 - 0x4EFF
	// 	Size = 6 * 64 = 384 dwords
	//---------------------------------------------
	#define __IPV4_LAN_COLLISION_ROUT_FWDA_TABLE_BASE	0x4D80
	#define __IPV4_LAN_COLLISION_ROUT_FWDA_TABLE_SIZE	384
	
	//---------------------------------------------
	// TUNNELLING L2TP Header Table Configuration
	//	0x2040 - 0x209F
	// 	Size = 8 * 12 = 96 dwords
	//---------------------------------------------
	#define __TUNNEL_L2TP_HDR_TABLE_BASE            0x2040
	#define xLDI_TUNNEL_L2TP_HDR_TABLE_BASE(__rd)	ldi __rd 0 __TUNNEL_L2TP_HDR_TABLE_BASE
	
	//======================================================
    // L2TP debug information(0x20A0-0x20A5) FOR GRX390_D5
    //======================================================
    
    #define __L2TP_DS_DBG_BASE             0x20A0
    #define __L2TP_DS_DBG_SIZE             4
    #define __L2TP_DS_DBG_PTR              0x20A4
    
    //Original payload_len including inner IPV4/IPV6 header length
    #define __L2TP_US_PAYLOAD_LEN          0x20A5
	
#else
    //For AR9_D5 and AR10_D5
    
    //---------------------------------------------
	// IPV4 Routing Forward Table Action Table HASH Table -LAN
	// 	0x1000 - 0x1BFF
	// 	Size = 6 * 512 = 3072 dwords
	//---------------------------------------------
	#define __IPV4_LAN_HASH_ROUT_FWDA_TABLE_BASE	0x1000
	#define __IPV4_LAN_HASH_ROUT_FWDA_TABLE_SIZE	3072
	#define __IPV4_LAN_HASH_ROUT_FWDA_TABLE_SIZE_ipv6_en	1536
	//---------------------------------------------

	// IPV4 Routing Forward Table Action Table COLLISION Table - WAN 
	// 	0x1C00 - 0x1D7F
	// 	Size = 6 * 64 = 384 dwords
	//---------------------------------------------
	#define __IPV4_WAN_COLLISION_ROUT_FWDA_TABLE_BASE	0x1C00
	#define __IPV4_WAN_COLLISION_ROUT_FWDA_TABLE_SIZE	384
    #define __xGET_wan_coll_action_tbl(__r_base, __r_ipv6_en)               \
        xLDI(__r_base, __IPV4_WAN_COLLISION_ROUT_FWDA_TABLE_BASE)           

	// IPV4 Routing Forward Table Action Table COLLISION Table 
	// 	0x1D80 - 0x1EFF
	// 	Size = 6 * 64 = 384 dwords
	//---------------------------------------------
	#define __IPV4_LAN_COLLISION_ROUT_FWDA_TABLE_BASE	0x1D80
	#define __IPV4_LAN_COLLISION_ROUT_FWDA_TABLE_SIZE	384


#endif

	//---------------------------------------------
	// IPV4 Routing Forward Table Compare Table HASH Table -WAN
	// 	0x2140 - 0x273F
	// 	Size = 3 * 512 = 1536 dwords
	//---------------------------------------------
	#define __IPV4_WAN_HASH_ROUT_FWDC_TABLE_BASE	0x2140
	#define __IPV4_WAN_HASH_ROUT_FWDC_TABLE_BASE_HW	0x0140

	#define __IPV4_WAN_HASH_ROUT_FWDC_TABLE_SIZE	1536
	#define __IPV4_WAN_HASH_ROUT_FWDC_TABLE_SIZE_ipv6_en	768
	
	//---------------------------------------------
	// IPV4 Routing Forward Table Action Table HASH Table -LAN
	// 	0x2800 - 0x2DFF
	// 	Size = 3 * 512 = 1536 dwords
	//---------------------------------------------
	#define __IPV4_LAN_HASH_ROUT_FWDC_TABLE_BASE	0x2800
	#define __IPV4_LAN_HASH_ROUT_FWDC_TABLE_BASE_HW	0x0800
	#define __IPV4_LAN_HASH_ROUT_FWDC_TABLE_SIZE	1536
	#define __IPV4_LAN_HASH_ROUT_FWDC_TABLE_SIZE_ipv6_en	768
	//---------------------------------------------

	// IPV4 Routing Forward Table Compare Table COLLISION Table WAN 
	// 	0x2E00 - 0x2EBF
	// 	Size = 3 * 64 = 192 dwords
	//---------------------------------------------
	#define __IPV4_WAN_COLLISION_ROUT_FWDC_TABLE_BASE		0x2E00
	#define __IPV4_WAN_COLLISION_ROUT_FWDC_TABLE_BASE_HW	0x0E00

	#define __IPV4_WAN_COLLISION_ROUT_FWDC_TABLE_SIZE	192


	// IPV4 Routing Forward Table Compare Table COLLISION Table LAN 
	// 	0x2740 - 0x27FF
	// 	Size = 3 * 64 = 192 dwords
	//---------------------------------------------
	#define __IPV4_LAN_COLLISION_ROUT_FWDC_TABLE_BASE	0x2740
	#define __IPV4_LAN_COLLISION_ROUT_FWDC_TABLE_BASE_HW 0x740
	#define __IPV4_LAN_COLLISION_ROUT_FWDC_TABLE_SIZE	192

    #define __xGET_lan_coll_cmp_tbl_hw_base(__r_base, __r_ipv6_en)      \
        xLDI(__r_base, __IPV4_LAN_COLLISION_ROUT_FWDC_TABLE_BASE_HW)        
	//---------------------------------------------
	// Routing Multicast COMPARE Table 
	//	0x2EC0 - 0x2EFF
	// 	Size = 1 * 64= 64 dwords
	//---------------------------------------------
	#define __IPV4_ROUT_MULTICAST_FWDC_TABLE_BASE		0x2EC0
	#define __IPV4_ROUT_MULTICAST_FWDC_TABLE_BASE_HW	0x0EC0
	#define __IPV4_ROUT_MULTICAST_FWDC_TABLE_SIZE		64
	//---------------------------------------------
	// Routing Multicast ACTION Table 
	//	0x31E0 - 0x321F
	// 	Size = 2 * 32= 64 dwords
	//---------------------------------------------
	#define __IPV4_ROUT_MULTICAST_FWDA_TABLE_BASE		0x31E0
	#define __IPV4_ROUT_MULTICAST_FWDA_TABLE_SIZE		64
	
    //---------------------------------------------
	// Routing Multicast MIB
	//	0x3220 - 0x323F
	// 	Size = 1 * 32= 32 dwords
	//---------------------------------------------
	#define __IPV4_ROUT_MULTICAST_MIB_BASE		0x3220
	#define __IPV4_ROUT_MULTICAST_MIB_SIZE		32
	
	//---------------------------------------------
	// Routing Multicast RTP MIB
	//	0x3240 - 0x325F
	// 	Size = 1 * 32= 32 dwords
	//---------------------------------------------
	#define __IPV4_ROUT_MULTICAST_RTP_MIB_BASE		0x3240
	#define __IPV4_ROUT_MULTICAST_RTP_MIB_SIZE	    32

	// IPv6 Routing Conversion Table Part 1
    // 	0x2440 - 0x263F
	// 	Size = 4 * 128 = 512 dwords
	//---------------------------------------------
	#define __IPV6_ROUT_CONVERT_TBL_1_BASE	        0x2440
	#define __IPV6_ROUT_CONVERT_TBL_1_BASE_HW       0x440
	#define __IPV6_ROUT_FWDA_TABLE_1_SIZE	        512

    #define xGET_ipv6_convert_tbl_1_hw_addr(__r_addr)   \
        xLDI(__r_addr, __IPV6_ROUT_CONVERT_TBL_1_BASE_HW)
        
	// IPv6 Routing Conversion Table Part 2
    // 	0X2B00 - 0x2CFF
	// 	Size = 4 * 128 = 512 dwords
	//---------------------------------------------
	#define __IPV6_ROUT_CONVERT_TBL_2_BASE	    0x2B00
	#define __IPV6_ROUT_CONVERT_TBL_2_BASE_HW   0xB00
	#define __IPV6_ROUT_FWDA_TABLE_2_SIZE	    512

    #define xGET_ipv6_convert_tbl_2_hw_addr(__r_addr)   \
        xLDI(__r_addr, __IPV6_ROUT_CONVERT_TBL_2_BASE_HW)

	//---------------------------------------------
	// Classification compare table 
	// 	0x2040 - 0x20BF
	// 	Size = 4 * 32 = 128 dwords
	//---------------------------------------------
	#define __CLASSIFICATION_COMPARE_TABLE_BASE	0x2040
	#define __CLASSIFICATION_COMPARE_TABLE_SIZE	128
	//---------------------------------------------
	// Classification MASK table 
	// 	0x20C0 - 0x213F
	// 	Size = 4 * 32 = 128 dwords
	//---------------------------------------------
	#define __CLASSIFICATION_MASK_TABLE_BASE	0x20C0
	#define __CLASSIFICATION_MASK_TABLE_SIZE	128

    //D5_MF_SLL_CMD1 = 0x002200C0   mtype = 0, esize = 4, ksize = 4, embase = 20C0
    //D5_MF_SLL_CMD0 = 0x00200040   num = 0x20, eybase = 2040
    
    #define MF_SLL_CMD1_HIGH16       0x0022
    #define MF_SLL_CMD1_LOW16        0x00C0 
    
    // eybase = , cmd = 1
    #define MF_SLL_CMD0_HIGH16       0x0200
    #define MF_SLL_CMD0_LOW16        0x0040  

	
    //=============================================
    // General Context  (0x3380-0x33FF) FOR D5
    //=============================================


    // CONSTANTS
    #define BITS_OF_BUCK_DEPTH      4
	#define CONST_HASH_BUCKET_SIZE				16
	#define CONST_HASH_BUCKET_NO				8

	#define CONST_IPV6_CNV_TBL_SIZE			128
	
	//============================================================
    // US_FPQ_SWAP_CFG_CTXT  (0x37D0-0x37D7) FOR AR10_D5
    //============================================================
    #define __US_FPQ_SWAP_CFG_CTXT    0x37D0
    
    //---------------------------------------------
    // Central DMA RX CH3 descriptor list base addr
	//	0x37E0 - 0x381F
	//	size = 2 * 32 = 64 dwords
	//---------------------------------------------
	#define __DMA_RX_CH3_DES_BASE				0x37E0
	#define __DMA_RX_CH3_DES_SIZE				64
	#define __DMA_RX_CH3_DES_NUM				32
	
	//---------------------------------------------
    // VRX218 SYNC descriptor list base addr
	//  0x3820 - 0x385F
	//	size = 2 * 32 = 64 dwords
	//---------------------------------------------
	#define __VRX218_SYN_DESC_BASE				0x3820
	#define __VRX218_SYN_DESC_SIZE				64
	#define __VRX218_SYN_DESC_NUM				32

#if (defined(PROCESSOR_AR10)|| defined(PROCESSOR_GRX390))
    //=====================================================
    // Dplus debug information(0x2F48-0x2F88) FOR AR10_D5
    //=====================================================
    //org_ctrl_dw_1st_page, page_id,     flag_header_dw0,     flag_header_dw1
    //new_ctrl_dw_1st_page, page_number, 1st_page_empty_flag, new_ctrl_dw_last_page
  
    #define __DPLUS_DBG_BASE              0x2F48
    #define __DPLUS_DBG_SIZE              64

    #define __DPLUS_DBG_PTR               0x2F88
    
    //Add __DPLUS_DBG_CFG for optimization, save debug information only when enabled (1)
    #define __DPLUS_DBG_CFG               0x2F89

#endif

	#if (defined(PROCESSOR_GRX390))
	
		#define	__VRX218_SYNC_DES_LIST_BASE		0x3820	/*0x3820-0x385F	32	x	2	=	64*/
		#define	__VRX218_SYNC_DES_LIST_SIZE		64
		#define	__VRX218_SYNC_DES_LIST_NUM		32
		#define	__VRX218_SYNC_DES_LIST_GUARD	31
		
		#define	__STD_DES_CFG					0x20A6
		
		#define	__SOC_ACA_CFG_CTXT				0x2030	/*0x2030-0x203F		16	x	1	=	16*/
		
		#define	__SOC_TX_IN_DESQ_CFG_CTXT		0x37D8	/*0x37D8-0x37DF		8	x	1	=	8*/
		#define	__SOC_RX_IN_DESQ_CFG_CTXT		0x3A60	/*0x3A60-0x3A67		8	x	1	=	8*/
	
		//#define	__SOC_TX_IN_DES_LIST_BASE		0x2640	/*0x2640-0x26BF	64	x	2	=	128*/
		#define	__SOC_TX_IN_DES_LIST_BASE		__ETH1_TX_DES_ADDR
		#define	__SOC_TX_IN_DES_LIST_SIZE		64
		#define	__SOC_TX_IN_DES_LIST_NUM		32
		#define	__SOC_TX_IN_DES_LIST_NUM_MASK	0x1F
		#define	__SOC_TX_IN_DES_LIST_GUARD		31
		
		#define	__SOC_TX_OUT_DES_LIST_BASE		0x26C0	/*0x26C0-0x273F	64	x	2	=	128*/
		#define	__SOC_TX_OUT_DES_LIST_SIZE		128
		#define	__SOC_TX_OUT_DES_LIST_NUM		64
		#define	__SOC_TX_OUT_DES_LIST_GUARD		63
		
		#define	__SOC_RX_IN_DES_LIST_BASE		0x5600	/*0x5600-0x57FD		255 x 2=	510*/
		#define	__SOC_RX_IN_DES_LIST_SIZE		510
		#define	__SOC_RX_IN_DES_LIST_NUM		255
		#define	__SOC_RX_IN_DES_LIST_NUM_MASK	0xFF
		#define	__SOC_RX_IN_DES_LIST_GUARD		254
		
		#define	__SOC_RX_OUT_DES_LIST_BASE		0x57FE	/*0x57FE-0x59FB		255 x 2=	510*/
		#define	__SOC_RX_OUT_DES_LIST_SIZE		510
		#define	__SOC_RX_OUT_DES_LIST_NUM		255
		#define	__SOC_RX_OUT_DES_LIST_GUARD		254
		
		#define	__TOTAL_SOC_ACA_CNT_BASE		0x3BF8	/*0x3BF8-0x3BFB	4 x 1 = 4*/
		
		#define	__TOTAL_DEV_ACA_CNT_LE_BASE		0x20B0	/*0x20B0-0x20B3	4 x 1 = 4*/
		#define	__TOTAL_DEV_ACA_CNT_BE_BASE		0x20B4	/*0x20B4-0x20B7	4 x 1 = 4*/
		
		#define	__TOTAL_DEV_ACA_CNT_BASE		__TOTAL_DEV_ACA_CNT_BE_BASE
		
		#define	__MAX_TX_IN_HD_DES_NUM			32
		
		#define	__MAX_RX_IN_HD_DES_NUM			32

		#define	__IS_VRX518						0x3439

		#define	__DSL_CPU_DES_LIST_BASE			0x2FA0	/*0x2FA0-0x2FDF	32	x	2	=	64*/
		#define	__DSL_CPU_DES_LIST_SIZE			64
		#define	__DSL_CPU_DES_LIST_NUM			32
		#define	__DSL_CPU_DES_LIST_GUARD		31
		
		#define __EMA_ID7_ACA_CNT				0x2F8A
		#define __EMA_ID7_ISR_CNT				0x2F8B
		
		#define __EMA_ID6_ACA_CNT				0x2F8C
		
		#define __EMA_TX_IN_ISSUE_CNT			0x2FE0
		#define __EMA_TX_OUT_ISSUE_CNT			0x2FE1
		#define __EMA_RX_IN_ISSUE_CNT			0x2FE2
		#define __EMA_RX_OUT_ISSUE_CNT			0x2FE3
		
		#define __EMA_TX_IN_DONE_CNT			0x2FE4
		#define __EMA_TX_OUT_DONE_CNT			0x2FE5
		#define __EMA_RX_IN_DONE_CNT			0x2FE6
		#define __EMA_RX_OUT_DONE_CNT			0x2FE7
		
		#define __TX_IN_TIMEOUT_CNT				0x2FE8
		#define __TX_OUT_TIMEOUT_CNT			0x2FE9
		#define __RX_IN_TIMEOUT_CNT				0x2FEA
		#define __RX_OUT_TIMEOUT_CNT			0x2FEB
		
		#define __SOC_MODE_SWITCH				0x2F14
		
		#define __TX_ACA_LOOP_CNT				0x2F15
		#define __TX_ACA_LOOP_CNT_CFG			0x2F16
		
		#define	__DSL_QOS_VALID					0x2F17
		
		// bit[0:3] qid for PVC0, bit[4:7] qid for PVC1,
		// bit[8:11]qid for PVC2, bit[12:15] qid for PVC3
		// bit[16:19] qid for PVC4, bit[20:23] qid for PVC5,
		// bit[24:27]qid for PVC6, bit[28:31] qid for PVC7
		#define	__PVC2QID_MAP0					0x2F18
		
		// bit[0:3] qid for PVC8, bit[4:7] qid for PVC9,
		// bit[8:11]qid for PVC10, bit[12:15] qid for PVC11
		// bit[16:19] qid for PVC12, bit[20:23] qid for PVC13,
		// bit[24:27]qid for PVC14, bit[28:31] qid for PVC15
		#define	__PVC2QID_MAP1					0x2F19
	
	#endif

#endif // __GUARDaddr_def_

