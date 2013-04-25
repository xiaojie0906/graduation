%union{
int itype;
char str[200];
struct con{
int i_index;
int i_type;
};
struct con stu_index;//index in IDENTIFIER CONSTANT STRING_LITERAL table
//int ival;
//double dval;
//char str[30];
//int type;



}  
%token <stu_index> IDENTIFIER <stu_index>CONSTANT <stu_index>STRING_LITERAL SIZEOF
%token <str>PTR_OP <str>INC_OP <str>DEC_OP <str>LEFT_OP RIGHT_OP LE_OP GE_OP <str>EQ_OP <str>NE_OP
%token <str>AND_OP <str>OR_OP MUL_ASSIGN DIV_ASSIGN MOD_ASSIGN ADD_ASSIGN
%token SUB_ASSIGN LEFT_ASSIGN RIGHT_ASSIGN AND_ASSIGN
%token XOR_ASSIGN OR_ASSIGN TYPE_NAME

%token TYPEDEF EXTERN STATIC AUTO REGISTER INLINE RESTRICT
%token <str>CHAR <str>SHORT <str>INT <str>LONG <str>SIGNED <str>UNSIGNED <str>FLOAT <str>DOUBLE <str>CONST <str>VOLATILE <str>VOID
%token <str>BOOL COMPLEX IMAGINARY
%token STRUCT UNION ENUM ELLIPSIS

%token CASE DEFAULT IF ELSE SWITCH WHILE DO FOR GOTO CONTINUE BREAK RETURN


%type <str>primary_expression
//%type <itype>type_specifier  
%type <str>postfix_expression
%type <str>argument_expression_list
%type <str>ael
%type <str>unary_expression
%type <str>unary_operator
%type <str>cast_expression
%type <str>multiplicative_expression
%type <str>additive_expression
%type <str>shift_expression
%type <str>relational_expression
%type <str>equality_expression
%type <str>and_expression
%type <str>exclusive_or_expression
%type <str>inclusive_or_expression
%type <str>logical_and_expression
%type <str>logical_or_expression
%type <str>conditional_expression
%type <str>assignment_expression
%type <str>assignment_operator
%type <str>expression
%type <str>declaration
%type <str>declaration_specifiers
%type <str>init_declarator_list
%type <str>init_declarator
%type <str>type_specifier
%type <str>declarator
%type <str>direct_declarator
%type <str>pointer
%type <str>parameter_type_list
%type <str>parameter_list
%type <str>parameter_declaration
%type <str>initializer
%type <str>initializer_list
%type <str>statement
%type <str>compound_statement
%type <str>block_item_list
%type <str>block_item
%type <str>expression_statement
%type <str>selection_statement
%type <str>iteration_statement
%type <str>jump_statement
%type <str>translation_unit
%type <str>external_declaration
%type <str>function_definition
%type <str>declaration_list


%start translation_unit

%{
#include<string.h>
#include"common.h"
#include <stdio.h>
#include <stdlib.h>
#include "y.tab.h"
//extern char yytext[];
void printlab();
extern FILE *yyout;
extern FILE *yyin;
int grammar;
int used[250]={0};
/*used for rule 1*/


/*used for rule 2*/
/*used for rule 3*/
int tag_assign_op=0;//assignment operator appeard,
int tag_cond_assign=0;//tag_cond_assign=1,means conditional expression,=2 means assignment expression
/*used for rule 4*/
int in1_out2=2;//in 1 means block in out2 means block out
int eki=0;// associated with ki
int ki=0;// block each block associated with a value
/*used for rule 5*/
/*used for rule 6*/
static int ifor=0;//for for statement ,3 expression_statament,0,first,1,second,2
char for_test[200];//for statement conditional-expresion
/*used for rule 7*/
/*used for rule 8*/
int tag_call_proc=0;//tag call procedure,1,else 0
char function_name[id_len];//save function name in expression,for rule 8, if(ecf!=kj) error
char function_name_table[table_len][id_len];//index is kj
int kj=0;
int ecf=0;//global varible


/*------------------------------*/
int varible[10][2];//save IDENTIFIER in expression
int p_varible=0;//index 0f varible
int vari_level=0;
int tag_assign=0;//tag of assigment_expression  (right)
int tag_for=0;//
int tag_ret=0;//
int tag_if=0;//if statement
int tag_while=0;//while statement
int tag_array=0;
int tag_func_type=1;//function declara type,save type onle once
char decl_type[10];//save type_specifier used for function declaration
int tag_parameter=0;////function parameter declaration,used for r,r_output only once
//char func_name[id_len];//save function name in declaration 
int tag_func_expr=0;//tag for if function used in expression
//struct name_kj{//procedure associated wwith kj;
//char func_name[id_len];
//int kj;
//};
//struct name_kj func_kj[table_len];


char left_expr1[100];
char left_expr[100];//left expression in assignment expression which right part is a function

char condi_expression[200];//save expression for test in if for while;
struct node{
int index;
struct ode * next;
};
struct node  tmp[20];//save primary_expression IDEN index
int p_tmp=0; //index of tmp array
%}


