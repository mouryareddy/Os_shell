#include <stdlib.h>
#include <pwd.h>
#include <stdio.h>
#include<unistd.h>
#include<malloc.h>
#include<fcntl.h>
#include<errno.h>
#include<sys/wait.h>
#include<string.h>
#include<fcntl.h>
#include<signal.h>
#include "cd.h"
#include "pwd.h"
#include "echo.h"
char *mp[1024];
char home[100];
int fl23,fc,fo,save,save1;
void redirection(char *token);
void mourya(int pk)
{
	struct passwd *pw;
	uid_t uid;
	int c;
	uid = geteuid ();
	pw = getpwuid (uid);
	char hostname[1024];
	char cwd[1024];
	char dir[1024];
	getcwd(cwd,1024);
	gethostname(hostname,1024);
	char *buffer;
	size_t bufsize = 32; 
	size_t characters;
	int bg_arr_size=0;
	int bg_array[1000000];
	buffer = (char *)malloc(bufsize * sizeof(char));
	char mro[1024];
	int i;


	printf("\n");
	getcwd(mro,1024);
	printf("%s@%s:",pw->pw_name,hostname);
	if(strlen(mro) >= strlen(cwd)-1)
	{
		printf("~%s:",&mro[strlen(cwd)]);    
	}
	else
	{
		printf("%s:",mro);
	}
	fflush(stdout);
}
void ctrlz(int sig)
{
	signal(SIGTSTP,SIG_IGN);
	fflush(stdout);
	printf("\n");
}

