#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "syntree.h"
#include "struct_analyzer.h"
#include "tokenizer.h"
#include "util.h"
#include "list.h"
#include "cogen_fun.h"
#include "cogen_env.h"
#include "cogen_label.h"
#include "cogen_stmt.h"

int cogen_fun_def(FILE *fp, fun_def_t d, label_gen_t lg)
{

  int frame_sz = d->num_var + d->memory;        //関数内変数、計算に必要なメモリブロックの個数

  env_t env = mk_env( d->num_var * (-4) );
  
  env = set_env_params(d->params,env);
   
  cogen_fun_def_header(fp,d->f);
  
  cogen_prologue(fp,frame_sz,env);
  
  cogen_stmt(fp,d->body,env,lg);
  
  cogen_epilogue(fp,lg,env);
  
  cogen_fun_def_trailer(fp,d->f);
  
  return 0;
}


int cogen_program(FILE *fp, program_t p)
{
  label_gen_t lg = mk_label();
  
  cogen_program_header(fp,p->filename);
  fun_def_list_t ds = p->fun_defs;
  int n = fun_def_list_sz(ds);
  int i;
  for(i=0;i<n;i++)
    {
      fun_def_t d = fun_def_list_get(ds,i);
      cogen_fun_def(fp,d,lg);
      lg->ret_label++;
    }
  cogen_program_trailer(fp);
  return 0;
}




/* headerなど */
void cogen_program_header(FILE *fp, char* filename){
	fprintf(fp,"\t.file\t\"%s\"\n\t.text\n",filename);
}

//Ubuntu...  は後で変数化しましょう
void cogen_program_trailer(FILE *fp){
	fprintf(fp,"\t.ident\t\"GCC: (Ubuntu 4.4.3-4ubuntu5.1) 4.4.3\"\n\t.section\t.note.GNU-stack,\"\",@progbits\n");
}

void cogen_fun_def_header(FILE *fp, char* fun_name){
	fprintf(fp,".globl %s\n\t.type\t%s, @function\n%s:\n",fun_name,fun_name,fun_name);
}

void cogen_fun_def_trailer(FILE *fp, char* fun_name){
	fprintf(fp,"\t.size\t%s, .-%s\n",fun_name,fun_name);
}

void cogen_prologue(FILE* fp, int frame_sz, env_t env){
                int n = ( frame_sz + 3 ) * 4;
	
	fprintf(fp,"\tpushl\t%%ebp\n\tmovl\t%%esp, %%ebp\n");
	fprintf(fp,"\tsubl\t$%d, %%esp\n",n);
	//------------------------------
	fprintf(fp,"\tpushl\t%%ebx\n");	/* ebxのみ使用 */
	//fprintf(fp,"\tmovl\t%%ebx, %d(%%ebp)\n",address_env(env) -12 );	/* esi未使用 */
	//fprintf(fp,"\tmovl\t%%ebx, %d(%%ebp)\n",address_env(env) -16 );	/* edi未使用 */
	//------------------------------
}

void cogen_epilogue(FILE* fp,label_gen_t lg, env_t env){
  fprintf(fp,".RETURN%d:\n",eat_ret_label(lg));
  //------------------------------
  fprintf(fp,"\tpopl\t%%ebx\n");	/* ebxのみ使用 */
	//fprintf(fp,"\tmovl\t%d(%%ebp), %%ebx\n",address_env(env) -8 );	/* esi未使用 */
	//fprintf(fp,"\tmovl\t%d(%%ebp), %%ebx\n",address_env(env) -8 );	/* edi未使用 */
  //------------------------------
  fprintf(fp,"\tleave\n\tret\n");
}

