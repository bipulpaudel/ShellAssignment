



#define _GNU_SOURCE

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <signal.h>

#define WHITESPACE " \t\n"      // We want to split our command line up into tokens
                                // so we need to define what delimits our tokens.
                                // In this case  white space
                                // will separate the tokens on our command line

#define MAX_COMMAND_SIZE 255    // The maximum command-line size

#define MAX_NUM_ARGUMENTS 10     // Mav shell only supports five arguments

int main()
{

  char * cmd_str = (char*) malloc( MAX_COMMAND_SIZE );
  char * history_array[15]; //malloc and 0 out 
  int history_index = 0;
  int pid_array[15];
  int pid_index = 0;


  while( 1 )
  {
    // Print out the msh prompt
    printf ("msh> ");

    // Read the command from the commandline.  The
    // maximum command that will be read is MAX_COMMAND_SIZE
    // This while command will wait here until the user
    // inputs something since fgets returns NULL when there
    // is no input
    while( !fgets (cmd_str, MAX_COMMAND_SIZE, stdin) );
    
    /* Parse input */
    char *token[MAX_NUM_ARGUMENTS];

    int   token_count = 0;                                 
                                                           
    // Pointer to point to the token
    // parsed by strsep
    char *argument_ptr;                                         
                                                           
    char *working_str  = strdup( cmd_str );   
    if (history_index > 14)
    {
		int i;
		for (i = 0; i < 14; i++)
		{
			strncpy(history[i], history[i+1], 255);
		}
		strncpy(history[14], cmd_str, 255);
    }
    else
    {
    	strncpy(history[history_index++], cmd_str, 255);
    }
  
    //if (history_index > 14)
    //{
    //	history_index = 0;
    //}  
    //
    if (cmd_str[0] == '!')
    {
    	int history_num= atoi(&token[0][1])

    	if (n < 15) //not sure if i have to do this
    	{
    		strncpy(&working_str, history[history_num], strlen(history[history_num]));
    	}
    	else
    	{
    		printf("Command not in history");
    	}
    }    
    


    // we are going to move the working_str pointer so
    // keep track of its original value so we can deallocate
    // the correct amount at the end
    char *working_root = working_str;

    // Tokenize the input stringswith whitespace used as the delimiter
    while ( ( (argument_ptr = strsep(&working_str, WHITESPACE ) ) != NULL) && 
              (token_count<MAX_NUM_ARGUMENTS))
    {
      token[token_count] = strndup( argument_ptr, MAX_COMMAND_SIZE );
      if( strlen( token[token_count] ) == 0 )
      {
        token[token_count] = NULL;
      }
        token_count++;
    }

    //Debug Output
    int token_index  = 0;
    for( token_index = 0; token_index < token_count; token_index ++ ) 
    {
      printf("token[%d] = %s\n", token_index, token[token_index] );  
    }
    //Debug Output


    //continue to start the loop again if user presses enter instead of a commmand
    if(token[0] = NULL)
    {
    	continue;
    }
    else if(strcmp(token[0], "exit") == 0 || strcmp(token[0], "quit") == 0)
    {
    	exit(0);
    }

    else if(strcmp(token[0], "cd") == 0)
    {
    	chdir(token[1]);
    }

    else if (strcmp(token[0],"showpids") == 0)
    {
    	int i;
    	for (i = 0; i < pid_index; i++)
    	{
    		printf("%d", pid_array[i]);
    	}
    }
    
    else if (strcmp(token[0],"history") == 0)
    {
    	int i;
    	for(i = 0; i < history_index; i++)
    	{
    		printf("%d %s", i+1, history_array[i]);
    	}
    }

    else
    {
    	pid_t pid = fork();
    		


    	if (pid == -1)
    	{
    		perror("Fork not implemented.");
    		exit(EXIT_FAILURE);
    	}
    	if (pid == 0)
    	{
    		int ret = execvp( token[0], token );  
    		if( ret == -1 )
    		{
      			printf("%s: Command not found", token[0]);
   		    }
   		    fflush(NULL);
   		    exit(EXIT_SUCCESS;
    	}
    	else
    	{
    		int status;
    		wait( & status);
    		//addpid
    		if (pid_index > 14)
    		{
    			int i;
    			for (i = 0; i < 14; i++)
	    		{
	    			pid_array[i] = pid_array[i+1];
	    		}
	    		pid_array[14] = pid;
    		}
    		else
    		{
    			pid_array[pid_index++] = pid;
    		}
    		
    		fflush(NULL);
    	}
    }
    free( working_root );

  }
  return 0;
}