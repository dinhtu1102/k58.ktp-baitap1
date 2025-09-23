#include <iostream>
#include <string>
#include <cctype>
using namespace std;

// ham chuyen sang chu hoa
string toUpper(const string &s) {
    string res = s;
    for (size_t i = 0; i < res.size(); i++) {
        if (isalpha(res[i])) res[i] = toupper(res[i]);
    }
    return res;
}

// ham ma hoa Vigenere
string encryptVigenere(const string &plain, const string &key) {
    string res;
    string K = toUpper(key);
    int m = K.size();
    int j = 0; // vi tri trong khoa

    for (size_t i = 0; i < plain.size(); i++) {
        char c = plain[i];
        if (isalpha(c)) {
            char p = toupper(c) - 'A';
            char k = K[j % m] - 'A';
            char ch = (p + k) % 26 + 'A';
            res.push_back(ch);
            j++;
        } else {
            res.push_back(c); // giu nguyen ky tu khong phai chu
        }
    }
    return res;
}

// ham giai ma Vigenere
string decryptVigenere(const string &cipher, const string &key) {
    string res;
    string K = toUpper(key);
    int m = K.size();
    int j = 0; // vi tri trong khoa

    for (size_t i = 0; i < cipher.size(); i++) {
        char c = cipher[i];
        if (isalpha(c)) {
            char ci = toupper(c) - 'A';
            char k = K[j % m] - 'A';
            char ch = (ci - k + 26) % 26 + 'A';
            res.push_back(ch);
            j++;
        } else {
            res.push_back(c);
        }
    }
    return res;
}

int main() {
    string text, key;
    int choice;

    cout << "Nhap khoa: ";
    cin >> key;
    cin.ignore(); // bo qua ky tu xuong dong

    cout << "Nhap chuoi: ";
    getline(cin, text);

    cout << "Chon 1=Ma hoa, 2=Giai ma: ";
    cin >> choice;

    if (choice == 1) {
        string c = encryptVigenere(text, key);
        cout << "Ciphertext: " << c << endl;
    } else if (choice == 2) {
        string p = decryptVigenere(text, key);
        cout << "Plaintext: " << p << endl;
    } else {
        cout << "Lua chon khong hop le" << endl;
    }
    return 0;
}