%%

primary_expression
	: IDENTIFIER 
		{grammar=1;
		printlab(grammar);
		strcpy($$,idTable1[$1.i_index]);
		strcpy(left_expr1,idTable1[$1.i_index]);//save init id for left expression
//	//	if(tag_assign&&!tag_if&&!tag_for&&!tag_ret){
	//	varible[p_varible][0]=$1.i_index;
	//	varible[p_varible][1]=vari_level;
		//printf("p_=%d,id_index=%d\n",p_varible,varible[p_varible]);
	//	p_varible++;
	//	}
		}
		 
	| CONSTANT    
		{grammar= 2 ;
		printlab(grammar);
		strcpy($$,strTable[$1.i_index]);
//		strcpy(left_expr1,strTable[$1.i_index]);
		}
	| STRING_LITERAL  
		{grammar= 3 ;
	       	printlab(grammar);
		strcpy($$,strTable[$1.i_index]);
//		strcpy(left_expr1,strTable[$1.i_index]);

		}	
		;

postfix_expression
	: primary_expression  
		{grammar= 5 ; printlab(grammar);}
	|  postfix_expression '[' { vari_level++;tag_array=1;} expression ']' 
		{vari_level--;
		tag_array=0;
		grammar= 6 ;
		printlab(grammar);
		strcat($1,"[");
		strcat($1,$4);
		strcat($1,"]"); 
		strcpy($$,$1);}
	| postfix_expression '(' {tag_call_proc=1;} noael')'//call procedure tag=1 
		{grammar= 7 ;
		printlab(grammar);
		strcpy(function_name,$1);
		strcat($1,"(");
		strcat($1,")");
	        strcpy($$,$1);	
		}

	|  postfix_expression '(' {tag_call_proc=1;} ael ')' //call procedure tag=1 
	{	strcpy(function_name,$1);
		grammar= 8 ; 
		printlab(grammar);
		strcat($1,"(");
		strcat($1,$4);
		strcat($1,")");
	        strcpy($$,$1);	
		}

	| postfix_expression INC_OP  
		{grammar= 11 ; printlab(grammar);
		strcat($1,"++");
		strcpy($$,$1);
		}
	;

noael
	:{
		if(tag_assign_op){
			back(')');
			fprintf(yyout,"&%s",left_expr);//increase parameter &r &r_ in function
			fprintf(yyout,",&%s)",left_expr1);
		}
	
	
	}


ael
	:argument_expression_list
		{     
		back(')');
		fprintf(yyout,",%s",$1);
		
		if(tag_assign_op){
			fprintf(yyout,",&%s",left_expr);
			fprintf(yyout,",&%s)",left_expr1);
		}
		else
			fprintf(yyout,")");
		
		}
argument_expression_list
	: assignment_expression  {grammar= 15 ; printlab(grammar);}
	| argument_expression_list ',' assignment_expression  
		{grammar= 16 ; printlab(grammar);
		strcat($1,",");
		strcat($1,$3);
 		strcpy($$,$1);	
		}
	;

unary_expression
	: postfix_expression  
		{grammar= 17 ;
	       	printlab(grammar);
		if(!tag_assign_op)
		strcpy(left_expr,$1);//save left part;if no '=',save total expression
		
		}
	| INC_OP unary_expression  
		{grammar= 18 ; printlab(grammar);
 		strcpy($$,"++");
		strcat($$,$2);
		}
	| DEC_OP unary_expression  
		{grammar= 19 ; printlab(grammar);
		strcpy($$,"--");
		strcat($$,$2);}
	| unary_operator cast_expression  
		{grammar= 20 ; printlab(grammar);
		strcat($1,$2);
		strcpy($$,$1);
		}
	
	;

unary_operator
	: '&'  {grammar= 23  ;strcpy($$,"&"); printlab(grammar);}
	| '!'  {grammar= 28 ; strcpy($$,"!");printlab(grammar);}
	;

cast_expression
	: unary_expression  {grammar= 29 ; printlab(grammar);}
	
	;

multiplicative_expression
	: cast_expression  {grammar= 31 ; printlab(grammar);}
	| multiplicative_expression '*' cast_expression  
      		{grammar= 32 ; printlab(grammar);
		strcpy($$,$1);
		strcat($$,"*");
		strcat($$,$3);
		}
	| multiplicative_expression '/' cast_expression  
		{grammar= 33 ; printlab(grammar);
		strcpy($$,$1);
		strcat($$,"/");
		strcat($$,$3);}
	| multiplicative_expression '%' cast_expression  
		{grammar= 34; printlab(grammar);
		strcpy($$,$1);
		strcat($$,"%");
		strcat($$,$3);}		
	;

