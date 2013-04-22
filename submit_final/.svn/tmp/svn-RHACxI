#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "tokenizer.h"


token cur_tok(tokenizer_t t)
{
  return t->tok;
}

token next_tok(tokenizer_t t)
{
    while( isspace(t->c) ){
	if(t->c == '\n' || t->c == '\r'){
	    t->tok.line++;
	}
	nextget(t);
    }

  
    if( isdigit(t->c) ){
	t->tok.kind = tok_int_literal;
	int val = t->c-'0';
	while( isdigit(nextget(t)) ){
	    val = val*10 + t->c-'0';
	}
	t->tok.int_literal = val;
    }

    else if(t->c == '('){
	t->tok.kind = tok_lparen;
	nextget(t);
    }else if(t->c == ')'){
	t->tok.kind = tok_rparen;
	nextget(t);
    }else if(t->c == '{'){
	t->tok.kind = tok_lbrace;
	nextget(t);
    }else if(t->c == '}'){
	t->tok.kind = tok_rbrace;
	nextget(t);
    }else if(t->c == '['){
	t->tok.kind = tok_lbracket;
	nextget(t);
    }else if(t->c == ']'){
	t->tok.kind = tok_rbracket;
	nextget(t);
    }else if(t->c == '*'){
	t->tok.kind = tok_mul;
	nextget(t);
    }else if(t->c == '+'){
	t->tok.kind = tok_plus;
	nextget(t);
    }else if(t->c == '-'){
	t->tok.kind = tok_minus;
	nextget(t);
    }else if(t->c == '/'){
	if( nextget(t) == '/'){
	    while( !( t->c  == '\n' || t->c == '\r') ) nextget(t);
	    next_tok(t);
	}else if(t->c == '*'){
	    char d;
	    nextget(t);
	    d = t->c;
	    nextget(t);
	    while( !(d=='*' && t->c=='/') ){
		d = t->c;
		nextget(t);
	    }
	    nextget(t);
	    next_tok(t);
	}else{
	    t->tok.kind = tok_div;
	}
    }else if(t->c == '%'){
	t->tok.kind = tok_rem;
	nextget(t);
    }else if(t->c == '!'){
	if( nextget(t) == '='){
	    t->tok.kind = tok_neq;
	    nextget(t);
	}else{
	    t->tok.kind = tok_bang;
	}
    }else if(t->c == '<'){
	if( nextget(t) == '='){
	    t->tok.kind = tok_le;
	    nextget(t);
	}else{
	    t->tok.kind = tok_lt;
	}
    }else if(t->c == '>'){
	if( nextget(t) == '='){
	    t->tok.kind = tok_ge;
	    nextget(t);
	}else{
	    t->tok.kind = tok_gt;
	}
    }else if(t->c == '='){
	if( nextget(t) == '='){
	    t->tok.kind = tok_eq;
	    nextget(t);
	}else{
	    t->tok.kind = tok_assign;
	}
    }else if(t->c == ';'){
	t->tok.kind = tok_semicolon;
	nextget(t);
    }else if(t->c == ','){
	t->tok.kind = tok_comma;
	nextget(t);
    }
  
    else if( (t->c=='_') || (t->c>='A' && t->c<='Z') || (t->c>='a' && t->c<='z') ){
	char_buf_t s = mk_char_buf();

	write_buf(s,t->c);
      
	nextget(t);
	while( (t->c=='_') || (t->c>='A' && t->c<='Z') || (t->c>='a' && t->c<='z') ||
	       (isdigit(t->c)) ){
	    write_buf(s,t->c);
	    nextget(t);
	}
	judge_tok( cur_buf(s) ,t);
      
    }


    else if(t->c == EOF){
	t->tok.kind = tok_eof;
    }else{
	syntax_error(t);
    }
  
    return t->tok;
}

//fgetcしていき、t->cに入れる。返り値は、t->c。next_tok関数で返り値を用いる。
int nextget(tokenizer_t t)
{ 
  t->c = fgetc(t->fp);
  return t->c;
}



tokenizer_t mk_tokenizer(char * filename)
{
    tokenizer_t t = (tokenizer_t)malloc(sizeof(struct tokenizer));
    FILE * fp = fopen(filename, "rb");
    if (fp == NULL) {
	perror("fopen");
	exit(1);
    }  
    t->fp = fp;
  
    t->tok.filename = filename;
    t->tok.line = 0;
  	
    t->c = '\n'; /* 初期値を入れておく。*/
    next_tok(t); /* 一つ目のtokを入れる */
  
    return t;
}



