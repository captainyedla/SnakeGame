#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;

const int width = 80;
const int height = 20;

int x, y; // Snake head position
int fruitCordX, fruitCordY; // Food position
int playerScore;
int snakeTailX[100], snakeTailY[100]; // Snake tail position arrays
int snakeTailLen;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };
Direction sDir;
bool isGameOver;

void GameInit() {
    isGameOver = false;
    sDir = STOP;
    x = width / 2;
    y = height / 2;
    fruitCordX = rand() % width;
    fruitCordY = rand() % height;
    playerScore = 0;
    snakeTailLen = 0;
}

void GameRender(string playerName) {
    system("cls");

    for (int i = 0; i < width + 2; i++) cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++) {
            if (j == 0 || j == width)
                cout << "|";
            else if (i == y && j == x)
                cout << "O";
            else if (i == fruitCordY && j == fruitCordX)
                cout << "#";
            else {
                bool isTail = false;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        cout << "o";
                        isTail = true;
                    }
                }
                if (!isTail) cout << " ";
            }
        }
        cout << endl;
    }

    for (int i = 0; i < width + 2; i++) cout << "-";
    cout << endl;

    cout << playerName << "'s Score: " << playerScore << endl;
}

void UpdateGame() {
    int prevX = snakeTailX[0], prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = x;
    snakeTailY[0] = y;

    for (int i = 1; i < snakeTailLen; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (sDir) {
        case LEFT:  x--; break;
        case RIGHT: x++; break;
        case UP:    y--; break;
        case DOWN:  y++; break;
        default: break;
    }

    if (x >= width || x < 0 || y >= height || y < 0)
        isGameOver = true;

    for (int i = 0; i < snakeTailLen; i++)
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            isGameOver = true;

    if (x == fruitCordX && y == fruitCordY) {
        playerScore += 10;
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        snakeTailLen++;
    }
}

int SetDifficulty() {
    int delay, choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: Hard\n";
    cout << "NOTE: Any other input sets it to Medium by default.\nChoose difficulty level: ";
    cin >> choice;
    switch (choice) {
        case 1: delay = 150; break;
        case 2: delay = 100; break;
        case 3: delay = 50; break;
        default: delay = 100;
    }
    return delay;
}

void UserInput() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a': sDir = LEFT; break;
            case 'd': sDir = RIGHT; break;
            case 'w': sDir = UP; break;
            case 's': sDir = DOWN; break;
            case 'x': isGameOver = true; break;
        }
    }
}

int main() {
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;

    int delay = SetDifficulty();
    GameInit();

    while (!isGameOver) {
        GameRender(playerName);
        UserInput();
        UpdateGame();
        Sleep(delay);
    }

    return 0;
}
