#include<stdlib.h>
#include<stdio.h>
#include<string.h>
int main(){
	static char *sorting_alg[] = {"selection", "bubble", "insert", "shell" , NULL}; 
	static char *sorting_alg2[] = {"quick", "merge", "heap", "qsort", "radix", NULL}; 
	char *command = malloc(sizeof(char)*100);
	for(int i = 0; sorting_alg[i] != NULL; i++){
		for(int n = 1; n < 1000000; n *= 10){
			for(int k = 1; k < 6; k++){
				sprintf(command, "./main %s %d random %d >> test.txt", sorting_alg[i], n, k);
				system(command);
			}
		}
	}
	for(int i = 0; sorting_alg[i] != NULL; i++){
		for(int n = 1; n < 1000000; n *= 10){
			for(int k = 1; k < 6; k++){
				sprintf(command, "./main %s %d swap %d >> test.txt", sorting_alg[i], n, k);
				system(command);
			}
		}
	}
	for(int i = 0; sorting_alg2[i] != NULL; i++){
		for(int n = 1; n < 1000000000; n *= 10){
			for(int k = 1; k < 6; k++){
				sprintf(command, "./main %s %d random %d >> test.txt", sorting_alg2[i], n, k);
				system(command);
			}
		}
	}
	for(int i = 0; sorting_alg2[i] != NULL; i++){
		for(int n = 1; n < 1000000000; n *= 10){
			for(int k = 1; k < 6; k++){
				sprintf(command, "./main %s %d swap %d >> test.txt", sorting_alg2[i], n, k);
				system(command);
			}
		}
	}
	return 0;
}
