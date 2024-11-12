#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>

using namespace std;

class Node {
    char value;
    Node* next;

	public:
    Node(char val) : value(val), next(NULL) {} //menginisiasikan value menjadi val dan next node null
    char getValue() { return value; }
    Node* getNext() { return next; }
    void setNext(Node* n) { next = n; } // untuk menuju ke node berikutnya
};

class Stack {
    Node* top; // menujuk node teratas stack

	public: 
	// karena menggunkan class maka jika perlu menggunakan public, jika tidak ingin menggunakan public gunakan typedef struct
    Stack() : top(NULL) {} //menunjukan stack itu kosong

    bool isEmpty() { //jika kosong, boolean seperti if atau else
        return top == NULL;
    }

    void push(char value) {
        Node* newNode = new Node(value);
        newNode->setNext(top);
        top = newNode;
    }

    char pop() {
        if (!isEmpty()) {
            char poppedValue = top->getValue();
            Node* temp = top;
            top = top->getNext();
            delete temp;
            return poppedValue;
        }
        return '\0'; // null menggunakan \0
    }

    char peek() { // mengintip nilai didalam stack
        return isEmpty() ? '\0' : top->getValue();
    }
};

int precedence(char op) { // untuk menciptakan hirarki antara +- dan */
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2; //lebiih tinggi */
    return 0;
}

// Fungsi untuk memeriksa keseimbangan tanda kurung
bool balanced(const string& expression) {
    Stack stack;
    
    for (size_t i = 0; i < expression.length(); ++i) {
    	char ch = expression[i];
        if (ch == '(') {
            stack.push(ch);  // Menambahkan tanda kurung buka ke stack
        } else if (ch == ')') {
            if (stack.isEmpty()) {
                return false;  // Tidak ada kurung buka untuk dipasangkan
            }
            stack.pop();  // Menghapus tanda kurung buka yang sesuai
        }
    }
    return stack.isEmpty();  // Jika stack kosong, berarti semua kurung terbuka sudah dipasangkan
}

string infixToPostfix(const string& expression) {
    Stack stack;
    string output; // untuk menyimpan hasil output

    for (size_t i = 0; i < expression.length(); ++i) {
        char ch = expression[i];
        if (isalnum(ch)) { // untuk menyimpan angka yang dimasukan
            output += ch;
        } else if (ch == '(') {
            stack.push(ch);
        } else if (ch == ')') {
            while (!stack.isEmpty() && stack.peek() != '(') {
                output += stack.pop(); // Pop dari stack ke output sampai menemukan '('
            }
            stack.pop();
        } else { // operator/ tanda +-*/
            while (!stack.isEmpty() && precedence(stack.peek()) >= precedence(ch)) {
                output += stack.pop(); // Pop operator dari stack ke output jika prioritas operator di stack lebih tinggi atau sama
            }
            stack.push(ch);
        }
    }

    while (!stack.isEmpty()) { // pop semua operator
        output += stack.pop();
    }

    return output;
}

int evaluatePostfix(const string& postfix) {
    Stack stack;

    for (size_t i = 0; i < postfix.length(); ++i) {
        char ch = postfix[i];
        if (isdigit(ch)) { // Memeriksa apakah karakter adalah digit (0-9), char '5' menjadi int 5
            stack.push(ch - '0'); // mengubah char menjadi int
        } else {
            int b = stack.pop();
            int a = stack.pop();
            switch (ch) {
                case '+': stack.push(a + b); break;
                case '-': stack.push(a - b); break;
                case '*': stack.push(a * b); break;
                case '/': stack.push(a / b); break;
            }
        }
    }
    return stack.pop();
}

int main() {
    string expression;
    char choice;
    bool exitProgram = false;
    
    do {
        system("cls");
        cout << "Ingin mengakhiri program? Tekan (n)\n";
        cout << "Masukkan kalimat matematika infix (contoh: 3+(5*2)): ";
        getline(cin, expression);
        
        if (expression == "n") {
            exitProgram = true;
            break;
        }

        do {
            system("cls");
            cout << "Ekspresi yang dimasukkan: " << expression << endl;
            cout << "\nMenu:\n";
            cout << "1. Cek keseimbangan kurung\n";
            cout << "2. Konversi Infix ke Postfix\n";
            cout << "3. Evaluasi ekspresi matematika\n";
            cout << "4. Memasukkan kalimat matematika lain? \n";
            cout << "Masukkan pilihan: ";
            cin >> choice;
            cin.ignore();

            if (choice == '1') {
                bool isBalanced = balanced(expression);
                cout << "Keseimbangan kurung: " << (isBalanced ? "Seimbang" : "Tidak Seimbang") << endl;
            } else if (choice == '2') {
                string postfix = infixToPostfix(expression);
                cout << "Bentuk Postfix: " << postfix << endl;
            } else if (choice == '3') {
                if (!balanced(expression)) {
                    cout << "Ekspresi tidak seimbang dalam tanda kurung.\n";
                } else {
                    string postfix = infixToPostfix(expression);
                    int result = evaluatePostfix(postfix);
                    cout << "Bentuk Infix: " << expression << endl;
                    cout << "Bentuk Postfix: " << postfix << endl;
                    cout << "Hasil Evaluasi: " << result << endl;
                }
            } else if (choice == '4') {
                cout << "Keluar dari program.\n";
                break;
            } else {
                cout << "Pilihan tidak valid. Silakan coba lagi.\n";
            }
            cout << "Tekan Enter untuk melanjutkan...";
            cin.get();

        } while (choice != '4');
    } while (!exitProgram);
    return 0;
}
