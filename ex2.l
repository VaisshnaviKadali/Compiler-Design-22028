%{
#include <stdio.h>
int punct = 0;
%}

%%
[.,!?;:] { punct++; }
.|\n { /* ignore */ }
%%

int main() {
    yylex();
    printf("Punctuation count: %d\n", punct);
    return 0;
}
