%{
#include <stdio.h>

int positive_count = 0;
int negative_count = 0;
int fraction_count = 0;
%}

%%

"-"[0-9]+              { negative_count++; }
[0-9]+"."[0-9]+        { fraction_count++; }
[0-9]+                 { positive_count++; }

[ \t\n]+               ;   // ignore whitespace
.                      ;   // ignore other characters

%%

int main(int argc, char **argv)
{
    yylex();
    printf("Positive numbers: %d\n", positive_count);
    printf("Negative numbers: %d\n", negative_count);
    printf("Fractions: %d\n", fraction_count);
    return 0;
}

