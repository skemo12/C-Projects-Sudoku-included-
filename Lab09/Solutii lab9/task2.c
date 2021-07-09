#include <stdio.h>
#include <stdlib.h>

int** allocate_matrix(int n, int m) {
    int **mat = (int**) calloc(n, sizeof(int*));
	for (int i = 0; i < n; i++) {
		mat[i] = (int*) calloc(m, sizeof(int));
    }
    return mat;
}

void free_matrix(int** mat, int n, int m) {
	for (int i = 0; i < n; i++) {
		free(mat[i]);
    }
	free(mat);
}

int** read_matrix(int n, int m) {
    int **mat = allocate_matrix(n, n);
    // int row, column, value;
    int **input = allocate_matrix(m, 3);

	for (int i = 0; i < m; i++) {
		for (int j = 0; j < 3; j++) {
			scanf("%d", &input[i][j]);
        }
        // input[i][0] = row
        // input[i][1] = column
        // input[i][2] = value
        // mat[row][column] = value
        mat[input[i][0]][input[i][1]] = input[i][2];
    }

    free_matrix(input, m, 3);
	return mat;
}

void print_matrix(int** mat, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("%d ", mat[i][j]);
        }
        printf("\n");
    }
}

int main() {
	int n, m;
    scanf("%d", &n);
	scanf("%d", &m);
	int **mat = read_matrix(n, m);
	
    print_matrix(mat, n, n);
	free_matrix(mat, n, n);
	return 0;
}