#include <stdio.h>
#include <stdlib.h>

int*** read_cube(int n) {
	int*** cube = (int***) calloc(n, sizeof(int**));
	for (int i = 0; i < n; i++) {
		cube[i] = (int**) calloc(n, sizeof(int*));
		for (int j = 0; j < n; j++) {
			cube[i][j] = (int*) calloc(n, sizeof(int));
            for (int k = 0; k < n; k++) {
                scanf("%d", &cube[i][j][k]);
            }
		}
	}
	return cube;
}

void print_upper_slice(int*** cube, int n) {
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			printf("%d ", cube[i][0][j]);
        }
		printf("\n");
	}
    printf("\n");
}

void print_front_slice(int*** cube, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", cube[0][i][j]);
		}
		printf("\n");
	}
    printf("\n");
}

void print_lower_slice(int*** cube, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			printf("%d ", cube[i][n - 1][j]);
		}
		printf("\n");	
	}
    printf("\n");
}

void print_back_slice(int*** cube, int n) {
	for (int i = n - 1; i >= 0; i--) {
		for (int j = 0; j < n; j++) {
			printf("%d ", cube[n - 1][i][j]);
        }
		printf("\n");
	}
}

void free_cube(int ***cube, int n) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			free(cube[i][j]);
        }
		free(cube[i]);
	}
	free(cube);
}

int main() {
	int n;
	scanf("%d", &n);
	int ***cube = read_cube(n);

	print_upper_slice(cube, n);
	print_front_slice(cube, n);
	print_lower_slice(cube, n);
	print_back_slice(cube, n);
	free_cube(cube, n);
	return 0;
}