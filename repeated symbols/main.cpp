#include <iostream>
using namespace std;
 
class SymbolNode {
public:
        SymbolNode *topNeighboor;
        SymbolNode *leftNeighboor;
        SymbolNode *rightNeighboor;
        SymbolNode *bottomNeighboor;
        bool searched;
        SymbolNode() {
                topNeighboor = nullptr;
                leftNeighboor = nullptr;
                rightNeighboor = nullptr;
                bottomNeighboor = nullptr;
                searched = false;
        }
        ~SymbolNode() {
                if (topNeighboor != nullptr) {
                        delete topNeighboor;
                        topNeighboor = NULL;
                }
                if (leftNeighboor != nullptr) {
                        delete leftNeighboor;
                        leftNeighboor = NULL;
                }
                if (rightNeighboor != nullptr) {
                        delete rightNeighboor;
                        rightNeighboor = NULL;
                }
                if (bottomNeighboor != nullptr) {
                        delete bottomNeighboor;
                        bottomNeighboor = NULL;
                }
        }
        void UnsearchNeighboors() {
                searched = false;
                if (topNeighboor != nullptr && topNeighboor->searched)
                        topNeighboor->UnsearchNeighboors();
                if (leftNeighboor != nullptr && leftNeighboor->searched)
                        leftNeighboor->UnsearchNeighboors();
                if (rightNeighboor != nullptr && rightNeighboor->searched)
                        rightNeighboor->UnsearchNeighboors();
                if (bottomNeighboor != nullptr && bottomNeighboor->searched)
                        bottomNeighboor->UnsearchNeighboors();
        }
        void PrintNeighBoors(char *picture, int width, int height, int id) {
                searched = true;
                if (topNeighboor != nullptr) {
                        picture[id - width] = '1';
                        topNeighboor->PrintNeighBoors(picture, width, height, id-width);
                }
                if (leftNeighboor != nullptr) {
                        picture[id - 1] = '1';
                        leftNeighboor->PrintNeighBoors(picture, width, height, id - 1);
                }
                if (rightNeighboor != nullptr) {
                        picture[id + 1] = '1';
                        rightNeighboor->PrintNeighBoors(picture, width, height, id + 1);
                }
                if (bottomNeighboor != nullptr) {
                        picture[id + width] = '1';
                        bottomNeighboor->PrintNeighBoors(picture, width, height, id + width);
                }
        }
};
class Symbol {
public:
        SymbolNode *head;
        int count, nodesCount, width, height, headRowId, leftMostId, rightMostId, topMostId, bottomMostId;
        Symbol *next;
        Symbol() {
                count = 1;
                width = 1;
                height = 1;
                nodesCount = 1;
                head = new SymbolNode();
                next = nullptr;
        }
        ~Symbol() {
                if (head != nullptr)
                        delete head;
                if (next != nullptr)
                        delete next;
        }
        int GetSymbolHash() {
                int sum = width + height + nodesCount;
                double x = sum * 0.61803398863412439823150634765625;
                return (int)(10000 * (x - (int)x));
        }
        bool CompareSymbols(Symbol *toCompare) {
                if (width != toCompare->width || height != toCompare->height || nodesCount != toCompare->nodesCount)
                        return false;
                head->UnsearchNeighboors();
                toCompare->head->UnsearchNeighboors();
                return CompareNeighBoors(head, toCompare->head);
        }
        bool CompareNeighBoors(SymbolNode *node, SymbolNode *toCompare) {
                node->searched = true;
                toCompare->searched = true;
                if (node->topNeighboor != nullptr && !node->topNeighboor->searched && toCompare->topNeighboor != nullptr && !toCompare->topNeighboor->searched) { //górni s¹siedzi
                        if (!CompareNeighBoors(node->topNeighboor, toCompare->topNeighboor))
                                return false;
                }
                else if (!(node->topNeighboor == nullptr && toCompare->topNeighboor == nullptr)) {
                        return false;
                }
                if (node->rightNeighboor != nullptr && !node->rightNeighboor->searched && toCompare->rightNeighboor != nullptr && !toCompare->rightNeighboor->searched) { //prawi s¹siedzi
                        if (!CompareNeighBoors(node->rightNeighboor, toCompare->rightNeighboor))
                                return false;
                }
                else if (!(node->rightNeighboor == nullptr && toCompare->rightNeighboor == nullptr)) {
                        return false;
                }
                if (node->leftNeighboor != nullptr && !node->leftNeighboor->searched && toCompare->leftNeighboor != nullptr && !toCompare->leftNeighboor->searched) { //lewi s¹siedzi
                        if (!CompareNeighBoors(node->leftNeighboor, toCompare->leftNeighboor))
                                return false;
                }
                else if (!(node->leftNeighboor == nullptr && toCompare->leftNeighboor == nullptr)) {
                        return false;
                }
                if (node->bottomNeighboor != nullptr && !node->bottomNeighboor->searched && toCompare->bottomNeighboor != nullptr && !toCompare->bottomNeighboor->searched) { // dolni s¹siedzi
                        if (!CompareNeighBoors(node->bottomNeighboor, toCompare->bottomNeighboor))
                                return false;
                }
                else if (!(node->bottomNeighboor == nullptr && toCompare->bottomNeighboor == nullptr)) {
                        return false;
                }
                return true;
        }
        void PushSymbol(Symbol *newSymbol) {
                if (next == nullptr) {
                        next = newSymbol;
                }
                else if (next->CompareSymbols(newSymbol)) {
                        next->count++;
                }
                else {
                        next->PushSymbol(newSymbol);
                }
        }
        void PrintSymbol(int maxCount) {
                if (maxCount == count) {
                        char *picture = new char[width*height];
                        for (int i = 0; i < width*height; i++)
                                picture[i] = '0';
                        head->UnsearchNeighboors();
                        picture[headRowId-leftMostId] = '1';
                        head->PrintNeighBoors(picture, width, height, headRowId-leftMostId);
                        for (int i = 0; i < width*height; i++) {
                                if (i % width == 0)
                                        cout << endl;
                                cout << picture[i];
                        }
                }
                else {
                        next->PrintSymbol(maxCount);
                }
        }
};
class Pixel {
public:
        bool color;
        bool searched;
        Pixel() {
                searched = false;
        }
        ~Pixel() {}
};
class Picture {
public:
        int width, height, totalSize;
        Pixel *picture;
        Symbol *hashArray[10000];
        Picture() {
                for (int i = 0; i < 10000; i++) {
                        hashArray[i] = nullptr;
                }
                cin >> width;
                cin >> height;
                totalSize = width * height;
                picture = new Pixel[totalSize+1];
                char input[1001];
                for (int i = 0; i < height; i++) {
                        cin >> input;
                        char *pixel = input;
                        for (int j = 0; j < width; j++) {
                                picture[i * width + j].color = *(pixel + j) == '1';
                        }
                }
        }
        ~Picture() {
                for (int i = 0; i < 10000; i++) {
                        if (hashArray[i] != nullptr) {
                                delete hashArray[i];
                        }
                }
                delete[] picture;
        }
 
