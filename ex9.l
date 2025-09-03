%{
#include <stdio.h>
%}

%%
\t { printf("    "); } // 1 tab = 4 spaces
.|\n { printf("%s", yytext); }
%%

int main() {
    yylex();
    return 0;
}
