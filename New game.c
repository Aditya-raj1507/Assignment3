#include <stdio.h>
#include <conio.h>
#include <windows.h>
#include <stdlib.h>
#include <time.h>

void gotoxy(int x, int y) {
    COORD c;
    c.X = x;
    c.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

int main() {
    srand(time(0));

    int player = 6;           // player X position (0–10)
    int enemyX = rand() % 11; // enemy starts at random X
    int enemyY = 1;           // enemy Y position
    int bulletX = -1;         // -1 means no bullet
    int bulletY = -1;
    int score = 0;
    int speed = 150;

    // ---- START MENU ----
    system("cls");
    printf("\n\n\n\t\tSHOOTING GAME\n");
    printf("\t\t-------------\n");
    printf("\t\tMove: LEFT / RIGHT\n");
    printf("\t\tShoot: SPACE\n");
    printf("\t\tPress ENTER to START\n");

    while (_getch() != 13);

    // ---- GAME LOOP ----
    while (1) {

        // ----- INPUT -----
        if (_kbhit()) {
            char ch = getch();

            if (ch == 75 && player > 0)     // left
                player--;

            if (ch == 77 && player < 10)    // right
                player++;

            if (ch == 32 && bulletY == -1) { // SPACE for shooting
                bulletX = player;
                bulletY = 8; // just above the player
            }
        }

        // ----- DRAW -----
        system("cls");
        printf(" SCORE: %d\n", score);
        printf("+-----------+\n");

        for (int y = 1; y <= 8; y++) {

            printf("|");

            for (int x = 0; x <= 10; x++) {

                if (x == enemyX && y == enemyY)
                    printf("%c", 1);       // enemy (?)

                else if (x == bulletX && y == bulletY)
                    printf("|");           // bullet

                else
                    printf(" ");
            }
            printf("|\n");
        }

        // ----- PLAYER -----
        printf("|");
        for (int x = 0; x <= 10; x++) {
            if (x == player)
                printf("%c", 30);          // player (?)
            else
                printf(" ");
        }
        printf("|\n");
        printf("+-----------+\n");

        // ----- BULLET MOVE -----
        if (bulletY != -1)
            bulletY--;

        if (bulletY < 1)
            bulletY = -1;

        // ----- ENEMY MOVE -----
        enemyY++;

        // ----- HIT DETECTION -----
        if (bulletX == enemyX && bulletY == enemyY) {
            score++;
            bulletY = -1;              // reset bullet
            enemyY = 1;                // new enemy
            enemyX = rand() % 11;

            if (speed > 40)            // increase difficulty
                speed -= 5;
        }

        // ----- ENEMY REACHES BOTTOM -----
        if (enemyY > 8) {
            printf("\nGAME OVER!\nFINAL SCORE: %d\n", score);
            break;
        }

        Sleep(speed);
    }

    return 0;
}

