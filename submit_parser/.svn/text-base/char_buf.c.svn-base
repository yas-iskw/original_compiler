#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "char_buf.h"



char *cur_buf(char_buf_t t)
{
  return t->buf;
}

void write_buf(char_buf_t t,char c)
{
  if( t->i >= t->limit-1 ){
    char *tmp = (char *)realloc(t->buf,t->limit+50);
    if(tmp == 0){
      perror("realloc");
      exit(1);
    }
    t->buf = tmp;
    
    t->limit += 50;
  }
  
  t->buf[t->i] = c;
  t->buf[t->i + 1] = 0;
  t->i++;
}

void write_str_buf(char_buf_t t,char *str)
{
  int len = strlen(str);
  
  while( t->i + len - 1 >= t->limit-1 ){
    char *tmp = (char *)realloc(t->buf,t->limit+50);
    if(tmp == 0){
      perror("realloc");
      exit(1);
    }
    t->buf = tmp;
    
    t->limit += 50;
  }
  
  strcat( t->buf , str );
  t->i += len;
}

void clear_buf(char_buf_t t){
  t->i = 0;
  t->buf[0] = 0;
}


char_buf_t mk_char_buf()
{
  char_buf_t t = (char_buf_t)malloc(sizeof(struct char_buf));
  if(t == NULL){
    perror("malloc");
    exit(1);
  }
  
  t->buf = (char*)malloc(sizeof(char) *50);
  if(t->buf == NULL){
    perror("malloc");
    exit(1);
  }
  
  t->buf[0] = 0;
  t->i = 0;
  t->limit = 50;
  
  return t;
}
