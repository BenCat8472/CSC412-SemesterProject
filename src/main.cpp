#include <iostream>
#include "affinecipher.h"

using std::cout;


int main() {
    string text = "helloworld";
    cout << '"' << text << '"' << " -> " << '"' << affine(2, 3, text) << '"' << std::endl;

    return 0;
}
