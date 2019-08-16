#include"headers.h"

ino_t par_node()
{
	DIR *dir;
	struct dirent *direntp;

	dir=opendir("..");

	if (dir == NULL)
	{
		perror("par_node");
		exit(1);
	}

	while ((direntp = readdir(dir)) != NULL)
	{
		if (strcmp(direntp->d_name,".") == 0)
		{
			closedir(dir);
			return direntp->d_ino;
		}
	}

	fprintf(stderr,"something wrong...\n");
	exit(1);
}

ino_t get_node()
{
	DIR *dir;
	struct dirent * p;

	if ( (dir = opendir(".")) == NULL)
	{
		perror("get_node")	;
		exit(1);
	}

	while ((p = readdir(dir)) != NULL)
	{
		if (strcmp(p->d_name,".") == 0)
		{
			closedir(dir);
			return p->d_ino;
		}
	}

	fprintf(stderr,"bad things happened...\n");
	exit(1);
}

char *get_name(ino_t son)
{
	DIR *dir;
	struct dirent *p;

	if ((dir = opendir(".")) == NULL)
	{
		perror("get_name");
		exit(1);
	}

	while ( (p = readdir(dir)) != NULL)
	{
		if (p->d_ino == son)
			{
				closedir(dir);
				return p->d_name ;
			}
	}
	
	fprintf(stderr,"It's in get_name");
	exit(1);

}

void show_info(ino_t current)
{
	ino_t par=par_node();

	if (par == current)
	{
		return;
	}

	
	chdir("..")	;
	show_info(par);
	printf("/%s",get_name(current));
	chdir(get_name(current));

}
