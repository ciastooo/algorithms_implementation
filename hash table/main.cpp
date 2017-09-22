#include <iostream>
using namespace std;
 
const int m = 10000;
const double a = 0.61803398863412439823150634765625;
 
int Hash(char *input) {
        char *letter = input;
        int sum = 0;
        while (*letter != '\0') {
                sum += *letter - 'A';
                letter++;
        }
        double x = sum *a;
        return (int)(m * (x - (int)x));
}
 
class Receiver {
public:
        char *name;
        int value;
        Receiver *next;
        Receiver(char *receiverName, int newValue) {
                next = nullptr;
                name = new char[17];
                int i = 0;
                while (*(receiverName + i) != '\0') {
                        *(name + i) = *(receiverName + i);
                        i++;
                }
                *(name + i) = '\0';
                value = newValue;
        }
        ~Receiver() {
                delete[] name;
                if (next != nullptr)
                        delete next;
        }
        bool CheckReceiver(char *inputReceiver) {
                int i = 0;
                while (*(inputReceiver + i) != '\0' && *(name + i) != '\0') {
                        if (*(name + i) != *(inputReceiver + i)) {
                                return false;
                        }
                        i++;
                }
                return *(name + i) == '\0' && *(inputReceiver + i) == '\0';
        }
        void AddAnotherNodeOrValue(char *inputReceiver, int inputValue) {
                if (CheckReceiver(inputReceiver)) {
                        value += inputValue;
                }
                else if (next == nullptr) {
                        next = new Receiver(inputReceiver, inputValue);
                }
                else {
                        next->AddAnotherNodeOrValue(inputReceiver, inputValue);
                }
        }
        int GetValue(char *inputReceiver) {
                if (CheckReceiver(inputReceiver)) {
                        return value;
                }
                else if (next != nullptr) {
                        return next->GetValue(inputReceiver);
                }
                else {
                        return 0;
                }
        }
};
class HashArrayNode {
public:
        char *senderName;
        Receiver *receivers[m];
        HashArrayNode *next;
        HashArrayNode(char *inputSender, char *inputReceiver, int value) {
                next = nullptr;
                for (int i = 0; i < m; i++)
                {
                        receivers[i] = nullptr;
                }
                senderName = new char[17];
                int i = 0;
                while (*(inputSender + i) != '\0') {
                        *(senderName + i) = *(inputSender + i);
                        i++;
                }
                *(senderName + i) = '\0';
                receivers[Hash(inputReceiver)] = new Receiver(inputReceiver, value);
        }
        ~HashArrayNode() {
                if (next != nullptr)
                        delete next;
                for (int i = 0; i < m; i++)
                        delete receivers[i];
                delete[] senderName;
        }
        bool CheckSender(char *inputSender) {
                int i = 0;
                while (*(inputSender + i) != '\0' && *(senderName + i) != '\0') {
                        if (*(senderName + i) != *(inputSender + i)) {
                                return false;
                        }
                        i++;
                }
                return *(senderName + i) == '\0' && *(inputSender + i) == '\0';
        }
        void AddAnotherNodeOrValue(char *inputKey, char *inputReceiver, int value) {
                if (CheckSender(inputKey)) {
                        int receiverKey = Hash(inputReceiver);
                        if (receivers[receiverKey] == nullptr) {
                                receivers[receiverKey] = new Receiver(inputReceiver, value);
                        }
                        else {
                                receivers[receiverKey]->AddAnotherNodeOrValue(inputReceiver, value);
                        }
                }
                else if (next == nullptr) {
                        next = new HashArrayNode(inputKey, inputReceiver, value);
                }
                else {
                        next->AddAnotherNodeOrValue(inputKey, inputReceiver, value);
                }
        }
        int GetValue(char *inputKey, char *inputReceiver) {
                if (CheckSender(inputKey)) {
                        int receiverKey = Hash(inputReceiver);
                        if (receivers[receiverKey] != nullptr) {
                                return receivers[receiverKey]->GetValue(inputReceiver);
                        }
                        else {
                                return 0;
                        }                       
                }
                else if (next != nullptr) {
                        return next->GetValue(inputKey, inputReceiver);
                }
                else {
                        return 0;
                }
        }
};
class HashArray {
public:
        HashArrayNode *Array[m];
        HashArray() {
                for (int i = 0; i < m; i++)
                        Array[i] = nullptr;
        }
        ~HashArray() {
                for (int i = 0; i < m; i++) {
                        if (Array[i] != nullptr)
                                delete Array[i];
                }
        }
        void Push(char *inputKey, char *inputReceiver, int value) {
                int key = Hash(inputKey);
                if (Array[key] == nullptr) {
                        Array[key] = new HashArrayNode(inputKey, inputReceiver, value);
                }
                else {
                        Array[key]->AddAnotherNodeOrValue(inputKey, inputReceiver, value);
                }
        }
        void PrintValue(char *inputKey, char *inputReceiver) {
                int key = Hash(inputKey);
                if (Array[key] != nullptr) {
                        cout << Array[key]->GetValue(inputKey, inputReceiver);
                }
                else {
                        cout << '0';
                }
                cout << endl;
        }
};
int main()
{
        HashArray *head = new HashArray();
        char *input = new char[17];
        char *input2 = new char[17];
        int number = 0;
        while (cin >> input) {
                switch (*input) {
                case '+':
                        cin >> input;
                        cin >> input2;
                        cin >> number;
                        head->Push(input, input2, number);
                        break;
                case'?':
                default:
                        cin >> input;
                        cin >> input2;
                        head->PrintValue(input, input2);
                        break;
                }
        }
        delete head;
        delete[] input;
        delete[] input2;
        return 0;
}