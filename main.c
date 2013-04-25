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
char str[100];
fgets(str,100,yyin);
while(str[0]=='#'){
fprintf(yyout,"%s",str);
fgets(str,100,yyin);
}

char ch='\0';
fseek(yyin,-1,SEEK_CUR);
ch=fgetc(yyin);
while(ch!='\n')//next line
{fseek(yyin,-2,SEEK_CUR);
ch=fgetc(yyin);
}
fseek(yyin,-1,SEEK_CUR);

fprintf(yyout,"int eki=0;\nint ecf=0;\n");
fprintf(yyout,"int error1()\n{printf(\"error!!!!!!!!!!\")\n;\n}\n");
fprintf(yyout,"int error2()\n{printf(\"error!!!!!!!!!!\")\n;\n}\n");
fprintf(yyout,"int error3()\n{printf(\"error!!!!!!!!!!\")\n;\n}\n");
fprintf(yyout,"int error4()\n{printf(\"error!!!!!!!!!!\")\n;\n}\n");
fprintf(yyout,"int error5()\n{printf(\"error!!!!!!!!!!\")\n;\n}\n");
fprintf(yyout,"int error6()\n{printf(\"error!!!!!!!!!!\")\n;\n}\n");
fprintf(yyout,"int error7()\n{printf(\"error!!!!!!!!!!\")\n;\n}\n");
fprintf(yyout,"int error8()\n{printf(\"error!!!!!!!!!!\")\n;\n}\n");
yyparse();

fclose(yyout);



}