additive_expression
	: multiplicative_expression  {grammar= 35 ; printlab(grammar);}
	| additive_expression '+' multiplicative_expression  
		{grammar= 36 ; printlab(grammar);
		strcpy($$,$1);
		strcat($$,"+");
		strcat($$,$3);
		}
	| additive_expression '-' multiplicative_expression  
		{grammar= 37 ; printlab(grammar);
		strcpy($$,$1);
		strcat($$,"-");
		strcat($$,$3);
		}
	;

shift_expression
	: additive_expression  {grammar= 38 ; printlab(grammar);}
	
	;

relational_expression
	: shift_expression  {grammar= 41 ; printlab(grammar);}
	| relational_expression '<' shift_expression  {grammar= 42 ; printlab(grammar);
		strcpy($$,$1);
		strcat($$,"<");
		strcat($$,$3);}
	| relational_expression '>' shift_expression  {grammar= 43 ; printlab(grammar);
		strcpy($$,$1);
		strcat($$,">");
		strcat($$,$3);}
	
	;

equality_expression
	: relational_expression  {grammar= 46 ; printlab(grammar);}
	| equality_expression EQ_OP relational_expression  {grammar=47  ; printlab(grammar);
		strcpy($$,$1);
		strcat($$,$2);
		strcat($$,$3);}
	| equality_expression NE_OP relational_expression  {grammar= 48 ; printlab(grammar);
		strcpy($$,$1);
		strcat($$,$2);
		strcat($$,$3);}
	;

and_expression
	: equality_expression  {grammar= 49 ; printlab(grammar);}
	
	;

exclusive_or_expression
	: and_expression  {grammar= 51 ; printlab(grammar);}
	
	;

inclusive_or_expression
	: exclusive_or_expression  {grammar=  53; printlab(grammar);}
	//| inclusive_or_expression '|' exclusive_or_expression  {grammar= 54 ; printlab(grammar);}
	;

logical_and_expression
	: inclusive_or_expression  {grammar= 55 ; printlab(grammar);}
	| logical_and_expression AND_OP inclusive_or_expression  {grammar= 56 ; printlab(grammar);
		strcpy($$,$1);
		strcat($$,$2);
		strcat($$,$3);}
	;


logical_or_expression
	: logical_and_expression  {grammar= 57 ; printlab(grammar);}
	| logical_or_expression OR_OP logical_and_expression  {grammar=  58; printlab(grammar);
		strcpy($$,$1);
		strcat($$,$2);
		strcat($$,$3);}
	;

conditional_expression
	: logical_or_expression  {grammar= 59 ; printlab(grammar);}
	//| logical_or_expression '?' expression ':' conditional_expression  {grammar= 60 ; printlab(grammar)};
	;

assignment_expression
	: conditional_expression  {tag_cond_assign=1;grammar= 61 ; printlab(grammar);}//
	| unary_expression assignment_operator assignment_expression //assignment
		{grammar= 62 ; printlab(grammar);
		tag_cond_assign=2;
		strcpy($$,$1);
		strcat($$,$2);
		strcat($$,$3);}
	;


assignment_operator
	: '='   {grammar= 63 ; printlab(grammar);
	strcpy($$,"=");tag_assign=1;
	tag_assign_op=1;//assign operator appear
	}
	| MUL_ASSIGN  {grammar= 64 ; printlab(grammar);}
	| DIV_ASSIGN  {grammar= 65 ; printlab(grammar);}
	| MOD_ASSIGN  {grammar= 66 ; printlab(grammar);}
	| ADD_ASSIGN  {grammar=  67; printlab(grammar);}
	| SUB_ASSIGN  {grammar= 68 ; printlab(grammar);}
	| LEFT_ASSIGN  {grammar=  69; printlab(grammar);}
	| RIGHT_ASSIGN  {grammar=  70; printlab(grammar);}
	| AND_ASSIGN  {grammar= 71 ; printlab(grammar);}
	| XOR_ASSIGN  {grammar= 72 ; printlab(grammar);}
	| OR_ASSIGN  {grammar=  73; printlab(grammar);}
	;  

expression
	: assignment_expression  
		{grammar= 74 ;
		       	printlab(grammar);
			if(tag_if||tag_while){//if it is if_statement
		strcpy(condi_expression,$$);
			}

			tag_assign_op=0;}
	| expression ',' assignment_expression  
		{grammar= 75 ; 
		printlab(grammar);
		strcpy($$,$1);
		strcat($$,",");
		strcat($$,$3);
			if(tag_if||tag_while){
		strcpy(condi_expression,$$);
			}
		}
	;
//constant_expression
	//: conditional_expression  {grammar= 76 ; printlab(grammar);}
	//;

declaration
	: declaration_specifiers ';'  {grammar= 77 ; printlab(grammar);}
	| declaration_specifiers init_declarator_list ';' 
	{
		strcat($1," ");
		strcat($1,$2);
		strcat($1,";");
		strcpy($$,$1);
		grammar=  78;
		fprintf(yyout,"\n%s\n",$$);//print rule ,dumplicate varible;
	 	printlab(grammar);}
	;

