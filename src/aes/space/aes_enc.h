#ifndef __AES_ENC_H
#define __AES_ENC_H

#include "scarv/util.h"

#include "scarv/aes/aes_conf.h"
#include "scarv/aes/aes_rc.h"

#include "scarv/aes/aes_dec.h"
#include "scarv/aes/aes_enc_imp.h"

#if defined( CONF_AES_PRECOMP_SBOX )
extern uint8_t AES_ENC_SBOX[];
#else
#error "no implementation for !defined( CONF_AES_PRECOMP_SBOX )"
#endif

#if defined( CONF_AES_ROUND_SPLIT )

extern void aes_enc_rnd_init( uint8_t* s, uint8_t* rk );

#if defined( CONF_AES_ENC_ITER_EXTERN )
extern void aes_enc_rnd_iter( uint8_t* s, uint8_t* rk,  uint8_t* sbox,  uint8_t* mulx );
#else
extern void aes_enc_rnd_iter( uint8_t* s, uint8_t* rk );
#endif

#if defined( CONF_AES_ENC_FINI_EXTERN )
extern void aes_enc_rnd_fini( uint8_t* s, uint8_t* rk,  uint8_t* sbox);
#else
extern void aes_enc_rnd_fini( uint8_t* s, uint8_t* rk );
#endif

#endif

#if defined( CONF_AES_PRECOMP_RK )
extern void aes_enc_exp     ( uint8_t* r, const uint8_t*  k             );
#endif
extern void aes_enc_exp_step( uint8_t* r, const uint8_t* rk, uint8_t rc );

extern void aes_enc( uint8_t* r, uint8_t* m, uint8_t* k,  uint8_t* sbox,  uint8_t* mulx );

#endif
