#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main() {
    int x = 0, n, i = 0, j = 0;
    void *mypointer;
    void *T4Tutorials_address[5]; // Stores addresses of identifiers/operators
    char ch, c;
    char T4Tutorials_Array2[15];  // Input expression
    char T4Tutorials_Array3[15];  // Stores symbols

    printf("Input the expression ending with $ sign: ");

    // Input expression until '$' is encountered
    while ((c = getchar()) != '$' && i < 15) {
        T4Tutorials_Array2[i++] = c;
    }

    n = i - 1;

    // Display the given expression
    printf("\nGiven Expression: ");
    for (i = 0; i <= n; i++) {
        printf("%c", T4Tutorials_Array2[i]);
    }

    // Print symbol table
    printf("\n\nSymbol Table Display\n");
    printf("Symbol\tAddress\t\tType\n");

    while (j <= n) {
        c = T4Tutorials_Array2[j];

        if (isalpha(c)) {
            // Identifier
            mypointer = malloc(sizeof(char));
            T4Tutorials_address[x] = mypointer;
            T4Tutorials_Array3[x] = c;

            printf("%c\t%p\tIdentifier\n", c, mypointer);

            x++;
        } else if (c == '+' || c == '-' || c == '*' || c == '=') {
            // Operator
            mypointer = malloc(sizeof(char));
            T4Tutorials_address[x] = mypointer;
            T4Tutorials_Array3[x] = c;

            printf("%c\t%p\tOperator\n", c, mypointer);

            x++;
        }

        j++;
    }

    // Free allocated memory
    for (i = 0; i < x; i++) {
        free(T4Tutorials_address[i]);
    }

    return 0;
}
