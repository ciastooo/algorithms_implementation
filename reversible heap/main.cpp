#include <iostream>
using namespace std;
 
class Heap {
public:
        Heap() {
                root = new int[65537];
                size = 0;
                ascending = false;
        }
        ~Heap() {
                delete[] root;
        }
        void Push(int number, bool repair = true) {
                *(root + 1 + size) = number;
                size++;
                if (repair && size > 1)
                {
                        RepairUp(size);
                }
        }
        void Pop() {
                cout << *(root + 1) << endl;
                *(root + 1) = *(root + size);
                size--;
                if (size > 1) {
                        Repair();
                }
        }
        void Print() {
                for (int i = 1; i <= size; i++) {
                        cout << *(root + i) << " ";
                }
                cout << endl;
        }
        void Clear() {
                size = 0;
        }
        void ChangeOrder() {
                ascending = !ascending;
                RepairArray();
        }
        void RepairArray() {
                for (int i = size / 2; i > 0; i--) {
                        Repair(i);
                }
        }
private:
        int *root;
        int size;
        bool ascending;
 
        void Repair(int index = 1) {
                int swap;
                int left = index * 2;
                int right = index * 2 + 1;
                if (left <= size && ((*(root + index) > *(root + left) && ascending) || (*(root + index) < *(root + left) && !ascending))) {
                        swap = left;
                }
                else {
                        swap = index;
                }
                if (right <= size && ((*(root + swap) > *(root + right) && ascending) || (*(root + swap) < *(root + right) && !ascending))) {
                        swap = right;
                }
                if (swap != index) {
                        int tmp = *(root + index);
                        *(root + index) = *(root + swap);
                        *(root + swap) = tmp;
                        Repair(swap);
                }
        }
        void RepairUp(int index) {
                if (index > 1) {
                        int parentIndex = index / 2;
                        if ((*(root + index) > *(root + parentIndex) && !ascending) || (*(root + index) < *(root + parentIndex) && ascending)) {
                                int tmp = *(root + index);
                                *(root + index) = *(root + parentIndex);
                                *(root + parentIndex) = tmp;
                                RepairUp(parentIndex);
                        }
                }
        }
};
 
int ParseToInt(char*);
 
int main()
{
        Heap *heap = new Heap();
        char *input = new char[100];
        while (cin >> input && *input != 'q') {
                switch (*input) {
                case '+':
                        cin >> input;
                        heap->Push(ParseToInt(input));
                        break;
                case 'r':
                        heap->Clear();
                        cin >> input;
                        int n;
                        for (int i = ParseToInt(input); i > 0; i--) {
                                cin >> n;
                                heap->Push(n, false);
                        }
                        heap->RepairArray();
                        break;
                case '-':
                        heap->Pop();
                        break;
                case 'p':
                        heap->Print();
                        break;
                case 's':
                        heap->ChangeOrder();
                        break;
                default:
                        break;
                }
        }
        delete heap;
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