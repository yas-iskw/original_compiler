#include <stdio.h>
#include <stdlib.h>

#include "tokenizer.h"

int main(int argc, char ** argv)
{
  tokenizer_t t = mk_tokenizer(argv[1]);
  int i=1;
  
  while (cur_tok(t).kind != tok_eof) {
    
    if(cur_tok(t).kind == tok_newline){
	i++;
    }else{
    	printf("%d:",i);
	print_tok(t);
	printf("\n");
    }    
    
    next_tok(t);
  }
  return 0;
}
