#include <iostream>
using namespace std;
 
class Board;
 
class Piece {
public:
        int width, height, rotationsCount;
        char ***pieceTemplate; //zawiera wszystkie obroty klocka
        bool mirrored, aleadyUsed;
        Board *board;
        Piece() {
                aleadyUsed = false;
                cin >> width;
                cin >> height;
                if (width == 1 && height == 1) {
                        rotationsCount = 1;
                }
                else if (width == 1 || height == 1) { //klocek o wysokoœci/szerokoœci 1 ma tylko 2 mo¿liwoœci obrotu
                        rotationsCount = 2;
                }
                else {
                        rotationsCount = 8;
                }
                char **tmpTemplate = new char *[height];
                for (int y = 0; y < height; y++) {
                        tmpTemplate[y] = new char[width];
                        for (int x = 0; x < width; x++) {
                                cin >> tmpTemplate[y][x];
                        }
                }
                if (rotationsCount == 1) {
                        pieceTemplate = new char **[rotationsCount];
                        pieceTemplate[0] = tmpTemplate;
                        return;
                }
                char **tmpTemplate2 = RotateRight(tmpTemplate, width, height); // obrót w prawo o 90 stopni
                if (CompareRotations(tmpTemplate, tmpTemplate2)) { // jeœli po obrocie jest taki sam
                        rotationsCount = 1;
                        pieceTemplate = new char **[rotationsCount];
                        pieceTemplate[0] = tmpTemplate;
                        for (int y = 0; y < width; y++)
                                delete[] tmpTemplate2[y];
                        delete[] tmpTemplate2;
                        return;
                }
                if (rotationsCount == 2) {
                        rotationsCount = 2;
                        pieceTemplate = new char **[rotationsCount];
                        pieceTemplate[0] = tmpTemplate;
                        pieceTemplate[1] = tmpTemplate2;
                        return;
                }
                char **tmpTemplate3 = RotateRight(tmpTemplate2, height, width); // obrót o 180 stopni
                if (CompareRotations(tmpTemplate, tmpTemplate3)) { //jeœli obrócone o 180 stopni s¹ takie same
                        rotationsCount = 4;
                        pieceTemplate = new char **[rotationsCount];
                        pieceTemplate[0] = tmpTemplate;
                        pieceTemplate[1] = tmpTemplate2;
                        pieceTemplate[2] = Mirror(tmpTemplate); // odbicie lustrzane pierwotnego kszta³tu
                        pieceTemplate[3] = RotateRight(tmpTemplate, width, height);
                        for (int y = 0; y < height; y++)
                                delete[] tmpTemplate3[y];
                        delete[] tmpTemplate3;
                        return;
                }
                char **tmpTemplate4 = RotateRight(tmpTemplate3, width, height); // obót o 270 stopni
                char **mirrored = Mirror(tmpTemplate); // odbicie lustrzane pierwotnego kszta³tu
                if (CompareRotations(tmpTemplate, mirrored) || (width == height && CompareRotations(tmpTemplate4, mirrored))) {
                        rotationsCount = 4;
                        pieceTemplate = new char **[rotationsCount];
                        pieceTemplate[0] = tmpTemplate;
                        pieceTemplate[1] = tmpTemplate2;
                        pieceTemplate[2] = tmpTemplate3;
                        pieceTemplate[3] = tmpTemplate4;
                        for (int y = 0; y < height; y++)
                                delete[] mirrored[y];
                        delete[] mirrored;
                        return;
                }
                rotationsCount = 8;
                pieceTemplate = new char **[rotationsCount];
                pieceTemplate[0] = tmpTemplate;
                pieceTemplate[1] = tmpTemplate2;
                pieceTemplate[2] = tmpTemplate3;
                pieceTemplate[3] = tmpTemplate4;
                pieceTemplate[4] = mirrored;
                pieceTemplate[5] = RotateRight(mirrored, width, height); // obrót odbicia w lewo o 90 stopni
                pieceTemplate[6] = RotateRight(pieceTemplate[5], height, width); // obrót odbicia o 180 stopni
                pieceTemplate[7] = RotateRight(pieceTemplate[6], width, height); // obrót obrót o 270 stopni
        };
        ~Piece() {
                for (int i = 0; i < rotationsCount; i++) {
                        int tmpHeight = height;
                        if (i % 2) {
                                tmpHeight = width;
                        }
                        for (int y = 0; y < tmpHeight; y++) {
                                delete[] pieceTemplate[i][y];
                        }
                        delete[] pieceTemplate[i];
                }
                delete[] pieceTemplate;
        }
        char** RotateRight(char **tmplt, int templateWidth, int templateHeight) {
                char **rotatedTemplate = new char *[templateWidth];
                for (int y = 0; y < templateWidth; y++) {
                        rotatedTemplate[y] = new char[templateHeight];
                }
                int newX = 0;
                int newY = 0;
                for (int x = 0; x < templateWidth; x++)
                {
                        for (int y = templateHeight - 1; y >= 0; y--) {
                                rotatedTemplate[newY][newX] = tmplt[y][x];
                                newX++;
                                if (newX == templateHeight)
                                        newX = 0;
                        }
                        newY++;
                }
                return rotatedTemplate;
        }
        char** Mirror(char **tmplt) {
                char **mirroredTemplate = new char *[height];
                for (int y = 0; y < height; y++) {
                        mirroredTemplate[y] = new char[width];
                }
                int newX;
                for (int y = 0; y < height; y++) {
                        newX = 0;
                        for (int x = width - 1; x >= 0; x--) {
                                mirroredTemplate[y][newX] = tmplt[y][x];
                                newX++;
                        }
                }
                return mirroredTemplate;
        }
        bool MatchPiece(int boardY, int boardX, int rotateId);
        bool CompareRotations(char **tmplt1, char **tmplt2) {
                for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                                if (tmplt1[y][x] != tmplt2[y][x])
                                        return false;
                        }
                }
                return true;
        }
};
 
