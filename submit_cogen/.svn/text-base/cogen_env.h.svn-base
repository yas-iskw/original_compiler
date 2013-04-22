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
void pos_v(char* str, char *var, env_t env);
void pos_e(char* str, expr_t e, env_t env);
int judge_e(expr_t e1,expr_t e2);
int judge_c(char *str);
