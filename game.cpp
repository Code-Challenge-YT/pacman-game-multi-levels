#include<iostream>
#include<sys/time.h>
#include<conio.h>
using namespace std;

void drawBoard(int board[19][19], int pacman[2], int score[1], int ghosts[4][4]) {
    for(int i = 0; i < 19; i++) {
        for(int j = 0; j < 19; j++) {
            if(i == pacman[0] && j == pacman[1]) {
                cout << "\033[1;43m  \033[0m";
            } else if(i == ghosts[0][0] && j == ghosts[0][1]) {
                cout << "\033[1;41m^^\033[0m";
            } else if(i == ghosts[1][0] && j == ghosts[1][1]) {
                cout << "\033[1;42m^^\033[0m";
            } else if(i == ghosts[2][0] && j == ghosts[2][1]) {
                cout << "\033[1;44m^^\033[0m";
            } else if(i == ghosts[3][0] && j == ghosts[3][1]) {
                cout << "\033[1;45m^^\033[0m";
            } else {
                cout << (board[i][j] == 0
                    ? "\033[1;40m  \033[0m"
                    : board[i][j] == 1
                        ? "\033[1;46m##\033[0m"
                        : "\033[1;46m  \033[0m");
            }
        }  
        cout << "\n";
    }
    cout << "\n" << score[0] << "/160" << "\n \n ";
}

void move(int board[19][19], int pacman[2], int pacmanDir[2], int score[1]) {
    int dir1 = pacman[0] + pacmanDir[0];
    int dir2 = pacman[1] + pacmanDir[1];
    if(board[dir1][dir2] != 0) {
        pacman[0] += pacmanDir[0];
        pacman[1] += pacmanDir[1];
        if(board[dir1][dir2] == 1) {
            board[dir1][dir2] = 2;
            score[0] += 1;
        }
    }
}

void checkKeyPress(int board[19][19], int pacman[2], int pacmanDir[2], int dirBuffer[2]) {
    if(kbhit()) {
        int key = getch(); // 68 Left, 67 Right, 66 Down, 65 Up
        if(key == 68) {
            if(board[pacman[0]+0][pacman[1]-1] != 0) {
                pacmanDir[0] = 0; pacmanDir[1] = -1;
            } else {
                dirBuffer[0] = 0; dirBuffer[1] = -1;
            }
        } else if(key == 67) {
            if(board[pacman[0]+0][pacman[1]+1] != 0) {
                pacmanDir[0] = 0; pacmanDir[1] = +1;
            } else {
                dirBuffer[0] = 0; dirBuffer[1] = +1;
            }
        } else if(key == 66) {
            if(board[pacman[0]+1][pacman[1]+0] != 0) {
                pacmanDir[0] = +1; pacmanDir[1] = 0;
            } else {
                dirBuffer[0] = +1; dirBuffer[1] = 0;
            }
        } else if(key == 65) {
            if(board[pacman[0]-1][pacman[1]+0] != 0) {
                pacmanDir[0] = -1; pacmanDir[1] = 0;
            } else {
                dirBuffer[0] = -1; dirBuffer[1] = 0;
            }
        }
    }
}

void moveDirBufferToDir(int board[19][19], int pacman[2], int pacmanDir[2], int dirBuffer[2]) {
    if((dirBuffer[0] != 0 || dirBuffer[1] != 0) && (board[pacman[0]+dirBuffer[0]][pacman[1]+dirBuffer[1]] != 0)) {
        pacmanDir[0] = dirBuffer[0];
        pacmanDir[1] = dirBuffer[1];
        dirBuffer[0] = 0;
        dirBuffer[1] = 0;
    }
}

