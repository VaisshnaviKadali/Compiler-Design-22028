%{
#include <stdio.h>
%}

%%
[0-9]{3}-[0-9]{3}-[0-9]{4} { printf("Phone: %s\n", yytext); }
.|\n { /* ignore */ }
%%

int main() {
    yylex();
    return 0;
}
