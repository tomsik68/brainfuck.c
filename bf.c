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
#include "configuration.h"
#include "execution.h"
#include "loader.h"

int main(int argc, char** argv){
	/* load command line arguments */
	bf_config_t* config = configure(argc, argv);
	/* create bf execution environment based on parameters */
	bf_env_t* env = create_environment(config);
	/* load program */
	bf_instruction_t* program = load_program_from_file(config->filename);
	/* execute program */
	execute(program, env);
	/* dump memory if asked to */
	if(config->dump_memory == 1) {
		FILE* dest = fopen("memory.bin", "w");
		fwrite(env->memory, sizeof(char), env->memory_size, dest);
		fclose(dest);
	}
	/* cleanup */
	return 0;
}

