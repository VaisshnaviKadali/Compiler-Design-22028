%{
#include <stdio.h>
#include <stdlib.h>
int com = 0;
%}

%s COMMENT
%%

"/*"                  { BEGIN(COMMENT); com++; }
<COMMENT>"*/"         { BEGIN(INITIAL); }
<COMMENT>\n           { com++; }
<COMMENT>.            { /* Consume characters */ }
.|\n                  { fprintf(yyout, "%s", yytext); }

%%

int yywrap() {
    return 1;
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <input_file> <output_file>\n", argv[0]);
        exit(0);
    }

    FILE *in = fopen(argv[1], "r");
    if (!in) {
        perror("Error opening input file");
        exit(1);
    }

    FILE *out = fopen(argv[2], "w");
    if (!out) {
        perror("Error opening output file");
        exit(1);
    }

    yyin = in;
    yyout = out;

    yylex();

    printf("No of comment lines = %d\n", com);
    fclose(in);
    fclose(out);
    return 0;
}
