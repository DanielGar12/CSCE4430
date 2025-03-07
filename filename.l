%{
	/*To find whether given letter is a vowel or not*/
#undef yywrap
#define yywrap() 1

%}

%%

[0-9]+ {	
	FILE* sfile;
	sfile = fopen("results.txt", "a");
	fprintf(sfile, "%s, is an integer\n", yytext);
	fclose(sfile);
	}
[+|\/|-|*|=|%|] {
	FILE* sfile;
	sfile = fopen("results.txt", "a");
	fprintf(sfile,"%s, is an operator\n", yytext);
	fclose(sfile);
	}
"int"|"float"|"auto"|"case"|"char"|"const"|"continue"|"default"|"do"|"double"|"else"|"enum"|"extern"|"float"|"for"|"goto"|"if"|"int"|"long"|"register"|"return"|"short"|"signed"|"sizeof"|"static"|"struct"|"switch"|"typedef"|"union"|"unsigned"|"void"|"volatile"|"while" {
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

main()
{
	FILE* file;
	file = fopen("test.txt", "r");
	yyin = file;
	printf("%s",yyin);
	FILE* sfile;
	sfile = fopen("results.txt", "w");
	yylex();

}
