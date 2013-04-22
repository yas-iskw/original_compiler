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
//最後にヘッダを確認する



//環境のコンストラクタ
env_t mk_env(int address){
	env_t env = (env_t)safe_malloc(sizeof(struct env));
	
	env->var_name = NULL;
	env->val = 4;
	env->scope = 0;
	env->address = address;
	env->next = NULL;
	
	return env;
}


//変数宣言のリストを環境に登録する
env_t set_env_params(var_decl_list_t params,env_t env){
	env_t pre_env;	
	//int max_scope = 0;
	int value = 8;
	int address = env->address;
		
	//paramsを入れる。
	int size = var_decl_list_sz(params);
	int i;
	char *str;
	for(i=0;i<size;i++){
		str = var_decl_list_get(params,i)->v;
		env->var_name = (char *)safe_malloc(sizeof(char) * (strlen(str)+1) );
		env->scope = 0;
		strcpy(env->var_name,str);
		env->val = value;
		value += 4;
		env->address = address;
		pre_env = (env_t)safe_malloc(sizeof(struct env));
		pre_env->next = env;
		
		env = pre_env;
	}
	
	env->var_name = NULL;
	env->val = -4;
	env->scope = 0;
	env->address = address;
	
	return env;
}

/* 引数と、関数内で宣言された変数の名前がかぶっていないかをチェックする。かぶっていた場合1、そうでない場合0を返す。 */
int env_judge(char* str, env_t env){
  while(env->scope != 0){
	if(env->next == NULL) return 0;
	env = env->next;	
  }
  if( read_env(str,env) == 0 ) return 0;
  return 1;
}


env_t set_env_vars(var_decl_list_t params,env_t env){
	env_t pre_env;	
	int max_scope = env->scope+1;
	int value = env->val;
	int address = env->address;
		
	//paramsを入れる。
	int size = var_decl_list_sz(params);
	int i;
	char *str;
	for(i=0;i<size;i++){
		str = var_decl_list_get(params,i)->v;
		if( env_judge(str,env) ){
		  printf("引数と同じ名前で宣言しないでください！\n");
		  exit(1);
		}    //引数とのチェック
		env->var_name = (char *)safe_malloc(sizeof(char) * (strlen(str)+1) );
		strcpy(env->var_name,str);
		env->val = value;
		value -= 4;
		env->scope = max_scope;
		env->address = address;
		pre_env = (env_t)safe_malloc(sizeof(struct env));
		pre_env->next = env;
		
		env = pre_env;
	}
	
	env->var_name = NULL;
	env->val = value;
	env->scope = max_scope;
	env->address = address;
	
	return env;
}

env_t delete_env_vars(env_t env){
	int max_scope = env->scope;
	env_t pre_env = env;
	while(env->scope < max_scope){
		pre_env = env;
		if(env->next == NULL) break;
		env = env->next;
	}
	
	env = pre_env;
	env->var_name = NULL;
	//env->valそのまま
	if(max_scope == 0){
		env->scope = 0;	
	}else{
		env->scope = max_scope-1;
	}
	
	return env;
}

int read_env(char *var,env_t env){
	for(; env->next != NULL ;){
		env = env->next;
		if( !strcmp(env->var_name,var) ) return env->val;
	}
	return 0;	//存在しない
}

int address_env(env_t env){
  return env->address;
}



//-----------------------------------
//memory管理
//----------------------------------

//	pos_v	渡された変数の割り当てメモリを返す
//　pos_v_array pos_vの配列版
//	pos_e	渡されたexpressionの対応するexpressionメモリを返す
//	judge_c	渡された文字列が、メモリかレジスタか即値かを返す
//	judge_e	渡された二つのexpressionの保存場所が両方メモリなら1を返す
//	change_int	expressionのinfoをliteral型に変える
//	change_id	expressionのinfoをid型に変える

//pos_vのstrは16バイトほど確保しておいてください。
void pos_v(char* str, char *var, env_t env){
  int n = read_env(var,env);
  if(n == 0){
  	printf("宣言されてません！\n");
		exit(1);
  }
  sprintf(str,"%d(%%ebp)", n );
}

