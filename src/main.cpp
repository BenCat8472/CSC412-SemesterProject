#include "main.h"


bool affine_menu();
void frequency_menu();
bool vigenere_menu();


int main() {
    int option = 0;

    fputs(MENU, stdout);
    while ( cin >> option && option != 0 ) {
        switch ( option ) {
            case 1: // Affine Cipher
                if ( !affine_menu() )
                    fputs("Bad input: returning to main menu...\n", stdout);
                break;

            case 2: // Vigenère Cipher
                if ( !vigenere_menu() )
                    fputs("Bad input: returning to main menu...\n", stdout);
                break;

            case 3: // Frequency calculation
                frequency_menu();
                break;

            case 4: // Affine Cipher attack
                printf("Frequency calculation\n");
                break;

            case 5: // Vigenère Cipher attack
                printf("Vigenère Cipher attack\n");
                break;

            case 6: // ADFGX Cipher
                printf("ADFGX Cipher\n");
                break;

            case 7: // ???
                printf("???\n");
                break;

            default:
                printf("Option not recognized.\n");
        }

        fputs(MENU, stdout);
    }

    return 0;
}


bool affine_menu() {
    string text;
    int option;
    Int a, b;

    fputs("a=", stdout);
    if ( !( cin >> a ) )
        return false;

    fputs("b=", stdout);
    if ( !( cin >> b ) )
        return false;

    fputs("Enter the text: ", stdout);
    cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, text);
    text = to_alphabet(toupper(text), ALPHABET);

    fputs("1) encode\n2) decode\n>", stdout);
    if ( cin >> option ) {
        if ( option == 1 )
            printf("\"%s\" -> \"%s\"\n", text.c_str(), affine_E(a, b, text).c_str());

        else if ( option == 2 )
            printf("\"%s\" -> \"%s\"\n", text.c_str(), affine_D(a, b, text).c_str());

        else
            return false;
    } else
        return false;

    return true;
}


void frequency_menu() {
    string text;

    fputs("Enter the text: ", stdout);
    cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, text);

    Frequencies f = frequency(text);

    fputs("Character   Frequency\n---------------------\n", stdout);
    for ( auto p : f )
        printf("   '%c'    :   %.4f\n", p.first, p.second);

    cout << std::endl;
}


bool vigenere_menu() {
    string text;
    string key;
    int option;

    fputs("Enter the key: ", stdout);
    cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, key);
    key = to_alphabet(toupper(key), ALPHABET);

    fputs("Enter the text: ", stdout);
    // cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, text);
    text = to_alphabet(toupper(text), ALPHABET);

    fputs("1) encode\n2) decode\n>", stdout);
    if ( cin >> option ) {
        if ( option == 1 )
            printf("\"%s\" -> \"%s\"\n", text.c_str(), vigenere_E(key, text).c_str());

        else if ( option == 2 )
            printf("\"%s\" -> \"%s\"\n", text.c_str(), vigenere_D(key, text).c_str());

        else
            return false;
    } else
        return false;

    return true;
}
