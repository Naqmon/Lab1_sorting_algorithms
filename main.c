#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
typedef unsigned long ul;
ul g_random_seed;
ul my_rand() {
	return g_random_seed = 69069LU*g_random_seed + 5LU;
}
int cmp(const void *a, const void *b) {
	 return *(int *)a - *(int *)b;
}
void swap_array(ul* array, ul n) {
	for (ul i = 0; i < n; i++) {
		array[i] = i;
	}
	ul a, b, temp;
	for (ul i = 0; i < n >> 16; i++) {
		a = my_rand() % n;
		b = my_rand() % n;
		temp = array[a];
		array[a] = array[b];
		array[b] = temp;
	}
}
void random_array(ul *array, ul n) {
	for (ul i = 0; i < n; i++) {
		array[i] = my_rand();
	}
}
void quick_sort(ul *array, ul n) {
	if (n < 2) return;
	ul left = 0;
	ul right = n - 1;
	ul mid = array[n >> 1];
	ul temp;
	while (left < right) {
		while (array[left] < mid) left++;
		while (array[right] > mid) right--;
		if (left <= right) {
			temp = array[left];
			array[left] = array[right];
			array[right] = temp;
			left++; right--;
		}
	}
	quick_sort(array, right + 1);
	quick_sort(array + left, n - left);
}
void radix_sort(ul *array, ul n) {
	const ul basis = 256;
	ul* buffer = (ul *)malloc(sizeof(ul) * n);
	if (buffer == NULL) return;
	ul* temp;
	for (ul shift = 0; shift < sizeof(ul)*8; shift += 8) {
		ul rem[256] = {0};
		for (ul i = 0; i < n; i++) {
			rem[(array[i] >> shift) & basis - 1]++;
		}
		for (ul i = 1; i < basis; i++) {
			rem[i] += rem[i - 1];
		}
		for (int i = n-1; i >= 0; i--) {
			buffer[--rem[(array[i] >> shift) & (basis - 1)]] = array[i];
		}
		temp = buffer;
		buffer = array;
		array = temp;
	}
	free(buffer);
}
void merge_sort(ul *array, ul *buffer, ul n) {
	if (n < 2) return;
	ul mid = n >> 1;
	merge_sort(array, buffer, mid);
	merge_sort(array + mid, buffer, n - mid);
	ul left = 0, right = mid;
	for (ul i = 0; i < n; i++) {
		if (array[left] < array[right]) 
			buffer[i] = array[left++];
		else 
			buffer[i] = array[right++];
		if (left == mid) left = n - 1;
		if (right == n) right = mid - 1;
	}
	for (ul i = 0; i < n; i++)
		array[i] = buffer[i];
}
void buffer_create(ul *array, ul n){
	ul *buffer = (ul *)malloc(sizeof(ul)*n);
	if(buffer == NULL) return;
	merge_sort(array, buffer, n);
	free(buffer);
}
void insert_sort(ul *array, ul n) {
	ul temp;
	for (ul i = 1; i < n; i++) {
		ul j = i;
		while (j > 0 && array[j] < array[j - 1]) {
			temp = array[j];
			array[j] = array[j - 1];
			array[j - 1] = temp;
			j--;
		}
	}
}
void bubble_sort(ul *array, ul n) {
	ul temp;
	for (ul i = 0; i < n; i++) {
		for (ul j = i + 1; j < n; j++) {
			if (array[i] > array[j]) {
				temp = array[i];
				array[i] = array[j];
				array[j] = temp;
			}
		}
	}
}
void selection_sort(ul *array, ul n) {
	ul min, min_ind, temp;
	for (ul i = 0; i < n; i++) {
		min = array[i];
		min_ind = i;
		for (ul j = i; j < n; j++) {
			if (array[j] < min) {
				min = array[j];
				min_ind = j;
			}
		}
		temp = array[i];
		array[i] = min;
		array[min_ind] = temp;
	}
}
void tournament_sort(ul* array, const ul n) {
	ul* winner = (ul*)malloc(sizeof(ul) * n);
	ul* loser = (ul*)malloc(sizeof(ul) * n);
	ul w_ind = 0, l_ind = 0;
	ul tour[511];
	for (ul i = 0; i < 256; i++)
		tour[255 + i] = array[i];
}
void shell_sort(ul* array, ul n) {
	ul temp;
	for (ul s = n >> 1; s > 0; s = s >> 1) {
		for (ul i = s; i < n; i++) {
			for (int j = i - s; j >= 0 && array[j] > array[j + s]; j -= s) {
				temp = array[j];
				array[j] = array[j + s];
				array[j + s] = temp;
			}
		}
	}
}
void heap_sort(ul* array, ul n) {
	ul temp;
	n--;
	for (ul i = n; i > 1; i--) {
		if (array[i] > array[(i - 1) >> 1]) {
			temp = array[i];
			array[i] = array[(i - 1) >> 1];
			array[(i - 1) >> 1] = temp;
		}
	}
	temp = array[n];
	array[n] = array[0];
	array[0] = temp;
	ul ind;
	ul l, r;
	while (n-- > 2) {
		ind = 0;
		l = 1; r = 2;
		while (l <= n) {
			if (l == n && array[ind] < array[l]) {
				temp = array[ind];
				array[ind] = array[l];
				array[l] = temp;
				ind = l;
			}
			else if (array[l] >= array[r] && array[ind] < array[l]) {
				temp = array[ind];
				array[ind] = array[l];
				array[l] = temp;
				ind = l;
			}
			else if (array[r] >= array[l] && array[ind] < array[r]) {
				temp = array[ind];
				array[ind] = array[r];
				array[r] = temp;
				ind = r;
			}
			else break;
			l = (ind << 1) + 1;
			r = l + 1;
		}
		temp = array[0];
		array[0] = array[n];
		array[n] = temp;
	}
	
}
void (*choise_func(char *argv))(ul *, ul){
	void (*sort_funcs[])(ul *, ul) = {quick_sort, heap_sort, radix_sort, shell_sort, bubble_sort, insert_sort, selection_sort, buffer_create};
	static const char *sort_alg[] = {"quick", "heap", "radix", "shell", "bubble", "insert", "selection", "merge", NULL}; 
	for(ul i = 0; sort_alg[i] != NULL; i++)
		if(strcmp(sort_alg[i], argv) == 0)
				return sort_funcs[i];
}

int main(int args, char **argv){
	void (*sort_fun)(ul *, ul) = choise_func(argv[1]);
	ul n = atoi(argv[2]);
	ul* array = (ul*)malloc(sizeof(ul) * n);
	if(array == NULL) return -1;

	if(strcmp(argv[3], "random") == 0) random_array(array, n);
	else swap_array(array, n);
	
	g_random_seed = n;
	clock_t start = clock();
	if(strcmp(argv[1], "qsort") == 0) qsort(array, n, sizeof(ul), cmp);
	else sort_fun(array, n);
	clock_t end = clock();

	if(strcmp(argv[4], "1") == 0) printf("%s(%u) =\n%u", argv[1], n, end - start);
	else printf(" %u", end - start);
	if(strcmp(argv[4], "5") == 0) printf("\n");
	return 0;
}
