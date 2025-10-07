#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_RULES 10
#define MAX_PRODUCTIONS 10
#define MAX_LENGTH 100

typedef struct {
    char nonTerminal;
    char productions[MAX_PRODUCTIONS][MAX_LENGTH];
    int prodCount;
} GrammarRule;

GrammarRule grammar[MAX_RULES];
int ruleCount = 0;

void inputGrammar() {
    printf("Enter number of grammar rules: ");
    scanf("%d", &ruleCount);
    getchar(); // consume newline
    
    for (int i = 0; i < ruleCount; i++) {
        printf("Enter non-terminal (single char): ");
        scanf("%c", &grammar[i].nonTerminal);
        getchar();
        
        printf("Enter number of productions for %c: ", grammar[i].nonTerminal);
        scanf("%d", &grammar[i].prodCount);
        getchar();
        
        for (int j = 0; j < grammar[i].prodCount; j++) {
            printf("Enter production %d: ", j + 1);
            fgets(grammar[i].productions[j], MAX_LENGTH, stdin);
            grammar[i].productions[j][strcspn(grammar[i].productions[j], "\n")] = 0; // remove newline
        }
    }
}

// Function to eliminate direct left recursion from a single grammar rule
void eliminateLeftRecursion(GrammarRule* rule) {
    char alpha[MAX_PRODUCTIONS][MAX_LENGTH];
    char beta[MAX_PRODUCTIONS][MAX_LENGTH];
    int alphaCount = 0, betaCount = 0;

    // Separate alpha and beta productions
    for (int i = 0; i < rule->prodCount; i++) {
        if (rule->productions[i][0] == rule->nonTerminal) {
            // left recursive production A -> A α
            strcpy(alpha[alphaCount++], rule->productions[i] + 1); // store α part (skip the non-terminal)
        } else {
            // non left recursive production
            strcpy(beta[betaCount++], rule->productions[i]);
        }
    }

    if (alphaCount == 0) {
        // No left recursion
        return;
    }

    // Modify the original rule and create new rule for A'
    char newNonTerminal = rule->nonTerminal + 39; // e.g., if 'A' then 'A'' = 'A' + 39 = 'A' + "'"
    printf("Eliminating left recursion for %c\n", rule->nonTerminal);

    // Print the new productions
    printf("%c -> ", rule->nonTerminal);
    for (int i = 0; i < betaCount; i++) {
        printf("%s%c'", beta[i], rule->nonTerminal);
        if (i != betaCount - 1) printf(" | ");
    }
    printf("\n");

    printf("%c' -> ", newNonTerminal);
    for (int i = 0; i < alphaCount; i++) {
        printf("%s%c'", alpha[i], newNonTerminal);
        if (i != alphaCount - 1) printf(" | ");
    }
    printf(" | ε\n"); // ε represents empty string
}

// Simple function to left factor a rule (only handles common prefix of length 1)
void leftFactoring(GrammarRule* rule) {
    int i, j;
    char commonPrefix[MAX_LENGTH];
    int prefixLength = 0;
    
    // Find common prefix among productions
    if (rule->prodCount < 2) return; // no factoring needed
    
    // For simplicity, let's check only prefix of length 1
    char firstChar = rule->productions[0][0];
    for (i = 1; i < rule->prodCount; i++) {
        if (rule->productions[i][0] != firstChar) {
            return; // no common prefix
        }
    }

    // There is common prefix of length 1
    prefixLength = 1;
    strncpy(commonPrefix, rule->productions[0], prefixLength);
    commonPrefix[prefixLength] = '\0';

    // Create new non-terminal for factoring
    char newNonTerminal = rule->nonTerminal + 39;

    printf("Left factoring for %c\n", rule->nonTerminal);
    printf("%c -> %s%c'\n", rule->nonTerminal, commonPrefix, newNonTerminal);

    printf("%c' -> ", newNonTerminal);
    for (i = 0; i < rule->prodCount; i++) {
        if (strlen(rule->productions[i]) > prefixLength) {
            printf("%s", rule->productions[i] + prefixLength);
        } else {
            printf("ε");
        }
        if (i != rule->prodCount - 1) printf(" | ");
    }
    printf("\n");
}

int main() {
    inputGrammar();

    for (int i = 0; i < ruleCount; i++) {
        eliminateLeftRecursion(&grammar[i]);
    }

    printf("\n");

    for (int i = 0; i < ruleCount; i++) {
        leftFactoring(&grammar[i]);
    }

    return 0;
}
