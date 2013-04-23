D			[0-9]
L			[a-zA-Z_]
H			[a-fA-F0-9]
E			([Ee][+-]?{D}+)
P                       ([Pp][+-]?{D}+)
FS			(f|F|l|L)
IS                      ((u|U)|(u|U)?(l|L|ll|LL)|(l|L|ll|LL)(u|U))

%{
#include <stdio.h>
#include "y.tab.h"
#include <string.h>
#include "common.h"
//#define table_len 100
//#define  id_len 30
//#define str_len 80
void count(void);
void insert();
//char strTable[table_len][str_len];
//char idTable[table_len][id_len];
char constTable[table_len][2];
%}

%%
"/*"			{ comment(); }
"//"[^\n]*              { /* consume //-comment */ }


"auto"			{ count();strcpy(yylval.str,"auto"); return(AUTO); }
"_Bool"			{ count();strcpy(yylval.str,"_Bool"); return(BOOL); }
"break"			{ count();strcpy(yylval.str,"break"); return(BREAK); }
"case"			{ count();strcpy(yylval.str,"case"); return(CASE); }
"char"			{ count();strcpy(yylval.str,"char"); return(CHAR); }
"_Complex"		{ count();strcpy(yylval.str,"_Complex"); return(COMPLEX); }
"const"			{ count();strcpy(yylval.str,"const"); return(CONST); }
"continue"		{ count();strcpy(yylval.str,"continue"); return(CONTINUE); }
"default"		{ count();strcpy(yylval.str,"continue"); return(DEFAULT); }
"do"			{ count();strcpy(yylval.str,"default"); return(DO); }
"double"		{ count();strcpy(yylval.str,"do"); yylval.itype=DOUBLE;return(DOUBLE); }
"else"			{ count();strcpy(yylval.str,"double"); return(ELSE); }
"enum"			{ count();strcpy(yylval.str,"else"); return(ENUM); }
"extern"		{ count();strcpy(yylval.str,"enum"); return(EXTERN); }
"float"			{ count();strcpy(yylval.str,"float");return(FLOAT); }
"for"			{ count();strcpy(yylval.str,"for"); return(FOR); }
"goto"			{ count();strcpy(yylval.str,"goto"); return(GOTO); }
"if"			{ count();strcpy(yylval.str,"if"); return(IF); }
"_Imaginary"		{ count();strcpy(yylval.str,"_Imaginar"); return(IMAGINARY); }
"inline"		{ count();strcpy(yylval.str,"inline"); return(INLINE); }
"int"			{ count();strcpy(yylval.str,"int"); strcpy(yylval.str,"int");return(INT); }
"long"			{ count();strcpy(yylval.str,"long"); return(LONG); }
"register"		{ count();strcpy(yylval.str,"register"); return(REGISTER); }
"restrict"		{ count();strcpy(yylval.str,"restrict"); return(RESTRICT); }
"return"		{ count();strcpy(yylval.str,"return"); return(RETURN); }
"short"			{ count();strcpy(yylval.str,"short"); yylval.itype=SHORT;return(SHORT); }
"signed"		{ count();strcpy(yylval.str,"signed"); return(SIGNED); }
"sizeof"		{ count();strcpy(yylval.str,"sizeof"); return(SIZEOF); }
"static"		{ count();strcpy(yylval.str,"static"); return(STATIC); }
"struct"		{ count();strcpy(yylval.str,"struct"); return(STRUCT); }
"switch"		{ count();strcpy(yylval.str,"switch"); return(SWITCH); }
"typedef"		{ count();strcpy(yylval.str,"ypedef"); return(TYPEDEF); }
"union"			{ count();strcpy(yylval.str,"nion"); return(UNION); }
"unsigned"		{ count();strcpy(yylval.str,"unsigned"); yylval.itype=UNSIGNED;return(UNSIGNED); }
"void"			{ count();strcpy(yylval.str,"void"); yylval.itype=VOID; return(VOID); }
"volatile"		{ count();strcpy(yylval.str,"volatite"); return(VOLATILE); }
"while"			{ count();strcpy(yylval.str,"while"); return(WHILE); }

