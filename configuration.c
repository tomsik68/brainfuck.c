#include "configuration.h"

/* creates the default configuration */
void configure_default(bf_config_t* config){
	config->array_length 	= 65536;
	config->dump_memory 	= 0;
	config->filename 	= "-";
}

bf_config_t* configure(int argc, char** argv){
	bf_config_t* result = malloc(sizeof(bf_config_t));
	configure_default(result);
	/* we're iterating up to argc - 2, because argc - 1 stores the file name */
	int i;
	for( i = 0; i < argc - 1; ++i){
		if(STRINGS_EQUAL(argv[i], "--memory") || STRINGS_EQUAL(argv[i], "-m")){
			/* get memory amount from argv[i+1] */
			sscanf(argv[i + 1], "%d", &(result->array_length));
			i += 1;
		} else if(STRINGS_EQUAL(argv[i], "-o") || STRINGS_EQUAL(argv[i], "--output")){
			result->dump_memory = 1;
		}
	}
	/* load filename from argc-1 */
	result->filename = argv[argc-1];
	return result;
}
