#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include <string.h>
#include "cogen_fun.h"
#include "cogen_stmt.h"
#include "cogen_env.h"
#include "cogen_label.h"

/*char *op_kind_to_jump(op_kind_t kind)
{
  switch(kind)
    {
    case op_kind_lt:
      return "jl";
    case op_kind_le:
      return "jle";
    case op_kind_gt:
      return "jg";
    case op_kind_ge:
      return "jge";
    case op_kind_eq:
      return "je";
    case op_kind_neq:
      return "jne";
    }
    }*/


int cogen_stmt(FILE *fp, stmt_t s, env_t env, label_gen_t lg)
{
  switch(s->kind)
    {
    case stmt_kind_return:
      return cogen_stmt_return(fp,s,env,lg);
    case stmt_kind_empty:
      return cogen_stmt_empty(fp,s,env,lg);
    case stmt_kind_continue:
      return cogen_stmt_continue(fp,s,env,lg);
    case stmt_kind_break:
      return cogen_stmt_break(fp,s,env,lg);
    case stmt_kind_expr:
      return cogen_stmt_expr(fp,s,env,lg);
    case stmt_kind_compound:
      return cogen_stmt_compound(fp,s,env,lg);
    case stmt_kind_if:
      return cogen_stmt_if(fp,s,env,lg);
    case stmt_kind_while:
      return cogen_stmt_while(fp,s,env,lg);
    default:
      assert(0);
    }
}


int cogen_stmt_if(FILE *fp,stmt_t s,env_t env,label_gen_t lg)
{
  int m,n;
  m = eat_label(lg);
  n = eat_label(lg);
  char str[16];
  cogen_expr(fp,s->u.i.e,env);
  pos_e(str,s->u.i.e,env);
  fprintf(fp,"\tcmpl\t$0,%s\n",str);
  fprintf(fp,"\tjne\t.L%d\n",m);
  if(s->u.i.el != NULL)
    {
      cogen_stmt(fp,s->u.i.el,env,lg);
    }
  fprintf(fp,"\tjmp\t.L%d\n",n);
  fprintf(fp,".L%d:\n",m);
  cogen_stmt(fp,s->u.i.th,env,lg);
  fprintf(fp,".L%d:\n",n);
  /*intを返すらしい*/
  return 0;
}

int cogen_stmt_while(FILE *fp,stmt_t s,env_t env,label_gen_t lg)
{
  int m,n;
  m = eat_label(lg);
  n = eat_label(lg);
  pop_label(lg,m,n);
  char str[16];
  fprintf(fp,".L%d:\n",m);
  cogen_expr(fp,s->u.w.e,env);
  pos_e(str,s->u.w.e,env);
  fprintf(fp,"\tcmpl\t$0,%s\n",str);
  fprintf(fp,"\tje\t.L%d\n",n);
  cogen_stmt(fp,s->u.w.body,env,lg);
  fprintf(fp,"\tjmp\t.L%d\n",m);
  fprintf(fp,".L%d:\n",n);
  //...
  rem_label(lg);//スタックを一階層上に
  return 0;
}


int cogen_stmt_compound(FILE *fp,stmt_t s,env_t env,label_gen_t lg)
{
  int sz;
  int i;
  env = set_env_vars(s->u.c.decls,env);//宣言された変数を環境に登録、ここではメモリ確保必要ないはず
  sz = stmt_list_sz(s->u.c.body);
  for(i=0;i<sz;i++)
    {
      stmt_t x = stmt_list_get(s->u.c.body,i);
      cogen_stmt(fp,x,env,lg);
    }
  delete_env_vars(env);//スコープ脱出の際に一番上のスタックを環境から削除
  return 0;
}



int cogen_stmt_expr(FILE *fp,stmt_t s,env_t env,label_gen_t lg)
{
  /*cogen_exprとの違いがよく分からんので怪しい*/
  cogen_expr(fp,s->u.e,env);
  return 0;
}


int cogen_stmt_break(FILE *fp,stmt_t s,env_t env,label_gen_t lg)
{
  fprintf(fp,"jmp .L%d\n",cur_label_b(lg));
  return 0;
}


int cogen_stmt_continue(FILE *fp,stmt_t s,env_t env,label_gen_t lg)
{
  fprintf(fp,"jmp .L%d\n",cur_label_c(lg));
  return 0;
}


