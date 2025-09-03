%{
#include <stdio.h>
%}

%%
[ \t]+ { printf(" "); }
[^\t \n]+ { printf("%s", yytext); }
\n { printf("\n"); }
%%

int main() {
    yylex();
    return 0;
}
