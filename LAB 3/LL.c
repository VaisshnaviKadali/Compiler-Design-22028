#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char s[20], stack[20];

int main() {
    // Parse table
    char m[5][6][3] = {
        {"tb",  "",     "",     "tb",   "",     ""   },  // e
        {"",    "+tb",  "",     "",     "n",    "n"  },  // b
        {"fc",  "",     "",     "fc",   "",     ""   },  // t
        {"",    "n",    "*fc",  "n",    "n",    "n"  },  // c
        {"i",   "",     "",     "(e)",  "",     ""   }   // f
    };

    int size[5][6] = {
        {2, 0, 0, 2, 0, 0},
        {0, 3, 0, 0, 1, 1},
        {2, 0, 0, 2, 0, 0},
        {0, 1, 3, 1, 1, 1},
        {0, 0, 0, 3, 0, 0}
    };

    int i, j, k, n, str1 = 0, str2 = 0;

    printf("\nEnter the input string: ");
    scanf("%s", s);

    strcat(s, "$");
    n = strlen(s);

    stack[0] = '$';
    stack[1] = 'e';
    i = 1;
    j = 0;

    printf("\nStack\tInput\n");
    printf("__________________\n");

    while ((stack[i] != '$') && (s[j] != '$')) {
        if (stack[i] == s[j]) {
            i--;
            j++;
        } else {
            // Map non-terminal to row index
            switch (stack[i]) {
                case 'e': str1 = 0; break;
                case 'b': str1 = 1; break;
                case 't': str1 = 2; break;
                case 'c': str1 = 3; break;
                case 'f': str1 = 4; break;
            }

            // Map terminal to column index
            switch (s[j]) {
                case 'i': str2 = 0; break;
                case '+': str2 = 1; break;
                case '*': str2 = 2; break;
                case '(': str2 = 3; break;
                case ')': str2 = 4; break;
                case '$': str2 = 5; break;
            }

            if (m[str1][str2][0] == '\0') {
                printf("\nERROR: Invalid string\n");
                exit(0);
            } else if (m[str1][str2][0] == 'n') {
                i--;  // Pop (ε production)
            } else if (m[str1][str2][0] == 'i') {
                stack[i] = 'i';  // Terminal
            } else {
                // Push RHS of production in reverse
                for (k = size[str1][str2] - 1; k >= 0; k--) {
                    stack[i] = m[str1][str2][k];
                    i++;
                }
                i--;  // Adjust top pointer
            }
        }

        // Print stack
        for (k = 0; k <= i; k++)
            printf("%c", stack[k]);
        printf("\t");

        // Print remaining input
        for (k = j; k <= n; k++)
            printf("%c", s[k]);
        printf("\n");
    }

    printf("\nSUCCESS: String parsed successfully.\n");
    return 0;
}
