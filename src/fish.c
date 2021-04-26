#include <stdio.h>
#include <stdbool.h>

bool isValidMove(char gameBoard[7][7], int pickX, int pickY, int posX, int posY);
bool isOver(char gameBoard[7][7], int x, int y);
bool isStraight(int posX, int posY, int i, int i1);

int position = 0;      // Global variable to keep track of the position. 
int playerPoint = 0;   // Global variable to keep track of the Player's points.
int aiPoint = 0;       // Global variable to keep track of AI's points.

// Convert the characters on the gameBoard to points.
int convertPoints(int x, int y){
    int points;
    char gameBoard[7][7] = {
            ' ', '1', '2', '3', '4', '5', '6',
            '1', '1', '1', '1', '1', '1', '1',
            '2', '1', '2', '2', '2', '2', '1',
            '3', '1', '2', '3', '3', '2', '1',
            '4', '1', '2', '3', '3', '2', '1',
            '5', '1', '2', '2', '2', '2', '1',
            '6', '1', '1', '1', '1', '1', '1'
    };

    if(gameBoard[x][y] == 49){
        points = 1;
    }
    else if(gameBoard[x][y] == 50){
        points = 2;
    }
    else if(gameBoard[x][y] == 51){
        points = 3;
    }
    return points;
}


int main() {
    int i,j, posX, posY,p1Points, pickX, pickY, curX, curY, aiPoints, aiX, aiY;
    char gameBoard[7][7] = {
            ' ', '1', '2', '3', '4', '5', '6',
            '1', '1', '1', '1', '1', '1', '1',
            '2', '1', '2', '2', '2', '2', '1',
            '3', '1', '2', '3', '3', '2', '1',
            '4', '1', '2', '3', '3', '2', '1',
            '5', '1', '2', '2', '2', '2', '1',
            '6', '1', '1', '1', '1', '1', '1'
    };
    for(i=0; i<7; i++) {
        for(j=0;j<7;j++) {
            printf("%-2c ", gameBoard[i][j]);
            if(j==6){
                printf("\n");
            }
        }
    }
    printf("Which Row:\n");
    scanf("%d", &posX);
    printf("Which Column:\n");
    scanf("%d", &posY);

    p1Points = convertPoints(posX,posY);
    playerPoint += p1Points;
    gameBoard[posX][posY] = 'P';


    for(i=0; i<7; i++) {
        for(j=0;j<7;j++) {
            printf("%-2c ", gameBoard[i][j]);
            if(j==6){
                printf("\n");
            }
        }
    }
    printf("\n");

    if(gameBoard[1][1] != 'P') {
        gameBoard[1][1] = 'A';
        aiPoints = convertPoints(1, 1);
        aiPoint += aiPoints;
        aiX = 1;
        aiY = 1;
    } else if(gameBoard[1][2] != 'P'){
        gameBoard[1][2] = 'A';
        aiPoints = convertPoints(1, 2);
        aiPoint += aiPoints;
        aiX = 1;
        aiY = 2;
    }
    for(i=0; i<7; i++) {
        for(j=0;j<7;j++) {
            printf("%-2c ", gameBoard[i][j]);
            if(j==6){
                printf("\n");
            }
        }
    }

    int turn = 0;
    bool gameOver = false;
    curX = posX;
    curY = posY;
    while(!gameOver){
    if(turn%2 == 0){
        if(isOver(gameBoard, curX,curY)){
            gameOver = true;
            break;
        }
    printf("Which Row:\n");
    scanf("%d", &pickX);
    printf("Which Column:\n");
    scanf("%d", &pickY);
    if(isValidMove(gameBoard,pickX,pickY,curX,curY)) {
        gameBoard[curX][curY] = '.';
        gameBoard[pickX][pickY] = 'P';
        playerPoint += convertPoints(pickX,pickY);
        curX = pickX;
        curY = pickY;
    }else {
        printf("Invalid move, your turn is skipped");  // If the move is invalid than the player/AI turn is skipped.
        printf("\n");
    }

    for(i=0; i<7; i++) {
        for(j=0;j<7;j++) {
            printf("%-2c ", gameBoard[i][j]);
            if(j==6){
                printf("\n");
            }
        }
    }

    }
    if(turn%2==1){
        if(isOver(gameBoard, aiX,aiY)) {
            gameOver = true;
            break;
        }
        bool moved = false;
        int value = 3;
        while(value != 0){
            for(int n = 1; n < 7; n++){
                for(int m = 1; m < 7; m++){
                    if(isValidMove(gameBoard, n, m, aiX, aiY)) {
                        if (convertPoints(n,m) == value) {
                            gameBoard[n][m] = 'A';
                            gameBoard[aiX][aiY] = '.';
                            aiPoints += convertPoints(n, m);
                            aiX = n;
                            aiY = m;
                            moved = true;
                            printf("\n");
                            for(i=0; i<7; i++) {
                                for(j=0;j<7;j++) {
                                    printf("%-2c ", gameBoard[i][j]);
                                    if(j==6){
                                        printf("\n");
                                    }
                                }
                            }
                            break;
                        }
                    }
                }
                if(moved){
                    break;
                }
            }
            if(moved){
                break;
            }
            value--;
        }
    }
    turn++;
    }
    printf("Player Points: %d",playerPoint);
    printf("\n");
    printf("Ai Points: %d",aiPoints);
    printf("\n");
    if(aiPoints > playerPoint){
        printf("The Ai won");
    }
    if(playerPoint > aiPoints){
        printf("The Player Won");
    }
    if(playerPoint == aiPoints){
        printf("The game was a tie");
    }
}

