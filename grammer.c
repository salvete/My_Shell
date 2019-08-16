#include"grammer.h"
#include"headers.h"

enum state parse_line(char **args)
{
	if (strcmp(args[0],IF) == 0 )
		return IF_STATE;
	else if (strcmp(args[0],THEN) == 0)
		return THEN_STATE;
	else if (strcmp(args[0],ELSE) == 0)
		return ELSE_STATE;
	else if (strcmp(args[0],FI) == 0)
		return FI_STATE;
	else 
		return NORMAL;
}

void process_control( enum state * should_be,enum state * record, char **args)
{
	enum state arg_state=parse_line(args);

	
	if ( arg_state == NORMAL)
	{
		if (*record == NORMAL)
		{
			*should_be=NORMAL;
		}
		else if (*record == IF_STATE)
			perror("then expected");
	}
	else if (arg_state == IF_STATE)
	{
		if (*record != NORMAL)
			error_occur("error");

		int result=execute(args+1);

		if (result == 0)
			*should_be=THEN_STATE;
		else 
			*should_be=ELSE_STATE;
		*record=IF_STATE;
	}
	else if (arg_state == THEN_STATE)
	{
		if (*record != IF_STATE)
			error_occur("if expected");

		*record=THEN_STATE;
		return;
	}
	else if (arg_state == ELSE_STATE )
	{
		if (*record != THEN_STATE)
			error_occur("then expected");

		*record=ELSE_STATE;	
		return;
	}
	else if (arg_state == FI_STATE)
	{
		if (*record != ELSE_STATE && *record != THEN_STATE)
			error_occur("else expected");
		*record=NORMAL;
		*should_be=NORMAL;
		return;
	}

	if (*should_be == *record)
		execute(args);
}
