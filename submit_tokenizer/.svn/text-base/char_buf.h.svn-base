typedef struct char_buf
{
  char *buf;		      /* buffer */
  int i;		      /* 現在の文字数 */
  int limit;		      /* bufferのサイズ */
} * char_buf_t;


char *cur_buf(char_buf_t t);
void write_buf(char_buf_t t,char c);
void write_str_buf(char_buf_t t,char *str);
void clear_buf(char_buf_t t);
char_buf_t mk_char_buf();
