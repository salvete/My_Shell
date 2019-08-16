#include"varlib.h"
#include"mysh.h"
#include"headers.h"


int var_handler(char **args)
{
	for (int i=0; *(args[0]+i); i++)	
	{
		if (*(args[0]+i) == '=')
		{
			char *name = get_memory(args[0],i);
			int len=strlen(args[0]);
			char *value =get_memory(args[0]+i+1,len-i);
			store_var(name,value);
			return 1;
		}
	}

	if (strcmp(args[0],"set") == 0)
	{
		show_all_var();
		return 1;
	}

/* To change the name to value */

	for (int i=0; *(args+i); i++) {
		if (args[i][0] == '$')
			args[i] = get_value(&args[i][1]);
	}

	return 0;
}


void store_var(char *name, char *value)
{
	if (var_num == VARSIZE -1)
		return;

	struct var *var_p=(struct var *)malloc(sizeof(struct var));
	
	var_p->name=name;
	var_p->value=value;
	var_p->is_globle=0;

	var_list[var_num ++ ] = var_p;
}

char *get_value(char *name)
{
	char *value_p=NULL;

	for (int i=0; i<var_num; i++)
		if (strcmp(name,var_list[i]->name) == 0)
			{
				value_p = var_list[i]->value;
				break;
			}
	return value_p;
}

void show_all_var()
{
	for (int i=0; i<var_num; i++)
	{
		printf("%s=%s\n",var_list[i]->name,var_list[i]->value);
	}
}

void free_all_var()
{
	for (int i=0; i<var_num; i++)
	{
		free(var_list[i]);
	}

	var_num=0;
}

void export_var(char *name)
{
	for (int i=0; i<var_num; i++)
	{
		if (strcmp(var_list[i]->name,name) == 0)
			var_list[i]->is_globle=1;
	}
}
