#ifndef	__VRX518_A1PLUS_ADDR_DEF_INC
#define	__VRX518_A1PLUS_ADDR_DEF_INC

/*==========================================================================
	Defines for "PPE	DSL	Notifications" Module
	==========================================================================*/
#define	__DREG_BC0_LINK_STATUS							0x7DC0
#define	__DREG_BC1_LINK_STATUS							0x7DD0
#define	__DREG_MEI_STATE										0x7DC1
#define	__DREG_PDBRAM_S_44K_OWN							0x7DC2
#define	__DREG_SIGNATURE										0x7DC3
#define	__SFSM_PGCNT0												0x741C
#define	__SFSM_PGCNT1												0x741D

/*==========================================================================
	General Configuration:	 0x2000	-	0x202F
	Need	to be	refined	further
	==========================================================================*/
#define	__FW_VER_ID											0x2001
#define	__PP32_0_TIME										0x2002
#define	__PP32_1_TIME										0x2003

#define	__DSL_LINK_DOWN									0x2004

/* to support unified driver	for	ATM/PTM*/
#define	__TC_SWITCH_FLAG								0x2005
#define	__PREV_TC_SWITCH_FLAG						0x2006

/*Number of	times	DREG_PDBRAM_S_44K_OWN	changes	from S_44K_OWN_PPE to	S_44K_OWN_DSL*/
#define	__PDBRAM_OWN_CHG_CNT						0x34B7

#define	__CFG_WRX_HTUTS									0x2010
#define	__STD_DES_CFG										0x2011
#define	__CFG_STD_DATA_LEN							__STD_DES_CFG
#define	__QOS_CFG												0x2012
#define	__TX_QOS_CFG										__QOS_CFG
#define	__QOSQ_FLOW_CTRL_CFG						0x2013
#define	__CFG_TX_QOSQ_BANDWIDTH_CTRL		__QOSQ_FLOW_CTRL_CFG

#define	__PSAVE_CFG											0x2014

#define	__CFG_WRX_DMACH_ON							0x2015
#define	__CFG_WTX_DMACH_ON							0x2016
#define	__CFG_WRX_HUNT_BITTH						0x2017
#define	__CFG_WAN_WRDES_DELAY						0x2018

#define	__QOS_SHADOW_TTICK							0x201E
#define	__TX_QOS_CFG_SHADOW							__QOS_SHADOW_TTICK

#define	__PP32_0_TASK_CFG								0x2020
#define	__PP32_1_TASK_CFG								0x2021

#define	__PP32_0_MODULE_ACTIVITY				0x2022
#define	__PP32_1_MODULE_ACTIVITY				0x2023
#define	__VRX218_FLOW_CTRL_CFG					 0x2026	 /*	new	*/

/*=============================================================================
	Unified QoS Part
	=============================================================================*/
#define	__INQ_QOS_CFG_BASE							0x2508	/* 0x2508-0x2509	2		x	1	=	2				*/


/*#define	__US_FAST_PATH_DES_LIST_BASE		0x2580*/	/* 0x2580-0x25FF	64	x	2	=	128			*/

#define	__US_FAST_PATH_DES_LIST_BASE		0xA070	/* 0xA070-0xA0EF	64	x	2	=	128			*/
#define	__US_FAST_PATH_DES_LIST_SIZE		128
#define	__US_FAST_PATH_DES_LIST_NUM			64
#define	__US_FAST_PATH_DES_LIST_GUARD		63


#define	__US_CPU_PATH_DEST_LIST_BASE		0x3D00	/* 0x3D00-0x3D7F	64	x	2	=	128			*/
#define	__QOSQ_OVERFLOW_STATE_BMAP			0x250c	/* 0x250c-0x250c	1		x	1	=	1				*/

#define	__QOSQ_CFG_CTXT_BASE						0x2FE0	/* 0x2FE0-0x2FFF	16	x	2	=	32			*/
#define	__QOSQ_PSEUDO_DES_CFG_BASE			0x2E80	/* 0x2E80-0x2EFF	16	x	8	=	128			*/
/*#define	__US_QOSQ_DES_LIST_BASE					0x2800*/	/* 0x2800-0x2BFF	512	x	2	=	1024		*/


#define	__US_QOSQ_DES_LIST_BASE					0xA9F0			/* 0xA9F0-0xADEF	16 x 32	x	2	=	1024 (VRX318:	0x2800)		*/
#define	__US_QOSQ_DES_LIST_SIZE					256
#define	__US_QOSQ_DES_LIST_NUM_Q				2						/* Number	of QOSQ	-one for preemption, one for non-preemption	*/
#define	__US_QOSQ_DES_LIST_PERQ_NUM			64					/* Number	of descriptors per QOSQ	*/


#define	__QOSQ_PKT_CNT									0x2680	 /*	0x2680-0x268f	16	 x 1 = 1			 */

#define	__QOSQ_MIB_BASE									0x2030	/* 0x2030-0x20AF	16	x	8	=	128			*/
#define	__QOSQ_EVENT_MBOX_INT_CFG				0x3F10	/* 0x3F10-0x3F13	1		x	4	=	4				*/
#define	__SWAPQ_CFG_CTXT_BASE						0x2500	/* 0x2500-0x2501	1		*	2	=	2				*/
#define	__SWAPQ_DES_LIST_BASE						0x3F60	/* 0x3F60-0x3F9F	32	*	2	=	64			*/
#define	__DESQ_MBOX_INT_CFG							0x3F14	/* 0x3F14-0x3F1F	6		 x 2 = 12			*/

