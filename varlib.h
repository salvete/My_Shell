#ifndef VARLIB_H
#define VARLIB_H

#include"headers.h"
#define VARSIZE 100


struct var{
	char *name;
	char *value;
	int is_globle;
};

/*varible container */
struct var *var_list[VARSIZE] ;

static int var_num=0;

/* determine whether the args is to set the varible*/
int var_handler(char **);
/* to store the varible */
void store_var(char *,char *);
/* to get the value of the varible according to its name */
char *get_value(char *);
/* to list the varibles*/
void show_all_var();
/* free the memory */
void free_all_var();
/* to make the varible be globle */
void export_var(char *);

#endif

