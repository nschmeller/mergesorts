#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LINE_PRINT_LIM 20

double rand_double();
int is_sorted(double* a, int len);
double* mergesort_t(double* input, int len);
double* merge(double* a, double* b, int alen, int blen);

double rand_double() {
	return rand() / (double) RAND_MAX;
}

double* merge(double* a, double* b, int alen, int blen) {
	double* c;
	int i;
	int j;
	int k;

	c = (double*) malloc(sizeof(double) * (alen + blen));
	i = 0;
	j = 0;
	for (k = 0; k < alen + blen; k++) {
		if (i >= alen) c[k] = b[j++];
		else if (j >= blen) c[k] = a[i++];
		else if (a[i] <= b[j]) c[k] = a[i++];
		else c[k] = b[j++];
	}

	free(a);
	free(b);

	return c;
}

double* mergesort_t(double* input, int len) {
	double* a;
	double* b;
	int i;

	if (len <= 1) return input;

	a = (double*) malloc(sizeof(double) * (len / 2));
	if (a == NULL) {
		printf("subarray malloc failed\n");
		exit(1);
	}

	b = (double*) malloc(sizeof(double) * (len - (len / 2)));
	if (b == NULL) {
		printf("subarray malloc failed\n");
		exit(1);
	}

	for (i = 0; i < len / 2; i++) {
		a[i] = input[i];
	}
	for (i = 0; i < len - (len / 2); i++) {
		b[i] = input[i + (len / 2)];
	}

	return merge(mergesort_t(a, len / 2), 
		mergesort_t(b, len - (len / 2)), len / 2, len - (len / 2));
}

int is_sorted(double* a, int len) {
	int i;

	for (i = 1; i < len; i++) {
		if (a[i] < a[i-1]) return 0;
	}
	return 1;
}

int main(int argc, char **argv) {
	int N;
	double *a;
	int i;

	N = atoi(argv[1]);
	a = (double*) malloc(sizeof(double) * N);

	if (a == NULL) {
		printf("main malloc failed\n");
		exit(1);
	}

	srand(time(NULL));
	for (i = 0; i < N; i++) {
		a[i] = rand_double();	}

	a = mergesort_t(a, N);

	/* make this human readable! */

	if (N < LINE_PRINT_LIM) {
		for (i = 0; i < N; i++) {
			printf("%f\n", a[i]);
		}
	} else {
		for (i = 0; i < LINE_PRINT_LIM; i++) {
			printf("%f\n", a[i]);
		}
		printf("Hid remaining %d lines for readability\n", 
			N - LINE_PRINT_LIM + 1);
	}

	if (!is_sorted(a, N)) {
		printf("sorting unsuccessful\n");
		free(a);
		exit(1);
	}

	free(a);
	return 0;
}