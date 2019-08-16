#include"redir.h"
#include"mysh.h"

void remove_args(char **args, char *name)
{

	if (name == NULL)
		error_occur("It is null");
	
	int i;

	for ( i=0; args[i]; i++)
	{
		if (strcmp(args[i], name) == 0)
			break;
	}

	char *p=name;

	while (args[i])
	{
		args[i] = args[i+1];
		i++;
	}

	free(p);
}

int is_redir(char **args)
{
	for (int i=0; args[i]; i++)
	{
		if (strcmp(args[i],">") == 0)
		{
			if (args[i+1] == NULL)
			{
				remove_args(args,args[i]);
				return 0;
			}
				

			int fd=creat(args[i+1],0644);

			close(1);

			if (dup(fd) == -1)
				error_occur("dup...");
			close(fd);
			
			char *p_1, *p_2;
			p_1=args[i];
			p_2=args[i+1];

			remove_args(args,p_1);
			remove_args(args,p_2);
			return 1;
		}

		if (strcmp(args[i],">>") == 0)
		{
			if (args[i+1] == NULL)
			{
				remove_args(args,args[i]);
				return 0;
			}

			int fd=open(args[i+1],O_WRONLY|O_CREAT|O_APPEND,0644);

			close(1);

			if (dup(fd) == -1)
				error_occur("dup...");

			close(fd);
			
			char *p_1,*p_2;

			p_1=args[i];
			p_2=args[i+1];
			remove_args(args,p_1);
			remove_args(args,p_2);
			return 1;
		}
	}
}


