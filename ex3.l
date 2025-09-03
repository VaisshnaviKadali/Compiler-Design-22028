%{
#include <stdio.h>
%}

%%
0[xX][0-9a-fA-F]+ { printf("Hex: %s\n", yytext); }
.|\n { /* ignore */ }
%%

int main() {
    yylex();
    return 0;
}
