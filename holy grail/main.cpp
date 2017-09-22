#include <iostream>
using namespace std;
 
enum Type {
        Town,
        BushSeller,
        BlackKnightCamp,
        NiKnightsCamp,
        Castle,
        HolyGraal
};
 
class Line {
public:
        int length;
        int destinatonId;
        Line() {
                cin >> destinatonId;
                cin >> length;
        }
        ~Line() {}
};
class Node {
private:
        class SearchNode {
        public:
                bool closed;
                int previousId;
                int nextId;
                int weight;
                SearchNode() {
                        closed = false;
                        weight = -1;
                        previousId = -1;
                        nextId = -1;
                }
                ~SearchNode() {}
        };
        int GetIdByType(Type searchType, Node *graph, int n) { //zwraca pierwsze znalezione miejsce o podanym typie
                for (int i = 0; i < n; i++) {
                        if (graph[i].type == searchType) {
                                return i;
                        }
                }
                return 0;
        }
        int GetLowestUnclosedWeightNodeId(SearchNode *searchNodes, int n) {
                SearchNode *search = nullptr;
                int lowest = 0;
                for (int i = 0; i < n; i++) {
                        if ((!searchNodes[i].closed && search == nullptr && searchNodes[i].weight != -1)
                                ||
                                (!searchNodes[i].closed && searchNodes[i].weight != -1 && searchNodes[i].weight < search->weight)) {
                                search = searchNodes + i;
                                lowest = i;
                        }
                }
                return lowest;
        }
public:
        Type type;
        Line *paths;
        int pathsCount;
        Node() {
                int newType;
                cin >> newType;
                type = (Type)newType;
                cin >> pathsCount;
                paths = new Line[pathsCount];
        }
        ~Node() {
                delete[] paths;
        }
        SearchNode* GetShortestLength(int n, int k, Node *graph, Type startType, Type endType, bool print) {
                SearchNode *searchNodes = new SearchNode[n];
                SearchNode *subSearch; // zmienna pomocnicza ze œcie¿k¹ w przypadku natrafienia na rycerzy Ni
                int startId = GetIdByType(startType, graph, n);
                int endId = GetIdByType(endType, graph, n);
                searchNodes[startId].weight = 0;
                int lowestUnclosedId;
                while (!searchNodes[endId].closed) {
                        lowestUnclosedId = GetLowestUnclosedWeightNodeId(searchNodes, n);
                        searchNodes[lowestUnclosedId].closed = true;
                        int neighbourId;
                        for (int i = 0; i < graph[lowestUnclosedId].pathsCount; i++) {
                                neighbourId = graph[lowestUnclosedId].paths[i].destinatonId;
                                if (searchNodes[neighbourId].closed)
                                        continue;
                                else if (searchNodes[neighbourId].weight == -1
                                        ||
                                        searchNodes[lowestUnclosedId].weight + graph[lowestUnclosedId].paths[i].length < searchNodes[neighbourId].weight) {
                                        searchNodes[neighbourId].weight = searchNodes[lowestUnclosedId].weight + graph[lowestUnclosedId].paths[i].length;
                                        if (graph[neighbourId].type == BlackKnightCamp) {
                                                searchNodes[neighbourId].weight += k;
                                        }
                                        else if (graph[neighbourId].type == NiKnightsCamp) {
                                                subSearch = GetShortestLength(n, k, graph, NiKnightsCamp, BushSeller, false);
                                                searchNodes[neighbourId].weight += 2 * subSearch[GetIdByType(BushSeller, graph, n)].weight;
                                        }
                                        searchNodes[neighbourId].previousId = lowestUnclosedId;
                                }
                        }
                }
                SearchNode *printNode = searchNodes + endId;
                int currentNodeId = endId;
                while (printNode->previousId != -1) {
                        (searchNodes + printNode->previousId)->nextId = currentNodeId;
                        currentNodeId = printNode->previousId;
                        printNode = searchNodes + printNode->previousId;
                }
                if (print) {
                        printNode = searchNodes + startId;
                        cout << startId << ' ';
                        while (printNode->nextId != -1) {
                                if (graph[printNode->nextId].type == NiKnightsCamp) {
                                        cout << printNode->nextId << ' ';
                                        SearchNode *printSubNode = subSearch + printNode->nextId;
                                        while (printSubNode->nextId != -1) {
                                                cout << printSubNode->nextId << ' ';
                                                printSubNode = subSearch + printSubNode->nextId;
                                        }
                                        while (printSubNode->previousId != printNode->nextId) {
                                                cout << printSubNode->previousId << ' ';
                                                printSubNode = subSearch + printSubNode->previousId;
                                        }
                                        cout << printNode->nextId << ' ';
                                }
                                else {
                                        cout << printNode->nextId << ' ';
                                }
                                printNode = searchNodes + printNode->nextId;
                        }
                }
                return searchNodes;
        }
};
int main()
{
        int n, k;
        cin >> n >> k;
        Node *graph = new Node[n];
        graph->GetShortestLength(n, k, graph, Castle, HolyGraal, true);
        delete[] graph;
        return 0;
}