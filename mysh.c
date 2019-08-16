#include"headers.h"
#include"varlib.h"
#include"mysh.h"
#include"mypwd.h"
#include"redir.h"
#include"pipe.h"
#include"color.h"

//#define DEBUG

/* This is the function to read the command line */
char *read_args(FILE *fp,char *prompt)
{
	char *cmd;
	int cnt=0;
	int ch;
	int cmd_size = BUFSIZE;
	cmd=(char *)malloc(cmd_size);

	//printf("%s",prompt);
	
	show_info(get_node());
	printf("$ ");


	while ((ch = fgetc(fp)) != EOF)
	{
		if (ch == '\n')
			break;

		cmd[cnt++]=ch;

		if (cnt ==BUFSIZE-1)
		{
			cmd_size+=BUFSIZE;
			cmd=realloc(cmd,cmd_size);
		}

	}

	if (cnt > 0)
	{
		cmd[cnt]='\0';
	}

	if (cnt == 0)
	{
		free(cmd);
		cmd=NULL;

		if (ch != EOF)
			return read_args(fp,prompt);
	}
	
	return cmd;
}

/* error handling function */

void error_occur(char *msg)
{
	char *p;
	int len=strlen(msg)+strlen(KYEL);
	p=(char*)malloc(len*sizeof(char) +1);
		
	strcpy(p,KYEL);
	strcat(p,msg);
	p[len] = '\0';

	perror(p);
	printf(KYEL"exiting...\n");

	free(p);
	exit(0);
}


/* To parse the command line */
char *get_memory(char *str, int len)
{
	char *return_value;
	return_value =(char*)malloc(len+1);

	if (return_value == NULL)
		error_occur("malloc error");
	
	for (int i=0; i<len; i++)
		return_value[i]=str[i];

	return_value[len]='\0';

	return return_value;
}

char **parse_args(char *cmd)
{
	int arg_nums=0;
	int arg_arry_len=ARG_ARRAY_LEN;
	char **args;

	if (cmd == NULL)
		return NULL;
	
	args = (char **)malloc(arg_arry_len*sizeof(char **)); /* Make sure to add "sizeof" */

	if (args == NULL)
		error_occur("malloc error");
	
	int len=0;
	char *start_pos;

	while (*cmd != '\0')
	{
		len=0;

		while ((*cmd) == ' ')
			cmd++;

		start_pos=cmd;

		while ((*cmd) != ' ' && (*cmd) != '\0')
		{
			len++;
			cmd++;
		}


		if (len > 0)
		{
			char *p = get_memory(start_pos,len);
			args[arg_nums++] = p;
			if (arg_nums == arg_arry_len -2)
			{
				arg_arry_len+=ARG_ARRAY_LEN;
				args = realloc(args, arg_arry_len*sizeof(char **));
			}
		}
	}

	args[arg_nums]=NULL;

	return args;
}

/*To free the memory thar args take*/
void free_args(char **args)
{
	for (int i=0; *(args+i); i++)
		free(*(args+i)); //IT IS VERY EASY TO GET WRONG!

	free(args);

}

/* to execute the programs */
int execute(char **args)
{
	int status;

	/* to handle the varible */
	if (var_handler(args))
		return (0);

	/* the build-in command 'cd' */

	if (strcmp(args[0],"cd") == 0)
	{
		if (!args[1])
			return 1;
		else
		{
			chdir(args[1]);
			return 0;
		}
	}
		
	/* quit command*/
	if (args == NULL)
		error_occur("args is NULL");

	if (strcmp(args[0],"exit") == 0)	
		exit(0);

	if (strcmp(args[0],"quit") == 0)
		exit(0);

	if (strcmp(args[0],"q") ==0)
		exit(0);

	int new_pid=fork();

	if (new_pid == -1)
		error_occur("fork");

	if (new_pid == 0)
	{
		/* redirect:to make the stdout be the filename*/
		is_redir(args);

		/* to handler the pipe situation*/
		int pipe_pos=is_pipe(args);
		if (pipe_pos > 0)
		{
			char *args1[pipe_pos+1];

			for (int i=0; i<pipe_pos; i++)
				args1[i]=args[i];

			args1[pipe_pos] = NULL;

			make_pipe(args1,args+pipe_pos+1);
		}
		/* normal condition */
		else
		{
			execvp(args[0],args);
			error_occur("the son program has some problems");
		}
	}
	else
	{

		if (wait(&status) == -1)
			error_occur("while waiting");
		return status;
	}
}

#ifdef DEBUG
void print_args(char ** args)
{
	for (int i=0; *(args+i); i++)
		printf("%s\n",*(args+i));
}
#endif
