#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_analyzer.h"
#include "tokenizer.h"
#include "syntree.h"
#include "list.h"
#include "util.h"

void eat_it(tokenizer_t t, token_kind_t kind)
{
  if(t->tok.kind == kind)
    {
      next_tok(t);
    }
  else
    {
      syntax_error(t);
    }
}


char* eat_it_id(tokenizer_t t)
{
  if(t->tok.kind == tok_id)
    {
      char *buf = t->tok.identifier;
      next_tok(t);
      return buf;
    }

  else
    {
      syntax_error(t);
      return 0;
    }
}

//tok_XXX を op_kind_XXX に変える関数（二項版）
op_kind_t judge_bin_op(tokenizer_t t){
	if(cur_tok(t).kind == tok_assign){
		eat_it(t,tok_assign);
		return op_kind_assign;
	}else if(cur_tok(t).kind == tok_eq){
		eat_it(t,tok_eq);
		return op_kind_eq;
	}else if(cur_tok(t).kind == tok_neq){
		eat_it(t,tok_neq);
		return op_kind_neq;
	}else if(cur_tok(t).kind == tok_lt){
		eat_it(t,tok_lt);
		return op_kind_lt;
	}else if(cur_tok(t).kind == tok_gt){
		eat_it(t,tok_gt);
		return op_kind_gt;
	}else if(cur_tok(t).kind == tok_le){
		eat_it(t,tok_le);
		return op_kind_le;
	}else if(cur_tok(t).kind == tok_ge){
		eat_it(t,tok_ge);
		return op_kind_ge;
	}else if(cur_tok(t).kind == tok_plus){
		eat_it(t,tok_plus);
		return op_kind_bin_plus;
	}else if(cur_tok(t).kind == tok_minus){
		eat_it(t,tok_minus);
		return op_kind_bin_minus;
	}else if(cur_tok(t).kind == tok_mul){
		eat_it(t,tok_mul);
		return op_kind_mult;
	}else if(cur_tok(t).kind == tok_div){
		eat_it(t,tok_div);
		return op_kind_div;
	}else if(cur_tok(t).kind == tok_rem){
		eat_it(t,tok_rem);
		return op_kind_rem;
	}
	syntax_error(t);
	exit(1);
}

//tok_XXX を op_kind_XXX に変える関数（単項版）
op_kind_t judge_un_op(tokenizer_t t){
	if(cur_tok(t).kind == tok_plus){
		eat_it(t,tok_plus);
		return op_kind_un_plus;
	}else if(cur_tok(t).kind == tok_minus){
		eat_it(t,tok_minus);
		return op_kind_un_minus;
	}else if(cur_tok(t).kind == tok_bang){
		eat_it(t,tok_bang);
		return op_kind_logneg;
	}
	syntax_error(t);	
	exit(1);
}


//unary-operatorかどうか判別する関数
int if_unary_ope(tokenizer_t t){
  if(cur_tok(t).kind == tok_plus ||cur_tok(t).kind == tok_minus || cur_tok(t).kind == tok_bang){
    return 1;
  }
  else{
    return 0;
  }
}
    
//multiplicative-operatorかどうか判別する関数
int if_mult_ope(tokenizer_t t){
  if(cur_tok(t).kind == tok_mul || cur_tok(t).kind == tok_div || cur_tok(t).kind == tok_rem){
    return 1;
  }
  else{
    return 0;
  }
}

//relation-operatorかどうか判別する関数
int if_rel_ope(tokenizer_t t){
  if(cur_tok(t).kind == tok_lt || cur_tok(t).kind == tok_gt || cur_tok(t).kind == tok_ge || cur_tok(t).kind == tok_le){
    return 1;
  }
  else{
    return 0;
  }
}

//additive-operatorか判別する関数
int if_add_ope(tokenizer_t t){
  if(cur_tok(t).kind == tok_plus || cur_tok(t).kind == tok_minus){
    return 1;
  }
  else{
    return 0;
  }
}

//equality-operatorかどうか判別する関数
int if_equ_ope(tokenizer_t t){
  if(cur_tok(t).kind == tok_eq || cur_tok(t).kind == tok_neq){
    return 1;
  }
  else{
    return 0;
  }
}


//program
program_t parse_program(tokenizer_t t){
	char *filename = cur_tok(t).filename;
	fun_def_list_t f = mk_fun_def_list();
	while( cur_tok(t).kind != tok_eof ){
		fun_def_list_add(f, parse_definition(t));
	}
	return mk_program(filename,f);
}

