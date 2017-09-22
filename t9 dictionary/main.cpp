#include <iostream>
using namespace std;
 
const int alphabetSize = 8;
 
struct WordsStack {
        char *Word;
        WordsStack *next;
        WordsStack(char *input) {
                Word = new char[100];
                int i = 0;
                while (*(input + i) != '\0') {
                        *(Word + i) = *(input + i);
                        i++;
                }
                *(Word + i) = '\0';
                next = nullptr;
        }
        ~WordsStack() {
                delete[] Word;
                if (next != nullptr)
                        delete next;
        }
        void CompareAndInsert(WordsStack *newWord) {
                char *wordA = Word;
                char *wordB = newWord->Word;
                while (*wordA != '\0' && *wordB != '\0') {
                        if (*wordA > *wordB) {
                                char *tmp = Word;
                                Word = newWord->Word;
                                newWord->Word = tmp;
                                if (next == nullptr) {
                                        next = newWord;
                                }
                                else {
                                        newWord->next = next;
                                        next = newWord;
                                }
                                return;
                        }
                        else if (*wordA < *wordB) {
                                break;
                        }
                        wordA++;
                        wordB++;
                }
                if (next == nullptr) {
                        next = newWord;
                }
                else {
                        next->CompareAndInsert(newWord);
                }
        }
};
struct Node {
        Node *children[alphabetSize];
        WordsStack *words;
        Node() {
                for (int i = 0; i < alphabetSize; i++) {
                        children[i] = NULL;
                }
                words = NULL;
        }
        ~Node() {
                for (int i = 0; i < alphabetSize; i++) {
                        if (children[i] != NULL) {
                                delete children[i];
                        }
                }
                if (words != nullptr)
                        delete words;
        }
        void Push(char *input, char *word) {
                if (*input == '\0') {
                        WordsStack *newWord = new WordsStack(word);
                        if (words == NULL) {
                                words = newWord;
                        }
                        else {
                                words->CompareAndInsert(newWord);
                        }
                }
                else
                {
                        int index = GetIndex(input);
                        if (children[index] == NULL)
                                children[index] = new Node();
                        children[index]->Push(input + 1, word);
                }
        }
        void PrintChildren(char *input) {
                if (*input == '\0') {
                        if (words != nullptr) {
                                WordsStack *printWord = words;
                                do {
                                        cout << printWord->Word << ' ';
                                        printWord = printWord->next;
                                } while (printWord != NULL);
                        }
                        for (int i = 0; i < alphabetSize; i++) {
                                if (children[i] != NULL) {
                                        children[i]->PrintChildren(input);
                                }
                        }
                        cout << endl;
                }
                else
                {
                        int index = *input - '2';
                        if (children[index] != NULL) {
                                children[index]->PrintChildren(input + 1);
                        }
                        else {
                                cout << '-' << endl;
                        }
                }
        }
        int GetIndex(char *input) {
                switch (*input) {
                case 'a':
                case 'b':
                case 'c':
                        return 0;
                        break;
                case 'd':
                case 'e':
                case 'f':
                        return 1;
                        break;
                case 'g':
                case 'h':
                case 'i':
                        return 2;
                        break;
                case 'j':
                case 'k':
                case 'l':
                        return 3;
                        break;
                case 'm':
                case 'n':
                case 'o':
                        return 4;
                        break;
                case 'p':
                case 'q':
                case 'r':
                case 's':
                        return 5;
                        break;
                case 't':
                case 'u':
                case 'v':
                        return 6;
                        break;
                case 'w':
                case 'x':
                case 'y':
                case 'z':
                default:
                        return 7;
                        break;
                }
        }
};
struct Trie {
        Node *head;
        Trie() {
                head = new Node();
        }
        ~Trie() {
                delete head;
        }
        void AddWord(char *input, char *word) {
                head->Push(input, word);
        }
        void PrintChildren(char *input) {
                head->PrintChildren(input);
        }
};
 
int main()
{
        Trie *trie = new Trie();
        int n;
        char *input = new char[100];
        cin >> n;
        for (int i = 0; i < n; i++) {
                cin >> input;
                trie->AddWord(input, input);
        }
        cin >> n;
        for (int i = 0; i < n; i++) {
                cin >> input;
                trie->PrintChildren(input);
        }
        delete trie;
        delete[] input;
        return 0;
}