#define	__US_FP_INQ_DES_CFG_CTXT				0x20B0	/* 0x20B0-0x20B7	1	 x 8 = 8			*/
#define	__US_CPU_INQ_DES_CFG_CTXT				0x20B8	/* 0x20B8-0x20BF	1	 x 8 = 8			*/

/*=============================================================================
	Des Queues, CDMA	 copy	channel	mgm, des_sync	(SmartPhy	Part)
	=============================================================================*/
#define	__US_TC_LOCAL_Q_CFG_CTXT_BASE		0x2E00	/* 0x2E00-0x2E7F	16 x 8 = 128 */
/*#define	__US_TC_LOCAL_Q_DES_LIST_BASE		0x2360*/	/* 0x2360-0x238F	1	 x 48= 48	 */


#define	__US_TC_LOCAL_Q_DES_LIST_BASE				0xA000	/* 0xA000-0xA03F	2	x	16 x 2=	64	*/
#define	__US_TC_LOCAL_Q_DES_LIST_SIZE				64
#define	__US_TC_LOCAL_Q_DES_LIST_NUM_Q			16
#define	__US_TC_LOCAL_Q_DES_LIST_PERQ_NUM		2


#define	__DS_TC_AAL5_LOCAL_Q_CFG_CTXT		0x20E0	/* 0x20E0-0x20E7	1	 x 8 = 8	*/
#define	__DS_TC_OAM_LOCAL_Q_CFG_CTXT		0x20E8	/* 0x20E8-0x20EF	1	 x 8 = 8	*/

/*#define	__DS_TC_LOCAL_AAL5Q_DES_LIST_BASE		0x3F20*/	/* 0x3F20-0x3F5F	32	x	2	=	64	*/

/*cdma read*/
#define	__US_CDMA_COPY_CH_CFG						0x2340	/* 0x2350-0x2350	1	x	1	=	1		*/
#define	__US_CDMA_CHAN_NO				8
#define	__US_CDMA_READ_CH_CFG_CTXT			0x2798	/* 0x2798-0x279F	1	 x 8 = 8	 */
#define	__US_CDMA_EXT_SB_BASE						0xBA80	/* 0xBA80-0xBC7F	128x4=512*/

#define	__US_LOCAL_Q_SHARED_CDMA_BASE		0xB980
#define	__US_LOCAL_Q_SHARED_CDMA_NUM		128
#define	__US_QOS_Q_SHARED_CDMA_BASE			0xB880
#define	__US_QOS_Q_SHARED_CDMA_NUM			128


/*PDBRAM limitation, allocate	extra	SB for descriptors only, to	match	PTM	descriptor list*/
#define	__DS_TC_LOCAL_AAL5Q_DES_LIST_BASE		0xB000	/* 0xB000-0xB03F	30 x 2 = 60	(VRX318:0x3F20)	*/
#define	__DS_TC_LOCAL_AAL5Q_DES_LIST_SIZE		48
#define	__DS_TC_LOCAL_AAL5Q_DES_LIST_NUM		24


/*#define	__DS_TC_LOCAL_OAMQ_DES_LIST_BASE		0x24D0*/	/* 0x24D0-0x24EF	16	x	2	=	32	*/

#define	__DS_TC_LOCAL_OAMQ_DES_LIST_BASE	 0xB040	 /*	0xB040-0xB053	 10	x	2	=	20 (VRX318:0x24D0) */
#define	__DS_TC_LOCAL_OAMQ_DES_LIST_SIZE	 20
#define	__DS_TC_LOCAL_OAMQ_DES_LIST_NUM		 10

#define	__DS_PKT_DESQ_CFG_CTXT					0x20F0	/* 0x20F0-0x20F7	1	 x 8 = 8	 */

#define	__DS_PKT_DES_LIST_BASE					0xB100	/* 0xB100-0xB13F	32 x 2 = 64	(VRX318: 0x2600)*/
#define	__DS_PKT_DES_LIST_SIZE					64
#define	__DS_PKT_DES_LIST_NUM						32
#define	__DS_PKT_DES_LIST_GUARD					31

#define	__DS_OAM_DESQ_CFG_CTXT					0x20F8	/* 0x20F8-0x20FF	1	 x 8 = 8	 */
/*#define	__DS_OAM_DES_LIST_BASE					0x2640*/	/* 0x2640-0x267F	32 x 2 = 64*/

#define	__DS_OAM_DES_LIST_BASE					0xB060	/* 0xB060-0xB09F	32 x 2 = 64	(VRX318: 0x2640)*/
#define	__DS_OAM_DES_LIST_SIZE					64
#define	__DS_OAM_DES_LIST_NUM						32
#define	__DS_OAM_DES_LIST_GUARD					31

#define	__DES_SYNC_CFG_CTXT							0x2F00	/* 0x2F00-0x2FBF	6	 x 32= 192*/
#define	__CDMA_DES_SYNC_DEST_LIST_BASE	0x27A0	/* 0x27A0-0x27FF	6	 x 4 x 2 x 2 = 96	*/

/*----------------------------------------------------------
	Detailed	Memory Allocation
	----------------------------------------------------------*/

/***********************************************
	"Unified QoS"	Module Memory	Allocation - START
	***********************************************/

/*2	INQs;	CPU	Path & Fast	Path*/
#define	__INQ_QOS_CFG_BASE							0x2508
#define	__INQ_QOS_CFG_END								0x2509
#define	__INQ_QOS_CFG_SIZE							1

/*16 QoSQs*/
#define	__QOSQ_CFG_CTXT_BASE						0x2FE0
#define	__QOSQ_CFG_CTXT_END							0x2FFF
#define	__QOSQ_CFG_CTXT_SIZE						2