declaration_specifiers
	//: storage_class_specifier  {grammar= 79 ; printlab(grammar);}
	//| storage_class_specifier declaration_specifiers  {grammar= 80 ; printlab(grammar);}
	: type_specifier  
		{
		if(tag_func_type)
		strcpy(decl_type,$1);
		tag_func_type=0;
		grammar= 81 ;printlab(grammar);}//printf("@%s@%s@@",$$,$1);}
	//| type_specifier declaration_specifiers  {grammar= 82 ; printlab(grammar);}
	//| type_qualifier  {grammar= 83 ; printlab(grammar);}
	//| type_qualifier declaration_specifiers  {grammar= 84 ; printlab(grammar);}
	//| function_specifier  {grammar=  85; printlab(grammar);}
	//| function_specifier declaration_specifiers  {grammar= 86 ; printlab(grammar);}
	;

init_declarator_list
	: init_declarator  {grammar= 87 ; printlab(grammar);}
	| init_declarator_list ',' init_declarator  
	{grammar= 88 ;
	strcat($1," , ");
 	strcat($1,$3);
        strcpy($$,$1);
	//printf("!!!%s!!!\n",$3);	
		printlab(grammar);}
	; 

init_declarator
	: declarator  {grammar= 89 ;
	//printf("!!!%s!!!\n",$1);	
	       	printlab(grammar);}
	| declarator '=' initializer   
		{grammar= 90 ; printlab(grammar);
		strcat($1,"=");
		strcat($1,$3);
		strcpy($$,$1);
		}
	;

//storage_class_specifier
	//: TYPEDEF  {grammar= 91 ; printlab(grammar);}
	//| EXTERN  {grammar= 92 ; printlab(grammar);}
	//| STATIC  {grammar= 93 ; printlab(grammar);}
	//| AUTO  {grammar= 94 ; printlab(grammar);}
	//| REGISTER  {grammar= 95 ; printlab(grammar);}
	;

type_specifier
	: VOID  {strcpy($$,"void");grammar=  96; printlab(grammar);}//printf("void=%d",$1);}
	| CHAR  {strcpy($$,"char");grammar= 97 ; printlab(grammar);}//printf("!%swww!",$1);
	| SHORT  {strcpy($$,"short");grammar= 98 ; printlab(grammar);}
	| INT  {strcpy($$,"int");grammar= 99 ; printlab(grammar);}//printf("int=%d",$$);}
	| LONG  {strcpy($$,"long");grammar= 100 ; printlab(grammar);}
	| FLOAT  {strcpy($$,"float");grammar= 101 ; printlab(grammar);}
	| DOUBLE  {strcpy($$,"double");grammar= 102 ; printlab(grammar);}
	| SIGNED  {strcpy($$,"signed");grammar= 103 ; printlab(grammar);}
	| UNSIGNED  {strcpy($$,"unsigned");grammar= 104 ; printlab(grammar);}
	| BOOL  {strcpy($$,"bool");grammar=  105; printlab(grammar);}
	| COMPLEX  {strcpy($$,"complex");grammar= 106 ; printlab(grammar);}
	| IMAGINARY  {strcpy($$,"imaginary");grammar=107  ; printlab(grammar);}
	//| struct_or_union_specifier  {grammar= 108 ; printlab(grammar);}
	//| enum_specifier  {grammar= 109 ; printlab(grammar);}
	| TYPE_NAME  {strcpy($$,"typename");grammar= 110 ; printlab(grammar);}
	;