int cogen_stmt_empty(FILE *fp,stmt_t s,env_t env,label_gen_t lg)
{
  /*よく分からん、謎*/
  return 0;
}

int cogen_stmt_return(FILE *fp,stmt_t s,env_t env,label_gen_t lg)
{
  cogen_stmt_expr(fp,s,env,lg);
  char str[16];
  pos_e(str,s->u.e,env);
  fprintf(fp,"\tmovl\t%s,%%eax\n",str);
  fprintf(fp,"\tjmp\t.RETURN%d\n",eat_ret_label(lg));
  return 0;
}




char *cogen_expr(FILE *fp,expr_t e,env_t env)
{
  switch(e->kind)
    {
    case expr_kind_int_literal:
      return cogen_expr_int_literal(fp,e,env);
    case expr_kind_id:
      return cogen_expr_id(fp,e,env);
    case expr_kind_paren:
      return cogen_expr(fp,e->u.p,env);
    case expr_kind_app:
      return cogen_expr_app(fp,e,env);
    default:
    assert(0);
    }
}





char *cogen_expr_int_literal(FILE *fp,expr_t e,env_t env)
{
  char str[16];
  pos_e(str,e,env);//数字を格納すべきレジスタを示している？？
  fprintf(fp,"\tmovl\t$%d,%s\n",atoi(e->u.s),str);
  return 0;
}


char *cogen_expr_id(FILE *fp,expr_t e,env_t env)
{
  char str1[16];
  char str2[16];
  pos_v(str1,e->u.s,env);
  pos_e(str2,e,env);
  if(judge_c(str2))
    {
      fprintf(fp,"\tmovl\t%s,%s\n",str1,str2);//読んできたメモリをどっかのレジスタに格納する
    }
  else
    {
      fprintf(fp,"\tmovl\t%s,%%edx\n",str1);
      fprintf(fp,"\tmovl\t%%edx,%s\n",str2);
    }

  return 0;
}





//関数呼び出しのcogen lgはいらないかな？
int cogen_expr_call(FILE *fp, expr_t e, env_t env){
  int i;
  int sz = expr_list_sz(e->u.a.args);
  char str[16];
  
  for(i=sz-1;i>=0;i--){
    cogen_expr(fp, expr_list_get(e->u.a.args,i), env);
    pos_e(str, expr_list_get(e->u.a.args,i) , env);
    fprintf(fp,"\tpushl\t%s\n",str);
  }
  fprintf(fp,"\tmovl\t%%ecx, %d(%%ebp)\n",address_env(env)-4);
  fprintf(fp,"\tcall\t%s\n",e->u.a.f);
  fprintf(fp,"\taddl\t$%d, %%esp\n",sz*4);
  fprintf(fp,"\tmovl\t%d(%%ebp), %%ecx\n",address_env(env)-4);
  pos_e(str, e, env);
  fprintf(fp,"\tmovl\t%%eax, %s\n",str);
  return 0;
}



//二項演算子によって命令を発行する関数
char *bin_op_to_order(op_kind_t kind)
{
  switch(kind)
    {
    case op_kind_bin_plus:
      return "addl";
    case op_kind_bin_minus:
      return "subl";
    case op_kind_mult:
      return "imull";
    case op_kind_div:
      return "idivl";
    case op_kind_rem:
      return "idivl";
    case op_kind_eq:
      return "e";
    case op_kind_neq:
      return "ne";
    case op_kind_lt:
      return "l";
    case op_kind_gt:
      return "g";
    case op_kind_le:
      return "le";
    case op_kind_ge:
      return "ge";
    default:
      assert(0);
    }
}

//単行演算の場合分けを行う関数
void un_op_cul(FILE *fp,op_kind_t kind,char *s1)
{
  if(kind == op_kind_un_minus)
    {
      fprintf(fp,"\tnegl\t%s\n",s1);
    }
  else if(kind == op_kind_logneg)
    {
      fprintf(fp,"\tcmpl\t$0,%s\n",s1);
      fprintf(fp,"\tsete\t%%al\n");
      fprintf(fp,"\tmovzbl\t%%al,%%edx\n");
      fprintf(fp,"\tmovl\t%%edx,%s\n",s1);
    }
}



