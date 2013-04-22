#pragma once


typedef struct label_gen
{
  int label;//次に使うべきラベルの番号
  int ret_label;//RETURNに使うラベルの番号
  struct scope
  {
    int b[100];//breakのほう、スコープから出た先のラベルの番号をスタックで表す
    int c[100];//continueのほう
    int i;//現在いる番号を表示、0番目から始める
  }scope;
}label_gen;

typedef  label_gen* label_gen_t;

int eat_label(label_gen_t lg);//使うべき番号を返す。返したらlabelの数字を++
int eat_ret_label(label_gen_t lg);
label_gen_t mk_label(void);
void pop_label(label_gen_t lg,int m,int n);
int cur_label_c(label_gen_t lg);
int cur_label_b(label_gen_t lg);
void rem_label(label_gen_t lg);
