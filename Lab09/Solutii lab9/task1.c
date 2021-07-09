#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int* my_realloc(int* initial, int old_size, int new_size) {
	int* new_array = (int*) calloc(new_size, sizeof(int));
	if (new_array == NULL) {
		return NULL;
	}
	for (int i = 0; i < fmin(new_size, old_size); i++) {
		new_array[i] = initial[i];
	}
	free(initial);
	return new_array;
}

int* read_array(int n) {
	int* array = (int*) calloc(n, sizeof(int));
	if (array == NULL) {
		return NULL;
	}
	for (int i = 0; i < n; i++) {
		scanf("%d", &array[i]);
    }
	return array;
}

void print_array(int* array, int size) {
	for (int i = 0; i < size; i++) {
		printf("%d ", array[i]);
    }
	printf("\n");
}

int main() {
	int old_size, new_size;
	int *initial;

	scanf("%d", &old_size);
	initial = read_array(old_size);
	scanf("%d", &new_size);
	initial = my_realloc(initial, old_size, new_size);
	print_array(initial, new_size);
	free(initial);

	return 0;
}