/*16 QoSQs*/
#define	__QOSQ_MIB_BASE									0x2030
#define	__QOSQ_MIB_END									0x20AF
#define	__QOSQ_MIB_SIZE									8


/*#define	__SWAPQ_CFG_CTXT_BASE						0x2500*/
#define	__SWAPQ_CFG_CTXT_DW1_ADDR				0x2501
#define	__SWAPQ_CFG_CTXT_END						0x2501
#define	__SWAPQ_CFG_CTXT_SIZE						2

/***********************************************
	"Unified QoS"	Module Memory	Allocation - END
	***********************************************/

#define	__DES_SYNC_CFG_CTXT_BASE				__DES_SYNC_CFG_CTXT
#define	__DES_SYNC_CFG_CTXT_BASE_END		0x2FBF

#define	__DES_READ_SYNC_CFG_CTXT_BASE	 __DES_SYNC_CFG_CTXT_BASE
#define	__DES_READ_SYNC_CFG_CTXT_END	 __DES_SYNC_CFG_CTXT_BASE_END

#define	__DES_WRITE_SYNC_CFG_CTXT_BASE	__DES_SYNC_CFG_CTXT_BASE
#define	__DES_WRITE_SYNC_CFG_CTXT_END		__DES_SYNC_CFG_CTXT_BASE_END

#define	__CDMA_READ_COPY_CH_CFG_BASE		__US_CDMA_COPY_CH_CFG
#define	__CDMA_READ_COPY_CH_CFG_END			0x2350
#define	__SIZE_OF_CDMA_COPY_CH_CFG		1

/*cdma write*/
#define	__DS_CDMA_COPY_CH_CFG						0x2350	/* 0x2350-0x2351	1	x	1	=	1		*/
#define	__REG_STACK_PI									0x2352	/* 0x2352-0x2352	2	x	1	=	2		*/

#define	__CDMA_READ_CH_CTXT				__US_CDMA_READ_CH_CFG_CTXT
#define	__CDMA_READ_CH_CTXT_END					0x27A0
#define	__SIZE_OF_CDMA_READ_CH_CTXT			8

#define	__DES_SIDEBAND_WR_PTR						0x2354	/*0x2354-0x2355	*/

#define	__DES_SIDEBAND_LIST_BASE		0x2800	/* 0x2800-0x283F	64 x 2 = 128 */
#define	__DES_SIDEBAND_LIST_SIZE				__DS_PKT_DES_LIST_NUM

/* SB	=	0x7000 */
#define	__WRITE_CH_DOORBELL_EXT_ADDR		0x1E700980
#define	__WRITE_CH_DOORBELL_EXT_ADDR_HI	0x1E70
#define	__WRITE_CH_DOORBELL_EXT_ADDR_LO	0x0980

/* SB	=	0x7001 */
#define	__READ_CH_DOORBELL_EXT_ADDR			0x1E709A0
#define	__READ_CH_DOORBELL_EXT_ADDR_HI	0x1E70
#define	__READ_CH_DOORBELL_EXT_ADDR_LO	0x09A0

#if	0
/*Prior	PPA2.16
	=============================================================================
	Extra DS	packet buffer	for	A1Plus to	avoid	DS packet	drop (due	to no	descriptors)
	total 13	packets
	packet	size = 400 DWs = 1600	bytes
=============================================================================*/
#define	__DS_SB_PKT_DATA_PTR_0	0x2100	/* 0x2100-0x228F,	size = 400DW */
#define	__DS_SB_PKT_DATA_PTR_1	0x2C00	/* 0x2C00-0x2D8F,	size = 400DW */
#define	__DS_SB_PKT_DATA_PTR_2	0x3000	/* 0x3000-0x318F,	size = 400DW */
#define	__DS_SB_PKT_DATA_PTR_3	0x3190	/* 0x3190-0x331F,	size = 400DW */
#define	__DS_SB_PKT_DATA_PTR_4	0x3D80	/* 0x3D80-0x3F0F,	size = 400DW */
#define	__DS_SB_PKT_DATA_PTR_5	0x44E0	/* 0x44E0-0x466F,	size = 400DW */
#define	__DS_SB_PKT_DATA_PTR_6	0x4670	/* 0x4670-0x47FF,	size = 400DW */
#define	__DS_SB_PKT_DATA_PTR_7	0x4800	/* 0x4800-0x498F,	size = 400DW */
#define	__DS_SB_PKT_DATA_PTR_8	0x4990	/* 0x4990-0x4B1F,	size = 400DW */
#define	__DS_SB_PKT_DATA_PTR_9	0x4D40	/* 0x4D40-0x4ECF,	size = 400DW */
#define	__DS_SB_PKT_DATA_PTR_10	0x5B00	/* 0x5B00-0x5C8F,	size = 400DW */
#define	__DS_SB_PKT_DATA_PTR_11	0x5C90	/* 0x5C90-0x5E1F,	size = 400DW */
#define	__DS_SB_PKT_DATA_PTR_12	0x5E20	/* 0x5E20-0x5FAF,	size = 400DW */

#else

/*PPA2.16	MTU
	=============================================================================
	 Extra DS	packet buffer	for	A1Plus to	avoid	DS packet	drop (due	to no	descriptors)
	 total 12	packets
	 packet	size = 408 DWs = 1632	bytes
	=============================================================================*/

