#include <stdio.h>
#include <ctype.h>
#include <string.h>

void main () { 
	char A[50];
	int i;
	
	fgets (A, 50, stdin);

	for (i = 0; A[i] != '\0'; i++) {
		if (( A[i] >= 'A' ) && ( A[i] <= 'Z' ))
		       A[i] = tolower (A[i]);
 		else if (( A[i] >= 'a') && ( A[i] <= 'z' ))
			A[i] = toupper (A[i]);
	}
	puts (A);
}	

