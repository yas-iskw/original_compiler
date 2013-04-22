#pragma once

#include "char_buf.h"

typedef enum{
  tok_break,
  tok_continue,
  tok_else,
  tok_if,
  tok_int,
  tok_return,
  tok_while,
  tok_for,//新規追加のfor文用のtoken_kind
  tok_id,
  tok_int_literal,
  tok_lparen,
  tok_rparen,
  tok_lbrace,
  tok_rbrace,
  tok_lbracket,//[
  tok_rbracket,//]
  tok_mul,
  tok_plus,
  tok_minus,
  tok_div,
  tok_rem,
  tok_bang,
  tok_lt,
  tok_gt,
  tok_le,
  tok_ge,
  tok_eq,
  tok_neq,
  tok_semicolon,
  tok_assign,
  tok_comma,
  tok_eof
}token_kind_t;


typedef struct token
{
  token_kind_t kind;
  char* identifier;
  int int_literal;
  
  char* filename;
  int line;
}token;

typedef struct tokenizer
{
  token tok;		      /* 最後に読んだ字句 */
  int c;		      /* 最後に読んだ文字(=tokの一文字後ろ) */
  FILE *fp;
} * tokenizer_t;



token cur_tok(tokenizer_t t);
token next_tok(tokenizer_t t);
tokenizer_t mk_tokenizer(char * filename);

//fgetcしていき、空白は読み飛ばし、空白以外がきたらt->cに入れる。返り値は、数字の直後に数字がくるときのみ1を返し、それ以外は0を返す。next_tok関数で返り値を用いる。
int nextget(tokenizer_t t);

//文字列を渡すと、keywordsかidentifierか判断してくれる。
int judge_tok(char *s,tokenizer_t t);

//TOK_XXX を表示する関数
void print_tok(tokenizer_t t);

//問題の箇所を表示し、プログラムを終了させる。
int syntax_error(tokenizer_t t);