#define	__DS_SB_PKT_DATA_PTR_0	0x2100	/* 0x2100-0x2297,	size = 408DW */
#define	__DS_SB_PKT_DATA_PTR_1	0x2C00	/* 0x2C00-0x2D97,	size = 408DW */
#define	__DS_SB_PKT_DATA_PTR_2	0x3000	/* 0x3000-0x3197,	size = 408DW */
#define	__DS_SB_PKT_DATA_PTR_3	0x3198	/* 0x3198-0x332F,	size = 408DW */
#define	__DS_SB_PKT_DATA_PTR_4	0x44E0	/* 0x44E0-0x4677,	size = 408DW */
#define	__DS_SB_PKT_DATA_PTR_5	0x4678	/* 0x4678-0x480F,	size = 408DW */
#define	__DS_SB_PKT_DATA_PTR_6	0x4810	/* 0x4810-0x49A7,	size = 408DW */
#define	__DS_SB_PKT_DATA_PTR_7	0x49A8	/* 0x49A8-0x4B3F,	size = 408DW */
#define	__DS_SB_PKT_DATA_PTR_8	0x4D40	/* 0x4D40-0x4ED7,	size = 408DW */
#define	__DS_SB_PKT_DATA_PTR_9	0x5B00	/* 0x5B00-0x5C97,	size = 408DW */
#define	__DS_SB_PKT_DATA_PTR_10	0x5C98	/* 0x5C98-0x5E2F,	size = 408DW */
#define	__DS_SB_PKT_DATA_PTR_11	0x5E30	/* 0x5E30-0x5EC7,	size = 408DW */

#endif

/*=============================================================================
	 DS	OAM	packet in	share	buffer for A1Plus
	 total	10 packets
	packet size	=	32 DWs = 128 bytes
	=============================================================================*/

#define	__DS_SB_OAM_DATA_PTR_0	0x3BC0	/* 0x3BC0-0x3BDF,	size = 32	DW */
#define	__DS_SB_OAM_DATA_PTR_1	0x3BE0	/* 0x3BE0-0x3BFF,	size = 32	DW */
#define	__DS_SB_OAM_DATA_PTR_2	0x3C00	/* 0x3C00-0x3C1F,	size = 32	DW */
#define	__DS_SB_OAM_DATA_PTR_3	0x3C20	/* 0x3C20-0x3C3F,	size = 32	DW */
#define	__DS_SB_OAM_DATA_PTR_4	0x3C40	/* 0x3C40-0x3C5F,	size = 32	DW */
#define	__DS_SB_OAM_DATA_PTR_5	0x3C60	/* 0x3C60-0x3C7F,	size = 32	DW */
#define	__DS_SB_OAM_DATA_PTR_6	0x3C80	/* 0x3C80-0x3C9F,	size = 32	DW */
#define	__DS_SB_OAM_DATA_PTR_7	0x3CA0	/* 0x3CA0-0x3CBF,	size = 32	DW */
#define	__DS_SB_OAM_DATA_PTR_8	0x3CC0	/* 0x3CC0-0x3CDF,	size = 32	DW */
#define	__DS_SB_OAM_DATA_PTR_9	0x3CE0	/* 0x3CE0-0x3CFF,	size = 32	DW */

#define	__SOC_FAMILY										0x2507

/*=============================================================================
	 A1+ part
	=============================================================================*/
/*~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
																										S_addr	E_addr	Size
		General	Context	1																5000		51FF		512

		DSL	WAN	MIB	Length															4EF0		4EFF		16
		DSL	WAN	RX VC	MIB	Length (A5 Only)							4F00		4F3F		64
		DSL	WAN	TX VC	MIB	Length (A5 Only)							4F40		4F7F		64
		HTU	table																				26A0		26FF		96
		WAN	RX Queue Configuration/Context Length				4C00		4D3F		320
		WAN	RX DMA Channel Configuration/Context Length	4F80		4FB7		56
		WAN	TX Queue/DMA Configuration/Context Length		3A00		3BAF		432
		WAN	TX Port	Configuration	Length								4FB8		4FB9		2

		SFSM 0 (pages) - Data														5200		557F		896
		SFSM 0 (pages) - Ctrl														5A80		5ABF		64
		FFSM 0 (pages) -	Data													4000		422F		560
		SFSM 1 (pages) - Data														5640		59BF		896
		SFSM 1 (pages) - Ctrl														5AC0		5AFF		64
		FFSM 1 (pages) -	Data													42A8		44D7		560
		EMA	Command	Buffer															5580		559F		32
		EMA	Data Buffer																	55A0		55DF		64

		WAN	RX Port	Context															55E0		55EF		16
		WAN	TX Port	Context															4FBA		4FBB		2
		WAN	TX&RX	Port Context EXT Length								55F0		55FF		16
		WAN	RX Descriptor	Prefetch Buffer								3900		39FF		256
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~*/

/*********************************************
	 detailed	allocation
	*********************************************/

		/*----------------------------------
			 WAN RX	Descriptor Prefetch	Buffer
			 0x5B00	-	0x5BFF
			 Size	=	16 * 16	=	256	dwords
			----------------------------------*/
/*		#define	__WRX_DES_PREFETCH_BUF									0x2600*/


		/*------------------------------------
			 WAN RX	ALL5 Channel Descriptor	List
			 0x5B00	-	0x5B3F
			 Size	=	32 * 2 = 64	dwords
			------------------------------------*/
/*		#define	__WRX_PKT_DES_BUF												0x2600*/

		/*------------------------------------
			 WAN RX	OAM	Channel	Descriptor List
			 0x5B40	-	0x5B7F
			 Size	=	32 * 2 = 64	dwords
			------------------------------------*/
