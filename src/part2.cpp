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


bool three_rounds_menu() {
    pair<set<byte>, set<byte>> k4;

    // prep for getline() input
    cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

    for (;;) {
        uint16_t m1, m2, c1, c2;

        puts("(Give values in binary, e.g., : 000111011011)");
        puts("First, input the values for the result of the first and fourth rounds:");
        fputs("Enter message1 = L1 R1: ", stdout);
        m1 = get_binary();

        fputs("Enter cipher1 = L4 R4: ", stdout);
        c1 = get_binary();

        puts("Now change the left half of the input:");
        fputs("Enter message2 = L1* R1: ", stdout);
        m2 = get_binary();

        fputs("Enter cipher2 = L4* R4*: ", stdout);
        c2 = get_binary();

        auto k4s = three_rounds(m1, c1, m2, c2);
        auto k4l = k4s.first;
        auto k4r = k4s.second;

        if ( k4s.first.size() == 0 || k4s.second.size() == 0 ) {
            puts("Bad input: no possibilities for the key found.");
            return false;
        }

        if ( k4.first.size() == 0 ) {
            k4 = k4s;
        } else {
            set<byte> intersection;
            for ( auto x : k4s.first ) {
                if ( k4.first.find(x) != k4.first.end() ) {
                    intersection.emplace(x);
                }
            }
            k4.first = intersection;

            intersection.clear();
            for ( auto x : k4s.second ) {
                if ( k4.second.find(x) != k4.second.end() ) {
                    intersection.emplace(x);
                }
            }
            k4.second = intersection;
        }

        std::cout << "K4 left half possibilities:\n";
        for ( auto x : k4.first ) {
            std::cout << Bits(x, 4) << ' ';
        }
        std::cout << "\nK4 right half possibilities:\n";
        for ( auto x : k4.second ) {
            std::cout << Bits(x, 4) << ' ';
        }
        std::cout << '\n';

        if ( k4.first.size() == 1 && k4.second.size() == 1 ) {
            uint16_t key = (*(k4.first.begin()) << 4) | *(k4.second.begin());
            uint16_t key0 = (key >> 2) | ((key & 0b11) << 7);
            uint16_t key1 = key0 | 0b001000000;
            std::cout << "The key is either: " << Bits(key0, 9) << " or " << Bits(key1, 9) << ".\n";
            break;
        } else if ( k4.first.size() == 0 || k4.second.size() == 0 ) {
            puts("Bad input: no possibilities for the key found.");
            return false;
        }
    }

    return true;
}


uint16_t get_binary() {
    string s;
    getline(cin, s);
    return strtoul(s.c_str(), NULL, 2);
}
