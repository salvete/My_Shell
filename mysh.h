#ifndef MYSH_H
#define MYSH_H

#include"headers.h"

#define BUFSIZE 2048
#define ARG_ARRAY_LEN 3
#define PROMPT "--->"

char *read_args(FILE *fp,char *prompt);/* To read the command line*/
char **parse_args(char *);/* To parse the command line*/
void error_occur(char *);/* Errors occur to call this function */
int execute(char **); /* To run the program that command line calls*/
void free_args(char **);
char *get_memory(char *, int );

#endif
