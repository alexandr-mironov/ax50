
#ifndef _LTQ_IPSEC_INS_H
#define _LTQ_IPSEC_INS_H

#ifdef CONFIG_LTQ_PPA_MPE_IP97
#include <linux/kernel.h>
/* These are some of the definitions that you will need */
/* Not defined here due to compile time redefinition issues */

/* ----- 
#define BIT_0   0x00000001U
#define BIT_1   0x00000002U
#define BIT_2   0x00000004U
#define BIT_3   0x00000008U
#define BIT_4   0x00000010U
#define BIT_5   0x00000020U
#define BIT_6   0x00000040U
#define BIT_7   0x00000080U
#define BIT_8   0x00000100U
#define BIT_9   0x00000200U
#define BIT_10  0x00000400U
#define BIT_11  0x00000800U
#define BIT_12  0x00001000U
#define BIT_13  0x00002000U
#define BIT_14  0x00004000U
#define BIT_15  0x00008000U
#define BIT_16  0x00010000U
#define BIT_17  0x00020000U
#define BIT_18  0x00040000U
#define BIT_19  0x00080000U
#define BIT_20  0x00100000U
#define BIT_21  0x00200000U
#define BIT_22  0x00400000U
#define BIT_23  0x00800000U
#define BIT_24  0x01000000U
#define BIT_25  0x02000000U
#define BIT_26  0x04000000U
#define BIT_27  0x08000000U
#define BIT_28  0x10000000U
#define BIT_29  0x20000000U
#define BIT_30  0x40000000U
#define BIT_31  0x80000000U
 ----- */

/* Flag bits for the IPsecFlags field. Combine any values using a
   bitwise or.
   Of SAB_IPSEC_ESP and SAB_AH, exactly one must be set.
   Of SAB_IPSEC_TUNNEL and SAB_IPSEC_TRANSPORT, exactly one must be set.
   Of SAB_IPSEC_IPV4 and SAB_IPSEC_IPV6, exactly one must be set.
*/


/* IPSEC mode */
#define LTQ_SAB_IPSEC_ESP             0x00000001U 
#define LTQ_SAB_IPSEC_AH              0x00000002U

/* Transport or Tunnel */
#define LTQ_SAB_IPSEC_TUNNEL          0x00000004U   
#define LTQ_SAB_IPSEC_TRANSPORT       0x00000008U

/* IP Type */
#define LTQ_SAB_IPSEC_IPV4            0x00000010U
#define LTQ_SAB_IPSEC_IPV6            0x00000020U

#define MAX_IV_LEN					  32
#define MAX_NONCE_LEN				  8

/* flags */
#define LTQ_STATIC_IV				  0x00000001  /* Tell API not to generate random IV, debug purpose only */

/* Direction */
enum
{
    LTQ_SAB_DIRECTION_OUTBOUND,
    LTQ_SAB_DIRECTION_INBOUND
};


/* Encryption Algo */
enum
{
    LTQ_SAB_CRYPTO_NULL,
    LTQ_SAB_CRYPTO_DES,
    LTQ_SAB_CRYPTO_3DES,
    LTQ_SAB_CRYPTO_AES,
    LTQ_SAB_CRYPTO_ARCFOUR
};

/* Encryption Mode used */
enum
{
    LTQ_SAB_CRYPTO_MODE_ECB,
    LTQ_SAB_CRYPTO_MODE_CBC,
    LTQ_SAB_CRYPTO_MODE_OFB,
    LTQ_SAB_CRYPTO_MODE_CFB,
    LTQ_SAB_CRYPTO_MODE_CFB1,
    LTQ_SAB_CRYPTO_MODE_CFB8,
    LTQ_SAB_CRYPTO_MODE_CTR,
    LTQ_SAB_CRYPTO_MODE_ICM,
    LTQ_SAB_CRYPTO_MODE_CCM,       // Only use with AES, set LTQ_SAB_AUTH_AES_CCM 
    LTQ_SAB_CRYPTO_MODE_GCM,       // Only use with AES, set LTQ_SAB_AUTH_AES_GCM 
    LTQ_SAB_CRYPTO_MODE_GMAC,      // Only use with AES, set LTQ_SAB_AUTH_AES_GMAC 
    LTQ_SAB_CRYPTO_MODE_STATELESS, // For ARC4 
    LTQ_SAB_CRYPTO_MODE_STATEFUL,  // For ARC4 
};


