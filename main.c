#include<stdlib.h>
#include"common.h"
#include<stdio.h>
#include<string.h>
extern FILE * yyin;
extern FILE *yyout;
int main(int argc,char *argv[])
{
	//char file_name[100];
//printf("input file name:\n");
//scanf("%s",file_name);
//yyin=fopen(file_name,"r");
yyin = fopen(argv[1],"r");
	if(yyin==NULL)
{printf("no file");
return -1;	}
else
printf("open successful!\n");
char out[10];
strcpy(out,"out_");
strcat(out,argv[1]);
yyout=fopen(out,"w+");


yyparse();

fclose(yyout);



}
