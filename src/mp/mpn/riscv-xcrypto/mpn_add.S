
.section .text
.global mpn_add
mpn_add:
    # a0 = limb_t * r
    # a1 = limb_t * x
    # a2 = int      l_x
    # a3 = limb_t * y
    # a4 = int      l_y

    mv   t1, a2
    bltu a2, a4, .l_y_min
    mv   t1, a4

    .l_y_min:                   // t1 = MIN(l_x, l_y)
        
       xc.gpr2xcr c1, zero

       li   t0, 0               // i = 0
       bgeu t0, t1, .mpn_add_done

    .loop_1:

       xc.ld.w c2, 0(a1)        // c0 = x[i]
       xc.ld.w c3, 0(a3)        // c1 = y[i]

       xc.madd.3 (c0,c1), c2,c3,c1 // (c1,c0) = c2+c3+(c1 & 0x1)

       xc.st.w c0, 0(a0)        // r[i] = c1 = lo(c2+c3)

       addi a0, a0, 4
       addi a1, a1, 4
       addi a3, a3, 4
       addi t0, t0, 1           // i++
       bltu t0, t1, .loop_1

    xc.gpr2xcr c3, zero

    bgeu t0, a2, .pre_loop_3        // if(i >= l_x) goto .loop_3
    .loop_2:

       xc.ld.w c2, 0(a1)        // c2 = x[i]

       xc.madd.3 (c0,c1), c2,c3,c1 // (c1,c0) = c2+c3+(c1 & 0x1)

       xc.st.w c0, 0(a0)        // r[i] = c1 = lo(c2+c3)

       addi a0, a0, 4
       addi a1, a1, 4
       addi t0, t0, 1
       bltu t0, a2, .loop_2
    
    .pre_loop_3:
        bgeu t0, a4, .mpn_add_done  // if(i >= l_y) goto mpn_add_done

    .loop_3:

       xc.ld.w c2, 0(a3)        // c2 = y[i]

       xc.madd.3 (c0,c1), c2,c3,c1 // (c1,c0) = c2+c3+(c1 & 0x1)

       xc.st.w c0, 0(a0)        // r[i] = c1

       addi a0, a0, 4
       addi a3, a3, 4
       addi t0, t0, 1
       bltu t0, a4, .loop_3

.mpn_add_done:
    xc.xcr2gpr  a0, c1          # Move a0 <= c1
    ret