/*		#define	__WRX_OAM_DES_BUF												0x2640*/

		/*---------------------------------------------
			 DSL WAN MIB (0x4EF0 - 0x4EFF)
			---------------------------------------------*/
		#define	__WRX_DROPHTU_CELL											0x4EF1
		#define	__WRX_DROPDES_PDU												0x4EF2
		#define	__WRX_CORRECT_PDU												0x4EF3
		#define	__WRX_ERR_PDU														0x4EF4
		#define	__WRX_DROPDES_CELL											0x4EF5
		#define	__WRX_CORRECT_CELL											0x4EF6
		#define	__WRX_ERR_CELL													0x4EF7
		#define	__WRX_TOTAL_BYTE												0x4EF8
		#define	__WTX_TOTAL_PDU													0x4EFA
		#define	__WTX_TOTAL_CELL												0x4EFB
		#define	__WTX_TOTAL_BYTE												0x4EFC

		/*--------------------------
			 DSL WAN RX	VC MIB
			 0x4F00	-	0x4F3F
			 Size	=	16 * 4 = 64	dwords
			--------------------------*/
		#define	__WRX_VC_MIB_BASE												0x4F00
		#define	__WRX_VC_IG_PKTS_OFF										0
		#define	__WRX_VC_IG_BYTES_OFF										1

		/*--------------------------
			 DSL WAN TX	VC MIB
			 0x4F40	-	0x4F7F
			 Size	=	16 * 4 = 64	dwords
			--------------------------*/
		#define	__WTX_VC_MIB_BASE												0x4F40
		#define	__WRX_VC_EG_PKTS_OFF										1
		#define	__WRX_VC_EG_BYTES_OFF										2

		/*----------------------------
			HTU Table (0x26A0 - 0x26FF)
			----------------------------*/
		#define	__HTU_ENTRY_TABLE												0x26A0
		#define	__HTU_MASK_TABLE												0x26C0
		#define	__HTU_RESULT_TABLE											0x26E0

		/*--------------------------------------
			WAN RX	Queue	(Configuration + Context)
			0x4C00	-	0x4D3F
			---------------------------------------*/
		#define	__WRX_QUEUE_CONFIG											0x4C00

		/*---------------------------------------------
			WAN RX	DMA	Channel	Configuration/Context
			0x4F80	-	0x4FB7
			pkt queue descriptor	rdptr, wrptr
			oam queue descriptor	rdptr, wrptr
			---------------------------------------------*/
		#define	__WRX_QUEUE_CHANNEL_CONTEXT							0x4F80

		/*---------------------------------------
			 WAN TX	Queue/DMA	Configuration/Context
			---------------------------------------*/
		#define	__WTX_QUEUE_CONFIG											0x3A00

		/*------------------------
			DSL WAN RX	Port Context
			 0x55E0	-	0x55EF
			------------------------*/
		#define	__WRXCTXT_TC_RdPtr0											0x55E0
		#define	__WRXCTXT_TC_RdPtr1											0x55E1
		#define	__WRXCTXT_L2_RdPtr0											0x55E2
		#define	__WRXCTXT_L2_RdPtr1											0x55E3
		#define	__WRXCTXT_L2Pages0											0x55E4
		#define	__WRXCTXT_L2Pages1											0x55E5
		#define	__WRXCTXT_MatchCells0										0x55E6
		#define	__WRXCTXT_MatchCells1										0x55E7
		#define	__WRXCTXT_NoMatchCells0									0x55E8
		#define	__WRXCTXT_NoMatchCells1									0x55E9
		#define	__WRXCTXT_PortState0										0x55EA
		#define	__WRXCTXT_PortState1										0x55EB
		#define	__WRXCTXT_Hunt_Cnt0											0x55EC
		#define	__WRXCTXT_Hunt_Cnt1											0x55ED

