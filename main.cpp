#include<stdio.h>
#include<stdlib.h>
#include<thread>
#include<time.h>
typedef unsigned long ul;
ul g_random_seed = -10;
ul my_rand() {
	return g_random_seed = 69069LU*g_random_seed + 5LU;
}
ul* random_array(ul n) {
	ul* array = (ul *)malloc(sizeof(ul)*n);
	if (array == NULL) return NULL;
	for (ul i = 0; i < n; i++) {
		array[i] = my_rand();
	}
	return array;
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
	quick_sort(array, right+1);
	quick_sort(array + left, n - left);
}
void radix_sort(ul *array, ul n) {
	const ul const basis = 256;
	ul* buffer = (ul *)malloc(sizeof(ul) * n);
	if (buffer == NULL) return;
	ul* temp;
	for (ul shift = 0; shift < sizeof(ul)*7; shift += 8) {
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
void tournament_sort(ul* array, ul n) {

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

}
int main(){
	ul n = 10000000;
	ul* array = random_array(n);
	if (array == NULL) {
		printf("Sasi lox\n");
		return 1;
	}
	time_t start = clock();
	/*ul* buffer = (ul*)malloc(sizeof(ul) * n);
	if (buffer == NULL) {
		printf("Sasi lox 2\n");
		return 1;
	}
	merge_sort(array, buffer, n);*/
	//bubble_sort(array, n);
	//shell_sort(array, n);
	quick_sort(array, n);
	printf("\nTime = %f\n", (double)clock()-start);
	for (ul i = 0; i < 10; i++)
		printf("%u ", array[i]);
	return 0;
}