void ghostsMove(int board[19][19], int ghosts[4][4], int pacman[2]) {
    for(int i = 0; i < 4; i ++) {
        if(board[ghosts[i][0]+ghosts[i][2]][ghosts[i][1]+ghosts[i][3]] != 0) {
            ghosts[i][0] += ghosts[i][2];
            ghosts[i][1] += ghosts[i][3];
        } else {
            bool moved = false;
            while(!moved) {
                int random = (rand() % 4);
                if(random == 0) {
                    if(board[ghosts[i][0]+0][ghosts[i][1]-1] != 0) {
                        ghosts[i][2] = 0;
                        ghosts[i][3] = -1;
                        moved = true;
                    } 
                } else if(random == 1) {
                    if(board[ghosts[i][0]+1][ghosts[i][1]+0] != 0) {
                        ghosts[i][2] = 1;
                        ghosts[i][3] = 0;
                        moved = true;
                    } 
                } else if(random == 2) {
                    if(board[ghosts[i][0]+0][ghosts[i][1]+1] != 0) {
                        ghosts[i][2] = 0;
                        ghosts[i][3] = 1;
                        moved = true;
                    } 
                } else if(random == 3) {
                    if(board[ghosts[i][0]-1][ghosts[i][1]+0] != 0) {
                        ghosts[i][2] = -1;
                        ghosts[i][3] = 0;
                        moved = true;
                    } 
                } 
            }
        }
    }
}

void checkEnd(int pacman[2], int ghosts[4][4], int gameEnd[1]) {
    for(int i = 0; i < 4; i++) {
        if((ghosts[i][0] == pacman[0]) && (ghosts[i][1] == pacman[1])) {
            gameEnd[0] = 1;
        }
    }
}

int main() {
    // 0 حائط
    // 1 خانة مع نقطة
    // 2 خانة فارغة
    int boards[3][19][19] = {{
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 1, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 1, 0, 0},
        {0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 1, 1, 0, 1, 1, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
    }, {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0},
        {0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
    }, {
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 1, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 1, 0, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 0, 0, 1, 0, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0},
        {0, 1, 0, 0, 1, 1, 1, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0, 0, 0, 1, 0},
        {0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0},
        {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}, 
    }};
    int pacman[2] = {17, 9};
    int pacmanDir[2] = {0, 1}; // 0, -1, 1
    int dirBuffer[2] = {0, 0};
    int score[1] = {0};
    int ghosts[4][4] = {{7, 7, 0, 1}, {7, 11, 0, -1}, {11, 7, 0, -1}, {11, 11, 0, +1}};
    int gameEnd[1] = {2};
    int level = 2;
    struct timeval time_now{};
    gettimeofday(&time_now, nullptr);
    time_t start = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
    while(gameEnd[0] == 2) {
        checkKeyPress(boards[level], pacman, pacmanDir, dirBuffer);
        gettimeofday(&time_now, nullptr);
        time_t timeNow = (time_now.tv_sec * 1000) + (time_now.tv_usec / 1000);
        if(timeNow - start > 200) {
            checkEnd(pacman, ghosts, gameEnd);
            moveDirBufferToDir(boards[level], pacman, pacmanDir, dirBuffer);
            move(boards[level], pacman, pacmanDir, score);
            ghostsMove(boards[level], ghosts, pacman);
            drawBoard(boards[level], pacman, score, ghosts);
            start = timeNow;
            if(score[0] == 160) {
                if(level < 2) {
                    pacman[0] = 17; pacman[1] = 9;
                    pacmanDir[0] = 0; pacmanDir[1] = 1;
                    dirBuffer[0] = 0; dirBuffer[1] = 0;
                    score[0] = 0;
                    ghosts[0][0] = 7; ghosts[0][1] = 7; ghosts[0][2] = 0; ghosts[0][3] = 1;
                    ghosts[1][0] = 7; ghosts[1][1] = 11; ghosts[1][2] = 0; ghosts[1][3] = -1;
                    ghosts[2][0] = 11; ghosts[2][1] = 7; ghosts[2][2] = 0; ghosts[2][3] = -1;
                    ghosts[3][0] = 11; ghosts[3][1] = 11; ghosts[3][2] = 0; ghosts[3][3] = 1;
                    level += 1;
                } else {
                    gameEnd[0] = 0;
                }
            }
        }
    }
    return gameEnd[0];
}