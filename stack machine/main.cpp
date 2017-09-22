#include <iostream>
using namespace std;
 
class node {
public:
        int number;
        node* previous;
        node(int value) {
                number = value;
                previous = nullptr;
        }
};
class stos {
public:
        node* top;
        stos() {
                top = nullptr;
        }
        void Push(int value) {
                node *newNode = new node(value);
                if (top != nullptr)
                        newNode->previous = top;
                top = newNode;
        }
        void Print() {
                node *currentNode = top;
                while (currentNode != nullptr)
                {
                        cout << currentNode->number << ' ';
                        currentNode = currentNode->previous;
                }
                cout << endl;
        }
        void Delete() {
                node *newTop = top->previous;
                delete top;
                top = newTop;
        }
        void Sum() {
                top->previous->number += top->number;
                Delete();
        }
        void Swap(int level) {
                node *oldTop = top;
                node *toSwap = top;
                while (level > 1) {
                        toSwap = toSwap->previous;
                        level--;
                }
                node *prev = toSwap->previous;
                toSwap->previous = oldTop;
                top = oldTop->previous;
                oldTop->previous = prev;
        }
};
 
int ParseToInt(char*);
 
int main()
{
        stos *stack = new stos();
        char *input = new char[100];
        int number;
        while (cin >> input) {
                if (*input == 'q')
                        break;
                if (*input == '\n' || *input == '\0')
                        continue;
                switch (*input) {
                case ' ':
                        break;
                case 'p':
                        stack->Print();
                        break;
                case 's':
                        stack->Swap(2);
                        break;
                case 'x':
                        stack->Delete();
                        break;
                case '+':
                        stack->Sum();
                        break;
                case 'r':
                        number = stack->top->number;
                        stack->Delete();
                        stack->Swap(number);
                        break;
                default:
                        stack->Push(ParseToInt(input));
                        break;
                }
        }
        while (stack->top != nullptr) {
                stack->Delete();
        }
        delete stack;
        delete[] input;
        return 0;
}
 
int ParseToInt(char* input) {
        int number = 0;
        bool positive = true;
        if (*input == '-') {
                positive = false;
                input++;
        }
        while (*input - '0' >= 0 && *input - '0' <= 9) {
                number = number * 10 + *input - '0';
                input++;
        }
        return positive ? number : -number;
}