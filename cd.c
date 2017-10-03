#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include "cd.h"
void change_dir(char* mp[1024],char dir[1024],char cwd[1024])
{
	if(mp[1]==NULL)
	{
		strcpy(dir,cwd);
		chdir(dir);
	}
	else if(mp[1][0]=='~')
	{
		strcpy(dir,cwd);
		strcat(dir,&mp[1][1]);
		chdir(dir);
	}
	else
		chdir(mp[1]);
}