/*struct_or_union_specifier
	: struct_or_union IDENTIFIER '{' struct_declaration_list '}'  {grammar= 111  ; printlab(grammar);}
	| struct_or_union '{' struct_declaration_list '}'  {grammar=112  ; printlab(grammar);}
	| struct_or_union IDENTIFIER  {grammar= 113 ; printlab(grammar);}
	;

struct_or_union
	: STRUCT  {grammar= 114 ; printlab(grammar);}
	| UNION  {grammar= 115 ; printlab(grammar);}
	;

struct_declaration_list
	: struct_declaration  {grammar= 116 ; printlab(grammar);}
	| struct_declaration_list struct_declaration  {grammar= 117 ; printlab(grammar);}
	;

struct_declaration
	: specifier_qualifier_list struct_declarator_list ';'  {grammar= 118 ; printlab(grammar);}
	;

specifier_qualifier_list
	: type_specifier specifier_qualifier_list  {grammar= 119 ; printlab(grammar);}
	| type_specifier  {grammar= 120 ; printlab(grammar);}
	| type_qualifier specifier_qualifier_list  {grammar=  121; printlab(grammar);}
	| type_qualifier  {grammar=122  ; printlab(grammar);}
	;

struct_declarator_list
	: struct_declarator  {grammar= 123 ; printlab(grammar);}
	| struct_declarator_list ',' struct_declarator  {grammar= 124 ; printlab(grammar);}
	;

struct_declarator
	: declarator  {grammar= 125 ; printlab(grammar);}
	| ':' constant_expression  {grammar=  126; printlab(grammar);}
	| declarator ':' constant_expression  {grammar=127  ; printlab(grammar);}
	;

enum_specifier
	: ENUM '{' enumerator_list '}'  {grammar=  128; printlab(grammar);}
	| ENUM IDENTIFIER '{' enumerator_list '}'  {grammar=  129; printlab(grammar);}
	| ENUM '{' enumerator_list ',' '}'  {grammar= 130 ; printlab(grammar);}
	| ENUM IDENTIFIER '{' enumerator_list ',' '}'  {grammar= 131 ; printlab(grammar);}
	| ENUM IDENTIFIER  {grammar= 132 ; printlab(grammar);}
	;

enumerator_list
	: enumerator  {grammar=133  ; printlab(grammar);}
	| enumerator_list ',' enumerator  {grammar= 134 ; printlab(grammar);}
	;$

enumerator
	: IDENTIFIER  {grammar= 135 ; printlab(grammar);}
	| IDENTIFIER '=' constant_expression  {grammar= 136 ; printlab(grammar);}
	;

type_qualifier
	: CONST  {grammar= 137 ; printlab(grammar);}
	| RESTRICT  {grammar= 138 ; printlab(grammar);}
	| VOLATILE  {grammar= 139 ; printlab(grammar);}
	;

function_specifier
	: INLINE  {grammar= 140 ; printlab(grammar);}
	;
*/
declarator
	: pointer direct_declarator  
		{grammar= 141 ; printlab(grammar);
		strcat($1,$2);
		strcpy($$,$1);}
	| direct_declarator  {grammar= 142 ;
	   //printf("!!!%s!!!",$1);    
		printlab(grammar);}
	;


direct_declarator
	: IDENTIFIER  
	{strcpy($$,idTable1[$1.i_index]);
		grammar= 143 ; printlab(grammar);
	}
//	| '(' declarator ')'  {grammar= 144 ; printlab(grammar);}
//	| direct_declarator '[' type_qualifier_list assignment_expression ']'  {grammar= 145 ; printlab(grammar);}
//	| direct_declarator '[' type_qualifier_list ']' {grammar= 146 ; printlab(grammar);}
	| direct_declarator '[' assignment_expression ']' {grammar= 147 ; 
		//printf("mmmm%s\n",$1);
		strcat($1,"[");
		strcat($1,$3);
		strcat($1,"]");
		strcpy($$,$1);
		//printf("mmmm%smmmm%s\n",$3,$$);
		printlab(grammar);}
	//| direct_declarator '[' STATIC type_qualifier_list assignment_expression ']' {grammar= 148 ; printlab(grammar);}
	//| direct_declarator '[' type_qualifier_list STATIC assignment_expression ']' {grammar= 149 ; printlab(grammar);}
	//| direct_declarator '[' type_qualifier_list '*' ']' {grammar= 150 ; printlab(grammar);}
	//| direct_declarator '[' '*' ']' {grammar= 151 ; printlab(grammar);}
	//| direct_declarator '[' ']' {grammar=152  ; printlab(grammar);}
	| direct_declarator '('  parameter_type_list nul ')' 
		{grammar=  153;
		printlab(grammar);
		strcpy(function_name_table[kj],$1);//Rule7,save function in function_name_talble associated with kj	
		strcat($1,"(");
		strcat($1,$3);
		strcat($1,")");
		strcpy($$,$1);}
	//| direct_declarator '(' identifier_list ')' {grammar=154  ; printlab(grammar);}
	| direct_declarator '(' nul1 ')' 
		{
			grammar=155  ; printlab(grammar);
		strcpy(function_name_table[kj],$1);	// rule 7,save function in function_name_talble associated with kj	
		strcat($1,"(");
		strcat($1,")");
		strcpy($$,$1);}
	;
nul
	: {
		if(strcmp(decl_type,"void")!=0)
		fprintf(yyout,",%s *r,%s *r_)",decl_type,decl_type);//X means delete previous char
		else
		fprintf(yyout,")");}
		;
nul1
	:{     
	       back(')');	
		if(strcmp(decl_type,"void")!=0)
		fprintf(yyout,"%s *r,%s *r_)",decl_type,decl_type);//X means delete previous char
		else
		fprintf(yyout,")");}
	;

pointer
	: '*' {grammar=235  ;strcpy($$,"*"); printlab(grammar);}
	//| '*' type_qualifier_list {grammar=236  ; printlab(grammar);}
	//| '*' pointer {grammar=237  ; printlab(grammar);}
	//| '*' type_qualifier_list pointer {grammar=238  ; printlab(grammar);}
	;

/*type_qualifier_list
	: type_qualifier {grammar= 156 ; printlab(grammar);}
	| type_qualifier_list type_qualifier {grammar=157 ; printlab(grammar);}
	;
*/

