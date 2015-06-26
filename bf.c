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

int main(int argc, char** argv){
	// load command line arguments
	// create bf execution environment based on parameters
	// load program
	// execute program
	// dump memory if asked to
	// cleanup
	return 0;
}

