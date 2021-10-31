#include "part2.h"


bool simple_DES_menu() {
    uint16_t msg;
    uint16_t key;

    puts("(Give values in hex, e.g., : a9f1)");
    fputs("Enter the message: ", stdout);
    cin >> hex >> msg;

    fputs("Enter the key: ", stdout);
    cin >> hex >> key;

    printf("DES(0x%04x, 0x%04x) == 0x%04x\n", msg, key, simpleDES(msg, key, 16));

    return true;
}


bool full_DES_menu() {
    uint64_t msg;
    uint64_t key;

    puts("(Give values in hex, e.g., : a9f1)");
    fputs("Enter the message: ", stdout);
    cin >> hex >> msg;

    fputs("Enter the key: ", stdout);
    cin >> hex >> key;

    printf("DES(0x%016lx, 0x%016lx) == 0x%016lx\n", msg, key, DES(msg, key));

    return true;
}