parameter_type_list
	: parameter_list 
		{grammar=158  ;
	     	 char ch='q';
		fseek(yyout,-1,SEEK_CUR);
		 ch=fgetc(yyout);
		
			while(ch!=')')
		{fseek(yyout,-2,SEEK_CUR);
			ch=fgetc(yyout);
		printf("%c",ch);
		}
		fseek(yyout,-1,SEEK_CUR);

		fprintf(yyout,",%s",$$);//parameter copy
	       	printlab(grammar);}
	//| parameter_list ',' ELLIPSIS {grammar= 159 ; printlab(grammar);}
	;

parameter_list
	: parameter_declaration  {grammar= 160 ; printlab(grammar);}
	| parameter_list ',' parameter_declaration  
		{grammar=  161; printlab(grammar);
		strcat($1,",");
		strcat($1,$3);
		strcpy($$,$1);}
	;

parameter_declaration  
	: declaration_specifiers declarator  
		{grammar= 163 ; printlab(grammar);
	 	strcat($1," ");
		strcat($1,$2);
		strcpy($$,$1);
		}
	//| declaration_specifiers abstract_declarator  {grammar= 164 ; printlab(grammar);}
	//| declaration_specifiers  {grammar=  165; printlab(grammar);}
	;

/*identifier_list
	: IDENTIFIER  {grammar= 166 ; printlab(grammar);}
	| identifier_list ',' IDENTIFIER  {grammar= 167 ; printlab(grammar);}
	;

type_name
	: specifier_qualifier_list  {grammar= 168; printlab(grammar);}
	| specifier_qualifier_list abstract_declarator  {grammar=169  ; printlab(grammar);}
	;

abstract_declarator
	: pointer  {grammar= 170 ; printlab(grammar);}
	| direct_abstract_declarator  {grammar= 171 ; printlab(grammar);}
	| pointer direct_abstract_declarator  {grammar= 172 ; printlab(grammar);}
	;

direct_abstract_declarator
	: '(' abstract_declarator ')'  {grammar= 173 ; printlab(grammar);}
	| '[' ']'  {grammar= 174 ; printlab(gramm
	| '[' assignment_expression ']'  {grammar= 175 ; printlab(grammar);}
	| direct_abstract_declarator '[' ']'  {grammar= 176 ; printlab(grammar);}
	| direct_abstract_declarator '[' assignment_expression ']'  {grammar= 177 ; printlab(grammar);}
	| '[' '*' ']'  {grammar= 178 ; printlab(grammar);}
	| direct_abstract_declarator '[' '*' ']'  {grammar= 179 ; printlab(grammar);}
	| '(' ')'  {grammar= 180 ; printlab(grammar);}
	| '(' parameter_typechar_list ')'  {grammar= 181 ; printlab(grammar);}
	| direct_abstract_declarator '(' ')'  {grammar= 182 ; printlab(grammar);}
	| direct_abstract_declarator '(' parameter_type_list ')'  {grammar= 183 ; printlab(grammar);}
	;
*/
initializer
	: assignment_expression  {grammar=  184; printlab(grammar);}
	| '{' initializer_list '}'  
		{grammar= 185 ; printlab(grammar);
    		strcpy($$,"{");
		strcat($$,$2);
		strcat($$,"}");
	        
}
	| '{' initializer_list ',' '}'  
		{grammar=186  ; printlab(grammar);
		strcpy($$,"{"); 
		strcat($$,$2);
		strcat($$,",");
		strcat($$,"}");
}
	;

initializer_list
	: initializer  {grammar=  187; printlab(grammar);}
	//| designation initializer  {grammar= 188 ; printlab(grammar);}
	| initializer_list ',' initializer  
		{grammar= 189 ; printlab(grammar);
		strcpy($$,$1); 
		strcat($$,",");
		strcat($$,$3);
		}
	//| initializer_list ',' designation initializer  {grammar= 190 ; printlab(grammar);}
	;

/*designation
	: designator_list '='  {grammar= 191 ; printlab(grammar);}
	;

designator_list
	: designator  {grammar=192  ; printlab(grammar);}
	| designator_list designator  {grammar= 193 ; printlab(grammar);}
	;

designator
	: '[' constant_expression ']'  {grammar= 194 ; printlab(grammar);}
	| '.' IDENTIFIER  {grammar= 195 ; printlab(grammar);}
	;
*/
statement
	//: labeled_statement  {grammar=  196; printlab(grammar);}
	: compound_statement  {grammar= 197 ; printlab(grammar);}
	| ineki expression_statement  
		{grammar= 198 ; printlab(grammar);
		}
	| selection_statement  {grammar=  199; printlab(grammar);}
	| iteration_statement  {grammar=  200; printlab(grammar);}
	| jump_statement  {grammar= 201 ; printlab(grammar);}
	;

