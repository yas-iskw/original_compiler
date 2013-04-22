#pragma once
#include "syntree.h"
#include "cogen_env.h"
#include "cogen_label.h"

int cogen_stmt(FILE *fp,stmt_t s,env_t env,label_gen_t lg);
char *cogen_expr(FILE *fp,expr_t e,env_t env);


int cogen_stmt_return(FILE *fp,stmt_t s,env_t env, label_gen_t lg);
int cogen_stmt_empty(FILE *fp,stmt_t s,env_t env, label_gen_t lg);
int cogen_stmt_continue(FILE *fp,stmt_t s,env_t env, label_gen_t lg);
int cogen_stmt_break(FILE *fp,stmt_t s,env_t env, label_gen_t lg);
int cogen_stmt_expr(FILE *fp,stmt_t s,env_t env, label_gen_t lg);
int cogen_stmt_compound(FILE *fp,stmt_t s,env_t env, label_gen_t lg);
int cogen_stmt_if(FILE *fp,stmt_t s,env_t env, label_gen_t lg);
int cogen_stmt_while(FILE *fp,stmt_t s,env_t env, label_gen_t lg);


char * cogen_expr_int_literal(FILE *fp,expr_t e,env_t env);
char * cogen_expr_id(FILE *fp,expr_t e,env_t env);
char * cogen_expr_app(FILE *fp,expr_t e,env_t env);
int cogen_expr_call(FILE *fp, expr_t e, env_t env);


char *bin_op_to_order(op_kind_t kind);
void un_op_cul(FILE *fp,op_kind_t kind,char *s1);
void bin_op_cul(FILE *fp,op_kind_t kind,char *s1,char *s2);
int judge_op_bin(op_kind_t kind);