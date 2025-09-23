#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

// ham so sanh de sap xep (thay cho lambda)
bool pairComp(const pair<char,int>& a, const pair<char,int>& b) {
    if (a.first != b.first) return a.first < b.first;
    return a.second < b.second;
}

// tinh thu tu cot tu khoa
vector<int> getOrderFromKey(const string &key) {
    int m = key.size();
    vector<pair<char,int> > v;   // phai viet > > de tranh loi
    for (int i = 0; i < m; i++) {
        v.push_back(make_pair(key[i], i));
    }
    sort(v.begin(), v.end(), pairComp);

    // colSeq[hang] = chi so cot goc
    vector<int> colSeq(m);
    for (int i = 0; i < m; i++) {
        colSeq[i] = v[i].second;
    }
    return colSeq;
}

// ma hoa
string encrypt(const string &plain, const string &key) {
    int m = key.size();
    vector<int> colSeq = getOrderFromKey(key);

    // dem so hang can co
    int n = (plain.size() + m - 1) / m;
    vector<string> mat(n, string(m, 'X'));

    // dien vao ma tran hang theo hang
    for (int i = 0; i < (int)plain.size(); i++) {
        mat[i / m][i % m] = plain[i];
    }

    // doc theo cot theo thu tu khoa
    string cipher;
    for (int k = 0; k < m; k++) {
        int col = colSeq[k];
        for (int row = 0; row < n; row++) {
            cipher.push_back(mat[row][col]);
        }
    }
    return cipher;
}

// giai ma
string decrypt(const string &cipher, const string &key) {
    int m = key.size();
    int n = (cipher.size() + m - 1) / m;
    vector<int> colSeq = getOrderFromKey(key);

    vector<string> mat(n, string(m, 'X'));

    int idx = 0;
    for (int k = 0; k < m; k++) {
        int col = colSeq[k];
        for (int row = 0; row < n; row++) {
            if (idx < (int)cipher.size()) {
                mat[row][col] = cipher[idx++];
            }
        }
    }

    string plain;
    for (int row = 0; row < n; row++) {
        for (int col = 0; col < m; col++) {
            plain.push_back(mat[row][col]);
        }
    }
    return plain;
}

int main() {
    string key, text;
    int choice;

    cout << "Nhap khoa (tu khoa): ";
    cin >> key;
    cout << "Nhap chuoi: ";
    cin >> text;
    cout << "Chon 1=Ma hoa, 2=Giai ma: ";
    cin >> choice;

    if (choice == 1) {
        string c = encrypt(text, key);
        cout << "Ciphertext: " << c << endl;
    } else if (choice == 2) {
        string p = decrypt(text, key);
        cout << "Plaintext: " << p << endl;
    } else {
        cout << "Lua chon khong hop le" << endl;
    }

    return 0;
}

