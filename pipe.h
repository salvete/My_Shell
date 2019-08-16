#ifndef PIPE_H
#define PIPE_H

#include"headers.h"
#include"mysh.h"

/* return the position of '|' -- if there is any */
int is_pipe(char **args);
/* to run when there is a pipe */
int make_pipe(char **, char **);

#endif


