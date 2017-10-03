#include<stdio.h>
#include <pwd.h>
#include<stdlib.h>
#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<unistd.h>
void dir_name(char bre[])
{
	getcwd(bre,1024);
	printf("%s\n",bre);
}
