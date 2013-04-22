#pragma once

#include <stdio.h>
#include "tokenizer.h"
#include "syntree.h"

stmt_t parse_stmt_while(tokenizer_t t);
void eat_it(tokenizer_t t,token_kind_t kind);
char* eat_it_id(tokenizer_t t);
stmt_t parse_stmt_if(tokenizer_t t);
var_decl_t parse_dec_var(tokenizer_t t);
stmt_t parse_stmt_comp(tokenizer_t t);
expr_t parse_expr(tokenizer_t t);
expr_t parse_expr_equal(tokenizer_t t);
expr_t parse_expr_unary(tokenizer_t t);
expr_list_t parse_expr_list(tokenizer_t t);
int if_unary_ope(tokenizer_t t);
int if_mult_ope(tokenizer_t t);
int if_rel_ope(tokenizer_t t);
int if_add_ope(tokenizer_t t);
int if_equ_ope(tokenizer_t t);
expr_t parse_expr_mul(tokenizer_t t);
expr_t parse_expr_add(tokenizer_t t);
expr_t parse_expr_rel(tokenizer_t t);

program_t parse_program(tokenizer_t t);
fun_def_t parse_definition(tokenizer_t t);
fun_def_t parse_fun_def(tokenizer_t t);
var_decl_list_t parse_parameter_list(tokenizer_t t);
var_decl_t parse_parameter(tokenizer_t t);
stmt_t parse_stmt(tokenizer_t t);
op_kind_t judge_bin_op(tokenizer_t t);
op_kind_t judge_un_op(tokenizer_t t);
