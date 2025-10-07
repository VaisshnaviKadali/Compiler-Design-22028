%{
#include <stdio.h>

int characters = 0;
int words = 0;
int spaces = 0;
int lines = 0;
int in_word = 0;  // flag to track if inside a word
%}

%%
[ \t]          { spaces++; characters += yyleng; in_word = 0; }
[\n]           { lines++; characters += yyleng; in_word = 0; }
[a-zA-Z0-9]+   { characters += yyleng; 
                 if (!in_word) { words++; in_word = 1; }
               }
.              { characters += yyleng; in_word = 0; }
%%

int yywrap() {
    return 1;
}

int main() {
    printf("Enter text (press Ctrl+D to end input):\n");
    yylex();
    printf("Characters: %d\nWords: %d\nSpaces: %d\nLines: %d\n", characters, words, spaces, lines);
    return 0;
}

