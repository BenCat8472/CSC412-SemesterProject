#ifndef __MENU__CLASS__H__
#define __MENU__CLASS__H__

#include <iostream>
#include <string>
#include <vector>

using std::cin;
using std::string;
using std::vector;

typedef bool(*Func)(void);


class Menu {
    string name;
    vector<string> labels;
    vector<Func> functions;

    void print_options();

public:
    Menu(string name);
    ~Menu();

    void add(string label, Func);
    bool run();
};


#endif//__MENU__CLASS__H__
