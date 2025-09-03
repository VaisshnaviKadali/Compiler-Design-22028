%{
#include <stdio.h>
#include <stdlib.h>
int posint = 0, negint = 0, posfraction = 0, negfraction = 0;
extern FILE *yyin;
%}

/* Named patterns */
POS_FRACTION   [\+]?([0-9]+\.[0-9]+|\.[0-9]+)
NEG_FRACTION   -([0-9]+\.[0-9]+|\.[0-9]+)
NEG_INT        -[0-9]+
POS_INT        [\+]?([0-9]+)
WHITESPACE     [ \t\n]+

%%
{NEG_FRACTION}     { negfraction++; }
{POS_FRACTION}     { posfraction++; }
{NEG_INT}          { negint++; }
{POS_INT}          { posint++; }
{WHITESPACE}       { /* ignore */ }
.                  { /* ignore other characters */ }
%%

int yywrap() {
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        exit(0);
    }

    yyin = fopen(argv[1], "r");
    if (!yyin) {
        perror("Error opening file");
        exit(1);
    }

    yylex();

    printf("No of +ve integers = %d\n", posint);
    printf("No of -ve integers = %d\n", negint);
    printf("No of +ve fractions = %d\n", posfraction);
    printf("No of -ve fractions = %d\n", negfraction);

    return 0;
}
