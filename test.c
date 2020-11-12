#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<string.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<stdlib.h>
#include<dirent.h>
#include<stddef.h>
#include<fcntl.h>
#include<time.h>
#include<sys/time.h>
#include<pwd.h>
#include"mycmd.h"
#define buffsize 1024
int main()
{
	char command[30];
	while(1)
	{	
		printf("$");
		scanf("%s",command);
		fflush(stdin);
		if(strcmp(command,"pwd")==0)	
		{
			pwd_();
		}
		else if(strcmp(command,"mkdir")==0)  
		{
			makedir_();
		}
		else if(strcmp(command,"exit")==0)
		{
			exit_();
		}
		else if(strcmp(command,"cd")==0) 
		{
			chadir_();
		}
		else if((strcmp(command,"ls")==0))
		{
			list_();
		}
		else if(strcmp(command,"cp")==0)	
		{
			copy_();
		}
		else if(strcmp(command,"find")==0)	
		{
			find_();
		}
		else if(strcmp(command,"touch")==0)	
		{
			touch_();
		}
		else if(strcmp(command,"whoami")==0)	
		{
			whoami_();
		}
		else if(strcmp(command,"rm")==0)	
		{
			remove_();
		}
		else if(strcmp(command,"date")==0)	
		{
			date();
		}
		else if(strcmp(command,"clear")==0)	
		{
			clear();
		}
		else 		
			error_();
	}
	return 0;
}

