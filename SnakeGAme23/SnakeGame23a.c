#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <windows.h>
#include <string.h>

#define larghezza 30
#define altezza 20

int gameOver;
int x, y, ciboX, ciboY, score;
int codaX[100], codaY[100];
int ncoda = 0;
int i;
int j;

enum direzione {STOP = 0, LEFT, RIGHT, UP, DOWN};
enum direzione dir;

void stampaMenu(char* nomeUtente) {
    printf("********** MENU **********\n");
    printf("1. Start the game\n");
    printf("2. Instructions\n");
    printf("3. Exit\n");
    printf("**************************\n");
    printf("Hello, %s!\n", nomeUtente);
    printf("Select one option: ");
}

void setup() {
    gameOver = 0;
    dir = STOP;
    x = larghezza / 2;
    y = altezza / 2;
    ciboX = rand() % larghezza;
    ciboY = rand() % altezza;
    score = 0;
    ncoda = 0;
}

void output() {
    COORD coord;
    coord.X = 0;
    coord.Y = 0;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);

    for (int i = 0; i < larghezza + 2; i++) {
        printf("#");
    }
    printf("\n");
    for (int i = 0; i < altezza; i++) {
        for(int j = 0; j < larghezza; j++) {
            if (j == 0) {
                printf("#");
            }
            if (i == y && j == x) {
                printf("O");
            } else if (i == ciboY && j == ciboX) {
                printf("@");
            } else {
                int stampa = 0;
                for (int k = 0; k < ncoda; k++) {
                    if (codaX[k] == j && codaY[k] == i) {
                        printf("o");
                        stampa = 1;
                    }
                }
                if (!stampa) {
                    printf(" ");
                }
            }
            if (j == larghezza - 1) {
                printf("#");
            }
        }
        printf("\n");
    }
    for (int i = 0; i < larghezza + 2; i++) {
        printf("#");
    }
    printf("\n");
    printf("Score: %d\n", score);
}


void comandi() {
    if (_kbhit()) {
        int key = _getch();
        switch (key) {
            case 'a':
                dir = LEFT;
                break;
            case 'd':
                dir = RIGHT;
                break;
            case 'w':
                dir = UP;
                break;
            case 's':
                dir = DOWN;
                break;
            case 'x':
                gameOver = 1;
                break;
            case 224: // Arrow key pressed
                key = _getch(); // Read the actual key code
                switch (key) {
                    case 75: // Left arrow
                        dir = LEFT;
                        break;
                    case 77: // Right arrow
                        dir = RIGHT;
                        break;
                    case 72: // Up arrow
                        dir = UP;
                        break;
                    case 80: // Down arrow
                        dir = DOWN;
                        break;
                    default:
                        break;
                }
                break;
            default:
                break;
        }
    }
}


void algoritmo() {
    static DWORD previousTime = 0;
    DWORD currentTime = GetTickCount();
    DWORD deltaTime = currentTime - previousTime;

    if (deltaTime >= 100) {
        previousTime = currentTime;

        int pX = codaX[0];
        int pY = codaY[0];
        int p2X, p2Y;
        codaX[0] = x;
        codaY[0] = y;
        for (int i = 1; i < ncoda; i++) {
            p2X = codaX[i];
            p2Y = codaY[i];
            codaX[i] = pX;
            codaY[i] = pY;
            pX = p2X;
            pY = p2Y;
        }

        switch (dir) {
            case LEFT:
                x--;
                break;
            case RIGHT:
                x++;
                break;
            case UP:
                y--;
                break;
            case DOWN:
                y++;
                break;
            default:
                break;
        }

        if (x >= larghezza || x < 0 || y >= altezza || y < 0) {
            gameOver = 1;
        }
        for (int i = 1; i < ncoda; i++) {
            if (codaX[i] == x && codaY[i] == y) {
                gameOver = 1;
            }
        }
        if (x == ciboX && y == ciboY) {
            score += 10;
            ciboX = rand() % larghezza;
            ciboY = rand() % altezza;
            ncoda++;
        }
    }
}

void stampaIstruzioni() {
    system("cls");
    printf("********** INSTRUCTIONS **********\n");
    printf("You aim to control the snake (represented by 'O').\n");
    printf("And eat the food (represented by '@') to accumulate points.\n");
    printf("Use the keys 'W' (up), 'A' (left), 'S' (down), 'D' (right)\n");
    printf("To move the snake in the desired direction\n");
    printf("Avoid hitting the edges of the field or colliding with your own tail,\n");
    printf("otherwise, you will lose the game. Reach a score of 100 or more to win!\n");
    printf("Press any key to return to the main menu\n");
    printf("*********************************\n");
    _getch();
}

int main() {
    char nomeUtente[50];
    printf("Select your username: ");
    scanf("%s", nomeUtente);

    int scelta;

    do {
        stampaMenu(nomeUtente);
        scanf("%d", &scelta);

        switch (scelta) {
            case 1:
                setup();
                while (!gameOver) {
                    output();
                    comandi();
                    algoritmo();
                }
                printf("Game Over!\n");
                printf("Score: %d\n", score);
                if (score >= 100)
                    printf("YOU WON\n");
                else{
                    printf("YOU LOST!\n");
                }
                break;
            case 2:
                stampaIstruzioni();
                break;
            case 3:
                printf("Thanks For Playing, %s!\n", nomeUtente);
                break;
            default:
                printf("Option dosen't Exist, Retry\n");
        }
    } while (scelta != 3);

    return 0;
}
