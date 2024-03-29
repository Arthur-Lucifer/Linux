/*************************************************************************
	> File Name: minishell.c
	> Author: lxh
	> Created Time: Fri 18 Oct 2019 03:11:25 AM PDT
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<string.h>
#include<ctype.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<fcntl.h>

#define MAX_CMD 1024
char command[MAX_CMD];

int do_face()
{
	memset(command,0x00,MAX_CMD);
	printf("minishell$");
	fflush(stdout);
	if(scanf("%[^\n]%*c",command) == 0){
		getchar();
		return -1;
	}
	return 0;
}
char **do_parse(char *buff)//识别输入
{
	char* ptr = buff;
	static char *argv[32];
	//static
	int argc = 0;
	while(*ptr!='\0')
	{
		if(!isspace(*ptr)){
			argv[argc++] = ptr;
			while(!isspace(*ptr) && (*ptr)!='\0')
			{
				ptr++;
			}
		}
		else{
			while(isspace(*ptr) && (*ptr != '\0')){
				*ptr = '\0';
				ptr++;
			}
		}
	}
	argv[argc] = NULL;
	return argv;
}
int do_exec(char *buff)
{
	char** argv = {NULL};

	int pid = fork();

	if(pid == 0)
	{
		argv = do_parse(buff);
		if(argv[0] == NULL){
			exit(-1);
		}
		execvp(argv[0],argv);
	}
	else{
		waitpid(pid,NULL,0);
		//wait();
	}
	return 0;
}
int main(int argc,char *argv[])
{
	while(1)
	{
		if(do_face()<0)
			continue;
		do_exec(command);
	}
	return 0;
}
