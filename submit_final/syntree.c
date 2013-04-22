/* 
 * syntree.c
 */

#include <assert.h>
#include <stdio.h>
#include "util.h"
#include "list.h"
#include "syntree.h"



/* memory_set コード生成でのメモリ割り当てを決める補助関数 */
memory_set_t mk_memory_set(){
  memory_set_t m = (memory_set_t)safe_malloc(sizeof(struct memory_set));
  m->cur = -4;
  m->max = m->cur;
  return m;
}
int cur_memory_set(memory_set_t m){
  return m->cur;
}
int max_memory_set(memory_set_t m){
  return m->max / (-4);        //必要メモリブロック数を返す。
}
void add_memory_set(memory_set_t m){
  m->cur -= 4;
  if(m->cur < m->max) m->max = m->cur;
}
void delete_memory_set(memory_set_t m){
  m->cur += 4;
};



/* syntree_infoのコンストラクタ */
syntree_info_t mk_syntree_info(int num_var, int rel_val){
  syntree_info_t info = (syntree_info_t)safe_malloc(sizeof(struct syntree_info));
  info->num_var = num_var;
  
  info->kind = 0;  //初期値は0 expressionを想定 //stmt_tもreturn文のみ想定
  info->rel_val = rel_val;
  return info;
}

/* 
 * ----------------------------------
 * 式のコンストラクタ達
 * -----------------------------------
 */

/* 
 * 補助関数 : 種類がkindの式ノードを作る. filename, lineはそれが出現した
 *          ファイル名と行番号(エラーメッセージを表示するために保存する)
 */
static expr_t alloc_expr(char * filename, int line, expr_kind_t kind, memory_set_t m)
{
  expr_t e = (expr_t)safe_malloc(sizeof(struct expr));
  e->filename = filename;
  e->line = line;
  e->kind = kind;
  e->info = mk_syntree_info(0,cur_memory_set(m));
  return e;
}

/* 整数リテラル (0, 1, 2, ...) の式ノードを作る */
expr_t mk_expr_int_literal(char * filename, int line, char * i, memory_set_t m)
{
  expr_t e = alloc_expr(filename, line, expr_kind_int_literal, m);
  e->u.s = i;
  return e;
}

/* 変数 (x, y, foo, bar, ...) の式ノードを作る */
expr_t mk_expr_id(char * filename, int line, char * v, memory_set_t m)
{
  expr_t e = alloc_expr(filename, line, expr_kind_id, m);
  e->u.s = v;
  return e;
}

/* 配列の式ノードを作る */
expr_t mk_expr_array(char * filename, int line, char * v, expr_t p, memory_set_t m)
{
  expr_t e = alloc_expr(filename, line, expr_kind_array, m);
  e->u.ar.s = v;
	e->u.ar.p = p;
  return e;
}

/* 括弧 ( 式 ) の式ノードを作る */
expr_t mk_expr_paren(char * filename, int line, expr_t p, memory_set_t m)
{
  expr_t e = alloc_expr(filename, line, expr_kind_paren, m);
  e->u.p = p;
  return e;
}

/* 関数呼び出し(f(式, 式, ...))の式ノードを作る 
   f : 関数名. args : 引数のリスト */
expr_t mk_expr_call(char * filename, int line, char * f, expr_list_t args, memory_set_t m)
{
  expr_t e = alloc_expr(filename, line, expr_kind_app, m);
  e->u.a.o = op_kind_fun;
  e->u.a.f = f;
  e->u.a.args = args;
  return e;
}

/* 2項演算式の式ノードを作る  */
expr_t mk_expr_bin_op(char * filename, int line, op_kind_t op, expr_t e0, expr_t e1, memory_set_t m)
{
  expr_t e = alloc_expr(filename, line, expr_kind_app, m);
  expr_list_t args = mk_expr_list();
  expr_list_add(args, e0);
  expr_list_add(args, e1);
  e->u.a.o = op;
  e->u.a.f = NULL;
  e->u.a.args = args;
  return e;
}

/* 単項演算式の式ノードを作る  */
expr_t mk_expr_un_op(char * filename, int line, op_kind_t op, expr_t a, memory_set_t m)
{
  expr_t e = alloc_expr(filename, line, expr_kind_app, m);
  expr_list_t args = mk_expr_list();
  expr_list_add(args, a);
  e->u.a.o = op;
  e->u.a.f = NULL;
  e->u.a.args = args;
  return e;
}