/***************************
	DSL	WAN	context	definition
	***************************/

		/*---------------------------------------
			WAN EMA	CMD	BUFFER	:	0x5580 - 0x559F
					 EMA	DATA BUFFER	:	0x55A0 - 0x55DF
			---------------------------------------*/
		#define	__EMA_CMD_BUF														0x5580
		#define	__EMA_DATA_BUF													0x55A0
		#define	__WAN_EMA_CMD_BUF												__EMA_CMD_BUF
		#define	__WAN_EMA_DATA_BUF											__EMA_DATA_BUF

		/*--------------------------------------
			WAN TX	Port Context (0x4FBA - 0x4FBB)
			--------------------------------------*/
		#define	__WTXCTXT_TC_WRPTR0											0x4FBA
		#define	__WTXCTXT_TC_WRPTR1											0x4FBB

		/*--------------------------------------------------
			WAN TX	Port Context (extension) (0x55F0 - 0x55F1)
			--------------------------------------------------*/
		#define	__WTXCTXT_WtxDBufStart0									0x55F0
		#define	__WTXCTXT_WtxDBufStart1									0x55F1

		/*--------------------------------------------------
			WAN RX	Port Context (extension) (0x55FC - 0x55FF)
			--------------------------------------------------*/
		#define	__WRXCTXT_WrxDBufStart0									0x55FC
		#define	__WRXCTXT_WrxDBufStart1									0x55FD
		#define	__WRXCTXT_WrxCBufStart0									0x55FE
		#define	__WRXCTXT_WrxCBufStart1									0x55FF

		/*--------------------------------------------
			WAN TX	Port Configuration (0x4FB8 - 0x4FB9)
			--------------------------------------------*/
		#define	__WTX_PORT_CONFIG0											0x4FB8
		#define	__WTX_PORT_CONFIG1											0x4FB9

		/*=============================================
			General Context (0x5000 - 0x51FF)
			0x5000	-	0x50FF used	in addr_def_vr9.inc
			=============================================*/

		/*Verify
			----------------------------------------------------
			WAN TX	ETH	HEADER PREFETCH	BUFFER (0x5100 - 0x513F)
			----------------------------------------------------*/
		#define	__WTX_ETH_HEADER_BUF_BASE								0x5100

		/*---------------------------------------------
			WAN - ATM General Context (0x5140 - 0x517F)
			---------------------------------------------*/
		#define	__FWGEN_BITS_WORD0											0x5140
		#define	__FWGEN_WRX_WREMA_PEND_DID							0x5141
		#define	__FWGEN_WTX_WRDES_PEND_DID							0x5142
		#define	__FWGEN_WRX_WRDES_PEND_DID							0x5143
		#define	__FWGEN_WTX_WRDES_FINAL_PEND_DID				0x5144
		#define	__FWGEN_WRX_WRDES_FINAL_PEND_DID				0x5145
		#define	__FWGEN_WTX_RDDATA_PEND_QID							0x5146
		#define	__FWGEN_WTX_CELLBUF_EMPTY_STATUS				0x5147
		#define	__FWGEN_WTX_DMACH_NONEMPTY_STATUS				0x5148
		#define	__FWGEN_WRX_DMACH_NONEMPTY_STATUS				0x5149
		#define	__FWGEN_WRX_DMACH_VLD_STATUS						0x514A
		#define	__FWGEN_WRX_VEN													0x514B
		#define	__FWGEN_WRX_DES_PREFETCH_DID						0x514C
		#define	__FWGEN_WRX_DID													0x514D
		#define	__FWGEN_EMA_CMD0												0x514E
		#define	__FWGEN_EMA_CMD1												0x514F
		#define	__FWGEN_WRX_CELL_TYPE										0x5150
		#define	__FWGEN_WRX_CELLID											0x5151
		#define	__FWGEN_WRX_DESBUF_NONFULL_STATUS				0x5152
		#define	__FWGEN_WTX_DES_PREFETCH_QID						0x5153
		#define	__FWGEN_WTX_DES_PREFETCH_DID						0x5154
		#define	__FWGEN_WTX_CURRDES_VLD_STATUS					0x5155
		#define	__FWGEN_WTX_DESBUF_NONFULL_STATUS				0x5156
		#define	__FWGEN_VAR_DES0												0x5158
		#define	__FWGEN_VAR_DES1												0x5159
		#define	__FWGEN_WRX_CELL_HEADER									0x515A
		/*#define	__FWGEN_VAR_EMADATA_WRPTR								0x515B*/
		#define	__FWGEN_WRX_QID													0x515C
		#define	__FWGEN_VAR_DWNUM												0x515D
		#define	__FWGEN_VAR_CURR_LEN										0x515E
		#define	__FWGEN_VAR_TRAILER_LEN									0x515F
		#define	__FWGEN_VAR_TRAILER_UU									0x5160
		#define	__FWGEN_VAR_TRAILER_CPI									0x5161
		#define	__FWGEN_VAR_STW													0x5162
		#define	__FWGEN_WTX_QID													0x5163
		#define	__FWGEN_VAR_BMC_CMD0										0x5164
		#define	__FWGEN_VAR_DW_OFF											0x5165
		#define	__FWGEN_VAR_LAST_CELL										0x5166
		#define	__FWGEN_VAR_FILL_CELL										0x5167
		#define	__FWGEN_VAR_EXP_LEN											0x5168
		#define	__FWGEN_WTX_CELL_HEADER									0x5169
		#define	__FWGEN_VAR_BYTEOFF											0x516A
		#define	__FWGEN_WTX_DATA_PREFETCH_QID						0x516B
		#define	__FWGEN_WRX_PID													0x516C
		#define	__FWGEN_WTX_PID													0x516D
		#define	__FWGEN_CELLS_QUEUED_0									0x516E
		#define	__FWGEN_CELLS_QUEUED_1									0x516F
		#define	__FWGEN_SPACE_PENDING0									0x5170
		#define	__FWGEN_SPACE_PENDING1									0x5171
		#define	__FWGEN_VAR_BMC_CMD1										0x5172
		#define	__FWGEN_WRX_DESREQ_NONPEND_STATUS				0x5173
		#define	__FWGEN_WTX_DESREQ_NONPEND_STATUS				0x5174
		#define	__FWGEN_WTX_CELLREQ_NONPEND_STATUS			0x5175
		#define	__FWGEN_PREV_EMA_ISR										0x5176
		#define	__FWGEN_MBOX0_ISR												0x5177
		#define	__FWGEN_WTX_1ST_CELL_READ_FLAG0					0x5178
		#define	__FWGEN_WTX_1ST_CELL_READ_FLAG1					0x5179

		/*upstream	local	queue	nonempty flag
			bit0	to bit15 correspond	to q0	to q15
			if	a	bit	is set,	the	corresponding	queue	is nonempty*/
		#define	__US_TC_LOCAL_Q_FULL_FLAG								0x517A

		#ifdef VR9_FIRMWARE_DESCRAMBER
				#define	_FW_DESCRAMBER_POLY_H								0x517E
				#define	_FW_DESCRAMBER_POLY_L								0x517F
		#endif

		/*=============================================
			EMA Context	(0x518E-0x518F)
			=============================================*/
		#define	__EMA_CONTEXT_CMD_WRPTR									0x518E
		#define	__EMA_CONTEXT_DATA_WRPTR								0x518F
		#define	__WAN_EMA_CONTEXT_CMD_WRPTR							__EMA_CONTEXT_CMD_WRPTR
		#define	__WAN_EMA_CONTEXT_DATA_WRPTR						__EMA_CONTEXT_DATA_WRPTR

		/*-----------------------------------------------------
			WAN RX	Decap	buffer (0x5190 - 0x51AF)	//temp address
			-----------------------------------------------------*/
		#define	__WRX_DECAP_BUF_BASE										0x5190
		#define	__WRX_DECAP_BUF_BASE_HW									0x3190

		/*0x51B0 - 0x51BF*/
		#define	__FWGEN_WTX_QSB_VC_CONTEXT_BASE					0x51B0

		/*--------------------------------------
			WRX General Context (0x51C0 - 0x51C8)
			--------------------------------------*/
		#define	__FWGEN_WRX_2684_ORIGINAL_FLAG					0x51C0
		#define	__FWGEN_WRX_2684_CELL_ALIGN_OFF					0x51C1
		#define	__FWGEN_WRX_2684_MPOA_TYPE							0x51C2
		#define	__FWGEN_WRX_AAL5_CELL1_ROUNDDOWN_DWNUM	0x51C3
		#define	__FWGEN_WRX_DES_BYTES										0x51C4
		#define	__FWGEN_WRX_FIRST_CELL									0x51C5
		#define	__FWGEN_WRX_PKT_LEN_WO_FCS							0x51C6
		#define	__FWGEN_WRX_ETH_TYPE										0x51C7
		#define	__FWGEN_WRX_MAC_BYTE										0x51C8

		/*--------------------------------------
			WTX General Context (0x51C9 - 0x51DF)
			--------------------------------------*/
		#define	__FWGEN_WTX_ETH_IS_VLAN									0x51C9
		#define	__FWGEN_WTX_MPOA_PT											0x51CA
		#define	__FWGEN_WTX_ENCAP_PARSE_DROP						0x51CB

		#define	__FWGEN_WTX_2684_RM_LEN									0x51CC
		#define	__FWGEN_WTX_2684_INSERT_LEN							0x51CD
		#define	__FWGEN_WTX_RDWNUM											0x51CE
		#define	__FWGEN_WTX_SWOFF												0x51CF

		#define	__FWGEN_WTX_CELL1_BYTEOFF								0x51D0
		#define	__FWGEN_WTX_ETH_IS_IPV4									0x51D1
		#define	__FWGEN_WTX_ETH_IPOFF										0x51D2

		#define	__FWGEN_WTX_QPKT_LEVEL_CONTROL					0x51D3

		#define	__FWGEN_WTX_ETH_HD_DONE									0x51D4

