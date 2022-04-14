#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int ASCII_Sum(char *word) {
	int sum = 0;

	for(int i = 0; word[i] != '\0'; i++) {
		sum = sum + (int)word[i];
	}

	return sum;
}

int Sum_of_Digits(int n) {
	int sum = 0;

	while(n != 0) {
		sum = sum + (n % 10);
		n = n / 10;
	}
	
	return sum;
}

void main() {
	char str[100000], str2[100000], word[100];
	int n, m;
	int stat[26];
	char val[1000];
	int count[26];
	int cnt = 0;

	for(int i = 0; i < 26; i++)
		count[i] = 0;

	scanf("%d\n", &n);

	for(int i = 0; i < 26; i++) 
		stat[i] = 0;

	scanf("%[^\n]", str);
    
    //store str in str2
    strcpy(str2, str);

	char *token = strtok(str2, " ");

	int i = 0;

	while(token != NULL) {
		int s = ASCII_Sum(token);
		int d = Sum_of_Digits(s);

		while(d > 26)
			d = Sum_of_Digits(d);

		if(count[d - 1] == 0)
			count[d - 1] = 1;

		char ch = (char) (d + 96);
		val[i++] = ch;
		printf("%c", ch);
		token = strtok(NULL, " ");
	}

	printf("\n");

	for(int i = 0; i < 26; i++) {
		if(count[i] == 1)
			cnt++;
	}

	printf("%d\n", cnt);
    	
    for(int i = 0; val[i] != '\0'; i++) {
        int temp = ( (int)val[i] ) - 97;
        if(stat[temp] == 0) {
            stat[temp] = 1;
            
            printf("%c ", val[i]);
            
            strcpy(str2, str);
            token = strtok(str2, " ");
            
            while(token != NULL) {
                int s = ASCII_Sum(token);
                int d = Sum_of_Digits(s);

                while(d > 26)
                    d = Sum_of_Digits(d);

                char ch = (char) (d + 96);
                
                if(ch == val[i])
                    printf("%s ", token);
                token = strtok(NULL, " ");
            }
            
            printf("\n");
        }
        
        /*else
            continue;*/
    }
}

		
