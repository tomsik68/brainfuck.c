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
	return result;
}

