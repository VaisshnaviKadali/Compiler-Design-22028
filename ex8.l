%{
#include <stdio.h>
%}

%%
[0-9]{2}/[0-9]{2}/[0-9]{4} { printf("Date: %s\n", yytext); }
.|\n { /* ignore */ }
%%

int main() {
    yylex();
    return 0;
}
