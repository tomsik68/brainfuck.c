/*
 * Brainfuck.c - A brainfuck language interpreter.
 *
 * Usage:
 * 	bfi <filename.bf> [options]
 *
 * Options:
 * 	Short	Long		Default value	Description
 * 	-m	--memory	65536		Sets length of character array
 * 	-o	--output	false		At the end of program execution, the character array will be dumped to stdout
 */


#include <stdio.h>
#include <string.h>


// Brainfuck interpreter configuration
typedef struct bf_config_t {
	// length of main character array
	int	array_length;
	// dump memory at the end of program execution
	int 	dump_memory;
	// file to execute
	char* 	filename;
	// read the code from stdout?
	int 	read_stdout;
} bf_config_t;

// Brainfuck execution environment
typedef struct bf_env_t {
	// 
	unsigned char* 	memory;
	/* where in the memory array this is pointing to.
	 * 0 means memory. 1 means *(memory + 1)
	 * pointers are checked by the interpreter not to overflow or cause issues
	 */
	unsigned int ptr;
} bf_env_t;

// creates the default configuration
void configure_default(bf_config_t* config){
	config->array_length 	= 65536;
	config->dump_memory 	= 0;
	config->filename 	= "-";
}

// this macro evaluates to true if all characters in s1 and s2 are equal
#define STRINGS_EQUAL(s1,s2) (strcmp(s1,s2) == 0)

/**
 * Creates configuration for brainfuck interpreter based on values of arguments
 */
bf_config_t* configure(int argc, char** argv){
	bf_config_t* result = malloc(sizeof(bf_config_t));
	configure_default(result);
	// we're iterating up to argc - 2, because argc - 1 stores the file name
	for(int i = 0; i < argc - 1; ++i){
		if(STRINGS_EQUAL(argv[i], "--memory") || STRINGS_EQUAL(argv[i], "-m")){
			// get memory amount from argv[i+1]
			i += 1;
		} else if(STRINGS_EQUAL(argv[i], "-o") || STRINGS_EQUAL(argv[i], "--output")){
			result->dump_memory = 1;
		}
	}
	// load filename from argc-1
	result->filename = argv[argc-1];
	return result;
}

bf_env_t* create_environment(bf_config_t* config){
	bf_env_t* result = malloc(sizeof(bf_env_t));
	result->memory = malloc(config->array_length * sizeof(char));
	result->ptr = 0;
	return result;
}
int main(int argc, char** argv){
	// load command line arguments
	bf_config_t* config = configure(argc, argv);
	// create bf execution environment based on parameters
	bf_env_t* env = create_environment(config);
	// load program
	// execute program
	// dump memory if asked to
	// cleanup
	return 0;
}

