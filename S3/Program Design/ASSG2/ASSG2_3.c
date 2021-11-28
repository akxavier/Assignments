#include <stdio.h>
#include <string.h>

int check (char str[], char sub[], int len, int n) {
        int flag = 1, i;
        for (i = 1; i < len - 1; i++)
                if (str[n + i] != sub[i] ) {
                        flag = 0;
                        break;
                }
        return flag;
}

void main () {
        char str[30], sub[30];
        int mod[30], n, len, x = 0, flag, key;

        //fgets (str, 30, stdin);
        //fgets (sub, 30, stdin);
	
	scanf ("%s", str);
	scanf ("%s", sub);

        len = strlen (sub);

        for (n = 0; str[n] != '\0'; n++) {
                if ( str[n] == sub[0] )
                        if ( check(str, sub, len, n) == 1)
				for (int i = 0; i < len - 1; i++) {
					key = n + i;
					flag = 0;
					
					for (int j = 0; j < x; j++) {
						if (mod[j] == key)
							flag = 1;
					}

					if (flag == 0)
						mod[x++] = key;
				}
	}

	n = 0;

	for (int i = 0; i < x; i++) {
		key = mod[i] - n;

		for (int i = key; str[i] != '\0'; i++)
			str[i] = str[i + 1];

		n++;
	}

	printf ("%s", str);

}