//definition
fun_def_t parse_definition(tokenizer_t t){
	return parse_fun_def(t);
}

//function-definition
fun_def_t parse_fun_def(tokenizer_t t){
	char *filename = cur_tok(t).filename;
	int line = cur_tok(t).line;
	
	eat_it(t,tok_int);
	char *identifier =eat_it_id(t);
	eat_it(t,tok_lparen);
	var_decl_list_t params = parse_parameter_list(t);
	eat_it(t,tok_rparen);
	stmt_t body = parse_stmt_comp(t);	
	return mk_fun_def(filename, line, identifier, params, body);
}

//parameter-list
var_decl_list_t parse_parameter_list(tokenizer_t t){
	var_decl_list_t l = mk_var_decl_list();
	int i=0;//現在読み込んだparameterの数
	
	while( cur_tok(t).kind != tok_rparen){
	  if(i>=1) eat_it(t,tok_comma);
	  var_decl_list_add(l, parse_parameter(t));
	  i++;
	}
	
	return l;
}

//parameter
var_decl_t parse_parameter(tokenizer_t t){
	char *filename = cur_tok(t).filename;
	int line = cur_tok(t).line;
	
	eat_it(t,tok_int);
	char *identifier = eat_it_id(t);
	
	return mk_var_decl(filename, line, identifier);
}

//statement
stmt_t parse_stmt(tokenizer_t t){
	char *filename = cur_tok(t).filename;
	int line = cur_tok(t).line;

	if(cur_tok(t).kind == tok_semicolon){
		eat_it(t,tok_semicolon);
		return mk_stmt_empty(filename, line);
	}else if(cur_tok(t).kind == tok_continue){
		eat_it(t,tok_continue);
		eat_it(t,tok_semicolon);
		return mk_stmt_continue(filename, line);
	}else if(cur_tok(t).kind == tok_break){
		eat_it(t,tok_break);
		eat_it(t,tok_semicolon);
		return mk_stmt_break(filename, line);
	}else if(cur_tok(t).kind == tok_return){
		eat_it(t,tok_return);
		expr_t e = parse_expr(t);
		eat_it(t,tok_semicolon);
		return mk_stmt_return(filename, line, e);
	}else if(cur_tok(t).kind == tok_lbrace){
		return parse_stmt_comp(t);
	}else if(cur_tok(t).kind == tok_if){
		return parse_stmt_if(t);
	}else if(cur_tok(t).kind == tok_while){
		return parse_stmt_while(t);
	}else {
		expr_t e = parse_expr(t);
		eat_it(t,tok_semicolon);
		return mk_stmt_expr(filename, line, e);	
	}	
}



stmt_t parse_stmt_while(tokenizer_t t)
{
  char *filename = cur_tok(t).filename;
  int line = cur_tok(t).line;
  eat_it(t,tok_while);
  eat_it(t,tok_lparen);
  expr_t e = parse_expr(t);
  eat_it(t,tok_rparen);
  stmt_t body = parse_stmt(t);
  return mk_stmt_while(filename,line,e,body);
}




//if-statementを読む関数
stmt_t parse_stmt_if(tokenizer_t t)
{
  char *filename = cur_tok(t).filename;
  int line = cur_tok(t).line;
  eat_it(t,tok_if);
  eat_it(t,tok_lparen);
  expr_t e = parse_expr(t);
  eat_it(t,tok_rparen);
  stmt_t body1 = parse_stmt(t);
  if(t->tok.kind != tok_else)
    {
      return mk_stmt_if(filename,line,e,body1,NULL);
    }
  else
    {
      eat_it(t,tok_else);
      stmt_t body2 = parse_stmt(t);
      return mk_stmt_if(filename,line,e,body1,body2);
    }
}


//var-declarationを読む
var_decl_t parse_dec_var(tokenizer_t t)
{
  char *filename = cur_tok(t).filename;
  int line = cur_tok(t).line;
  eat_it(t,tok_int);
  char *identifier = eat_it_id(t);
  eat_it(t,tok_semicolon);
  return mk_var_decl(filename,line,identifier);

}



//compound-statementを読む
stmt_t parse_stmt_comp(tokenizer_t t)
{
  char *filename = cur_tok(t).filename;
  int line = cur_tok(t).line;
  eat_it(t,tok_lbrace);
  var_decl_list_t list_v = mk_var_decl_list();
  while(t->tok.kind == tok_int)
    {
      var_decl_list_add(list_v,parse_dec_var(t));
    }

  stmt_list_t list_s = mk_stmt_list();
  while(t->tok.kind != tok_rbrace)
    {
      stmt_list_add(list_s,parse_stmt(t));
    }
  eat_it(t,tok_rbrace);
  return mk_stmt_compound(filename,line,list_v,list_s);
}

