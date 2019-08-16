objs = main.c mysh.c varlib.c  grammer.c welcome.c  mypwd.c redir.c pipe.c
mysh: $(objs)
	gcc  -o   mysh    $(objs)
