%{
#include <stdio.h>
%}

%%
"+"|"-"|"*"|"/"|"%" { printf("Operator: %s\n", yytext); }
.|\n { /* ignore */ }
%%

int main() {
    yylex();
    return 0;
}
