%{
#include <stdio.h>
%}

%%
[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,} {
    printf("Email: %s\n", yytext);
}
.|\n { /* ignore */ }
%%

int main() {
    yylex();
    return 0;
}
