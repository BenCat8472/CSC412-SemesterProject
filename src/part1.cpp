#include "part1.h"


bool adfgx_menu() {
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
    text = toupper(text);

    fputs("1) encode\n2) decode\n>", stdout);
    if ( cin >> option ) {
        if ( option == 1 ) {
            text = to_alphabet(text, ALPHABET);
            printf("\"%s\" -> \"%s\"\n", text.c_str(), adfgx_E(key, text).c_str());
        }

        else if ( option == 2 ) {
            text = to_alphabet(text, string(ALPHABET) + ' ');
            printf("\"%s\" -> \"%s\"\n", text.c_str(), adfgx_D(key, text).c_str());
        }

        else
            return false;
    } else
        return false;

    return true;
}


bool affine_attack() {
    char p1, p2, c1, c2;
    fputs("Four characters are needed--'p1', 'p2', 'c1', 'c2'--"
          "where 'pi' is plaintext and 'ci' is ciphertext s.t.:\n"
          "\tE(p1)=c1 and E(p2)=c2\n"
          "Enter p1: ", stdout);
    if ( !( cin >> p1 ) )
        return false;
    fputs("Enter c1: ", stdout);
    if ( !( cin >> c1 ) )
        return false;
    fputs("Enter p2: ", stdout);
    if ( !( cin >> p2 ) )
        return false;
    fputs("Enter c2: ", stdout);
    if ( !( cin >> c2 ) )
        return false;

    printf("\nGiven: %c->%c; %c->%c\n", p1, c1, p2, c2);
    // a * p1 + b = c1; a * p2 + b = c2
    // a = (c1 - c2) * (p1 - p2)^-1
    // b = c1 - a * p1
    Int x1 = ord(toupper(p1));
    Int x2 = ord(toupper(p2));
    Int y1 = ord(toupper(c1));
    Int y2 = ord(toupper(c2));

    Int a = mod((y1 - y2) * findModInverse(x1 - x2, 26), 26);
    Int b = mod(y1 - a * x1, 26);

    printf("The affine cipher is:\n\tE(mi) = %d * mi + %d (mod 26)\n", a, b);

    return true;
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


bool frequency_menu() {
    string text;

    fputs("Enter the text: ", stdout);
    cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, text);

    Frequencies f = frequency(text);

    fputs("Character   Frequency\n---------------------\n", stdout);
    for ( auto p : f )
        printf("   '%c'    :   %.4f\n", p.first, p.second);

    cout << std::endl;

    return true;
}


bool vigenere_attack() {
    string cipher_text;
    int key_length = 1;

    fputs("Enter the cipher text: ", stdout);
    cin.clear(); cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    getline(cin, cipher_text);
    cipher_text = to_alphabet(toupper(cipher_text), ALPHABET);

    int max_coincidence = 0;
    for ( unsigned i = 1; i < cipher_text.size(); ++i ) {
        int coincidence = 0;
        unsigned k = i;
        for ( int j = 0; k < cipher_text.size(); ++j, ++k ) {
            if ( cipher_text[j] == cipher_text[k] )
                ++coincidence;
        }
        if ( coincidence > max_coincidence ) {
            max_coincidence = coincidence;
            key_length = i;
        }
    }
    printf("key length: %d\n", key_length);
    vector<int> key;
    key.reserve(key_length);

    vector<float> w;
    w.reserve(26);

    auto a = deque<float>(STANDARD_FREQUENCIES, STANDARD_FREQUENCIES + 26);
    for ( int i = 0; i < key_length; ++i ) {
        w.clear();
        for ( int j = 0; j < 26; ++j ) {
            int count = 0;
            for ( unsigned k = i; k < cipher_text.size(); k += key_length ) {
                if ( cipher_text[k] == chr(j) )
                    ++count;
            }
            w.push_back(float(count) / cipher_text.size());
        }

        float max_dot = 0.0;
        int shift = 0;

        for ( int j = 0; j < 26; ++j ) {
            float dot = 0;
            for ( int k = 0; k < 26; ++k )
                dot += w[k] * a[k];

            if ( dot > max_dot ) {
                max_dot = dot;
                shift = j;
            }

            a.push_front(a.back());
            a.pop_back();
        }

        key.push_back(shift);
    }

    fputs("The key is probably:\n\t", stdout);
    for ( int i = 0; i < key_length; ++i )
        cout << chr(key[i]);
    cout << std::endl;

    return true;
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