/* Auth Algo used */
enum
{
    LTQ_SAB_AUTH_NULL,
    LTQ_SAB_AUTH_HASH_MD5,
    LTQ_SAB_AUTH_HASH_SHA1,
    LTQ_SAB_AUTH_HASH_SHA2_224,
    LTQ_SAB_AUTH_HASH_SHA2_256,
    LTQ_SAB_AUTH_HASH_SHA2_384,
    LTQ_SAB_AUTH_HASH_SHA2_512,
    LTQ_SAB_AUTH_SSLMAC_MD5,
    LTQ_SAB_AUTH_SSLMAC_SHA1,
    LTQ_SAB_AUTH_HMAC_MD5,
    LTQ_SAB_AUTH_HMAC_SHA1,
    LTQ_SAB_AUTH_HMAC_SHA2_224,
    LTQ_SAB_AUTH_HMAC_SHA2_256,
    LTQ_SAB_AUTH_HMAC_SHA2_384,
    LTQ_SAB_AUTH_HMAC_SHA2_512,
    LTQ_SAB_AUTH_AES_XCBC_MAC, 	// Can also be used to implement AES-CMAC 
    LTQ_SAB_AUTH_AES_CCM,      	// Set matching crypto algorithm and mode 
    LTQ_SAB_AUTH_AES_GCM,       // Set matching crypto algorithm and mode 
    LTQ_SAB_AUTH_AES_GMAC,     	// Set matching crypto algorithm and mode 
};

typedef struct
{
    void * p;
} DMABuf_Handle_t;

/* Proposed structure definition that can be passed to EIP97 API.
 * Some of the EIP97 DDK APIs require bit conventions as defined above. 
 * Please follow them accordingly. 
 */

struct ltq_crypto_ipsec_params {
	int ipsec_mode;				/* AH/ESP */
	int ipsec_tunnel;			/* Tunnel or transport mode */
	int direction;				/* INBOUND or OUTBOUND */
	int ip_type;				/* IPv4 or IPv6*/
	unsigned int ring_no;		/* Ring number this SA is registered to */
	unsigned int data_len;		/* size of packet */
	unsigned int crypto_offs;	/* DWORD offset of buffer */
	unsigned int total_pad_offs;	/* IPSec packet padding length offset (for all outbound) */
	unsigned int hash_pad_offs;	/* AES-CCM MSG length offset value (depends on pkt alignment) */
	unsigned int msg_len_offs;	/* AES-CCM MSG length offset value */
	unsigned int pad_blksize;	/* Padding block size filled by eip97 */
	u32	flags;					/* optional flag for future use */
	u32	spi;					/* SPI number */
	
	u32 crypto_algo;			/* crypto algo used */
	u32 crypto_mode;			/* crypto mode used */
	u32	cryptosize;				/* size of encrypted data */
	u32 crypto_keysize;			/* key size used for crypto algo */
	u8 *crypto_key;				/* pointer to the crypto key buffer */
	
	u32 auth_algo;				/* auth algo used */
	u32	authsize;				/* expected size of authentication data */
	u32 auth_keysize;			/* key size used for auth algo */
	u8 *auth_key;				/* pointer to the auth key buffer */
	u8 opad[64];				/* opad buffer filled by eip97 api */
	u8 ipad[64];				/* ipad buffer filled by eip97 api */
	u8 authkey3[16];			/* Third auth key for XCBC algorithm */
	
	u8 nonce[MAX_NONCE_LEN];	/* nonce buffer */
	u8 IV[MAX_IV_LEN];			/* IV buffer */
	u8 ivsize;					/* Length of IV */
	u8 ICV_length;				/* Length of ICV */
	
	u32 *SA_buffer;				/* SA buffer updated by eip97 api */
	u32 *token_buffer;			/* token instruction word updated by eip97 api */
	u32 *context_data;			/* context data */
	unsigned int SAWords;		/* No of words in SA */
	
	u32 token_headerword;		/* token header instruction word updated by eip97 api */
	unsigned int tokenwords;	/* number of dwords for token buffer updated by eip97 api */

	/* Handles which have to be returned to the 
	 * DDK
	 */
	DMABuf_Handle_t SAHandle;
	DMABuf_Handle_t TokenHandle;
	DMABuf_Handle_t SrcHandle;
	DMABuf_Handle_t DstHandle;
};

struct ltq_ipsec_complete {
	int err;
	void *data;
	u32 ret_pkt_len;
	u8 nexthdr;
	int flag;
	void (*callback_fn)(struct ltq_ipsec_complete *complete);
	u32 *token_ptr;
};


/* API - dummy placer */
int ltq_ipsec_setkey(struct ltq_crypto_ipsec_params *ipsec_params); 
int ltq_get_ipsec_token(struct ltq_crypto_ipsec_params *ipsec_params); 
void ltq_destroy_ipsec_sa(struct ltq_crypto_ipsec_params *ipsec_params);
int ltq_ipsec_enc(u32 spi, u16 ip_prot, u8 *in, u8 *out, void (*callback)(struct ltq_ipsec_complete *done),
			unsigned int buflen, void *ip_data);
int ltq_ipsec_dec(u32 spi, u8 *in, u8 *out, void (*callback)(struct ltq_ipsec_complete *done),
            unsigned int buflen, void *ip_data);
int ltq_get_length_params(u32 spi, unsigned int *ivsize, unsigned int *ICV_length,
			unsigned int *blksize);
struct ltq_crypto_ipsec_params *ltq_ipsec_get_params(u32); 
#endif /* CONFIG_LTQ_PPA_MPE_IP97 */ 
#endif /* _LTQ_IPSEC_INS_H */
