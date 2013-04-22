#pragma once

#include "syntree.h"
#include "cogen_label.h"
#include "cogen_env.h"



/*char *op_kind_to_jump(op_kind_t kind);*/



int cogen_fun_def(FILE *fp,fun_def_t d, label_gen_t lg);
int cogen_program(FILE *fp,program_t p);
int cogen_alloc_storage_fun_def(fun_def_t d);
void cogen_program_header(FILE *fp,char* filename);
void cogen_program_trailer(FILE *fp);
void cogen_fun_def_header(FILE *fp,char *fun_name);
void cogen_fun_def_trailer(FILE *fp,char * fun_name);
void cogen_prologue(FILE *fp,int frame_sz,env_t env);
void cogen_epilogue(FILE *fp,label_gen_t lg,env_t env);