{L}({L}|{D})*		{ count(); return(check_type()); }

0[xX]{H}+{IS}?		{ count(); insertstr();return(CONSTANT); }
0[0-7]*{IS}?		{ count(); insertstr(); return(CONSTANT); }
[1-9]{D}*{IS}?		{ count(); insertstr(); return(CONSTANT); }
L?'(\\.|[^\\'\n])+'	{ count(); insertstr();return(CONSTANT); }

{D}+{E}{FS}?		{ count(); insertstr();return(CONSTANT); }
{D}*"."{D}+{E}?{FS}?	{ count(); insertstr();return(CONSTANT); }
{D}+"."{D}*{E}?{FS}?	{ count(); insertstr(); return(CONSTANT); }
0[xX]{H}+{P}{FS}?	{ count(); insertstr(); return(CONSTANT); }
0[xX]{H}*"."{H}+{P}?{FS}?     { count(); insertstr(); return(CONSTANT); }
0[xX]{H}+"."{H}*{P}?{FS}?     { count(); insertstr();return(CONSTANT); }


L?\"(\\.|[^\\"\n])*\"	{ count();insertstr(); return(STRING_LITERAL);}

"..."			{ count();strcpy(yylval.str,"..."); return(ELLIPSIS); }
">>="			{ count();strcpy(yylval.str,">>="); return(RIGHT_ASSIGN); }
"<<="			{ count();strcpy(yylval.str,"<<="); return(LEFT_ASSIGN); }
"+="			{ count();strcpy(yylval.str,"+="); return(ADD_ASSIGN); }
"-="			{ count();strcpy(yylval.str,"-="); return(SUB_ASSIGN); }
"*="			{ count();strcpy(yylval.str,"*="); return(MUL_ASSIGN); }
"/="			{ count();strcpy(yylval.str,"/="); return(DIV_ASSIGN); }
"%="			{ count();strcpy(yylval.str,"%="); return(MOD_ASSIGN); }
"&="			{ count();strcpy(yylval.str,"&="); return(AND_ASSIGN); }
"^="			{ count();strcpy(yylval.str,"^="); return(XOR_ASSIGN); }
"|="			{ count();strcpy(yylval.str,"|="); return(OR_ASSIGN); }
">>"			{ count();strcpy(yylval.str,">>"); return(RIGHT_OP); }
"<<"			{ count();strcpy(yylval.str,"<<"); return(LEFT_OP); }
"++"			{ count();strcpy(yylval.str,"++"); return(INC_OP); }
"--"			{ count();strcpy(yylval.str,"--"); return(DEC_OP); }
"->"			{ count();strcpy(yylval.str,""); return(PTR_OP); }
"&&"			{ count();strcpy(yylval.str,""); return(AND_OP); }
"||"			{ count();strcpy(yylval.str,""); return(OR_OP); }
"<="			{ count();strcpy(yylval.str,""); return(LE_OP); }
">="			{ count();strcpy(yylval.str,">="); return(GE_OP); }
"=="			{ count();strcpy(yylval.str,""); return(EQ_OP); }
"!="			{ count();strcpy(yylval.str,""); return(NE_OP); }
";"			{ count();strcpy(yylval.str,""); return(';'); }
("{"|"<%")		{ count();strcpy(yylval.str,""); return('{'); }
("}"|"%>")		{ count();strcpy(yylval.str,""); return('}'); }
","			{ count();strcpy(yylval.str,""); return(','); }
":"			{ count();strcpy(yylval.str,""); return(':'); }
"="			{ count();strcpy(yylval.str,"");return('='); }
"("			{ count();strcpy(yylval.str,""); return('('); }
")"			{ count();strcpy(yylval.str,""); return(')'); }
("["|"<:")		{ count();strcpy(yylval.str,""); return('['); }
("]"|":>")		{ count();strcpy(yylval.str,""); return(']'); }
"."			{ count();strcpy(yylval.str,""); return('.'); }
"&"			{ count();strcpy(yylval.str,""); return('&'); }
"!"			{ count();strcpy(yylval.str,""); return('!'); }
"~"			{ count();strcpy(yylval.str,""); return('~'); }
"-"			{ count();strcpy(yylval.str,""); return('-'); }
"+"			{ count();strcpy(yylval.str,""); return('+'); }
"*"			{ count();strcpy(yylval.str,""); return('*'); }
"/"			{ count();strcpy(yylval.str,""); return('/'); }
"%"			{ count();strcpy(yylval.str,""); return('%'); }
"<"			{ count();strcpy(yylval.str,""); return('<'); }
">"			{ count();strcpy(yylval.str,""); return('>'); }
"^"			{ count();strcpy(yylval.str,""); return('^'); }
"|"			{ count();strcpy(yylval.str,""); return('|'); }
"?"			{ count();strcpy(yylval.str,""); return('?'); }

