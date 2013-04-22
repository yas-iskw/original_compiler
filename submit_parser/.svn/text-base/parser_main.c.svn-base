/* 
 * parser_main.c
 */

/* 構文木を表示するプログラム */
#include <stdio.h>
#include <stdlib.h>
#include "tokenizer.h"
#include "syntree.h"
#include "struct_analyzer.h"

int main(int argc, char ** argv)
{
  tokenizer_t t = mk_tokenizer(argv[1]);
  
  program_t P = parse_program(t);
  
  pr_program(stdout, P);
  
  return 0;
}