//expressionを読む関数
expr_t parse_expr(tokenizer_t t)
{
  char *filename = cur_tok(t).filename;
  int line = cur_tok(t).line;
  expr_t a  = parse_expr_equal(t);
  if(cur_tok(t).kind == tok_assign)
    {
      eat_it(t,tok_assign);
      expr_t b = parse_expr(t);
      a = mk_expr_bin_op(filename,line,op_kind_assign,a,b);
    }
  return a;
}

//equality-expressionを読む関数
expr_t parse_expr_equal(tokenizer_t t)
{
  char *filename = cur_tok(t).filename;
  int line = cur_tok(t).line;
  expr_t a = parse_expr_rel(t);
  while(if_equ_ope(t))
    {
      op_kind_t op = judge_bin_op(t);
      expr_t b = parse_expr_rel(t);
      a = mk_expr_bin_op(filename,line,op,a,b);
    }
  return a;
}




//unary-expressionを読む関数
expr_t parse_expr_unary(tokenizer_t t)
{
  char *filename =  cur_tok(t).filename;
  int line = cur_tok(t).line;
  if(cur_tok(t).kind == tok_int_literal)
    {
      char *s = (char*)safe_malloc(20);//20取っておけばint型を文字列化するのには十分
      sprintf(s,"%d",t->tok.int_literal);
      eat_it(t,tok_int_literal);
      return mk_expr_int_literal(filename,line,s);
    }
  else if(cur_tok(t).kind == tok_id)
    {
      char *s = t->tok.identifier;
      next_tok(t);
      if(cur_tok(t).kind != tok_lparen)
	{
	  return mk_expr_id(filename,line,t->tok.identifier);
	}
      else
	{
	  eat_it(t,tok_lparen);
	  if(cur_tok(t).kind == tok_rparen)
	    {
	      expr_list_t h = mk_expr_list();
	      eat_it(t,tok_rparen);
	      return mk_expr_call(filename,line,s,h);
	    }
	  else
	    {
	      expr_list_t h = parse_expr_list(t);
	      eat_it(t,tok_rparen);
	      return mk_expr_call(filename,line,s,h);
	    }
	}
    }
  else if(cur_tok(t).kind == tok_lparen)
    {
      eat_it(t,tok_lparen);
      expr_t e = parse_expr(t);
      eat_it(t,tok_rparen);
      return mk_expr_paren(filename,line,e);
    }
  else if(if_unary_ope(t))
    {
      op_kind_t op = judge_un_op(t);
      expr_t e = parse_expr_unary(t);
      return mk_expr_un_op(filename,line,op,e);
    }
  syntax_error(t);
  exit(1);
}

//argument-expression-listを読む関数
expr_list_t parse_expr_list(tokenizer_t t)
{

  expr_list_t h = mk_expr_list();
  expr_list_add(h,parse_expr(t));
  while(cur_tok(t).kind == tok_comma)
    {
      eat_it(t,tok_comma);
      expr_list_add(h,parse_expr(t));
    }
  return h;
}




expr_t parse_expr_mul(tokenizer_t t)
{
  char *filename = cur_tok(t).filename;
  int line = cur_tok(t).line;
  expr_t a = parse_expr_unary(t);
  while(if_mult_ope(t))
    {
      op_kind_t op = judge_bin_op(t);
      expr_t b = parse_expr_unary(t);
      a = mk_expr_bin_op(filename,line,op,a,b);
    }
  return a;
}

//
expr_t parse_expr_add(tokenizer_t t)
{
  char *filename = cur_tok(t).filename;
  int line = cur_tok(t).line;
  expr_t a  = parse_expr_mul(t);
  while(if_add_ope(t))
    {
      op_kind_t op = judge_bin_op(t);
      expr_t b = parse_expr_mul(t);
      a = mk_expr_bin_op(filename,line,op,a,b);
    }
  return a;
}

//
expr_t parse_expr_rel(tokenizer_t t)
{
  char *filename = cur_tok(t).filename;
  int line = cur_tok(t).line;
  expr_t a =  parse_expr_add(t);
  while(if_rel_ope(t))
    {
      op_kind_t op = judge_bin_op(t);
      expr_t b = parse_expr_add(t);
      a = mk_expr_bin_op(filename,line,op,a,b);
    }
  return a;
}