class Board {
public:
        int width, height, piecesCount;
        Piece *pieces;
        char **boardTemplate;
        bool solved;
        Board() {
                solved = false;
                cin >> width;
                cin >> height;
                cin >> piecesCount;
                pieces = new Piece[piecesCount];
                for (int i = 0; i < piecesCount; i++)
                        pieces[i].board = this;
                boardTemplate = new char*[height];
                for (int y = 0; y < height; y++) {
                        boardTemplate[y] = new char[width];
                        for (int x = 0; x < width; x++) {
                                cin >> boardTemplate[y][x];
                        }
                }
        }
        ~Board() {
                delete[] pieces;
                for (int i = 0; i < height; i++)
                        delete[] boardTemplate[i];
                delete[] boardTemplate;
        };
        void PrintPiece(int boardY, int boardX, int pieceId, int rotateId) {
                int pieceWidth = pieces[pieceId].width;
                int pieceHeight = pieces[pieceId].height;
                if (rotateId % 2 != 0) { // jeœli klocek jest obrócony to zamieniamy jego sprawdzan¹ szerokoœæ z wysokoœæi¹
                        pieceWidth = pieces[pieceId].height;
                        pieceHeight = pieces[pieceId].width;
                }
                for (int y = 0; y < pieceHeight; y++) {
                        for (int x = 0; x < pieceWidth; x++) {
                                if (pieces[pieceId].pieceTemplate[rotateId][y][x] == 'X') {
                                        boardTemplate[boardY + y][boardX + x] = 'A' + pieceId;
                                }
                        }
                }
                pieces[pieceId].aleadyUsed = true;
        }
        void RemovePiece(int pieceId) {
                for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                                if (boardTemplate[y][x] == 'A' + pieceId) {
                                        boardTemplate[y][x] = 'X';
                                }
                        }
                }
                pieces[pieceId].aleadyUsed = false;
        }
        bool CheckIfSolved() {
                for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                                if (boardTemplate[y][x] == 'X')
                                        return false;
                        }
                }
                return true;
        }
        bool CheckRow(int y) {
                for (int x = 0; x < width; x++) {
                        if (boardTemplate[y][x] == 'X')
                                return false;
                }
                return true;
        }
        bool CheckColumn(int x) {
                for (int y = 0; y < height; y++) {
                        if (boardTemplate[y][x] == 'X')
                                return false;
                }
                return true;
        }
        bool CheckNeighboors(int y, int x) {
                if (boardTemplate[y][x] == 'X')
                        return true;
                if (y != 0 && boardTemplate[y - 1][x] == 'X')
                        return true;
                if (y != height - 1 && boardTemplate[y + 1][x] == 'X')
                        return true;
                if (x != 0 && boardTemplate[y][x-1] == 'X')
                        return true;
                if (x != width - 1 && boardTemplate[y][x+1] == 'X')
                        return true;
 
                return false;
        }
        void PrintBoard() {
                for (int y = 0; y < height; y++) {
                        for (int x = 0; x < width; x++) {
                                cout << boardTemplate[y][x];
                        }
                        cout << endl;
                }
        }
        void SolvePixel(int, int, bool);
};
 