/* 式のリスト関係の関数.
   中身は実際には作らずに, list (void *のリスト)
   の関数を呼び出すだけ. */

/* 式のリスト(空)を作る */
expr_list_t mk_expr_list()
{
  return (expr_list_t)mk_list();
}

/* 式のリストに式を追加する */
void expr_list_add(expr_list_t l, expr_t x)
{
  list_add((list_t)l, (void *)x);
}

/* 式のリストのi番目の要素を返す */
expr_t expr_list_get(expr_list_t l, int i)
{
  return (expr_t)list_get((list_t)l, i);
}

/* 式のリストの長さを返す */
int expr_list_sz(expr_list_t l)
{
  return list_sz((list_t)l);
}

/* -------------------------
 * 変数宣言  int z; に相当する構文木のノード
 * intしかないので,
   実質的な情報は変数名だけ 
 * -------------------------
 */

/* コンストラクタ. vは定義される変数名 */
var_decl_t mk_var_decl(char * filename, int line, char * v)
{
  var_decl_t d = (var_decl_t)safe_malloc(sizeof(struct var_decl));
  d->v = v;
  d->info = NULL;
  return d;
}

/* 変数宣言のリスト関係の関数. 意味は expr_listの場合と同じ */
var_decl_list_t mk_var_decl_list()
{
  return (var_decl_list_t)mk_list();
}

void var_decl_list_add(var_decl_list_t l, var_decl_t x)
{
  list_add((list_t)l, (void *)x);
}

var_decl_t var_decl_list_get(var_decl_list_t l, int i)
{
  return (var_decl_t)list_get((list_t)l, i);
}

int var_decl_list_sz(var_decl_list_t l)
{
  return list_sz((list_t)l);
}

/* 
 * ---------------------------------
 * 文
 * ---------------------------------
 */

/* 
 * 補助関数 : 種類がkindの文ノードを作る. filename, lineはそれが出現した
 *          ファイル名と行番号(エラーメッセージを表示するために保存する)
 */
static stmt_t alloc_stmt(char * filename, int line, stmt_kind_t kind)
{
  stmt_t s = (stmt_t)safe_malloc(sizeof(struct stmt));
  s->filename = filename;
  s->line = line;
  s->kind = kind;
  s->info = mk_syntree_info(0,0);
  return s;
}

/* 空文の文ノードを作る */
stmt_t mk_stmt_empty(char * filename, int line)
{
  return alloc_stmt(filename, line, stmt_kind_empty);
}

/* continue文の文ノードを作る */
stmt_t mk_stmt_continue(char * filename, int line)
{
  return alloc_stmt(filename, line, stmt_kind_continue);
}

/* break文の文ノードを作る */
stmt_t mk_stmt_break(char * filename, int line)
{
  return alloc_stmt(filename, line, stmt_kind_break);
}

/* return e; の文ノードを作る */
stmt_t mk_stmt_return(char * filename, int line, expr_t e)
{
  stmt_t s = alloc_stmt(filename, line, stmt_kind_return);
  s->u.e = e;
  return s;
}

/* 式文 e; の文ノードを作る */
stmt_t mk_stmt_expr(char * filename, int line, expr_t e)
{
  stmt_t s = alloc_stmt(filename, line, stmt_kind_expr);
  s->u.e = e;
  return s;
}

/* 複合文 の文ノードを作る. decls : 変数宣言. body 本体の文のリスト */
stmt_t mk_stmt_compound(char * filename, int line, 
			var_decl_list_t decls, stmt_list_t body)
{
  stmt_t s = alloc_stmt(filename, line, stmt_kind_compound);
  s->u.c.decls = decls;
  s->u.c.body = body;
  
  int i;
  int num = 0;
  int sz = stmt_list_sz(body);
  for(i=0;i<sz;i++) num += stmt_list_get(body,i)->info->num_var;
  s->info->num_var = var_decl_list_sz(decls) + num;
  
  return s;
}

/* if文の文ノードを作る (e) th else el  */
stmt_t mk_stmt_if(char * filename, int line, expr_t e, stmt_t th, stmt_t el)
{
  stmt_t s = alloc_stmt(filename, line, stmt_kind_if);
  s->u.i.e = e;
  s->u.i.th = th;
  s->u.i.el = el;
  s->info->num_var = th->info->num_var + th->info->num_var;
  return s;
}

