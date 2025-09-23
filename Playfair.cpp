#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cctype>
using namespace std;

// tao bang khoa 5x5 tu khoa
vector<vector<char> > generateKeySquare(const string &key) {
    string K;
    // chuyen sang in hoa, J -> I
    for (size_t i = 0; i < key.size(); i++) {
        char c = toupper(key[i]);
        if (c < 'A' || c > 'Z') continue;
        if (c == 'J') c = 'I';
        if (K.find(c) == string::npos) K.push_back(c);
    }
    // them cac chu cai con lai
    for (char c = 'A'; c <= 'Z'; c++) {
        if (c == 'J') continue; // bo qua J
        if (K.find(c) == string::npos) K.push_back(c);
    }

    vector<vector<char> > square(5, vector<char>(5));
    int idx = 0;
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            square[r][c] = K[idx++];
        }
    }
    return square;
}

// tim vi tri cua ky tu trong bang
pair<int,int> findPosition(const vector<vector<char> > &square, char c) {
    if (c == 'J') c = 'I';
    for (int r = 0; r < 5; r++) {
        for (int col = 0; col < 5; col++) {
            if (square[r][col] == c) return make_pair(r, col);
        }
    }
    return make_pair(-1,-1);
}

// tao digraph tu plaintext
vector<pair<char,char> > prepareText(const string &text) {
    string s;
    // chuan hoa
    for (size_t i = 0; i < text.size(); i++) {
        char c = toupper(text[i]);
        if (c < 'A' || c > 'Z') continue;
        if (c == 'J') c = 'I';
        s.push_back(c);
    }

    vector<pair<char,char> > digraphs;
    for (size_t i = 0; i < s.size(); ) {
        char a = s[i];
        char b;
        if (i + 1 < s.size()) b = s[i+1];
        else b = 'X';

        if (a == b) {
            digraphs.push_back(make_pair(a, 'X'));
            i++;
        } else {
            digraphs.push_back(make_pair(a, b));
            i += 2;
        }
    }
    if (digraphs.size() > 0) {
        if (digraphs.back().second == 0) digraphs.back().second = 'X';
    }
    return digraphs;
}

// ma hoa
string encrypt(const string &plain, const vector<vector<char> > &square) {
    vector<pair<char,char> > digraphs = prepareText(plain);
    string cipher;
    for (size_t i = 0; i < digraphs.size(); i++) {
        char a = digraphs[i].first;
        char b = digraphs[i].second;
        pair<int,int> pa = findPosition(square, a);
        pair<int,int> pb = findPosition(square, b);

        if (pa.first == pb.first) { // cung hang
            cipher.push_back(square[pa.first][(pa.second+1)%5]);
            cipher.push_back(square[pb.first][(pb.second+1)%5]);
        } else if (pa.second == pb.second) { // cung cot
            cipher.push_back(square[(pa.first+1)%5][pa.second]);
            cipher.push_back(square[(pb.first+1)%5][pb.second]);
        } else { // khac hang, khac cot
            cipher.push_back(square[pa.first][pb.second]);
            cipher.push_back(square[pb.first][pa.second]);
        }
    }
    return cipher;
}

// giai ma
string decrypt(const string &cipher, const vector<vector<char> > &square) {
    string s;
    for (size_t i = 0; i < cipher.size(); i++) {
        char c = toupper(cipher[i]);
        if (c < 'A' || c > 'Z') continue;
        if (c == 'J') c = 'I';
        s.push_back(c);
    }

    string plain;
    for (size_t i = 0; i < s.size(); i += 2) {
        char a = s[i];
        char b = (i+1 < s.size()) ? s[i+1] : 'X';
        pair<int,int> pa = findPosition(square, a);
        pair<int,int> pb = findPosition(square, b);

        if (pa.first == pb.first) { // cung hang
            plain.push_back(square[pa.first][(pa.second+4)%5]);
            plain.push_back(square[pb.first][(pb.second+4)%5]);
        } else if (pa.second == pb.second) { // cung cot
            plain.push_back(square[(pa.first+4)%5][pa.second]);
            plain.push_back(square[(pb.first+4)%5][pb.second]);
        } else {
            plain.push_back(square[pa.first][pb.second]);
            plain.push_back(square[pb.first][pa.second]);
        }
    }
    return plain;
}

int main() {
    string key, text;
    int choice;

    cout << "Nhap khoa: ";
    getline(cin, key);
    cout << "Nhap chuoi: ";
    getline(cin, text);
    cout << "Chon 1=Ma hoa, 2=Giai ma: ";
    cin >> choice;

    vector<vector<char> > square = generateKeySquare(key);

    cout << "Bang khoa 5x5:\n";
    for (int r = 0; r < 5; r++) {
        for (int c = 0; c < 5; c++) {
            cout << square[r][c] << " ";
        }
        cout << endl;
    }

    if (choice == 1) {
        string c = encrypt(text, square);
        cout << "Ciphertext: " << c << endl;
    } else if (choice == 2) {
        string p = decrypt(text, square);
        cout << "Plaintext: " << p << endl;
    } else {
        cout << "Lua chon khong hop le" << endl;
    }

    return 0;
}

