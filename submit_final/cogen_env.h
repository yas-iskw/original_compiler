#pragma once

#include "syntree.h"
#include "cogen_env.h"

struct env
{
  char *var_name;
  int val;	//envは、引数なら+、関数内変数なら-のvalを持っている。
  int scope;
	
  int address;
	 
  struct env *next;
};

typedef struct env * env_t;

env_t mk_env(int address);
env_t set_env_params(var_decl_list_t params,env_t env);
env_t set_env_vars(var_decl_list_t params, env_t env);
env_t delete_env_vars(env_t env);
int read_env(char *var,env_t env);
int address_env(env_t env);
int env_judge(char* str, env_t env);

/* 格納場所管理関数 */
void pos_v(char* str, char *var, env_t env);	//varのアドレスをstrに格納
void pos_v_array(int *n, char* var, env_t env);//var[i]のアドレスを指示する。strはiのアドレス、memoryはvarのアドレスの%ebpとのずれを代入する。
void pos_e(char* str, expr_t e, env_t env);		//expr_tのアドレスをstrに格納　値の場合は$Xを格納
int judge_e(expr_t e1,expr_t e2);			//両方メモリーかの判断　両方memory:1 それ以外:0
int judge_c(char *str);				//レジスタかどうかの判別　レジスタ、値:1　メモリ:0
int judge_kind(expr_t e);				//e->info->kindの判別　0:expressionメモリ　1:int　2:id　3:関数
void change_int(expr_t e, int num);		//e->info->kindをintに変える
void change_id(expr_t e, char *var, env_t env);	//e->info->kindをidに変える
void change_call(expr_t e, env_t env);	//e->info->kindを関数型に変える
