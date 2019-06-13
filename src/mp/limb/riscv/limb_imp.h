#ifndef __LIMB_IMP_H
#define __LIMB_IMP_H

#include "scarv/util.h"
#include "scarv/xdivinsa.h"

typedef uint32_t  limb_t;
typedef uint64_t dlimb_t;

//  r_1*2^w + r_0  = e+f
//#if defined(XDIVINSA)    

//#define LIMB_ADD0(r_1,r_0,e,f)     {                          \
  xadd1(r_1,r_0,e,f);                                        \
}

//#else
#define LIMB_ADD0(r_1,r_0,e,f)     {                          \
  dlimb_t __t  = ( dlimb_t )( e ) +                           \
                 ( dlimb_t )( f ) ;                           \
                                                              \
  r_0 =       ( limb_t )( __t >> 0                );          \
  r_1 = 0x1 & ( limb_t )( __t >> BITSOF( limb_t ) );          \
}
//#endif


//  r_1*2^w + r_0  = e+f+g
#define LIMB_ADD1(r_1,r_0,e,f,g)   {                          \
  dlimb_t __t  = ( dlimb_t )( e ) +                           \
                 ( dlimb_t )( f ) +                           \
                 ( dlimb_t )( g ) ;                           \
                                                              \
  r_0 =       ( limb_t )( __t >> 0                );          \
  r_1 = 0x1 & ( limb_t )( __t >> BITSOF( limb_t ) );          \
}
//  r_1*2^w + r_0  = e+f+g+h
#define LIMB_ADD2(r_1,r_0,e,f,g,h) {                          \
  dlimb_t __t  = ( dlimb_t )( e ) +                           \
                 ( dlimb_t )( f ) +                           \
                 ( dlimb_t )( g ) +                           \
                 ( dlimb_t )( h ) ;                           \
                                                              \
  r_0 =       ( limb_t )( __t >> 0                );          \
  r_1 =       ( limb_t )( __t >> BITSOF( limb_t ) );          \
}
// -r_1*2^w + r_0  = e-f
#define LIMB_SUB0(r_1,r_0,e,f)     {                          \
  dlimb_t __t  = ( dlimb_t )( e ) -                           \
                 ( dlimb_t )( f ) ;                           \
                                                              \
  r_0 =       ( limb_t )( __t >> 0                );          \
  r_1 = 0x1 & ( limb_t )( __t >> BITSOF( limb_t ) );          \
}
// -r_1*2^w + r_0  = e-f-g
#define LIMB_SUB1(r_1,r_0,e,f,g)   {                          \
  dlimb_t __t  = ( dlimb_t )( e ) -                           \
                 ( dlimb_t )( f ) -                           \
                 ( dlimb_t )( g ) ;                           \
                                                              \
  r_0 =       ( limb_t )( __t >> 0                );          \
  r_1 = 0x1 & ( limb_t )( __t >> BITSOF( limb_t ) );          \
}
// -r_1*2^w + r_0  = e-f-g-h
#define LIMB_SUB2(r_1,r_0,e,f,g,h) {                          \
  dlimb_t __t  = ( dlimb_t )( e ) -                           \
                 ( dlimb_t )( f ) -                           \
                 ( dlimb_t )( h ) -                           \
                 ( dlimb_t )( g ) ;                           \
                                                              \
  r_0 =       ( limb_t )( __t >> 0                );          \
  r_1 = 0x1 & ( limb_t )( __t >> BITSOF( limb_t ) );          \
}
//  r_1*2^w + r_0 += e
#define LIMB_ACC1(r_1,r_0,e)       {                          \
  dlimb_t __t  = ( ( dlimb_t )( r_0 ) << 0                ) | \
                 ( ( dlimb_t )( r_1 ) << BITSOF( limb_t ) ) ; \
                                                              \
          __t += ( dlimb_t )( e );                            \
                                                              \
  r_0 =       ( limb_t )( __t >> 0                );          \
  r_1 =       ( limb_t )( __t >> BITSOF( limb_t ) );          \
}
//  r_1*2^w + r_0 += e+f
#define LIMB_ACC2(r_1,r_0,e,f)     {                          \
  dlimb_t __t  = ( ( dlimb_t )( r_0 ) << 0                ) | \
                 ( ( dlimb_t )( r_1 ) << BITSOF( limb_t ) ) ; \
                                                              \
          __t += ( dlimb_t )( e ) +                           \
                 ( dlimb_t )( f ) ;                           \
                                                              \
  r_0 =       ( limb_t )( __t >> 0                );          \
  r_1 =       ( limb_t )( __t >> BITSOF( limb_t ) );          \
}
//  r_1*2^w + r_0  = e*f
#define LIMB_MUL0(r_1,r_0,e,f)   {                            \
  dlimb_t __t  = ( dlimb_t )( e ) *                           \
                 ( dlimb_t )( f ) ;                           \
                                                              \
  r_0 =       ( limb_t )( __t >> 0                );          \
  r_1 =       ( limb_t )( __t >> BITSOF( limb_t ) );          \
}
//  r_1*2^w + r_0  = e*f+g
#define LIMB_MUL1(r_1,r_0,e,f,g)   {                          \
  dlimb_t __t  = ( dlimb_t )( e ) *                           \
                 ( dlimb_t )( f ) +                           \
                 ( dlimb_t )( g ) ;                           \
                                                              \
  r_0 =       ( limb_t )( __t >> 0                );          \
  r_1 =       ( limb_t )( __t >> BITSOF( limb_t ) );          \
}

//  r_1*2^w + r_0  = e*f+g+h
#if defined(XDIVINSA)   

//#define LIMB_MUL2(r_1,r_0,e,f,g,h) {                          \
  dlimb_t __t,__ta;                                           \
  xmul2(__t, e,f);                                            \
  xadd2(__ta,g,h);                                            \
  __t +=     __ta;                                            \
  r_0  =       ( limb_t )( __t >> 0                );         \
  r_1  =       ( limb_t )( __t >> BITSOF( limb_t ) );         \
}     
#define LIMB_MUL2(r_1,r_0,e,f,g,h) {                          \
  dlimb_t __t,__ta;                                           \
  xmul2(__t, e,f);                                            \
  __ta = ( dlimb_t )( g ) + ( dlimb_t )( h ) ;                \
  __t +=     __ta;                                            \
  r_0  =       ( limb_t )( __t >> 0                );         \
  r_1  =       ( limb_t )( __t >> BITSOF( limb_t ) );         \
} 
#else
#define LIMB_MUL2(r_1,r_0,e,f,g,h) {                          \
  dlimb_t __t  = ( dlimb_t )( e ) *                           \
                 ( dlimb_t )( f ) +                           \
                 ( dlimb_t )( g ) +                           \
                 ( dlimb_t )( h ) ;                           \
                                                              \
  r_0 =       ( limb_t )( __t >> 0                );          \
  r_1 =       ( limb_t )( __t >> BITSOF( limb_t ) );          \
}
#endif

#endif

