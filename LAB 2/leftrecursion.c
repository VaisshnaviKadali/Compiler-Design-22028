#include <stdio.h>
#include <string.h>

#define SIZE 50

int main() {
    int num;
    char production[10][SIZE];  
    char non_terminal;
    int index;

    printf("Enter number of productions: ");
    scanf("%d", &num);

    printf("Enter the grammar productions (e.g. E->E-A):\n");
    for (int i = 0; i < num; i++) {
        scanf("%s", production[i]);
    }

    printf("\n");

    for (int i = 0; i < num; i++) {
        printf("GRAMMAR: %s\n", production[i]);

        non_terminal = production[i][0];  

        index = 3;

        
        if (production[i][index] == non_terminal) {
            printf("This production is left recursive.\n");

            char alpha[SIZE];
            int alphaIndex = 0;

            
            index++;  
            while (production[i][index] != '\0' && production[i][index] != '|') {
                alpha[alphaIndex++] = production[i][index++];
            }
            alpha[alphaIndex] = '\0';
            char beta[SIZE];
            int betaIndex = 0;
            int pipePos = 0;

 
            for (int j = 3; production[i][j] != '\0'; j++) {
                if (production[i][j] == '|') {
                    pipePos = j;
                    break;
                }
            }

            if (pipePos == 0) {
                printf("No beta part found; can't eliminate left recursion.\n\n");
                continue;
            }

         
            pipePos++;
            while (production[i][pipePos] != '\0') {
                beta[betaIndex++] = production[i][pipePos++];
            }
            beta[betaIndex] = '\0';

          
            printf("Grammar after eliminating left recursion:\n");
            printf("%c -> %s%c'\n", non_terminal, beta, non_terminal);
            printf("%c' -> %s%c' | ε\n\n", non_terminal, alpha, non_terminal);

        } else {
            printf("This production is not left recursive.\n\n");
        }
    }

    return 0;
}
