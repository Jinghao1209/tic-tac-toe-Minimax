#include <stdio.h>

#pragma region type

#define true 1
#define false 0
#define O 79
#define X 88
typedef int boolean;
enum Scores_t {
    AI_WIN = 1,
    PLAYER_WIN = -1,
    TIE = 0
} Scores;
typedef struct {
    int x;
    int y;
} Map;

#pragma endregion

#pragma region init

int map[3][3] = {
    {0, 0, 0},
    {0, 0, 0},
    {0, 0, 0},
};

boolean playerTurn = false;
int player = X;
int ai = O;

#pragma endregion

void insertBasicMap(Map *tempMap) {
    tempMap->x = 0;
    tempMap->y = 0;
}

boolean isSpace(int x, int y) {
    return map[x][y] == 0;
}

int equals3(int x, int y, int z) {
    return x == y && y == z && x != 0;
}

boolean haveSpace() {
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            if (!map[i][j])
                return 1;
    return 0;
}

void printMap() {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            // 如果是空位
            if (isSpace(i, j))
                printf("%d ", map[i][j]);

            // 不然就是有玩家或者是AI占据了位置，需根据char来输出
            else
                printf("%c ", map[i][j]);
        }
        printf("\n");
    }
}

char playerType(int pl) {
    if (pl == X)
        return X;
    return O;
}

// 如果有赢家，则返回赢家，没有赢家则返回0
// return winner if have winner else return 0
int Winner() {
    // horizontal
    for (int i = 0; i < 3; i++) {
        if (equals3(map[i][0], map[i][1], map[i][2])) {
            return map[i][0];
        }
    }

    // Vertical
    for (int i = 0; i < 3; i++) {
        if (equals3(map[0][i], map[1][i], map[2][i])) {
            return map[0][i];
        }
    }

    // Diagonal
    if (equals3(map[0][0], map[1][1], map[2][2])) {
        return map[0][0];
    }
    if (equals3(map[2][0], map[1][1], map[0][2])) {
        return map[2][0];
    }

    return 0;
}

boolean isValidMove(Map place) {
    if (place.x >= 0 && place.x <= 2 && place.y >= 0 && place.y <= 2) {
        return true;
    } else {
        return false;
    }
}

boolean isPlayerTime() {
    if (playerTurn) {
        playerTurn = false;
        return true;
    } else {
        playerTurn = true;
        return false;
    }
}

void getPlayerMove(int player) {
    Map move;
    int c;
    while ((c = getchar()) != '\0') {
        scanf("%d%d", &move.x, &move.y);
        break;
    }
    if (!isValidMove(move)) {
        printf("Not A Valid Move! Move should be: <int x> <int y>\nYou Enter: <x: %d> <y: %d>\n", move.x, move.y);
        getPlayerMove(player);
    }
    if (!isSpace(move.x, move.y)) {
        printf("<%d %d> is NOT a space!\n", move.x, move.y);
        getPlayerMove(player);
    } else {
        map[move.x][move.y] = playerType(X);
    }
}

int Minimax(int map[3][3], int depth, boolean isMaximizing) {
    int result = Winner();
    if (result) {
        if (result == ai) {
            return AI_WIN;
        } else if (result == player) {
            return PLAYER_WIN;
        } else {
            return TIE;
        }
    }

    if (isMaximizing) {
        int bestScore = -0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (isSpace(i, j)) {
                    map[i][j] = ai;
                    int score = Minimax(map, depth + 1, false);
                    map[i][j] = 0;
                    if (score > bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    } else {
        int bestScore = -0;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                if (isSpace(i, j)) {
                    map[i][j] = player;
                    int score = Minimax(map, depth + 1, true);
                    map[i][j] = 0;
                    if (score < bestScore) {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
}

void bestMove() {
    Map move;
    insertBasicMap(&move);
    int bestScore = -2;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (isSpace(i, j)) {
                map[i][j] = ai;
                int score = Minimax(map, 0, false);
                map[i][j] = 0;
                if (score > bestScore) {
                    bestScore = score;
                    move.x = i;
                    move.y = j;
                }
            }
        }
    }
    map[move.x][move.y] = ai;
}

int main(int argc, char const *argv[]) {
    printf("FIX SOME BUG BUT THE AI STILL IDIOT\n");
    printf("AI FIRST? (Y, N): ");          // default AI first
    char first = getchar();
    if (first == 78) {          // N, Y: 89
        printf("\n\nSOME BUG IN HERE, :(\n\n");
        playerTurn = true;
        printf("\n");
        printf("Map: \n");
        printMap();
    }

    // 如果还有位置，并且没有赢家，执行
    // if still have place and no winner
    while (haveSpace() && !Winner()) {
        if (isPlayerTime()) {
            printf("Is Player Time!\n");

            // 获取玩家步骤
            // get player move
            getPlayerMove(player);
        } else {
            printf("Is AI Time!\n");

            // MINIMAX 算法
            // MINIMAX algorithm
            bestMove();
        }

        // 打印地图
        // print the map
        printMap();
        // 如果还有空间并且没有赢家
        // if still have space and no winner
        haveSpace() && !Winner() ? printf("Next Round\n\n") : 0;
    }

    if (Winner())
        // 所以检测是AI还是玩家
        // check is AI or player
        printf("\nWinner is: %s!\n", playerType(Winner()) == ai ? "AI" : "PLAYER");
    else
        printf("\nTIE!\n");
    return 0;
}