        void SearchSymbolsInPictue() {
                for (int i = 0; i < totalSize; i++) {
                        if (picture[i].color && !picture[i].searched) {
                                Symbol *newSymbol = new Symbol();
                                newSymbol->headRowId = i%width;
                                newSymbol->bottomMostId = i/width;
                                newSymbol->leftMostId = i%width;
                                newSymbol->rightMostId = i%width;
                                newSymbol->topMostId = i/width;
                                SaveSymbol(i, newSymbol->head, newSymbol);
                                int hashId = newSymbol->GetSymbolHash();
                                if (hashArray[hashId] == nullptr) {
                                        hashArray[hashId] = newSymbol;
                                }
                                else {
                                        if (hashArray[hashId]->CompareSymbols(newSymbol)) {
                                                hashArray[hashId]->count++;
                                        }
                                        else {
                                                hashArray[hashId]->PushSymbol(newSymbol);
                                        }
                                }
                        }
                }
        }
        void SaveSymbol(int id, SymbolNode *node, Symbol *symbol) {
                picture[id].searched = true;
                int neighboorId = id - width; // górny s¹siad
                if (neighboorId >= 0 && picture[neighboorId].color && !picture[neighboorId].searched) {
                        node->topNeighboor = new SymbolNode();
                        if (neighboorId/width < symbol->topMostId) {
                                symbol->height++;
                                symbol->topMostId = neighboorId / width;
                        }
                        symbol->nodesCount++;
                        SaveSymbol(neighboorId, node->topNeighboor, symbol);
                }
                neighboorId = id + 1; //prawy s¹siad
                if (neighboorId < totalSize && neighboorId % width != 0 && picture[neighboorId].color && !picture[neighboorId].searched) {
                        node->rightNeighboor = new SymbolNode();
                        if (neighboorId%width > symbol->rightMostId)
                        {
                                symbol->width++;
                                symbol->rightMostId = neighboorId%width;
                        }
                        symbol->nodesCount++;
                        SaveSymbol(neighboorId, node->rightNeighboor, symbol);
                }
                neighboorId = id - 1; // lewy s¹siad
                if (neighboorId >= 0 && neighboorId % width != width-1 && picture[neighboorId].color && !picture[neighboorId].searched) {
                        node->leftNeighboor = new SymbolNode();
                        if (neighboorId%width < symbol->leftMostId)
                        {
                                symbol->width++;
                                symbol->leftMostId = neighboorId%width;
                        }
                        symbol->nodesCount++;
                        SaveSymbol(neighboorId, node->leftNeighboor, symbol);
                }
                neighboorId = id + width; // dolny s¹siad
                if (neighboorId < totalSize && picture[neighboorId].color && !picture[neighboorId].searched) {
                        node->bottomNeighboor = new SymbolNode();
                        if (neighboorId/width > symbol->bottomMostId)
                        {
                                symbol->height++;
                                symbol->bottomMostId = neighboorId/width;
                        }
                        symbol->nodesCount++;
                        SaveSymbol(neighboorId, node->bottomNeighboor, symbol);
                }
        }
        void WriteMostncounteredSymbol() {
                int maxCountId = -1;
                int maxcount = 0;
                for (int i = 1; i < 10000; i++) {
                        if (hashArray[i] != nullptr) {
                                if (maxCountId == -1) {
                                        maxCountId = i;
                                        maxcount = hashArray[i]->count;
                                        continue;
                                }
                                if (maxcount < hashArray[i]->count) {
                                        maxCountId = i;
                                        maxcount = hashArray[i]->count;
                                }
                                if (hashArray[i]->next != nullptr) {
                                        Symbol *search = hashArray[i]->next;
                                        while (search != nullptr) {
                                                if (maxcount < search->count) {
                                                        maxCountId = i;
                                                        maxcount = search->count;
                                                }
                                                search = search->next != nullptr ? search->next : nullptr;
                                        }
                                }
                        }
                }
                cout << maxcount;
                hashArray[maxCountId]->PrintSymbol(maxcount);
        }
};
 
int main()
{
        Picture *picture = new Picture();
        picture->SearchSymbolsInPictue();
        picture->WriteMostncounteredSymbol();
        delete picture;
        return 0;
}