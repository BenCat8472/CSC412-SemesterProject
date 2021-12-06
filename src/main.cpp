#include "menu.h"
#include "part1.h"
#include "part2.h"


bool menu1();
bool menu2();


int main() {
    Menu main_menu("--- Main Menu ---");
    main_menu.add("Part I", menu1 );
    main_menu.add("Part II", menu2 );
    main_menu.run();

    return 0;
}


bool menu1() {
    static bool init = false;
    static Menu menu("--- Part I Menu ---");

    if ( !init ) {
        menu.add("Affine Cipher", affine_menu);
        menu.add("Vigenère Cipher", vigenere_menu);
        menu.add("Frequency Calculation", frequency_menu);
        menu.add("Affine Cipher Attack", affine_attack);
        menu.add("Vigenère Cipher Attack", vigenere_attack);
        menu.add("ADFGX Cipher", adfgx_menu);
    }

    return menu.run();
}


bool menu2() {
    static bool init = false;
    static Menu menu("--- Part II Menu ---");

    if ( !init ) {
        menu.add("Simple DES", simple_DES_menu);
        menu.add("Full DES", full_DES_menu);
        menu.add("Three Rounds Attack", three_rounds_menu);
    }

    return menu.run();
}
