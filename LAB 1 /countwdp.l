%{
#include <stdio.h>

int word_count = 0;
int digit_count = 0;
int punctuation_count = 0;
%}

%%

[A-Za-z]+          { word_count++; }
[0-9]              { digit_count++; }
[.,;:!?]           { punctuation_count++; }
[ \t\n]+           ;    // ignore whitespace
.                  ;    // ignore other characters

%%

int main() {
    yylex();
    printf("Words: %d\n", word_count);
    printf("Digits: %d\n", digit_count);
    printf("Punctuation marks: %d\n", punctuation_count);
    return 0;
}
