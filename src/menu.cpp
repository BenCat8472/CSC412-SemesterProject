#include "menu.h"


Menu::Menu(string n) : name(n) {}


Menu::~Menu() {}


void Menu::add(string l, Func f) {
    labels.push_back(l);
    functions.push_back(f);
}


void Menu::print_options() {
    puts("0) Exit");
    for ( unsigned i = 0; i < labels.size(); ++i ) {
        printf("%d) %s\n", i + 1, labels[i].c_str());
    }
    putchar('>');
}


bool Menu::run() {
    unsigned option = 0;

    puts(name.c_str());
    print_options();

    while ( cin >> option && option != 0 ) {
        if ( option < functions.size() + 1 ) {
            Func f = functions[option - 1];
            if ( !(*f)() ) {
                fputs("Bad input: returning to menu...\n", stdout);
            }
        } else {
            return false;
        }
        print_options();
    }

    return true;
}