/*labeled_statement
	: IDENTIFIER ':' statement  {grammar= 202 ; printlab(grammar);}
	| CASE constant_expression ':' statement  {grammar= 203 ; printlab(grammar);}
	| DEFAULT ':' statement  {grammar= 204 ; printlab(grammar);}
	;
*/
compound_statement
	: '{'	'}'
	{grammar= 205 ; printlab(grammar);
		strcpy($$,"{ }");		}

	|'{' block_item_list outeki '}'
	{grammar=  206; printlab(grammar);
		strcpy($$,"{"); 
		strcat($$,$2);
		strcat($$,"}");}
	;
	
	
	;
ineki
	:
	{	/*rule 4,enter into block,print eki=ki */
		if(in1_out2==2&&!tag_for){
		char word[500];
		memset(word,'\0',500);
		saveword('\n',word);//save expression
		fprintf(yyout,"eki=%d;\n%s",ki,word);
		       in1_out2=1;//means has enter in
		}
	}
	;
outeki
	:
	{	/*rule 4,get out block,check eki  */
		if(in1_out2==1){
		char word[500];
		memset(word,'\0',500);
		saveword('\n',word);
		fprintf(yyout,"\nif(eki!=%d)\nerror5();\n%s",ki,word);ki++;
		       in1_out2=2;}
	}
	;

block_item_list
	: block_item  {grammar= 207 ; printlab(grammar);}
	| block_item_list block_item  
		{grammar= 208 ; printlab(grammar);
		strcpy($$,$1); 
		strcat($$,$2);
}
	;

block_item
	: ineki declaration  {grammar=  209; printlab(grammar);}
	| statement  {grammar= 210 ; printlab(grammar);}
	;

expression_statement
	: ';'  {grammar=211  ; strcpy($$,";");printlab(grammar);}
	| expression ';'  
		{grammar= 212 ; printlab(grammar);
		strcpy($$,$1);
	       	strcat($$,";");
		
		/* rule3,check if x1=x2? */	
		if(tag_cond_assign==2&&!tag_call_proc&&!tag_for&&!tag_if&&!tag_ret&&tag_while)//expression right part has not function
		{	
		//	fprintf(yyout,"\n%s\n",$1);//assignment expression
		
			//if not test expression ,print detect
		fprintf(yyout,"if(%s!=%s)\nerror();\n",left_expr,left_expr1);
		}

		/*   rule 8,if call procedure in expression,check ecf*/
		else if(tag_call_proc)
		{
		int kjtmp=0;
		for(kjtmp=0;kjtmp<kj;kjtmp++)//search kj associated with the function
		   if(strcmp(function_name_table[kjtmp],function_name)==0)
			   break;
		if(kjtmp<kj)
		fprintf(yyout,"\nif(ecf!=%d)\nerror8();\n",kjtmp);
		tag_call_proc=0;
		}
		else if(tag_for==1){/*rule 6,in for statement*/	
		
		if(ifor==0)
		{back(';');
			fprintf(yyout,",%s;",$1);
		}
			else if(ifor==1)
		{
		strcpy(for_test,$1);	
				//fprintf(yyout,"&&(%s);",$1);
		}
		ifor++;
				
		}	
		tag_assign=0;
	//	char var[10][50];
	// 	char var1[10][50];
	//	int p_var=0;
	//	memset(var,'\0',50);
	//	memset(var1,'\0',50);

	//	int j=0;
	//	for(j=0;j<p_varible;j++){
	//	if(varible[j][1]==0)
	//			//&&varible[j+1][1]==0)
	//	{
	//	p_var++;
	//		strcpy(var[p_var],idTable[varible[j][0]]);
	//	strcpy(var1[p_var],idTable1[varible[j][0]]);
	//	}
	//	else if(varible[j][1]>varible[j-1][1])
	//	{strcat(var[p_var],"[");
	//	strcat(var[p_var],idTable[varible[j][0]]);
	//	strcat(var1[p_var],"[");
	//	strcat(var1[p_var],idTable1[varible[j][0]]);
	//	}
	//	else if(varible[j][1]==varible[j-1][1])
	//	{strcat(var[p_var],idTable[varible[j][0]]);
	//	strcat(var1[p_var],idTable1[varible[j][0]]);
	//	}	
	//	else if(varible[j][1]>varible[j+1][1])
	//	{int k=varible[j][1]-varible[j+1][1];
	//	strcat(var[p_var],idTable[varible[j][0]]);
	//	strcat(var1[p_var],idTable1[varible[j][0]]);
	//	while(k>0){
	//	strcat(var[p_var],"]");
	//	strcat(var1[p_var],"]");
	//	k--;
	//	}
	//	}	
	//	}
	//	while(p_var){
	//	//fprintf(yyout,"-----%s\n",var[p_var]);
	//	p_var--;
	//	}


	//	p_var=0;
	//	p_varible=0;
		//j=0;
		//			printf("0)\nerror();\n");
	//	int j=0;
	//	for(j=0;j<p_varible;j++){
	//	if(varible[j][1]==0)
	//			//&&varible[j+1][1]==0)
		}
	;

