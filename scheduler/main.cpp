#include <iostream>
using namespace std;
 
class Task {
public:
        int id;
        Task *prevTask;
        Task *nextTask;
        Task(int newId) {
                id = newId;
                prevTask = nullptr;
                nextTask = nullptr;
        }
        ~Task() {
                if (prevTask != nullptr && nextTask != nullptr) {
                        prevTask->nextTask = nextTask;
                        nextTask->prevTask = prevTask;
                }
        }
};
class TaskList {
public:
        Task *firstTask;
        Task *lastTask;
        TaskList() {
                firstTask = nullptr;
                lastTask = nullptr;
        }
        ~TaskList() {
                if (firstTask != nullptr && lastTask != nullptr) {
                        do {
                                Terminate(firstTask);
                        } while (firstTask != nullptr);
                }
        }
        void Terminate(Task *toDelete) {
                if (firstTask == toDelete && lastTask == toDelete) {
                        firstTask = nullptr;
                        lastTask = nullptr;
                }
                else if (firstTask == toDelete) {
                        firstTask = toDelete->nextTask;
                }
                else if (lastTask == toDelete) {
                        lastTask = toDelete->prevTask;
                }
                delete toDelete;
        }
        Task* Find(int searchId) {
                if (firstTask == nullptr)
                        return nullptr;
                Task *search = firstTask;
                do {
                        if (search->id == searchId)
                                return search;
                        else {
                                if (search->nextTask == nullptr)
                                        return nullptr;
                                search = search->nextTask;
                        }
                } while (search != firstTask);
                return nullptr;
        }
        void Print() {
                if (firstTask != nullptr) {
                        Task *print = firstTask;
                        do {
                                cout << print->id << ' ';
                                if (print->nextTask == nullptr)
                                        break;
                                print = print->nextTask;
                        } while (print != firstTask);
                }
                cout << endl;
        }
        void Add(int newId) {
                Task *newTask = new Task(newId);
                if (firstTask == nullptr && lastTask == nullptr) {
                        firstTask = newTask;
                        lastTask = newTask;
                        return;
                }
                else {
                        newTask->prevTask = lastTask;
                        newTask->nextTask = firstTask;
                }
                lastTask->nextTask = newTask;
                firstTask->prevTask = newTask;
                lastTask = newTask;
        }
        void Run() {
                cout << firstTask->id << endl;
                if (firstTask->nextTask != nullptr) {
                        firstTask = firstTask->nextTask;
                        lastTask = firstTask->prevTask;
                }
        }
};
class Plan {
public:
        TaskList *highPriority;
        TaskList *mediumPriority;
        TaskList *lowPriority;
        Plan() {
                highPriority = new TaskList();
                mediumPriority = new TaskList();
                lowPriority = new TaskList();
        }
        ~Plan() {
                delete highPriority;
                delete mediumPriority;
                delete lowPriority;
        }
        void Add(int newId, int priority) {
                switch (priority) {
                case 1:
                        highPriority->Add(newId);
                        break;
                case 0:
                        mediumPriority->Add(newId);
                        break;
                case -1:
                        lowPriority->Add(newId);
                        break;
                }
        }
        void Terminate(int deleteId) {
                Task *toDelete = highPriority->Find(deleteId);
                if (toDelete != nullptr) {
                        highPriority->Terminate(toDelete);
                }
                else {
                        toDelete = mediumPriority->Find(deleteId);
                        if (toDelete != nullptr) {
                                mediumPriority->Terminate(toDelete);
                        }
                        else {
                                toDelete = lowPriority->Find(deleteId);
                                lowPriority->Terminate(toDelete);
                        }
                }
        }
        void ChangePriority(int id, int newPriority) {
                Terminate(id);
                Add(id, newPriority);
        }
        void Print() {
                cout << "1: ";
                highPriority->Print();
                cout << "0: ";
                mediumPriority->Print();
                cout << "-1: ";
                lowPriority->Print();
        }
        void Run() {
                if (highPriority->firstTask != nullptr) {
                        highPriority->Run();
                }
                else if (mediumPriority->firstTask != nullptr) {
                        mediumPriority->Run();
                }
                else if (lowPriority->firstTask != nullptr) {
                        lowPriority->Run();
                }
                else {
                        cout << "idle" << endl;
                }
        }
};
 
int ParseToInt(char*);
 
int main()
{
        Plan *plan = new Plan();
        char *input = new char[10];
        int number, id;
        while (cin >> input) {
                switch (*input) {
                case ' ':
                case '\0':
                        break;
                case 'n':
                        plan->Run();
                        break;
                case 'l':
                        plan->Print();
                        break;
                case 't':
                        cin >> id;
                        plan->Terminate(id);
                        break;
                case 'p':
                        cin >> number;
                        cin >> id;
                        plan->ChangePriority(number, id);
                        break;
                case 'c':
                        cin >> number;
                        cin >> id;
                        plan->Add(number, id);
                        break;
                default:
                        break;
                }
        }
        delete[] input;
        delete plan;
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