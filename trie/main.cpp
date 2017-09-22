#include <iostream>
using namespace std;
 
const int alphabetSize = 26;
 
struct Node {
        Node *children[alphabetSize];
        char *translate;
        Node() {
                for (int i = 0; i < alphabetSize; i++) {
                        children[i] = NULL;
                }
                translate = new char[16];
                *translate = '-';
        }
        ~Node() {
                for (int i = 0; i < alphabetSize; i++) {
                        if (children[i] != NULL) {
                                delete children[i];
                        }
                }
                delete[] translate;
        }
        void Push(char *input, char *word) {
                if (*input == '\0') {
                        int i = 0;
                        while (*(word + i) != '\0') {
                                *(translate + i) = *(word + i);
                                i++;
                        }
                        *(translate + i) = '\0';
                }
                else if (children[*input - 97] == NULL) {
                        children[*input - 97] = new Node();
                        children[*input - 97]->Push(input + 1, word);
                }
                else {
                        children[*input - 97]->Push(input + 1, word);
                }
        }
        void Print(char *input) {
                if (*input == '\0') {
                        PrintTranslate();
                }
                else if (children[*input - 97] == NULL) {
                        cout << '-' << endl;
                }
                else {
                        children[*input - 97]->Print(input + 1);
                }
        }
        void PrintTranslate() {
                if (*translate != '-') {
                        for (char *letter = translate; *letter != '\0'; letter++) {
                                cout << *letter;
                        }
                }
                else {
                        cout << '-';
                }
                cout << endl;
        }
        void PrintChildren(char *input) {
                if (*input == '\0') {
                        if (*translate != '-') {
                                PrintTranslate();
                        }
                        for (int i = 0; i < alphabetSize; i++) {
                                if (children[i] != NULL) {
                                        children[i]->PrintChildren(input);
                                }
                        }
                }
                else if (children[*input - 97] != NULL) {
                        children[*input - 97]->PrintChildren(input + 1);
                }
                else {
                        cout << '-' << endl;
                }
        }
};
struct Trie {
        Node *children[alphabetSize];
        Trie() {
                for (int i = 0; i < alphabetSize; i++) {
                        children[i] = NULL;
                }
        }
        ~Trie() {
                for (int i = 0; i < alphabetSize; i++) {
                        if (children[i] != NULL) {
                                delete children[i];
                        }
                }
        }
        void AddWord(char *input, char *word) {
                if (children[*input - 97] == NULL) {
                        children[*input - 97] = new Node();
                        children[*input - 97]->Push(input + 1, word);
                }
                else {
                        children[*input - 97]->Push(input + 1, word);
                }
        }
        void PrintWord(char *input) {
                if (children[*input - 97] == NULL) {
                        cout << '-' << endl;
                }
                else {
                        children[*input - 97]->Print(input + 1);
                }
        }
        void PrintChildren(char *input) {
                if (children[*input - 97] == NULL) {
                        cout << "-" << endl;
                }
                else
                        children[*input - 97]->PrintChildren(input + 1);
        }
};
 
int main()
{
        Trie *trie = new Trie();
        char *input = new char[16];
        char *word = new char[16];
        while (cin >> input) {
                switch (*input) {
                case '+':
                        cin >> input;
                        cin >> word;
                        trie->AddWord(input, word);
                        break;
                case '?':
                        cin >> word;
                        trie->PrintWord(word);
                        break;
                case '*':
                        cin >> word;
                        trie->PrintChildren(word);
                        break;
                default:
                        break;
                }
        }
        delete trie;
        delete[] input;
        delete[] word;
        return 0;
}