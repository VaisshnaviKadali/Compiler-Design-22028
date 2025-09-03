%{
#include <stdio.h>
int caps = 0;
%}

%%
[A-Z] { caps++; }
.|\n { /* ignore */ }
%%

int main() {
    yylex();
    printf("Capital letters: %d\n", caps);
    return 0;
}
