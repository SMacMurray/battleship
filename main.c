#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

const int N = 10;



void initialize_grid(int **grid){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			grid[i][j] = 0;		
		}
	}
}

void initialize_front(char **front){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			front[i][j] = 126;
		}
	}
}

void print_grid(int **grid){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			printf("%d ", grid[j][i]);	
		}
		printf("\n");
	}
}

void print_front(char **front){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			printf("%c ", front[j][i]);
		}
		printf("\n");
	}
}


//direction
//0=east
//1=north
//2=west
//3=south


bool seed_ships_helper(int **grid, int x, int y, int ship_size, int dir){
	if (ship_size == 0){
		return true;
	}
	if (x >= 0 && x < N && y >= 0 && y < N){
		if (grid[x][y] == 0){
			if (dir == 0){
				if (seed_ships_helper(grid, x+1, y, ship_size-1, dir)){
					grid[x][y] = 1;
					return true;
				}
			}
			if (dir == 1){
				if (seed_ships_helper(grid, x, y-1, ship_size-1, dir)){
					grid[x][y] = 1;
					return true;
				}
			}	
			if (dir == 2){
				if (seed_ships_helper(grid, x-1, y, ship_size-1, dir)){
					grid[x][y] = 1;
					return true;
				}
			}
			if (dir == 3){
				if (seed_ships_helper(grid, x, y+1, ship_size-1, dir)){
					grid[x][y] = 1;
					return true;
				}
			}
		}
		return false;
	}
	return false;
}

void seed_ships(int **grid){
	int x; int y; int dir; 
	int ships[5] = {5,4,3,3,2};

	srand(time(NULL));
	for (int i = 0; i < 5; i++){
		while (true){
			x = rand() % 10;
			y = rand() % 10;
			dir = rand() % 4;
			if (seed_ships_helper(grid, x, y, ships[i], dir)){
				break;
			}
		}
	}
}


bool test_ships(int **grid){
	for (int i = 0; i < N; i++){
		for (int j = 0; j < N; j++){
			if (grid[j][i] == 1){
				return false;
			}
		}
	}
	return true;
}


void game_loop(int **grid, char **front){
	int x; int y;
	print_front(front);
	while (true){
		scanf("%d %d", &x, &y);
		if (grid[x][y] == 1){
			front[x][y] = 35;
		} 
		if (grid[x][y] == 0){
			front[x][y] = 42;
		}
		grid[x][y] = 2;
		print_front(front);

		if (test_ships(grid)){
			printf("You win.");
			return;
		}
	}
}



int main(){
	int **grid = malloc(sizeof(*grid) * N);
	for (int i = 0; i < N; i++) {
		grid[i] = malloc(sizeof(*grid[i]) * N);
	}

	char **front = malloc(sizeof(*grid) * N);
	for (int i = 0; i < N; i++) {
		front[i] = malloc(sizeof(*front[i]) * N);
	}


	initialize_grid(grid);
	initialize_front(front);
	seed_ships(grid);
	game_loop(grid, front);

	free(grid);
	free(front);
	return 0;
}