#include "loader.h"

/*
 * This is stack used for while loops in the program.
 * When loader finds a WHILE instruction, it will push it to a stack.
 * When it finds ENDWHILE, it will pop address to jump back to from the stack.
 */
typedef struct loopstart_t {
	/* previous brackets_t in the stack */
	struct loopstart_t*	prev;
	/* address of this bracket */
	int			address;
} loopstart_t;

/* returns 1 if this character is a valid instruction character */
int is_instruction(char c){
	static char* instructionChars = "+-[],.<>";
	return (strchr(instructionChars, c) != NULL);
}

/* converts character to instruction code */
bf_instruction_code_t type_from_char(char c){
	bf_instruction_code_t result;
	switch(c){
		case '+':
			result = INC_PTR;
			break;
		case '-':
			result = DEC_PTR;
			break;
		case '>':
			result = PTR_RIGHT;
			break;
		case '<':
			result = PTR_LEFT;
			break;
		case '.':
			result = PRINT;
			break;
		case ',':
			result = READ;
			break;
		case '[':
			result = WHILE;
			break;
		case ']':
			result = ENDWHILE;
			break;
		default:
			break;
	}
	return result;
}




/* we won't read the whole program at once. instead, we'll use blocks to read it... */
#define BLOCK_SIZE 128
/* loads program from a stream */
bf_instruction_t* load_program_from_stream(FILE* stream){
	bf_instruction_t* result = malloc(sizeof(bf_instruction_t));
	result->prev = NULL;
	bf_instruction_t* current = result;
	loopstart_t* loopstarts = NULL;
	/* block of program */
	char block[BLOCK_SIZE];
	int address = 0;
	while(!feof(stream)){
		size_t bytesRead = fread(block, sizeof(char), BLOCK_SIZE, stream);
		/* process the block */
		size_t index;
		for( index = 0; index < bytesRead; ++index){
			char aChar = block[index];
			/* if there's a valid instruction, add it to the linked list */
			if(is_instruction(aChar)){
				current->type = type_from_char(aChar);
				current->next = malloc(sizeof(bf_instruction_t));
				current->next->prev = current;
				current->parameters = 0;
				/* perform while loop linking */
				if(current->type == WHILE){
					/* PUSH address */
					loopstart_t* newloop = malloc(sizeof(loopstart_t));
					newloop->prev = loopstarts;
					newloop->address = address;
					loopstarts = newloop;
				} else if(current->type == ENDWHILE){
					/* POP address */
					loopstart_t* loop = loopstarts;
					if(loop == NULL) {
						/* TODO: ERROR: unbalanced loops */
					}
					loopstarts = loopstarts->prev;
					/* save the address in parameters */
					current->parameters = malloc(sizeof(int));
					memcpy(current->parameters, &(loop->address), sizeof(int));
					free(loop);
				}
				/* move the pointer */
				current = current->next;
				++address;
			}
		}
	}
	return result;
}

bf_instruction_t* load_program_from_file(char* filename){
	bf_instruction_t* result;
	FILE* stream;
	if(STRINGS_EQUAL(filename, "-")){
		stream = stdin;
	} else {
		stream = fopen(filename, "r");
	}
	result = load_program_from_stream(stream);
	return result;
}
