// caesar_fixed.cpp
// Bien dich: g++ -std=c++11 caesar_fixed.cpp -o caesar
#include <iostream>
#include <string>
#include <cctype>
#include <limits>

using namespace std;

string mahoa(const string &text, int k) {
    string result;
    result.reserve(text.size());
    // chuan hoa k ve 0..25
    k %= 26;
    if (k < 0) k += 26;

    for (size_t i = 0; i < text.size(); ++i) {
        char c = text[i];
        unsigned char uc = static_cast<unsigned char>(c);
        if (isupper(uc)) {
            result += static_cast<char>((c - 'A' + k) % 26 + 'A');
        } else if (islower(uc)) {
            result += static_cast<char>((c - 'a' + k) % 26 + 'a');
        } else {
            result += c; // giu nguyen ky tu khac
        }
    }
    return result;
}

string giaima(const string &text, int k) {
    return mahoa(text, -k);
}

void bruteforce(const string &text) {
    cout << "\n>>> Thu tat ca khoa tu 0 den 25:\n";
    for (int k = 0; k < 26; ++k) {
        cout << "k = " << k << " | " << giaima(text, k) << endl;
    }
}

int main() {
    int chon = -1;
    do {
        cout << "\n===== CHUONG TRINH MA HOA CAESAR =====\n";
        cout << "1. Ma hoa (Encrypt)\n";
        cout << "2. Giai ma (Decrypt voi khoa biet truoc)\n";
        cout << "3. Brute-force (Thu tat ca khoa)\n";
        cout << "0. Thoat\n";
        cout << "======================================\n";
        cout << ">> Moi ban chon chuc nang (0-3): ";

        if (!(cin >> chon)) {
            cout << "Nhap khong hop le. Thoat.\n";
            return 0;
        }
        // xoa phan con lai cua dong
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (chon == 1) {
            int k;
            string plaintext;
            cout << "\nBan da chon: MA HOA\n";
            cout << "Nhap khoa k (so nguyen, co the am hoac duong): ";
            if (!(cin >> k)) { cout << "Khoa nhap sai. Thoat.\n"; return 0; }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nhap van ban can ma hoa: ";
            getline(cin, plaintext);

            string ciphertext = mahoa(plaintext, k);
            cout << "\n>>> Ban ma hoa duoc: " << ciphertext << endl;

        } else if (chon == 2) {
            int k;
            string ciphertext;
            cout << "\nBan da chon: GIAI MA\n";
            cout << "Nhap khoa k (so nguyen, dung khoa da dung khi ma hoa): ";
            if (!(cin >> k)) { cout << "Khoa nhap sai. Thoat.\n"; return 0; }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Nhap van ban da ma hoa: ";
            getline(cin, ciphertext);

            string plaintext = giaima(ciphertext, k);
            cout << "\n>>> Ban giai ma duoc: " << plaintext << endl;

        } else if (chon == 3) {
            string ciphertext;
            cout << "\nBan da chon: BRUTE-FORCE\n";
            cout << "Nhap van ban da ma hoa: ";
            getline(cin, ciphertext);
            bruteforce(ciphertext);

        } else if (chon == 0) {
            cout << "\nThoat chuong trinh. Tam biet!\n";
        } else {
            cout << "\nLua chon khong hop le. Moi ban nhap lai!\n";
        }
    } while (chon != 0);

    return 0;
}

