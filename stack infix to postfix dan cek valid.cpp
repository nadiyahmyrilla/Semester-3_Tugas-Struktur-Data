#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>
#include <stack>

using namespace std;

bool isValidBrackets(const string& code) {
	    stack<char> s; // stack untuk menyimpan tanda kurung yang belum ditutup
	
	    //pasangan tanda kurung
	    for (size_t i = 0; i < code.length(); ++i) {
	        char ch = code[i];
	        
	        //jika tanda kurung pembuka
	        if (ch == '(' || ch == '{' || ch == '[' || ch == '<') {
	            s.push(ch); //menambahkan ke stack
	        }
	        //jika tanda kurung penutup
	        else if (ch == ')' || ch == '}' || ch == ']' || ch == '>') {
	            if (s.empty()) {
	                return false; // Jika stack kosong, berarti tidak ada kurung pembuka yang cocok
	            }
	
	            char top = s.top(); //ambil tanda kurung teratas di stack
	            s.pop(); //menghapus tanda kurung teratas dari stack
	
	            //uji kevalidan
	            if ((ch == ')' && top != '(') ||
	                (ch == '}' && top != '{') ||
	                (ch == ']' && top != '[') ||
	                (ch == '>' && top != '<')) {
	                return false;
	            }
	        }
	    }
	    return s.empty();
	}

class Node {
    char value;
    Node* next;

	public:
    Node(char val) : value(val), next(NULL) {} //menginisiasikan value menjadi val dan next node null
    char getValue() { return value; }
    Node* getNext() { return next; }
    void setNext(Node* n) { next = n; }
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

int main() {
    string expression;
    char choice;

    do {
        system("cls");
        cout << "Masukkan kalimat matematika infix (contoh: 3+(5*2)): ";
        getline(cin, expression);

        // Pertama, cek validitas bracket
        if (isValidBrackets(expression)) {
            cout << "Bentuk Infix: " << expression << endl;
            string postfix = infixToPostfix(expression);
            cout << "Bentuk Postfix: " << postfix << endl;
        } else {
            cout << "Kode tidak valid! Ada pasangan tanda kurung yang tidak sesuai." << endl;
        }

        cout << "Apakah Anda ingin memasukkan kalimat matematika lain? (y/n): ";
        cin >> choice;
        cin.ignore();
    } while (choice == 'y' || choice == 'Y');

    return 0;
}
