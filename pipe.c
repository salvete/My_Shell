#include"pipe.h"
/* return the position of '|' */
int is_pipe(char **args)
{
	for (int i=0; args[i]; i++)
	{
		if (strcmp(args[i],"|") == 0)
		{
			return i;	
		}
	}

	return 0;
}

/* to run when there is a pipe*/
int make_pipe(char **args1, char **args2)
{
	int pid;
	int p[2];


	if (pipe(p) == -1)
		error_occur("pipe");

	pid=fork();

	if (pid == -1)
		error_occur("fork");

	if (pid == 0)
	{
		close(p[0])	;
		if (dup2(p[1],1) == -1)
			error_occur("dup2");
		close(p[1]);
		//execvp(args1[0],args1);
		execute(args1);
		exit(1);// exit directly
	}
	else
	{
		if (wait(NULL) == -1)
			error_occur("while waiting");

		close(p[1]);
		if (dup2(p[0],0) == -1)
			error_occur("dup2");
		close(p[0]);
		//execvp(args2[0],args2);
		execute(args2);
		exit(1);// exit directly
	}

	return 0;
}