/* while文文の文ノードを作る  while(e) body */
stmt_t mk_stmt_while(char * filename, int line, expr_t e, stmt_t body)
{
  stmt_t s = alloc_stmt(filename, line, stmt_kind_while);
  s->u.w.e = e;
  s->u.w.body = body;
  s->info->num_var = body->info->num_var;
  return s;
}

/* 文のリスト関係 */
stmt_list_t mk_stmt_list()
{
  return (stmt_list_t)mk_list();
}

void stmt_list_add(stmt_list_t l, stmt_t x)
{
  list_add((list_t)l, (void *)x);
}

stmt_t stmt_list_get(stmt_list_t l, int i)
{
  return (stmt_t)list_get((list_t)l, i);
}

int stmt_list_sz(stmt_list_t l)
{
  return list_sz((list_t)l);
}

/* ---------------------------------
 * 関数定義
 * --------------------------------- 
 */

/* コンストラクタ */
fun_def_t mk_fun_def(char * filename, int line, 
		     char * f, var_decl_list_t params, stmt_t body, int memory)
{
  fun_def_t d = (fun_def_t)safe_malloc(sizeof(struct fun_def));
  d->filename = filename;
  d->line = line;
  d->f = f;
  d->params = params;
  d->body = body;
  d->num_var = body->info->num_var;
  d->memory = memory;
  return d;
}

/* 関数定義のリスト関係 */
fun_def_list_t mk_fun_def_list()
{
  return (fun_def_list_t)mk_list();
}

void fun_def_list_add(fun_def_list_t l, fun_def_t x)
{
  list_add((list_t)l, (void *)x);
}

fun_def_t fun_def_list_get(fun_def_list_t l, int i)
{
  return (fun_def_t)list_get((list_t)l, i);
}

int fun_def_list_sz(fun_def_list_t l)
{
  return list_sz((list_t)l);
}

/* ---------------------------------
 * 1ファイル中のプログラム全体
 * --------------------------------- 
 */

/* コンストラクタ */
program_t mk_program(char * filename, fun_def_list_t fun_defs)
{
  program_t p = (program_t)safe_malloc(sizeof(struct program));
  p->filename = filename;
  p->fun_defs = fun_defs;
  return p;
}

/* 
 * 構文木を表示する関数群
 */

/* 式のリストを , で区切りながら表示 */
void pr_expr_list_comma(FILE * fp, expr_list_t es)
{
  int n = expr_list_sz(es);
  int i;
  for (i = 0; i < n; i++) {
    if (i > 0) fprintf(fp, ", ");
    expr_t e = expr_list_get(es, i);
    pr_expr(fp, e);
  }
}

/* opが単項演算子なら演算子を文字列で返す */
char * un_op_to_str(op_kind_t op)
{
  switch (op) {
  case op_kind_un_plus: return "+";
  case op_kind_un_minus: return "-";
  case op_kind_logneg:    return "!";
  default:
    return NULL;
  }
}

/* opが2項演算子なら演算子を文字列で返す */
char * bin_op_to_str(op_kind_t op)
{
  switch (op) {
  case op_kind_assign:    return "=";
  case op_kind_eq:        return "==";
  case op_kind_neq:       return "!=";
  case op_kind_lt:        return "<";
  case op_kind_gt:        return ">";
  case op_kind_le:        return "<=";
  case op_kind_ge:        return ">=";
  case op_kind_bin_plus:  return "+";
  case op_kind_bin_minus: return "-";
  case op_kind_mult:      return "*";
  case op_kind_div:       return "/";
  case op_kind_rem:       return "%";
  default:
    return NULL;
  }
}