//pos_vのstrは16バイトほど確保しておいてください。
void pos_v_array(int* n, char *var, env_t env){
	char* str1;
	str1 = (char *)malloc(sizeof(char) * (strlen(var)+4) );
	strcpy(str1,var);
	strcat(str1,"[0]");
	int m = read_env(str1,env);
	free(str1);
	if(m == 0){
  	printf("%s配列が宣言されてません！\n",var);
		exit(1);
  }
  *n = m;
}

//pos_eのstrは16バイトほど確保しておいてください。	ecx,ebxのみ使用 esi,edi未使用
/* ebx:-4 ecx:-8 とすることでecxをできるだけ使わないようにする */
//---------
//pos_e judge_e judge_c cogen_expr_call cogen_prologue cogen cogen_epilogue の6関数が関与
//---------
void pos_e(char *str, expr_t e,env_t env){
  if(e->info->kind == 0){
    if( e->info->rel_val == -4 ){
      sprintf(str,"%%ebx");
     //-------------------------
    }else if( e->info->rel_val == -8 ){
      sprintf(str,"%%ecx");
		/*}else if( e->info->rel_val == -12 ){
      sprintf(str,"%%esi");
		}else if( e->info->rel_val == -16 ){
      sprintf(str,"%%edi");*/
     //-------------------------
    }else{
      sprintf(str,"%d(%%ebp)", address_env(env) + e->info->rel_val );
    }
  }else if(e->info->kind == 1){
    sprintf(str, "$%d",e->info->rel_val);
  }else if(e->info->kind == 2){
    sprintf(str, "%d(%%ebp)", e->info->rel_val);
  }else if(e->info->kind == 3){
    sprintf(str, "%%eax");
  }else{
    printf("error!!!!! expression->infoいじるな!!!!!");
    exit(1);
  }
}

//両方memory:1 それ以外:0		ecx,ebxのみ使用 esi,edi未使用
int judge_e(expr_t e1,expr_t e2){
  if(  (e1->info->rel_val < /*-4*/-8/*-12,-16*/ && e1->info->kind==0)  ||  e1->info->kind==2  ){
    if(  (e2->info->rel_val < /*-4*/-8/*-12,-16*/ && e2->info->kind==0)  ||  e2->info->kind==2  ){
      return 1;
    }
  }
      return 0;
}

//レジスタなら:1 メモリ:0 即値:2 ←NEW!	
int judge_c(char *str){
  if( !strcmp("%ecx",str) 
	//------------------------
	|| !strcmp("%ebx",str)
	|| !strcmp("%esi",str)
	|| !strcmp("%edi",str)
	//------------------------
	|| !strcmp("%eax",str) || !strcmp("%edx",str)
   ) return 1;
	if( str[0] == '$') return 2;
  return 0;
}

//e->info->kindの判別　0:expressionメモリ　1:int　2:id	3:関数
int judge_kind(expr_t e){
  return e->info->kind;
}

//e->info->kindをintに変える
void change_int(expr_t e, int num){
  e->info->kind = 1;
  e->info->rel_val = num;
}

//e->info->kindをidに変える
void change_id(expr_t e, char *var, env_t env){
  e->info->kind = 2;
  
  int n = read_env(var,env);
  if(n == 0){
    printf("宣言されてません！\n");
    exit(1);
  }
  e->info->rel_val = n;
}

//e->info->kindを関数型に変える
void change_call(expr_t e, env_t env){
  //e->info->kind = 3;
	e->info->kind = 0;
}



/*
pos_v,judge_e,judge_cは変えていない。

expr_t の中に、そのexpressionがすでにcogen_exprを通過していた場合、
中身がint_literalかidかそれ以外かをe->info->kindの中に記憶している。

これで場合分けして、
cogen_exprの中で　int_literalを読むときはmovlを出力せずchange_intを実行して、
int_idを読むときもmovlを出力せずchange_idを実行して。

pos_e は拡張して、kindに応じて、必要なものを返すようにしている。
 */
