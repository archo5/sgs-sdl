#ifndef SS_MAIN_H_INCLUDED#define SS_MAIN_H_INCLUDED#include "ss_cfg.h"#include <SDL/SDL.h>#include "../sgscript/src/sgscript.h"/* Utilities */#define ARRAY_SIZE( x ) (sizeof(x)/sizeof(x[0]))/* SGScript helpers */typedef struct flag_string_item_s{	const char* name;	int value;}flag_string_item_t;#define FSI_LAST { NULL, 0 }sgs_Integer sgs_GlobalInt( SGS_CTX, const char* name );uint32_t sgs_GetFlagString( SGS_CTX, int pos, flag_string_item_t* items );uint32_t sgs_GlobalFlagString( SGS_CTX, const char* name, flag_string_item_t* items );/* SGScript - SDL */#endif /* SS_MAIN_H_INCLUDED */