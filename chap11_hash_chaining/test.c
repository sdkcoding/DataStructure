#include <stdio.h>

int hash_function(char *key) {
	int hash_index = 0;
	while (*key) {
		printf("%d\n", *key);
		hash_index = 31 * hash_index + *key++;
		printf("%d\n", hash_index);
	}
	return hash_index;
}

int main(void) {
	char * string = "abcde";
	printf("%d\n", hash_function(string));
}