
#include <stdio.h>
#include <stdlib.h>
#define WALL '#'
#define EMPTY ' '
#define END 'E'
#define PLAYER 'X'

#define MAX_MAZE_SIZE_X 20
#define MAX_MAZE_SIZE_Y 10
#define MAX_MOVE_COUNT 100

int maze[MAX_MAZE_SIZE_Y][MAX_MAZE_SIZE_X];
int move_count;
int pos_x, pos_y;

void init_maze() {
    FILE *input = fopen("map.txt", "r");
	int i, j;
	for (i = 0; i <= MAX_MAZE_SIZE_Y; i++) {
		for (j = 0; j <= MAX_MAZE_SIZE_X; j++) {
			maze[i][j] = fgetc(input);
		}
	}
	maze[1][1] = PLAYER;
	pos_x = 1;
	pos_y = 1;
	move_count = 0;
}

void print_maze() {
	int i, j;
	for (i = 0; i < MAX_MAZE_SIZE_Y; i++) {
		for (j = 0; j < MAX_MAZE_SIZE_X; j++) {
			printf("%c", maze[i][j]);
		}
		printf("\n");
	}
}

int check_move(int x, int y) {
	if (maze[x][y] != WALL) {
        if (maze[pos_x][pos_y] == END) {
			return 0;
		}
		maze[pos_x][pos_y] = EMPTY;
		maze[x][y] = PLAYER;
		pos_x = x;
		pos_y = y;
		move_count++;
		return 1;
	}
	return -1;
}

int main() {
	char c;
	int ret;
	
	init_maze();
	
	while (move_count < MAX_MOVE_COUNT) {
		print_maze();
		printf("Move (a, s, d, w): ");
		scanf("%c", &c);
		
		switch (c) {
			case 'a':
				ret = check_move(pos_x-1, pos_y);
				break;
			case 's':
				ret = check_move(pos_x, pos_y-1);
				break;
			case 'd':
				ret = check_move(pos_x+1, pos_y);
				break;
			case 'w':
				ret = check_move(pos_x, pos_y+1);
				break;
			default:
				ret = -1;
				break;
		}
		
		if (ret == 0) {
			printf("You made it in %d moves!\n", move_count);
			break;
		}
		else if (ret == -1) {
			printf("Invalid move!\n");
		}
	}
	
	if (move_count == MAX_MOVE_COUNT) {
		printf("You failed to make it in %d moves!\n", move_count);
	}
	
	return 0;
}