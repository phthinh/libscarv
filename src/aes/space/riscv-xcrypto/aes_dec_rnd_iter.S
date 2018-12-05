
.section .text
.global aes_dec_rnd_iter
aes_dec_rnd_iter:
    # a0 =  uint32_t * s 
	# a1 =  uint32_t * k
	
#load 
	xc.ld.w c0,  0(a0)
	xc.ld.w c1,  4(a0)
	xc.ld.w c2,  8(a0)
	xc.ld.w c3, 12(a0)
	xc.ld.w c4,  0(a1)
	xc.ld.w c5,  4(a1)
	xc.ld.w c6,  8(a1)
	xc.ld.w c7, 12(a1)
#key
	xc.bop	c0, c0, c4, 0x6		#xor
	xc.bop	c1, c1, c5, 0x6		#xor
	xc.bop	c2, c2, c6, 0x6		#xor
	xc.bop	c3, c3, c7, 0x6		#xor

#mix
	xc.bop	c4, c4, c0, 0xA		#mov c4 <- c0
	xc.bop	c5, c5, c1, 0xA		#mov c5 <- c1
	xc.bop	c6, c6, c2, 0xA		#mov c6 <- c2
	xc.bop	c7, c7, c3, 0xA		#mov c7 <- c3

	xc.aesmix.dec c0, c0, c4
	xc.aesmix.dec c1, c1, c5
	xc.aesmix.dec c2, c2, c6
	xc.aesmix.dec c3, c3, c7

#sub; second row
	xc.aessub.dec c4, c0, c3
	xc.aessub.dec c5, c1, c0
	xc.aessub.dec c6, c2, c1
	xc.aessub.dec c7, c3, c2

# third and fourth row
	xc.ld.hiu c0, 0xFFFF
	xc.ld.liu c0, 0x0000
	
	xc.mix.l c1, c4, c0, 0
	xc.mix.l c2, c5, c0, 0

	xc.mix.l c4, c6, c0, 0
	xc.mix.l c5, c7, c0, 0
	xc.mix.l c6, c1, c0, 0
	xc.mix.l c7, c2, c0, 0

	xc.st.w c4, 0(a0)
	xc.st.w c5, 4(a0)
	xc.st.w c6, 8(a0)
	xc.st.w c7, 12(a0)

	ret