bool Piece::MatchPiece(int boardY, int boardX, int rotateId) {
        int pieceWidth = width;
        int pieceHeight = height;;
        if (rotateId % 2 != 0) { // jeœli klocek jest obrócony to zamieniamy jego sprawdzan¹ szerokoœæ z wysokoœci¹
                pieceWidth = height;
                pieceHeight = width;
        }
        if (boardX + pieceWidth > board->width || boardY + pieceHeight > board->height) // klocek nie mieœcy siê na porównywanym polu na planszy
                return false;
        for (int y = 0; y < pieceHeight; y++) {
                for (int x = 0; x < pieceWidth; x++) {
                        char boardPixel = board->boardTemplate[boardY + y][boardX + x];
                        char piecePixel = pieceTemplate[rotateId][y][x];
                        if (boardPixel == '.' && piecePixel == 'X')
                                return false;
                        if (boardPixel != '.' && boardPixel != 'X' && piecePixel != '.') //jeœli pole na planszy jest wype³nione innym klockiem
                                return false;
                }
        }
        return true;
}
 
void Board::SolvePixel(int y, int x, bool moveHorizontally) {
        if (x == width - 1 && y == height - 1 && CheckIfSolved()) {
                PrintBoard();
                solved = true;
                return;
        }
 
        if (CheckNeighboors(y,x)) // prawda jeœli pixel lub jakiœ jego s¹siad posiada miejsce na klocek
        {
                for (int i = 0; i < piecesCount; i++) {
                        if (!pieces[i].aleadyUsed) {
                                for (int rotation = 0; rotation < pieces[i].rotationsCount; rotation++) {
                                        if (pieces[i].MatchPiece(y, x, rotation)) {
                                                PrintPiece(y, x, i, rotation);
                                                if ((moveHorizontally && x == width - 1) || (!moveHorizontally && y == height - 1)) {
                                                        if (moveHorizontally && CheckRow(y)) {
                                                                SolvePixel(y + 1, 0, moveHorizontally);
                                                        }
                                                        else if (!moveHorizontally && CheckColumn(x)) {
                                                                SolvePixel(0, x + 1, moveHorizontally);
                                                        }
                                                        else {
                                                                RemovePiece(i);
                                                                return;
                                                        }
                                                }
                                                else {
                                                        if (moveHorizontally)
                                                                SolvePixel(y, x + 1, moveHorizontally);
                                                        else
                                                                SolvePixel(y + 1, x, moveHorizontally);
                                                }
                                                if (solved)
                                                        return;
                                                RemovePiece(i);
                                        }
                                }
                        }
                }
        }
 
        if ((moveHorizontally && x == width - 1) || (!moveHorizontally && y == height - 1)) {
                if (moveHorizontally && CheckRow(y)) {
                        SolvePixel(y + 1, 0, moveHorizontally);
                }
                else if (!moveHorizontally && CheckColumn(x)) {
                        SolvePixel(0, x + 1, moveHorizontally);
                }
                return;
        }
        if (moveHorizontally)
                SolvePixel(y, x + 1, moveHorizontally);
        else
                SolvePixel(y + 1, x, moveHorizontally);
        if (solved)
                return;
}
 
int main()
{
        Board *board = new Board();
        board->SolvePixel(0, 0, board->width < board->height);
        delete board;
        return 0;
}