#ifndef GRAMMER_H
#define GRAMMER_H

#include"mysh.h"


#define IF "if"
#define ELSE "else"
#define THEN "then"
#define FI "fi"

enum state{NORMAL,IF_STATE,THEN_STATE,ELSE_STATE,FI_STATE };

/*To find out if the cmd line is for grammer */
enum state parse_line(char **args);

/* To process the programm */
void process_control(enum state *, enum state *, char **);


#endif
