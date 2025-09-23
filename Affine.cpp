// affine_oldcpp.cpp
// Affine cipher: encrypt, decrypt, brute-force
// Phiên b?n: không dùng range-based for (tuong thích trình biên d?ch cu)
// Biên d?ch v?i g++: g++ -std=c++98 affine_oldcpp.cpp -o affine

#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

int mod26(int x) {
    x %= 26;
    if (x < 0) x += 26;
    return x;
}

int gcd(int a, int b) {
    while (b) {
        int t = a % b;
        a = b;
        b = t;
    }
    return a;
}

int modInverse(int a) {
    a = mod26(a);
    for (int x = 1; x < 26; ++x) {
        if ((a * x) % 26 == 1) return x;
    }
    return -1;
}

int charToNum(char c) {
    if (isupper((unsigned char)c)) return c - 'A';
    if (islower((unsigned char)c)) return c - 'a';
    return -1;
}

char numToChar(int n, bool isUpper) {
    n = mod26(n);
    return isUpper ? char('A' + n) : char('a' + n);
}

string encryptAffine(const string &plaintext, int a, int b) {
    if (gcd(a, 26) != 1) {
        return "[L?I] a không h?p l? (gcd(a,26) ph?i = 1).";
    }
    string out;
    out.reserve(plaintext.size());
    for (size_t i = 0; i < plaintext.size(); ++i) {
        char ch = plaintext[i];
        int v = charToNum(ch);
        if (v == -1) {
            out.push_back(ch);
        } else {
            bool isUpper = isupper((unsigned char)ch);
            int c = mod26(a * v + b);
            out.push_back(numToChar(c, isUpper));
        }
    }
    return out;
}

string decryptAffine(const string &ciphertext, int a, int b) {
    if (gcd(a, 26) != 1) {
        return "[L?I] a không h?p l? (gcd(a,26) ph?i = 1).";
    }
    int a_inv = modInverse(a);
    if (a_inv == -1) return "[L?I] Không tìm du?c ngh?ch d?o cho a.";
    string out;
    out.reserve(ciphertext.size());
    for (size_t i = 0; i < ciphertext.size(); ++i) {
        char ch = ciphertext[i];
        int v = charToNum(ch);
        if (v == -1) {
            out.push_back(ch);
        } else {
            bool isUpper = isupper((unsigned char)ch);
            int p = mod26(a_inv * (v - b));
            out.push_back(numToChar(p, isUpper));
        }
    }
    return out;
}

vector<int> validAs() {
    vector<int> res;
    for (int a = 1; a < 26; ++a) if (gcd(a,26)==1) res.push_back(a);
    return res;
}

void bruteForceAffine(const string &ciphertext) {
    vector<int> As = validAs();
    cout << "Brute-force (a,b) -> Plaintext candidates:\n";
    for (size_t i = 0; i < As.size(); ++i) {
        int a = As[i];
        for (int b = 0; b < 26; ++b) {
            string plain = decryptAffine(ciphertext, a, b);
            cout << "a=" << a << ", b=" << b << " -> " << plain << "\n";
        }
    }
}

void showMenu() {
    cout << "Affine Cipher\n";
    cout << "1) Mã hoá (encrypt)\n";
    cout << "2) Gi?i mã (decrypt) v?i a,b\n";
    cout << "3) Brute-force (th? t?t c? a,b)\n";
    cout << "0) Thoát\n";
    cout << "Ch?n: ";
}

int main() {
    while (true) {
        showMenu();
        int choice;
        if (!(cin >> choice)) break;
        cin.ignore();
        if (choice == 0) break;

        if (choice == 1) {
            string plain;
            int a, b;
            cout << "Nh?p plaintext: ";
            getline(cin, plain);
            cout << "Nh?p a (gcd(a,26) = 1): ";
            cin >> a;
            cout << "Nh?p b (0..25): ";
            cin >> b;
            cin.ignore();
            cout << "Ciphertext: " << encryptAffine(plain, a, b) << "\n\n";
        } else if (choice == 2) {
            string cipher;
            int a, b;
            cout << "Nh?p ciphertext: ";
            getline(cin, cipher);
            cout << "Nh?p a (gcd(a,26) = 1): ";
            cin >> a;
            cout << "Nh?p b (0..25): ";
            cin >> b;
            cin.ignore();
            cout << "Plaintext: " << decryptAffine(cipher, a, b) << "\n\n";
        } else if (choice == 3) {
            string cipher;
            cout << "Nh?p ciphertext d? brute-force: ";
            getline(cin, cipher);
            bruteForceAffine(cipher);
            cout << "\n";
        } else {
            cout << "L?a ch?n không h?p l?.\n\n";
        }
    }

    cout << "K?t thúc chuong trình.\n";
    return 0;
}

