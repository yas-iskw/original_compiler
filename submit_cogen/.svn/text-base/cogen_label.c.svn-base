#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "syntree.h"
#include "struct_analyzer.h"
#include "tokenizer.h"
#include "util.h"
#include "list.h"
#include "cogen_fun.h"
#include "cogen_label.h"
//最後にヘッダを確認する

/*constracter*/
label_gen_t mk_label(void)
{
  label_gen_t l = (label_gen_t)safe_malloc(sizeof(struct label_gen));
  l->label = 1;
  l->scope.i = -1;
  l->ret_label = 0;
  return l;
}

//pop label
void pop_label(label_gen_t lg,int m,int n)
{
  ++lg->scope.i;
  /* if(i>=100) exit(1); */
  int i = lg->scope.i;
  lg->scope.c[i] = m;
  lg->scope.b[i] = n;
}


//push label
int cur_label_c(label_gen_t lg)
{
  int n = lg->scope.c[lg->scope.i];
  return n;
}

int cur_label_b(label_gen_t lg)
{
  int n = lg->scope.b[lg->scope.i];
  return n;
}


void rem_label(label_gen_t lg)
{
  --lg->scope.i;
}



//これは必要なのかわからないのでとりあえず残しときます。
int eat_label(label_gen_t lg){
  int n = lg->label;
  lg->label++;
  return n;
}

int eat_ret_label(label_gen_t lg)
{
  int n = lg->ret_label;
  return n;
}