/*---------------------------------------------------
	Task	pending	flag for power save	in A1plus
	---------------------------------------------------*/
#define	__TASK_PENDING_FLAG_VRX318_PPA						0x51E0
#define	__TASK_PENDING_FLAG											 __TASK_PENDING_FLAG_VRX318_PPA

#define	__WAKEUP_MIB_VRX318												0x51E1

		#define	MPOA_TYPE_EOA1									0		/*without	FCS*/
		#define	MPOA_TYPE_EOA2									1		/*with FCS*/
		#define	MPOA_TYPE_PPPOA_IPV4						2
		#define	MPOA_TYPE_IPOA_IPV4							3
		#define	MPOA_TYPE_PPPOA_IPV6						6
		#define	MPOA_TYPE_IPOA_IPV6							7
		#define	MPOA_TYPE_PPPOA_OTHER						10
		#define	MPOA_TYPE_IPOA_OTHER						11
		#define	BITS_OF_BUCK_DEPTH							4
		#define	CONST_HASH_BUCKET_SIZE					16
		#define	CONST_HASH_BUCKET_NO						32

		#define	CONST_IPV6_CNV_TBL_SIZE					64

/*==============================================================================
	FROM	vr9	bonding
	--------------
	PDMA Registers
	--------------*/
#define	__DMAL_BAR0_FIFO_STATUS							0x7600
#define	__DMAL_BAR1_FIFO_STATUS							0x7601
#define	__PDMA_BAR0													0x7602
#define	__PDMA_BAR1													0x7603

#define	__BAR0_WINDOW_SB_ADDR								0x6000
#define	__BAR0_WINDOW_SB_ADDR_PLUS_1				0x6001
#define	__BAR1_WINDOW_SB_ADDR								0x6800
#define	__BAR1_WINDOW_SB_ADDR_PLUS_1				0x6801


/* hardware	registers */
#define	__SAR_PDMA_RX_FW_DATABUF_CFG				0x7F02
#define	__SAR_PDMA_TX_FW_DATABUF_CFG				0x7F03
#define	__PDMA_IER													0x7A0B


/*---------------------------------------------------
	ACA FW	Context
	2 * 8 = 16
	---------------------------------------------------*/
#define	__US_ACA_CFG_CTXT_BASE							 0x4BB0	/* 0x4BB0--0x4BB7	 1 x 8 = 8	 */
#define	__DS_ACA_CFG_CTXT_BASE							 0x4BB8	/* 0x4BB8--0x4BBF	 1 x 8 = 8	 */


/*----------------------------------------------------------
	ACA Shadow	Registers
	3 * 4 = 12
	*_STATUS	need to	be initialized to	nonzero	by PPE driver
	----------------------------------------------------------*/

#define	__ACA_SHADOW_REG_BASE								 0xADF0

#define	__TX_IN_ACA_ACCUM_COUNT							 0xADF0

#define	__TX_IN_ACA_ACCUM_STATUS						 0xADF1

#define	__TX_IN_QUEUE_PD_BASE_ADDR_OFFSET		 0xADF2

#define	__TX_OUT_ACA_ACCUM_COUNT						 0xADF3

#define	__TX_OUT_ACA_ACCUM_STATUS						 0xADF4

