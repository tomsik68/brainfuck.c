#include "execution.h"

bf_env_t* create_environment(bf_config_t* config){
	bf_env_t* result = malloc(sizeof(bf_env_t));
	/* allocate memory for execution */
	result->memory = malloc(config->array_length * sizeof(char));
	/* initialize memory to all zeros */
	int i;
	for( i = 0; i < config->array_length; ++i){
		result->memory[i] = 0;
	}
	/* the pointer points to the first element of memory array */
	result->ptr = 0;
	result->address = 0;
	result->memory_size = config->array_length;
	return result;
}

void inc_ptr(bf_env_t* env, void* params){
	++(env->memory[env->ptr]);
}

void dec_ptr(bf_env_t* env, void* params){
	--(env->memory[env->ptr]);
}

void ptr_left(bf_env_t* env, void* params){
	if(env->ptr == 0){
		/* ERROR: ptr can't go more to the left */
	}
	--(env->ptr);
}

void ptr_right(bf_env_t* env, void* params){
	if(env->ptr == env->memory_size - 1) {
		/* ERROR: ptr can't go more to the right */
	}
	++(env->ptr);
}

void print(bf_env_t* env, void* params){
	putchar(env->memory[env->ptr]);
}

void read(bf_env_t* env, void* params){
	env->memory[env->ptr] = getchar();
}

void execute(bf_instruction_t* program, bf_env_t* environment) {
	printf("\n------------------Execution start.---------------------\n");
	bf_instruction_t* currentInstruction = program;
	/* seek to address specified by environment */
	int addr;
	for(addr = 0; addr < environment->address; ++addr){
		currentInstruction = currentInstruction->next;
	}
	while(currentInstruction != NULL){
		switch(currentInstruction->type){
			case INC_PTR:
				inc_ptr(environment, currentInstruction->parameters);
				break;
			case DEC_PTR:
				dec_ptr(environment, currentInstruction->parameters);
				break;
			case READ:
				read(environment, currentInstruction->parameters);
				break;
			case PRINT:
				print(environment, currentInstruction->parameters);
				break;
			case PTR_LEFT:
				ptr_left(environment, currentInstruction->parameters);
				break;
			case PTR_RIGHT:
				ptr_right(environment, currentInstruction->parameters);
				break;
			case WHILE:
				/* do nothing */
				if(!(environment->memory[environment->ptr])){
					currentInstruction = currentInstruction->parameters;
				}
				break;
			case ENDWHILE:
				if(environment->memory[environment->ptr]) {
					/* jump back to associated while */
					currentInstruction = currentInstruction->parameters;
				} else {
					/* do nothing, we're continuing in the program */
				}
				break;
		}
		currentInstruction = currentInstruction->next;
		++(environment->address);
	}
	printf("\n------------------Execution end.---------------------\n");
}
