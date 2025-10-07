%{
#include <ctype.h>
#include <stdio.h>

int yylex();
int yyerror(const char *s);
#define YYSTYPE double
%}

%token NUMBER
%left '+' '-'
%left '*' '/'
%right UMINUS

%%
lines:
      lines expr '\n'        { printf("%g\n", $2); }
    | lines '\n'
    | /* empty */
    ;

expr:
      expr '+' expr          { $$ = $1 + $3; }
    | expr '-' expr          { $$ = $1 - $3; }
    | expr '*' expr          { $$ = $1 * $3; }
    | expr '/' expr          { $$ = $1 / $3; }
    | '(' expr ')'           { $$ = $2; }
    | '-' expr %prec UMINUS  { $$ = -$2; }
    | NUMBER
    ;
%%

int yylex() {
    int c;
    while ((c = getchar()) == ' ' || c == '\t');

    if (c == EOF) return 0;

    if (isdigit(c) || c == '.') {
        ungetc(c, stdin);
        scanf("%lf", &yylval);
        return NUMBER;
    }

    return c;
}

int yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
    return 1;
}

int main() {
    return yyparse();
}
