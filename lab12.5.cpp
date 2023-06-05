#include <iostream>
#include <fstream>
#include <string>

using namespace std;

struct Stack {
    char data;
    Stack* next;
};

Stack* top = NULL;

void push(char c) {
    Stack* new_node = new Stack;
    new_node->data = c;
    new_node->next = top;
    top = new_node;
}

char pop() {
    if (top == NULL) {
        return '\0';
    }
    char c = top->data;
    Stack* temp = top;
    top = top->next;
    delete temp;
    return c;
}

void count_operands_and_operators() {
    int operands = 0;
    int operators = 0;
    Stack* current = top;
    while (current != NULL) {
        if (current->data >= '0' && current->data <= '9') {
            operands++;
        }
        else if (current->data == '+' || current->data == '-' || current->data == '*' || current->data == '/') {
            operators++;
        }
        current = current->next;
    }
    cout << "Number of operands: " << operands << endl;
    cout << "Number of operators: " << operators << endl;
}

int main() {
    ifstream file("expressions.txt");
    if (!file.is_open()) {
        cout << "Error opening file." << endl;
        return 0;
    }
    string line;
    while (getline(file, line)) {
        for (int i = 0; i < line.length(); i++) {
            push(line[i]);
        }
        count_operands_and_operators();
        while (top != NULL) {
            cout << pop() << " ";
        }
        cout << endl << endl;
    }
    file.close();
    return 0;
}
