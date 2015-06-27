#ifndef __CONFIGURATION_H__
#define __CONFIGURATION_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/* Brainfuck interpreter configuration */
typedef struct bf_config_t {
	/* length of main character array */
	int	array_length;
	/* dump memory at the end of program execution */
	int 	dump_memory;
	/* file to execute */
	char* 	filename;
} bf_config_t;

/* creates the default configuration */
void configure_default(bf_config_t* config);

/* this macro evaluates to true if all characters in s1 and s2 are equal */
#define STRINGS_EQUAL(s1,s2) (strcmp(s1,s2) == 0)

/**
 * Creates configuration for brainfuck interpreter based on values of arguments
 */
bf_config_t* configure(int argc, char** argv);

#endif /* __CONFIGURATION_H__ */
