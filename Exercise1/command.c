#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "command.h"

#define MAX_CMD_COUNT 50
#define MAX_CMD_LEN 25


	//TODO FUNCTION COMMENT
	/*
	 * PURPOSE: parse the input provided by the user and save it within 
			cmd data structure
	 * INPUTS: input - char string received from user input
		   cmd - Commands_t data structure to hold commands
	 * RETURN: returns true if user input was saved within cmd structure
			otherwise returns false if there is an error
	 **/
bool parse_user_input (const char* input, Commands_t** cmd) {
	
	//TODO ERROR CHECK INCOMING PARAMETERS
	// check if input and cmd variables exists
	if( (input == NULL) | (cmd == NULL) ) {
		return false;
	}
	char *string = strdup(input);
	
	*cmd = calloc (1,sizeof(Commands_t));
	(*cmd)->cmds = calloc(MAX_CMD_COUNT,sizeof(char*));

	unsigned int i = 0;
	char *token;
	token = strtok(string, " \n");
	for (; token != NULL && i < MAX_CMD_COUNT; ++i) {
		(*cmd)->cmds[i] = calloc(MAX_CMD_LEN,sizeof(char));
		if (!(*cmd)->cmds[i]) {
			perror("Allocation Error\n");
			return false;
		}	
		strncpy((*cmd)->cmds[i],token, strlen(token) + 1);
		(*cmd)->num_cmds++;
		token = strtok(NULL, " \n");
	}
	free(string);
	return true;
}

	//TODO FUNCTION COMMENT
	/*
	 * PURPOSE: free memory for a commands structure if the structure exists
	 * INPUTS: received a Commands_t data structure
	 * RETURN: nothing to return
	 **/
void destroy_commands(Commands_t** cmd) {

	//TODO ERROR CHECK INCOMING PARAMETERS
	// check if cmd structure exists
	if(cmd != NULL) {
		for (int i = 0; i < (*cmd)->num_cmds; ++i) {
			free((*cmd)->cmds[i]);
		}
		free((*cmd)->cmds);
		free((*cmd));
		*cmd = NULL;
	}
}

