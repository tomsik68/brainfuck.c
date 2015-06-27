#ifndef __EXECUTION_H__
#define __EXECUTION_H__

#include "configuration.h"

/* Brainfuck execution environment */
typedef struct bf_env_t {
	/* brainfuck interpreter memory(accessible char array)  */
	unsigned char* 	memory;
	/* memory size(length of array) */
	size_t memory_size;
	/* where in the memory array this is pointing to.
	 * 0 means memory. 1 means *(memory + 1)
	 * pointers are checked by the interpreter not to overflow or cause issues
	 */
	unsigned int ptr;
	/* address of instruction that is currently being executed */
	int address;
} bf_env_t;

typedef enum {
	/* > */
	PTR_RIGHT,
	/* < */
	PTR_LEFT,
	/* + */
	INC_PTR,
	/* - */
	DEC_PTR,
	/* . */
	PRINT,
	/* , */
	READ,
	/* [ */
	WHILE,
	/* ] */
	ENDWHILE
} bf_instruction_code_t;

typedef struct bf_instruction_t {
	/* instruction type */
	bf_instruction_code_t		type;
	/* next instruction in the program */
	struct bf_instruction_t*	next;
	/* previous instruction in the program(for jumping) */
	struct bf_instruction_t* 	prev;
	/* pointer to instruction parameters
	* this is mainly used for ENDWHILE
	* to remember address of the associated while */
	void* 				parameters;
} bf_instruction_t;


bf_env_t* 	create_environment(bf_config_t* config);

void 		execute(bf_instruction_t* program, bf_env_t* environment);

#endif /* __EXECUTION_H__ */
