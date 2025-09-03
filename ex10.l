%{
#include <stdio.h>
int round=0, curly=0, square=0;
%}

%%
"(" | ")" { round++; }
"{" | "}" { curly++; }
"[" | "]" { square++; }
.|\n { /* ignore */ }
%%

int main() {
    yylex();
    printf("Round brackets: %d\n", round);
    printf("Curly brackets: %d\n", curly);
    printf("Square brackets: %d\n", square);
    return 0;
}