//keywords と identifier を区別
int judge_tok(char *s,tokenizer_t t)
{
    if(strcmp("break",s) == 0)
	{
	    t->tok.kind = tok_break;
	}
    else if(strcmp("continue",s) == 0)
	{
	    t->tok.kind = tok_continue;
	}
    else if(strcmp("else",s) == 0)
	{
	    t->tok.kind = tok_else;
	}
    else if(strcmp("if",s) == 0)
	{
	    t->tok.kind = tok_if;
	}
    else if(strcmp("int",s) == 0)
	{
	    t->tok.kind = tok_int;
	}
    else if(strcmp("while",s) == 0)
	{
	    t->tok.kind = tok_while;
	}
    else if(strcmp("for", s) == 0)
	{
	    t->tok.kind = tok_for;
	}
    else if(strcmp("return",s) == 0)
	{
	    t->tok.kind = tok_return;
	}
    else
	{
	    t->tok.kind = tok_id;
	    t->tok.identifier = s;
			return 0;
	}
	return 1;
}




//TOK_XXX を表示する関数
void print_tok(tokenizer_t t)
{
    if(t->tok.kind == tok_break)
	{
	    printf("TOK_BREAK");
	}
    else if(t->tok.kind == tok_continue)
	{
	    printf("TOK_CONTINUE");
	}
    else if(t->tok.kind == tok_else)
	{
	    printf("TOK_ELSE");
	}
    else if(t->tok.kind == tok_if)
	{
	    printf("TOK_IF");
	}
    else if(t->tok.kind == tok_int)
	{
	    printf("TOK_INT");
	}
    else if(t->tok.kind == tok_return)
	{
	    printf("TOK_RETURN");
	}
    else if(t->tok.kind == tok_while)
	{
	    printf("TOK_WHILE");
	}
    else if(t->tok.kind == tok_for)
	{
	    printf("TOK_FOR");
	}
    else if(t->tok.kind == tok_id)
	{
	    printf("TOK_ID (%s)",t->tok.identifier );
	}
    else if(t->tok.kind == tok_int_literal)
	{
	    printf("TOK_INT_LITERAL (%d)",t->tok.int_literal);
	}
    else if(t->tok.kind == tok_lparen)
	{
	    printf("TOK_LPAREN");
	}
    else if(t->tok.kind == tok_rparen)
	{
	    printf("TOK_RPAREN");
	}
    else if(t->tok.kind == tok_lbrace)
	{
	    printf("TOK_LBRACE");
	}
    else if(t->tok.kind == tok_rbrace)
	{
	    printf("TOK_RBRACE");
	}
    else if(t->tok.kind == tok_mul)
	{
	    printf("TOK_MUL");
	}
    else if(t->tok.kind == tok_plus)
	{
	    printf("TOK_PLUS");
	}
    else if(t->tok.kind == tok_minus)
	{
	    printf("TOK_MINUS");
	}
    else if(t->tok.kind == tok_div)
	{
	    printf("TOK_DIV");
	}
    else if(t->tok.kind == tok_rem)
	{
	    printf("TOK_REM");
	}
    else if(t->tok.kind == tok_bang)
	{
	    printf("TOK_BANG");
	}
    else if(t->tok.kind == tok_lt)
	{
	    printf("TOK_LT");
	}
    else if(t->tok.kind == tok_gt)
	{
	    printf("TOK_GT");
	}
    else if(t->tok.kind == tok_le)
	{
	    printf("TOK_LE");
	}
    else if(t->tok.kind == tok_ge)
	{
	    printf("TOK_GE");
	}
    else if(t->tok.kind == tok_eq)
	{
	    printf("TOK_EQ");
	}
    else if(t->tok.kind == tok_neq)
	{
	    printf("TOK_NEQ");
	}
    else if(t->tok.kind == tok_semicolon)
	{
	    printf("TOK_SEMICOLON");
	}
    else if(t->tok.kind == tok_assign)
	{
	    printf("TOK_ASSIGN");
	}
    else if(t->tok.kind == tok_comma)
	{
	    printf("TOK_COMMA");
	}
}
      


//問題の箇所を表示し、プログラムを終了させる。
int syntax_error(tokenizer_t t)
{
    fprintf(stderr,"syntax_error\n");
    printf("filename : %s\nline : %d\n",t->tok.filename,t->tok.line);
    print_tok(t);
    printf("\n");
  
    exit(1);
}
