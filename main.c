#include"headers.h"
#include"mysh.h"
#include"grammer.h"
#include"welcome.h"
#include"varlib.h"

#define VERSION_1_0

enum state should_be;
enum state record;

void setup()
{
	char *args[2]={
		"clear",NULL
	};

	execute(args);
	welcome();

	signal(SIGINT,SIG_IGN);
	signal(SIGQUIT,SIG_IGN);
	
	should_be=NORMAL;
	record = NORMAL;
}

int main()
{
	char *cmd, **args;

	setup();

	while ((cmd = read_args(stdin,PROMPT)) != NULL)
	{
		
		args = parse_args(cmd);

		if (args[0] == NULL)
			continue;

		process_control(&should_be,&record,args);
		free(cmd);

		free_args(args);
	}
	return 0;
}
