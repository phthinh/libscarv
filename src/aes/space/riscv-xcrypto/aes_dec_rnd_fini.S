.include "aes_macro.S"

.section .text
.global aes_dec_rnd_fini
aes_dec_rnd_fini:
// a0 =  uint32_t * s 
// a1 =  uint32_t * k
// a2 =	uint8_t * sbox

#ifdef CONF_AES_ROUND_PACK
//load
AES_LDW_XC      c0,c1,c2,c3, a0
//sub
AES_DEC_SUB_XC  c0,c1,c2,c3, a2
//row
AES_DEC_ROW_XC  c0,c1,c2,c3
//key
AES_LDW_XC      c4,c5,c6,c7, a1
AES_KEY_XC      c0,c1,c2,c3, c4,c5,c6,c7	
//store
AES_STW_XC      c0,c1,c2,c3, a0

#else
// AES_ROUND_UNPACK using XCRYPTO AES instructions ================
//load 
AES_LDW_XC      c0,c1,c2,c3, a0
//sub// second row	
xc.aessub.dec c4, c2, c1
xc.aessub.dec c5, c3, c2
xc.aessub.dec c6, c0, c3
xc.aessub.dec c7, c1, c0
// third and fourth row
xc.ins c1, c4, 0, 16
xc.ins c2, c5, 0, 16
xc.ins c4, c6, 0, 16
xc.ins c5, c7, 0, 16
xc.ins c6, c1, 0, 16
xc.ins c7, c2, 0, 16
//key		
AES_LDW_XC      c0,c1,c2,c3, a1
AES_KEY_XC      c0,c1,c2,c3, c4,c5,c6,c7	
//store
AES_STW_XC      c0,c1,c2,c3, a0

#endif
ret
