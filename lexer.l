%{
#include <stdio.h>
	/*To find whether given letter is a vowel or not*/
// #undef yywrap
// #define yywrap() 1

int yywrap() {return 1;}

%}

%%

[0-9]+ {	
	FILE* sfile = fopen("results.txt", "a");
	if(sfile) {
	fprintf(sfile, "%s,integer\n", yytext);
	fclose(sfile);
}
	}
[\+\-\*/] {
	FILE* sfile = fopen("results.txt", "a");
if(sfile) {
	fprintf(sfile,"%s, is an operator\n", yytext);
	fclose(sfile);
	}
}

"(" {
	FILE* sfile = fopen("results.txt", "a");
	if (sfile) {
		fprintf(sfile, "%s,left_paren\n", yytext);
		fclose(sfile);
	}
}

")" {
	FILE* sfile = fopen("results.txt", "a");
	if(sfile) { 
		fprintf(sfile, "%s,right_paren\n", yytext);
		fclose(sfile);
	}
}

[ \t\n] ; /* Ignore  whitespace */

. {
	printf("Error: Unrecognizable character %s\n", yytext);
}

%%

/* "int"|"float"|"auto"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while" {
	FILE* sfile;
	sfile = fopen("results.txt", "a");
	fprintf(sfile,"%s, is a reserved\n", yytext);
	fclose(sfile);
	}	
[a-zA-Z]+ {	
	FILE* sfile;
	sfile = fopen("results.txt", "a");
	fprintf(sfile,"%s, is an identifier\n", yytext);
	fclose(sfile);
	}
[\\0|!|@|$|%|]+ {
	FILE* sfile;
	sfile = fopen("results.txt", "a");
	fprintf(sfile,"%s, is an invalid identifier\n", yytext);
	fclose(sfile);
	}
[\.|\?|-|^|,|>|<|;] {
	FILE* sfile;
	sfile = fopen("results.txt", "a");
	fprintf(sfile,"%s, is punctuation\n", yytext);
	fclose(sfile);
	}

%%
*/
int main()
{
	FILE* file = fopen("test.txt", "r"); //read from input file
	// printf("%s",yyin);
	if(!file) {
		perror("Error opening input file");
		return 1;
	}
	yyin = file;

	FILE* sfile = fopen("results.txt", "w"); //clear previous output
	if(sfile) fclose(sfile);

	yylex();
	fclose(file);
	return 0;
}
