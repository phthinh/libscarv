
#include <stdio.h>
#include <stdint.h>

#include "test_util.h"
#include "scarv/keccak/KeccakP-1600-SnP.h"

//! Print the KeccakP1600 state to stdout as a hex string.
void keccakp1600_dump_state(uint64_t state[25]) {
    uint8_t * p = (uint8_t*)state;

    printf("0x");
    for(int i = 0; i < 200; i ++) {
        int k = 200-i;
        uint8_t c = p[i];
        printf("%.2X", c);
    }
}

/*!
@brief Check that the reference and dut state objects match for P1600
@returns Zero if both match, nonzero if they do not.
*/
int keccakp1600_check_states(
    uint64_t ref[25],   //!< The correct, reference state
    uint64_t dut[25]    //!< The design under test's state.
) {
    for(int i = 0; i < 25; i++ ) {
        if(ref[i] != dut[i]) {
            return 1;
        }
    }
    return 0;
}


//! Perform a motecarlo test stream of KeccakP1600.
void test_keccakp_1600(
    int n //!< The number of test iterations to perform
) {

    uint32_t nrounds        = maxNrRounds1600;
    uint64_t state_ref [25];
    uint64_t state_dut [25];

    for(int i = 0; i < 25; i ++) {
        state_ref[i] = 0;
        state_dut[i] = 0;
    }

    for(int i = 0; i < n; i ++) {

        printf("# ------ keccakp1600 %d/%d ------\n", i,n);
        printf("state_ref_pre  = "); keccakp1600_dump_state(state_ref);
        printf("\n");
        printf("state_dut_pre  = "); keccakp1600_dump_state(state_dut);
        printf("\n");

        uint32_t count_c = test_util_rdcycle();
        uint32_t count_i = test_util_rdinstret();

        for(uint32_t round = 0; round < nrounds; round++) {
            KeccakP1600RoundReference(state_ref, round);
        }

        count_c = test_util_rdcycle()  - count_c;
        count_i = test_util_rdinstret()- count_i;

        printf("# ref cycles = %d\n", count_c);
        printf("# ref instrs = %d\n", count_i);

        count_c = test_util_rdcycle();
        count_i = test_util_rdinstret();

        for(uint32_t round = 0; round < nrounds; round++) {
            KeccakP1600Round(state_dut, round);
        }

        count_c = test_util_rdcycle()  - count_c;
        count_i = test_util_rdinstret()- count_i;

        printf("# dut cycles = %d\n", count_c);
        printf("# dut instrs = %d\n", count_i);

        printf("state_ref_post = "); keccakp1600_dump_state(state_ref);
        printf("\n");
        printf("state_dut_post = "); keccakp1600_dump_state(state_dut);
        printf("\n");

        int fail = keccakp1600_check_states(state_ref, state_dut);
        if(fail) {
            printf("print(\"Keccak %d/%d Failed after %d rounds.\")\n",
                i,n,nrounds);
            printf("sys.exit(1)\n");
        } else {
            // Test passed
        }

    }

}

int main(int argc, char ** argv) {
    test_keccakp_1600(30);
}

