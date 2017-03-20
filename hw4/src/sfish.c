#include "sfish.h"
#include "debug.h"

void execute_command(char **cmdtok){

	//If it is a recognized built-in command
	if(is_builtin(cmdtok[0])){

		if(strcmp(cmdtok[0], "exit") == 0){

			exit(EXIT_SUCCESS);

		}else if(strcmp(cmdtok[0], "help") == 0){

			print_help();

		}else if(strcmp(cmdtok[0], "cd") == 0){

			debug("%s","cd was entered\n");

		}else if(strcmp(cmdtok[0], "pwd") == 0){

			debug("%s", "pwd was entered");

		}else{

			printf("command not found: %s\n", cmdtok[0]);

		}


	//If not...
	}else{




	}

}

char *pwd(){

	return NULL;

}

//Return true if the command is a builtin, false otherwise
int is_builtin(const char *command){

	return strcmp(command, "help") || strcmp(command, "exit") || strcmp(command, "cd") || strcmp(command, "pwd");

}