[ \t\v\n\f]		{ count(); }
.			{ /* Add code to complain about unmatched characters */ }

%%

int yywrap(void)
{
	
//int i=0;
//for(i=0;i<100;i++)
//printf("%d=%s\n",i,name_t[i]);
return 1;
}


void comment(void)
{
	char c, prev = 0;
  
	while ((c = input()) != 0)      /* (EOF maps to 0) */
	{
		if (c == '/' && prev == '*')
			return;
		prev = c;
	}
	error("unterminated comment");
}


//int column = 0;
column=0;
int p_sentence=0;
void count(void)/**/
{
	int i;

	for (i = 0; yytext[i] != '\0'; i++)
		if (yytext[i] == '\n')
			column = 0;
		else if (yytext[i] == '\t')
			column += 8 - (column % 8);
		else
			column++;

	ECHO;

	int j=0;
	if(yytext[j]=='\n')
	{	p_sentence=0;
	 memset(sentence,'\0',strlen(sentence));
	}
	else {
	for(j=0;j<yyleng&&p_sentence<sent_len;j++){
        sentence[p_sentence]=yytext[j];
	p_sentence++;
	}
	sentence[p_sentence]=' ';
	p_sentence++;
}
}

int strIndex=0;
int idIndex=0;
int constIndex=0;

void insertstr(){

//printf("insertstrndex=%d\n",strIndex);
int j,ex=0;
for(j=0;j<strIndex;j++)
if(strcmp(strTable[j],yytext)==0)//exist
{
yylval.stu_index.i_index=j;
yylval.stu_index.i_type=STRING_LITERAL;
ex=1;
break;
}

if(!ex)
if(strIndex<table_len){
int j=0;
for(j=0;j<yyleng;j++)
strTable[strIndex][j]=yytext[j];
strTable[strIndex][j]='\0';
yylval.stu_index.i_index=strIndex;
yylval.stu_index.i_type=STRING_LITERAL;
strIndex++;
}
}

int check_type(void)
{
/*
* pseudo code --- this is what it should check
*
*	if (yytext == type_name)
*		return TYPE_NAME;
*
*	return IDENTIFIER;
*/

/*
*	it actually will only return IDENTIFIER
*/
int j,ex=0;
for(j=0;j<idIndex;j++)
if(strcmp(idTable[j],yytext)==0)//exist
{
yylval.stu_index.i_index=j;
yylval.stu_index.i_type=IDENTIFIER;
ex=1;
break;
}

if(!ex)
if(idIndex<table_len){
for(j=0;j<yyleng;j++)
{
idTable[idIndex][j]=yytext[j];
idTable1[idIndex][j]=yytext[j];
}
idTable1[idIndex][j]=' ';
idTable1[idIndex][j+1]='_';
//idTable1[idIndex][j+2]='|';
//idTable1[idIndex][j+3]='|';

idTable[idIndex][j]='\0';
idTable1[idIndex][j+4]='\0';
yylval.stu_index.i_index=idIndex;
yylval.stu_index.i_type=IDENTIFIER;
idIndex++;
}


return IDENTIFIER;
}

