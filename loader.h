#ifndef __LOADER_H__
#define __LOADER_H__

#include <string.h>
#include "configuration.h"
#include "execution.h"

int is_instruction(char c);

bf_instruction_code_t type_from_char(char c);

bf_instruction_t* load_program_from_stream(FILE* stream);

bf_instruction_t* load_program_from_file(char* filename);

#endif /* __LOADER_H__ */
