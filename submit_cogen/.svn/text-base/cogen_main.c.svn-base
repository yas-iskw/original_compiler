#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "tokenizer.h"
#include "syntree.h"
#include "struct_analyzer.h"
#include "util.h"
#include "cogen_fun.h"

int main(int argc, char ** argv)
{
  /*char* str;
  int n = strlen(argv[1]);
  str = (char *)safe_malloc(sizeof(char) * (n+1) );
  strcpy(str,argv[1]);
  str[n-1] = 's';
  FILE *fp = fopen(str,"w");
  if(fp == NULL)
    {
      perror("file doesn't open");
      exit(1);
    }*/
  
  tokenizer_t t = mk_tokenizer(argv[1]);
  
  program_t P = parse_program(t);
  
  cogen_program(stdout,P);	//fpも可
  
  return 0;
}
