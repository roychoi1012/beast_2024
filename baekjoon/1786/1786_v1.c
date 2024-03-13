#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
How to approach
function search_pattern
1. Compare txt with ptn in range of len(ptn), beginning at the right side.
2. If there are new string in txt which is not in ptn,
3. Research after new string.
4. Repeat these process until find ptn in txt.

In best case, time complexity is same with 'Boyer-Moore'
But, in worst case, time complexity is same with 'brute-force'
*/

//@brief		return how many times they are founded and index where they are founded
void
search_ptn(const char* T, const char* P, const int32_t len_T, const int32_t len_P) 
{
	int32_t next = 0;
	int32_t cnt = 0;

	int32_t* idx = calloc(len_T, sizeof(int32_t));
	char* str = calloc(len_P+1, sizeof(char));

	for (int32_t i = 0; i < (len_T - len_P); i++) {
		// adjust range to search
		strncpy(str, T + i, len_P);

		for (int32_t j = len_P-1; j >= 0; j--) {
			// if there are new string in text which is not in pattern
			char* ptr = strchr(P, str[j]);
			if (ptr == NULL) {
				i += j;
			}

			if (P[j] == str[j]) {
				next++;
				// success to search pattern in  text
				if (next == len_P) {
					idx[cnt++] = i + 1;
					next = 0;
				}
			}
		}
	}

	// result
	printf("%d\n", cnt);

	for (int32_t i = 0; i < cnt; i++) {
		printf("%d ", idx[i]);
	}
	printf("\n");

	free(idx); idx = 0;
	free(str); str = 0;

	return;
}

int 
main() 
{
	const size_t BUFFER_LENGTH = 100000;

	// T = text, P = pattern
	char* T = (char*)calloc(BUFFER_LENGTH, sizeof(char));
	char* P = (char*)calloc(BUFFER_LENGTH, sizeof(char));

	scanf("%[^\n]s", T);
	scanf(" %[^\n]s", P);

	int32_t len_T = strlen(T);
	int32_t len_P = strlen(P);

	search_ptn(T, P, len_T, len_P);

	free(T); T = 0;
	free(P); P = 0;

	return 0;
}