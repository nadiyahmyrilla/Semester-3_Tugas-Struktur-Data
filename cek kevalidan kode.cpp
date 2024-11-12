#include <iostream>
#include <stack>
#include <string>

using namespace std;

// Fungsi untuk memeriksa apakah kode valid
bool isValidCode(const string& code) {
    stack<char> stack;
    
    for (size_t i = 0; i < code.length(); ++i) {
        char ch = code[i];
        if (ch == '(' || ch == '{' || ch == '[' || ch == '<') {
            stack.push(ch);
        } else if (ch == ')' || ch == '}' || ch == ']' || ch == '>') {
            if (stack.empty()) {
                return false;
            }
            char top = stack.top();
            stack.pop();
            if ((ch == ')' && top != '(') || 
                (ch == '}' && top != '{') || 
                (ch == ']' && top != '[') || 
                (ch == '>' && top != '<')) {
                return false;
            }
        }
    }
    
    return stack.empty();
}

int main() {
    string line, allCode = "";
    char pilih;

    do {
        system("cls"); // Hanya untuk membersihkan layar di Windows

        cout << "Masukkan kode untuk diperiksa validitasnya (tekan Enter 2 kali untuk selesai):\n";

        // Membaca input sampai pengguna menekan Enter dua kali
        while (true) {
            getline(cin, line);

            // Berhenti jika input kosong (Enter ditekan dua kali)
            if (line.empty()) {
                break;
            }

            // Tambahkan baris input ke semua kode
            allCode += line + '\n';
        }

        // Cek apakah kode valid atau tidak
        if (isValidCode(allCode)) {
            cout << "Kode valid!\n";
        } else {
            cout << "Kode tidak valid!\n";
        }

        // Reset variabel allCode untuk input selanjutnya
        allCode = "";

        cout << "Tekan n untuk keluar atau tekan tombol lain untuk memeriksa kode lain: ";
        cin >> pilih;
        cin.ignore(); // Mengabaikan karakter newline di buffer input

    } while (pilih != 'n');

    return 0;
}

