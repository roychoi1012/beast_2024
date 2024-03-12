#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

/*
	How to approach
	function search_pattern
	1. Compare txt with ptn in range of len(ptn), beginning at the right side.
	2. If there is a new string (character) in txt which is not in ptn,
	3. Search again after the new string.
	4. Repeat the process until finding ptn in txt.

	In best case, time complexity is the same as 'Boyer-Moore'
	But, in worst case, time complexity is the same as 'brute-force'
*/

// @brief
// @return		the number that they are found and indices where they are found
void
search_ptn(const char* T, const char* P, const int32_t len_T, const int32_t len_P) 
{
	int32_t next = 0;
	int32_t cnt = 0;

	int32_t* idx = (int32_t*)calloc(len_T, sizeof(int32_t));
	char* str = (char*)calloc(len_P+1, sizeof(char));

	for (int32_t i = 0; i < (len_T - len_P); i++) {
		// adjust range to search
		strncpy(str, &T[i], len_P);

		for (int32_t j = len_P-1; j >= 0; j--) {
			// if there is a new string (character) in text which is not in pattern
			char* c_ptr = (char*)strchr(P, str[j]);
			if (NULL == c_ptr) {
				i += j;
				break;
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
main(void) 
{
	// T = text, P = pattern
	char* T = (char*)calloc(1000, sizeof(char*));
	char* P = (char*)calloc(1000, sizeof(char*));

	scanf("%[^\n]s", T);
	scanf(" %[^\n]s", P);

	int32_t len_T = strlen(T);
	int32_t len_P = strlen(P);

	search_ptn(T, P, len_T, len_P);

	return 1;
}