//二項演算の場合分けを行う関数
void bin_op_cul(FILE *fp,op_kind_t kind,char *s1,char *s2)
{
  if(kind == op_kind_bin_plus||kind == op_kind_bin_minus)
    {
      fprintf(fp,"\t%s\t%s,%s\n",bin_op_to_order(kind),s2,s1);
    }
  else if(kind == op_kind_mult)
    {
      fprintf(fp,"\tmovl\t%s,%%eax\n",s1);
      fprintf(fp,"\timull\t%s,%%eax\n",s2);
      fprintf(fp,"\tmovl\t%%eax,%s\n",s1);
    }
  else if(kind == op_kind_eq||kind == op_kind_neq||kind == op_kind_lt||kind == op_kind_gt||kind == op_kind_le||kind == op_kind_ge)
    {
      fprintf(fp,"\tcmpl\t%s,%s\n",s2,s1);
      fprintf(fp,"\tset%s\t%%al\n",bin_op_to_order(kind));
      if(judge_c(s1))
	{
	  fprintf(fp,"\tmovzbl\t%%al,%s\n",s1);
	}
      else
	{
	  fprintf(fp,"\tmovzbl\t%%al,%%edx\n");
	  fprintf(fp,"\tmovl\t%%edx,%s\n",s1);
	}
    }
  else if(kind == op_kind_assign)
    {
      fprintf(fp,"\tmovl\t%s,%s\n",s2,s1);
    }
  else if(kind == op_kind_div)
    {
      fprintf(fp,"\tmovl\t%s,%%eax\n",s1);
      fprintf(fp,"\tmovl\t%%eax,%%edx\n");
      fprintf(fp,"\tsarl\t$31,%%edx\n");
      fprintf(fp,"\tidivl\t%s\n",s2);
      fprintf(fp,"\tmovl\t%%eax,%s\n",s1);
    }
  else if(kind == op_kind_rem)
    {
      fprintf(fp,"\tmovl\t%s,%%eax\n",s1);
      fprintf(fp,"\tmovl\t%%eax,%%edx\n");
      fprintf(fp,"\tsarl\t$31,%%edx\n");
      fprintf(fp,"\tidivl\t%s\n",s2);
      fprintf(fp,"\tmovl\t%%edx,%s\n",s1);
    }
}




char *cogen_expr_app(FILE *fp,expr_t e,env_t env)
{
  if(e->u.a.o == op_kind_fun)
    {
      cogen_expr_call(fp,e,env);
    }
  else
    {
      char str1[16];
      char str2[16];
      if(e->u.a.o != op_kind_assign)
	{
	  cogen_expr(fp,expr_list_get(e->u.a.args,0),env);
	}
      pos_e(str1,expr_list_get(e->u.a.args,0),env);
      if(judge_op_bin(e->u.a.o))
	{
	  cogen_expr(fp,expr_list_get(e->u.a.args,1),env);
	  pos_e(str2,expr_list_get(e->u.a.args,1),env);
	  if(judge_e(expr_list_get(e->u.a.args,0),expr_list_get(e->u.a.args,1))&&e->u.a.o != op_kind_div&&e->u.a.o != op_kind_rem)
	    {
	      fprintf(fp,"\tmovl\t%s,%%edx\n",str2);
	      bin_op_cul(fp,e->u.a.o,str1,"%edx");
	    }
	  else
	    {
	      bin_op_cul(fp,e->u.a.o,str1,str2);
	      //ここでなんかしらの二項演算を行う感じ,種類はe->u.a.oに従う
	    }
	  if(e->u.a.o == op_kind_assign)
	    {
	      if(expr_list_get(e->u.a.args,0)->kind != expr_kind_id)
		{
		  printf("左側が変数ではありません\n");
		  exit(1);
		}
	      else 
		{
		  pos_v(str2,expr_list_get(e->u.a.args,0)->u.s,env);
		  if(judge_c(str1))
		    {
		      fprintf(fp,"\tmovl\t%s,%s\n",str1,str2);
		    }
		  else
		    {
		      fprintf(fp,"\tmovl\t%s,%%edx\n",str1);
		      fprintf(fp,"\tmovl\t%%edx,%s\n",str2);
		    }
		}
	    }
	}
      else
	{
	  un_op_cul(fp,e->u.a.o,str1);
	  //ここで単行演算を行う感じ,種類はe->u.a.oに従う
	}
    }
  return 0;
}

int judge_op_bin(op_kind_t kind)
{
  if(kind == op_kind_un_plus||kind == op_kind_un_minus||kind == op_kind_logneg)
    {
      return 0;
    }
  else
    {
      return 1;
    }
}