selection_statement
	//: IF {tag_if=1;} '(' expression ')'{tag_if=0;tag_assign=0;} statement  
//		{grammar= 213 ; printlab(grammar);
	: IF  ifsta '(' expression ')'  rule6 statement {grammar= 213 ; printlab(grammar);}
//	| IF '(' ifelse expression ')' statement ELSE statement  {grammar= 214 ; printlab(grammar);}
//	| IF {tag_if=1;}'(' expression ')' statement ELSE statement  {grammar= 214 ; printlab(grammar);}
	//| SWITCH '(' expression ')' statement  {grammar= 215 ; printlab(grammar);}
	;

ifsta 
	:outeki
		{tag_if=1;}
	;
rule6
	:{ /*rule 6,check conditional expression again in target block*/
		char word[100];
		memset(word,'\0',100);
		saveword(')',word);
		//int i=0;
		//for(i=0;i<100;i++)
		//	if(word[i]=='{')
		//	{word[i]=' ';//delete first '{'
		//	break;}
	fprintf(yyout,"--\n{/*add*/ \nif(!(%s))\nerror6();\n%s",condi_expression,word);
		tag_if=0;
		tag_while=0;
	}
whilesta
	:outeki
	{tag_while=1;}
	;
iteration_statement
	: WHILE whilesta '(' expression ')' rule6 statement  {grammar= 216 ; printlab(grammar);}
//| DO statement WHILE '(' expression ')' ';'  {grammar= 217 ; printlab(grammar);}
//	| FOR '(' expression_statement expression_statement ')' statement  {grammar= 218 ; printlab(grammar);}
	| FOR outeki {tag_for=1;}'(' expression_statement expression_statement expression ')' 
		{	
			if(tag_for==1&&ifor==2){
			   back(')');
			fprintf(yyout,",%s)",$7);
			ifor=0;
			}
	fprintf(yyout,"----\n/*add*/ \n{if(!(%s))\nerror6();\n",for_test);

		tag_for=0;
		tag_assign=0;} 
	 statement {grammar= 219 ; printlab(grammar);}
//	| FOR '(' declaration expression_statement ')' statement  {grammar= 220 ; printlab(grammar);}
//	| FOR '(' declaration expression_statement expression ')' statement  {grammar=  221; printlab(grammar);}


jump_statement
	//: GOTO IDENTIFIER ';'  {grammar= 222 ; printlab(grammar);}
	: CONTINUE ';'  {grammar= 223 ; printlab(grammar);}
	| BREAK ';'  {grammar=  224; printlab(grammar);}
	| RETURN outeki ';'  {grammar= 225 ; printlab(grammar);}
	| RETURN outeki { tag_ret=1;} expression ';'  
		{
			tag_ret=0;
			back('\n');	
			fprintf(yyout,"\n*r=%s;\n*r_=%s;\n",$4,$4);
			tag_assign=0;grammar= 226 ; printlab(grammar);}
	;

translation_unit
	: external_declaration  {grammar=227 ; printlab(grammar);tag_func_type=1;}
	| translation_unit external_declaration  {grammar=  228; printlab(grammar);}
	;

external_declaration
	: function_definition  {grammar= 229 ; printlab(grammar);kj++;}
	| declaration  {grammar= 230 ; printlab(grammar);}
	;

function_definition
	: declaration_specifiers  declarator declaration_list compound_statement  {grammar=231  ; printlab(grammar);}
	| declaration_specifiers declarator compound_statement  
	{	grammar= 232 ; printlab(grammar);
		back('}');	
		fprintf(yyout,"ecf=%d;\n",kj);//for rule 7
			fprintf(yyout,"}\n");
	}
	;

declaration_list
	: declaration  {grammar= 233 ; printlab(grammar);}
	| declaration_list declaration  {grammar= 234 ; printlab(grammar);}
	;



%%

void yyerror(char const *s)
{
	fflush(stdout);
	fprintf(yyout,"\n%*s\n%*s\n", column, "^", column, s);
}

void printlab(int i){
used[i]=1;
//fprintf(yyout,"%d\n",i);
}
/*back and delete the char*/
void back(char ch){
fseek(yyout,-1,SEEK_CUR);
char c='\0';
c=fgetc(yyout);
while(c!=ch){
fseek(yyout,-2,SEEK_CUR);
c=fgetc(yyout);
}
fseek(yyout,-1,SEEK_CUR);

}

void saveword(char ch,char word[]){
int i=0;
char tmp[100];
memset(tmp,'\0',100);
	char  c='\0';
	fseek(yyout,-1,SEEK_CUR);
c=fgetc(yyout);
printf("\n%c",c);
while(c!=ch){
strcpy(tmp,&c);
printf("%c",c);
strcat(tmp,word);
strcpy(word,tmp);
	fseek(yyout,-2,SEEK_CUR);
	c=fgetc(yyout);
}


}