// Determine is the next row/column the player/AI choses is a valid move from 
// it's current location. 
// Takes in the gameBoard, the location the player/AI choses (pickX and pickY) 
// and the position of the player/AI (posX and posY).
bool isValidMove(char gameBoard[7][7], int pickX, int pickY, int posX, int posY) {
    if(pickX == posX && pickY == posY){
        return false;
    }
    if(isStraight(pickX, pickY, posX, posY)) {
        if(position == 2){
            int x = posX;
            if(x < pickX){
                while(x != pickX){
                    x++;
                    if(gameBoard[x][posY] == '.' ){
                        return false;
                    }
                    if(gameBoard[x][posY] == 'P' ){
                        return false;
                    }
                    if(gameBoard[x][posY] == 'A' ){
                        return false;
                    }
                }
            }
            if(x > pickX){
                while(x != pickX){
                    x--;
                    if(gameBoard[x][posY] == '.' ){
                        return false;
                    }
                    if(gameBoard[x][posY] == 'P' ){
                        return false;
                    }
                    if(gameBoard[x][posY] == 'A' ){
                        return false;
                    }
                }
            }
            return true;
        }
        if(position == 1){
            int y = posY;
            if(y < pickY){
                while(y != pickY){
                    y++;
                    if(gameBoard[posX][y] == '.'){
                        return false;
                    }
                    if(gameBoard[posX][y] == 'P'){
                        return false;
                    }
                    if(gameBoard[posX][y] == 'A'){
                        return false;
                    }
                }
            }
            if(y > pickY){
                while(y != pickY){
                    y--;
                    if(gameBoard[posX][y] == '.'){
                        return false;
                    }
                    if(gameBoard[posX][y] == 'P'){
                        return false;
                    }
                    if(gameBoard[posX][y] == 'A'){
                        return false;
                    }
                }
            }
            return true;
        }
        if(position == 3){
            int x = posX;
            int y = posY;
            while (x != pickX && y != pickY) {
                x++;
                y++;
                if (gameBoard[x][y] == '.') {
                    return false;
                }
                if (gameBoard[x][y] == 'P') {
                    return false;
                }
                if (gameBoard[x][y] == 'A') {
                    return false;
                }
            }
            return true;
        }
        if(position == 4){
            int x = posX;
            int y = posY;
            while (x != pickX && y != pickY) {
                x--;
                y--;
                if (gameBoard[x][y] == '.') {
                    return false;
                }
                if (gameBoard[x][y] == 'P') {
                    return false;
                }
                if (gameBoard[x][y] == 'A') {
                    return false;
                }
            }
            return true;
        }
        if(position == 5){
            int x = posX;
            int y = posY;
            while (x != pickX && y != pickY) {
                x++;
                y--;
                if (gameBoard[x][y] == '.') {
                    return false;
                }
                if (gameBoard[x][y] == 'P') {
                    return false;
                }
                if (gameBoard[x][y] == 'A') {
                    return false;
                }
            }
            return true;
        }
        if(position == 6){
            int x = posX;
            int y = posY;
            while (x != pickX && y != pickY) {
                x--;
                y++;
                if (gameBoard[x][y] == '.') {
                    return false;
                }
                if (gameBoard[x][y] == 'P') {
                    return false;
                }
                if (gameBoard[x][y] == 'A') {
                    return false;
                }
            }
            return true;
        }
    }
    return false;
}

// Determines if the path from chosen row/column to
// current row/column is a straight line. 
// Takes in the Row(pickX) and Column(pickY) the player
// desires. Takes in the Current Row (curX) and Current 
// Column (curY) the player or AI is on. F
bool isStraight(int pickX, int pickY, int curX, int curY) {
    if (pickX == curX && pickY <= 6 && pickY >= 1) {
        position = 1;
        return true;
    }
    if (pickY == curY && pickX <= 6 && pickX >= 1) {
        position = 2;
        return true;
    }
    int x = curX;
    int y = curY;
    while (x <= 6 && y <= 6) {
        x++;
        y++;
        if (x == pickX && y == pickY) {
            position = 3;
            return true;
        }
    }
    x = curX;
    y = curY;
    while (x >= 0 && y >= 0) {
        x--;
        y--;
        if (x == pickX && y == pickY) {
            position = 4;
            return true;
        }
    }
    x = curX;
    y = curY;
    while (x <= 6 && y >= 0) {
        x++;
        y--;
        if (x == pickX  && y == pickY ) {
            position = 5;
            return true;
        }
    }

    x = curX;
    y = curY;
    while (x >= 0 && y <= 6) {
        x--;
        y++;
        if (x == pickX && y == pickY) {
            position = 6;
            return true;
        }
    }
    return false;
}
// If there are no moves available, then the game is over.
// The points are tallied up and the winner is determined. 
bool isOver(char gameBoard[7][7], int x, int y){
    for(int i = 1; i < 7; i++){
        for(int j = 1; j < 7; j++){
            if(isValidMove(gameBoard, i,j,x,y)){
                return false;
            }
        }
    }
    return true;
}