/* 式を表示 */
void pr_expr(FILE * fp, expr_t e)
{
  switch (e->kind) {
  case expr_kind_int_literal:
  case expr_kind_id:
    fprintf(fp, "%s", e->u.s);
    break;
  case expr_kind_paren:
    fprintf(fp, "(");
    pr_expr(fp, e->u.p);
    fprintf(fp, ")");
    break;
  case expr_kind_app:
    if (e->u.a.o == op_kind_fun) {
      fprintf(fp, "%s", e->u.a.f);
      fprintf(fp, "(");
      pr_expr_list_comma(fp, e->u.a.args);
      fprintf(fp, ")");
    } else if (un_op_to_str(e->u.a.o)) {
      fprintf(fp, "%s ", un_op_to_str(e->u.a.o));
      pr_expr(fp, expr_list_get(e->u.a.args, 0));
    } else if (bin_op_to_str(e->u.a.o)) {
      pr_expr(fp, expr_list_get(e->u.a.args, 0));
      fprintf(fp, " %s ", bin_op_to_str(e->u.a.o));
      pr_expr(fp, expr_list_get(e->u.a.args, 1));
    } else {
      assert(0);
    }
    break;
  default:
    assert(0);
  }
}

/* 変数宣言を表示 */
void pr_var_decl(FILE * fp, var_decl_t d)
{
  fprintf(fp, "int %s", d->v);
}

/* 変数宣言のリストを表示. 各宣言の後ろに ; をつけて */
void pr_var_decl_list_semicolon(FILE * fp, var_decl_list_t ds)
{
  int n = var_decl_list_sz(ds);
  int i;
  for (i = 0; i < n; i++) {
    var_decl_t d = var_decl_list_get(ds, i);
    pr_var_decl(fp, d);
    fprintf(fp, ";\n");
  }
}

/* 変数宣言のリストを表示. 各宣言の後ろに , をつけて */
void pr_var_decl_list_comma(FILE * fp, var_decl_list_t ds)
{
  int n = var_decl_list_sz(ds);
  int i;
  for (i = 0; i < n; i++) {
    if (i > 0) fprintf(fp, ", ");
    var_decl_t d = var_decl_list_get(ds, i);
    pr_var_decl(fp, d);
  }
}

/* 文のリストを表示 */
void pr_stmt_list(FILE * fp, stmt_list_t ss)
{
  int n = stmt_list_sz(ss);
  int i;
  for (i = 0; i < n; i++) {
    stmt_t s = stmt_list_get(ss, i);
    pr_stmt(fp, s);
  }
}

/* 文を表示 */
void pr_stmt(FILE * fp, stmt_t s)
{
  switch (s->kind) {
  case stmt_kind_empty:
    fprintf(fp, ";\n");
    break;
  case stmt_kind_continue:
    fprintf(fp, "continue;\n");
    break;
  case stmt_kind_break:
    fprintf(fp, "break;\n");
    break;
  case stmt_kind_return:
    fprintf(fp, "return ");
    pr_expr(fp, s->u.e);
    fprintf(fp, ";\n");
    break;
  case stmt_kind_expr:
    pr_expr(fp, s->u.e);
    fprintf(fp, ";\n");
    break;
  case stmt_kind_compound:
    fprintf(fp, "{\n");
    pr_var_decl_list_semicolon(fp, s->u.c.decls);
    pr_stmt_list(fp, s->u.c.body);
    fprintf(fp, "}\n");
    break;
  case stmt_kind_if:
    fprintf(fp, "if (");
    pr_expr(fp, s->u.i.e);
    fprintf(fp, ") ");
    pr_stmt(fp, s->u.i.th);
    if (s->u.i.el) {
      fprintf(fp, " else ");
      pr_stmt(fp, s->u.i.el);
    }
    break;
  case stmt_kind_while:
    fprintf(fp, "while(");
    pr_expr(fp, s->u.w.e);
    fprintf(fp, ") ");
    pr_stmt(fp, s->u.w.body);
    break;
  default:
    assert(0);
  }
}

/* 関数定義を表示 */
void pr_fun_def(FILE * fp, fun_def_t d)
{
  fprintf(fp, "int %s(", d->f);
  pr_var_decl_list_comma(fp, d->params);
  fprintf(fp, ") ");
  pr_stmt(fp, d->body);
}

/* 関数定義のリストを表示 */
void pr_fun_def_list(FILE * fp, fun_def_list_t ds)
{
  int n = fun_def_list_sz(ds);
  int i;
  for (i = 0; i < n; i++) {
    if (i > 0) fprintf(fp, "\n");
    fun_def_t d = fun_def_list_get(ds, i);
    pr_fun_def(fp, d);
  }
}

/* プログラム全体(関数定義のリスト)を表示 */
void pr_program(FILE * fp, program_t p)
{
  pr_fun_def_list(fp, p->fun_defs);
  fprintf(fp, "\n");
}