#define	__TX_OUT_QUEUE_PD_BASE_ADDR_OFFSET	 0xADF5

#define	__RX_IN_ACA_ACCUM_COUNT							 0xADF6

#define	__RX_IN_ACA_ACCUM_STATUS						 0xADF7	/*0x1E22AFDC for VRX318	*/

#define	__RX_IN_QUEUE_PD_BASE_ADDR_OFFSET		 0xADF8

#define	__RX_OUT_ACA_ACCUM_COUNT						 0xADF9

#define	__RX_OUT_ACA_ACCUM_STATUS						 0xADFA

#define	__RX_OUT_QUEUE_PD_BASE_ADDR_OFFSET	 0xADFB


#define	__QOSQ_NO_DROP										 0x4BFE

#define	__TOTAL_DS_ACA_DEQ_CNT								0x4BFF

#define	__TOTAL_RX_IN_ACA_ACCUM_CNT							0x347F


/*---------------------------------------------------------------
	Programmable	Address	Mapping	(To	be initialized by	PPE	driver)
	---------------------------------------------------------------*/
#define	__EP_ADDR_BAR										 0x2028


/*----------------------------------------------------------------
	ACA TX_IN PD	List
	----------------------------------------------------------------*/
#define	__ACA_TX_IN_PD_LIST_BASE				__US_FAST_PATH_DES_LIST_BASE
#define	__ACA_TX_IN_PD_LIST_SIZE				__US_FAST_PATH_DES_LIST_SIZE
#define	__ACA_TX_IN_PD_LIST_NUM					__US_FAST_PATH_DES_LIST_NUM

/*__ACA_TX_IN_PD_LIST_GUARD	<= __ACA_TX_IN_PD_LIST_NUM - 1*/
#define	__ACA_TX_IN_PD_LIST_GUARD				__US_FAST_PATH_DES_LIST_GUARD

/*----------------------------------------------------------------
	ACA TX_OUT	PD List
	----------------------------------------------------------------*/

#define	__ACA_TX_OUT_PD_LIST_BASE				 0xA960	/* 0xA960-0xA9DF	128	 */
#define	__ACA_TX_OUT_PD_LIST_SIZE				 128
#define	__ACA_TX_OUT_PD_LIST_NUM				 64

/*__ACA_TX_OUT_PD_LIST_GUARD <=	__ACA_TX_OUT_PD_LIST_NUM - 1*/
#define	__ACA_TX_OUT_PD_LIST_GUARD			 63


/*----------------------------------------------------------------
	ACA RX_IN PD	List
	----------------------------------------------------------------*/
#define	__ACA_RX_IN_PD_LIST_BASE				__DS_PKT_DES_LIST_BASE
#define	__ACA_RX_IN_PD_LIST_SIZE				__DS_PKT_DES_LIST_SIZE
#define	__ACA_RX_IN_PD_LIST_NUM					__DS_PKT_DES_LIST_NUM

/*__ACA_RX_IN_PD_LIST_GUARD	<= __ACA_RX_IN_PD_LIST_NUM - 1*/
#define	__ACA_RX_IN_PD_LIST_GUARD				__DS_PKT_DES_LIST_GUARD

/*----------------------------------------------------------------
	ACA RX_OUT	PD List
	----------------------------------------------------------------*/
#define	__ACA_RX_OUT_PD_LIST_BASE				 __DS_PKT_DES_LIST_BASE
#define	__ACA_RX_OUT_PD_LIST_SIZE				 __DS_PKT_DES_LIST_SIZE
#define	__ACA_RX_OUT_PD_LIST_NUM				 __DS_PKT_DES_LIST_NUM

/*__ACA_RX_OUT_PD_LIST_GUARD <=	__ACA_RX_OUT_PD_LIST_NUM - 1 */
#define	__ACA_RX_OUT_PD_LIST_GUARD			 __DS_PKT_DES_LIST_GUARD

/* DSL showtime/leave showtime interrupt from MIPS to PP32_2 
   (TC_RX core for PTM) and PP32_0 for ATM                  */
#define	__MBOX2_PPM_IER						__MBOX_IGU5_IER
#define	__MBOX2_PPM_ISR						__MBOX_IGU5_ISR
#define	__MBOX2_PPM_ISRS					__MBOX_IGU5_ISRS
#define	__MBOX2_PPM_ISRC					__MBOX_IGU5_ISRC

#define	BIT_MBOX2_PPM						BIT0
#define	__ISRS_SET_CNT_MBOX2_PPM			0x5FC8
#define	__ISR_CHECK_CNT_MBOX2_PPM			0x5FC9

#define	__INT_MBOX2_PPM_CNT					0x5FCA
#define	__INT_MBOX2_PPM_WAKEUP_CNT			0x5FCB

/* 0x2FC0--0x2FDF 1 x 32 = 32  */
#define	__INT_PP32_2_CNT					0x5FCC 


#define	__MODE_SW_CFG						__DREG_MEI_STATE
#define	__MODE_SW_INT						0x5FCD

/* 0x5FCE--0x5FCD 1 x 32 = 32 */
#define	__MODE_SW_CNT						0x5FCE

#define	__DS_ACA_DELAY						0x4BC1

#define	__DS_ACA_TIMEOUT_CNT				0x4BC2

#define	__PCIE_SWITCH_PRESENT				0x4BC3

#define	__TX_IN_OUT_TOTAL_CNT				0x4BC4

#define	__PD_SHADOW_PRESENT					0x4BC5

#define	__TX_OUT_SHADOW_PTR					0x4BC6

#define	__RX_OUT_SHADOW_PTR					0x4BC7

#endif
