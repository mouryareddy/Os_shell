#include<stdio.h>
#include<string.h>
void print1(char* mp[1024],int h)
{
	int i;
	for(i=1;i<h;i++)
	{
		printf("%s ",mp[i]);
	}
	printf("\n");
}
