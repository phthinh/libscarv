
#include <stdio.h>
#include <stdint.h>

#include "test_util.h"
#include "scarv/sha2/sha2_512.h"

const uint32_t LEN = 64;

//! Print the state to stdout as a hex string.
void sha2_512_dump_state(uint8_t * state, uint32_t l) {
    uint8_t * p = (uint8_t*)state;

    for(int i = 0; i < l; i ++) {
        uint8_t c = p[i];
        printf("%02X", c);
    }
}

int main(int argc, char ** argv) {

    uint8_t data_in  [LEN];
    uint8_t data_out [LEN];

    for(int i =0; i < LEN; i++){
        data_in[i] = i;
    }

    printf("import hashlib\n");
    printf("import binascii\n");
    printf("import sys\n");

    for(int i = 0; i < 5; i ++) {

        printf("din  = binascii.a2b_hex('");
        sha2_512_dump_state(data_in,LEN);
        printf("')\n");

        uint32_t count_c = test_util_rdcycle();
        uint32_t count_i = test_util_rdinstret();

        sha2_512(data_out, 1, data_in, LEN);

        count_c = test_util_rdcycle()  - count_c;
        count_i = test_util_rdinstret()- count_i;

        printf("# cycles = %lu\n", count_c);
        printf("# instrs = %lu\n", count_i);
        printf("# cycles/byte = %d\n", count_c/(LEN*4));

        printf("dout = '");
        sha2_512_dump_state(data_out,LEN);
        printf("'\n");

        printf("golden = hashlib.sha512(din).hexdigest().upper()\n");
        printf("if (golden != dout):\n");
        printf("    sys.stdout.write('Input   : ')\n");
        printf("    print(binascii.b2a_hex(din)   )\n");
        printf("    sys.stdout.write('Expected: ')\n");
        printf("    print(golden)\n");
        printf("    sys.stdout.write('Got     : ')\n");
        printf("    print(dout)\n");
        printf("    sys.exit(1)\n\n");

        for(int i = 0; i < LEN; i ++) {
            data_in[i] = data_out[i];
        }

    }

    return 0;
}