void piping(char *token)
{
	int   pip[2];
	int fd_inp=0;
	int g,v=0,u=0,f23;
	pid_t pid;
	char *str1;
	char *ftok[1024],*str2,*str3;
	char *ftok1[1024];
	str1=token;
	int h=0;
	str2=strtok(str1,"|");
	while(str2!=NULL)
	{
		ftok[h]=str2;
		h++;
		str2=strtok(NULL,"|");
	}
	ftok[h]=NULL;
	fl23=1;
	for(g=0;g<h;g++)
	{
		pipe(pip);
		v=0;
		f23=0;
		for(int co=0;co<strlen(ftok[g]);co++)
		{
			if(ftok[g][co]=='<' || ftok[g][co]=='>')
			{
				redirection(ftok[g]);
				f23=1;
				break;
			}
		}
		str3=strtok(ftok[g]," ");
		while(str3!=NULL)
		{
			ftok1[v]=str3;
			//printf("%d %s\n",v,ftok1[v]);
			v++;
			str3=strtok(NULL," ");
		}

		ftok1[v]=NULL;

		if ((pid = fork()) == -1)
		{

			exit(EXIT_FAILURE);
		}
		else if (pid == 0)
		{
			//printf("%d %d\n",fo,fc);
			if(fo==0)
				dup2(fd_inp, 0); //change the input according to the old one 
			if ((g+1)!=h && fc==0)
				dup2(pip[1], 1);
			close(pip[0]);
			execvp(ftok1[0], ftok1);
			exit(EXIT_FAILURE);
		}
		else
		{
			wait(NULL);
			close(pip[1]);
			fd_inp = pip[0]; //save the input for the next command
		}
		if(f23==1)
		{
			dup2(save,0);

			dup2(save1,1);
			close(save);
			close(save1);
		}
	}
	return;
}
typedef struct node{
	int x;
	char data[10000];
	struct node *next;
}node;
void print(node* head)
{
	int i=1;
	node* temp1;
	temp1=head;
	while(temp1!=NULL)
	{
		printf("[%d] [%d]",i,temp1->x);
		printf("%s\n",temp1->data);
		temp1=temp1->next;
		i++;
	}
}
node* append(node* head,char data[10000],int x)
{
	struct node* temp = malloc(sizeof(struct node));
	struct node *temp1;
	temp->next=NULL;
	strcpy(temp->data,data);
	temp->x=x;
	if(head == NULL)
	{
		head=temp;
	}	
	else{
		temp1=head;
		while(temp1->next != NULL)
			temp1 = temp1->next;
		temp1->next=temp;
	}
	return head;
}
node* delete(node* head,int position)
{
	if(head==NULL)
		return head;
	else 
	{
		if(position==1)
		{
			node* temp;
			temp=head;
			if(head->next!=NULL)
				head=head->next;
			else
				head=NULL;
			free(temp);
			return head;
		}
		else if(position>1)
		{
			node* temp2;
			temp2=head;
			int count=1;
			while(count<position-1 && temp2 !=NULL)
			{
				temp2=temp2->next;
				count++;
			}
			node* temp3;
			temp3=temp2->next;
			if(temp3!=NULL)
				temp2->next=temp2->next->next;
			else
				printf("Query out of range\n");
			free(temp3);
			return head;
		}
	}
}
void redirection(char *token)
{	char* temp;
	temp=token;
	int len=strlen(token);
	int i;
	fo=0,fc=0;
	int k,r=0;
	int flag2=0;
	int fdo,rc,wc1,fdc;
	char openp[1024],closep[1024];
	save=dup(0);
	save1=dup(1);
	for(i=0;i<len;i++)
	{
		if(temp[i]=='<')
		{
			temp[i]='\0';
			fo=1;
			for(k=i+1;k<len;k++)
			{
				if(temp[k]==' ')
					continue;
				else
				{
					i=k;
					break;
				}
			}
			for(k=i;k<len;k++)
			{
				if(temp[k]=='>' || temp[k]=='<')
				{
					openp[k-i]='\0';
					i=k-1;
					break;

				}
				else
				{
					openp[k-i]=temp[k];
				}
			}
			if(k==len)
			{
				openp[k-i]='\0';
				i=len;
			}
		}
		else if(temp[i]=='>')
		{	fc=1;
			temp[i]='\0';
			if(temp[i+1]=='>')
			{
				flag2=1;
			}
			if(flag2==1)
			{
				for(k=i+2;k<len;k++)
				{if(temp[k]==' ')
					continue;
					else
					{
						i=k;
						break;
					}
				}
				for(k=i;k<len;k++)
				{
					if(temp[k]=='<' || temp[k]=='>')
					{
						closep[k-i]='\0';
						i=k-1;
						break;
					}
					else
					{
						closep[k-i]=temp[k];
					}
				}
				if(k==len)
				{
					closep[k-i]='\0';
					i=len;
				}
			}
			else
			{//	printf("%s\n",array[j]);
				for(k=i+1;k<len;k++)
				{
					if(temp[k]==' ')
						continue;
					else
					{
						i=k;
						break;
					}
				}
				for(k=i;k<len;k++)
				{	//printf("%d\n",i);
					if(temp[k]=='<' || temp[k]=='>')
					{
						closep[k-i]='\0';
						i=k-1;
						break;
					}
					else
					{	//printf("%c\n",array[j][k]);
						closep[k-i]=temp[k];
					}
				}
				if(k==len)
				{
					closep[k-i]='\0';
					i=len;
				}
			}
		}
	}
	len=strlen(closep);
	for(i=len-1;i>=0;i--)
	{
		if(closep[i]==' ')
			closep[i]='\0';
		else
			break;
	}
	len=strlen(openp);
	for(i=len-1;i>=0;i--)
	{
		if(openp[i]==' ')
			openp[i]='\0';
		else
			break;
	}
	if(fo==1)
	{
		fdo = open(openp,O_RDONLY, 0644);
		close(0);
		if(dup2(fdo,0)!=0)
			perror("dup2 fail");
		close(fdo);
	}
	if(fc==1)
	{
		if(flag2==0)
			fdc = open(closep, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		else
			fdc = open(closep, O_APPEND | O_WRONLY | O_CREAT, 0644);

		close(1);
		if(dup2(fdc,1)!=1)
			perror("dup2 fail");
		close(fdc);

	}
	//parse(temp,argv);
	int id,status;
	id=0;
	char *seperate;
	seperate=strtok(temp," ");
	while(seperate!=NULL)
	{
		mp[id]=seperate;
		id++;
		seperate=strtok(NULL," ");
	}
	mp[id]=NULL;
	//    execute(argv);

	if((id=fork())<0)
		perror("error while forking");
	else if(id==0)
	{
		if(execvp(*mp,mp)<0)
		{
			perror("ERROR in exec function");
			exit(0);
		}

	}
	else
		while(wait(&status)!=id);

	dup2(save,0);
	dup2(save1,1);
	close(save);
	close(save1);
	return;
}
int flg=0;

int main(int argc, char *argv[])
{
	node *root=0;
	node *conductor;
	conductor=root;

	struct passwd *pw;
	uid_t uid;
	int c;
	uid = geteuid ();
	pw = getpwuid (uid);
	char hostname[1024];
	char cwd[1024];
	char dir[1024];
	getcwd(cwd,1024);
	gethostname(hostname,1024);
	char *buffer;
	size_t bufsize = 32;
	size_t characters;
	int bg_arr_size=0;
	int bg_array[1000000];
	buffer = (char *)malloc(bufsize * sizeof(char));
	char mro[1024];
	int i;

	while(1)
	{
		signal(SIGTSTP,ctrlz);
		getcwd(mro,1024);
		printf("%s@%s:",pw->pw_name,hostname);
		if(strlen(mro) >= strlen(cwd)-1)
		{
			printf("~%s:",&mro[strlen(cwd)]);	
		}
		else
		{
			printf("%s:",mro);
		}
		int status;
		for(i=0; i<bg_arr_size; i++)
		{
			if(bg_array[i]!=-1)
				if(waitpid(bg_array[i],&status,WNOHANG))
				{
					if(WIFEXITED(status))
					{
						fprintf(stderr,"process with pid %d exited normally\n",bg_array[i]);
						bg_array[i] =-1;

					}
				}
		}
		signal(SIGINT,mourya);
		int characters = getline(&buffer,&bufsize,stdin);
		if(characters==-1)
		{
			printf("\n");
			exit(0);
		}

		buffer[strlen(buffer)-1]='\0';
		char *semi;
		char command[100][100];
		int k=0,i=0;
		semi = strtok(buffer,";");
		while(semi != NULL)
		{

			strcpy(command[i],semi);
			i++;
			k++;
			semi=strtok(NULL,";");
		}
		int flag2,a;
		char com[100][100];
		char *mou;
		char *mp[1024];
		int j=0;
		int h=0;
		for(i=0;i<k;i++)
		{
			int pf=0;
			int len=strlen(command[i]),lf;
			for(a=0;a<len;a++)
			{
				if(command[i][a]=='|')
				{
					piping(command[i]);
					pf=2;
					break;
				}
			}
			if(pf==2)
			{
				//token=strtok(NULL,";");
				continue;
			}
			for(lf=0;lf<len;lf++)
			{
				if(command[i][lf]=='>' || command[i][lf]=='<')
				{
					pf=1;
					redirection(command[i]);
					break;
				}
			}
			if(pf==1)
			{
				i++;//co=strtok(NULL,";");
				continue;
			}


			j=0;
			h=0;
			mou=strtok(command[i]," ");
			if(mou!=NULL)
			{
				mp[0]=mou;
				j++;
				h++;
				mou=strtok(NULL," ");
				char bre[1024];
				int flag=0;
				if((strcmp(mp[0],"cd"))==0)
				{
					flag=-1;
				}
				else if((strcmp(mp[0],"pwd"))==0)
				{
					flag=-2;
				}
				else if((strcmp(mp[0],"echo"))==0)
				{
					flag=-3;
				}
				else if((strcmp(mp[0],"exit"))==0)
				{
					break;
				}
				else if((strcmp(mp[0],"quit"))==0)
				{
					exit(0);
				}
				else if((strcmp(mp[0],"fg"))==0)
				{
					flag=-420;
				}
				else if((strcmp(mp[0],"jobs"))==0)
				{
					flag=-100;
				}
				else if((strcmp(mp[0],"kjob"))==0)
				{
					flag=-101;
				}
				else if((strcmp(mp[0],"killallbg"))==0)
				{
					flag=-85;
				}

				else if(strcmp("pinfo",mp[0])==0)
				{
					FILE *fp;
					flg=0;
					char buf1[1256],buf2[1256];
					int pid;
					char var[1256],state;
					long unsigned int size;
					if(mp[1]==NULL)
					{
						sprintf(buf1,"/proc/%d/stat",getpid());                                 //open the stat and exe files
						sprintf(buf2,"/proc/%d/exe",getpid());
					}
					else
					{
						sprintf(buf1,"/proc/%s/stat",(mp[1]));
						sprintf(buf2,"/proc/%s/exe",(mp[1]));
					}
					if((fp=fopen(buf1,"r"))!=NULL)
					{
						fscanf(fp,"%d %*s %c %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %lu %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d %*d",&pid,&state,&size);  
						fclose(fp);
						printf("pid -- %d\nProcess Status -- %c\nmemory -- %lu\n",pid,state,size);
						readlink(buf2,var,1256);
						if(strstr(var,cwd))
						{
							char fi[1000]="~";
							strcat(fi,var+strlen(cwd));
							printf("Executable Path -- %s\n",fi);                           //print print the stuff
						}
						else
							printf("Executable Path -- %s\n",var);
					}
					else
						fprintf(stderr,"No such process\n");
				}
				int flag5=0;
				while(mou != NULL)
				{
					mp[j]=mou;
					if((strcmp(mp[j],"&"))==0)
					{
						flag5=-10;
						break;
					}
					j++;
					h++;
					mou=strtok(NULL," ");
				}	
				int m;
				mp[h] = NULL;
				if(flag==0)
				{
					int fd;
					int rc=fork();
					if(rc==0)
					{

						int p; 
						p=execvp(mp[0],mp);
					}
					if(flag5==-10)
					{
						int pre;
						char ntr[10000];
						strcpy(ntr,mp[0]);
						for(pre=1;pre<h;pre++)
						{
							strcat(ntr," ");
							strcat(ntr,mp[pre]);
						}
						root=append(root,ntr,rc);


					bg_array[bg_arr_size++]=rc;
					}




					else if(flag5!=-10)
					{
						int wc,status;
						wc=waitpid(rc,&status,WUNTRACED);
						//wc=wait(NULL);
					}
				}
				else if(flag==-1)
				{
					change_dir(mp,dir,cwd);

				}
				else if(flag==-2)
				{

					dir_name(bre);

				}
				else if(flag==-3)
				{
					print1(mp,h);


				}
				else if(flag==-100)
				{
					print(root);
				}
				else if(flag==-101)
				{
					node* temp2;
					temp2=root;
					int jk,vi=1,hp;
					jk=atoi(mp[1]);
					while(temp2!=NULL)
					{
						if(vi==jk)
						{
							hp=temp2->x;

							int si;
							si=atoi(mp[2]);
							kill(hp,si);
							if(si==9)
							{

								root=delete(root,vi);
							}
						}
						temp2=temp2->next;
						vi++;
					}
				}
				else if(flag==-420)
				{
					node* temp3;
					temp3=root;
					int status,kg,vm=1,dell;
					kg=atoi(mp[1]);
					while(temp3!=NULL)
					{
						if(vm==kg)
						{
							dell=temp3->x;
							waitpid(dell,&status,0);
						}
						temp3=temp3->next;
						vm++;
					}
				}
				else if(flag==-85)
				{
					node* temp4;
					temp4=root;
					int ed=1,lenovo;
					while(temp4!=NULL)
					{
						lenovo=temp4->x;
						kill(lenovo,9);
						temp4=temp4->next;
						root=delete(root,ed);
						ed++;
					}
				}
			}

	
			if((strcmp(mp[0],"exit"))==0)
			{
				break;
			}
		}
		
	}
	return 0;
}
