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
void pwd_()
{
	char *path=NULL;
	path=getcwd(NULL,0);
	puts(path);
}

void makedir_()
{
	char command1[30];
	scanf("%s",command1);
	fflush(stdin);
	if(mkdir(command1,0755)!=0)     
		printf("make dir default!\n");
}


void exit_()
{
	exit(0);
}

void chadir_()
{
	char command3[50];
	scanf("%s",command3);
	fflush(stdin);
	if(chdir(command3)!=0)
	{
		printf("change dir path default!\n");
	}
}

void list_()
{
	char command4[50];
	struct dirent *entry;
	DIR *olist=NULL;
	scanf("%s",command4);
	fflush(stdin);
	if((olist=opendir(command4))==NULL)
	{
		printf("opendir  default!\n");
	}
	while(entry=readdir(olist))
	{
		if(strncmp(entry->d_name,".",1) == 0 )
			continue;
		printf("%s\t",entry->d_name);
	}
	printf("\n");
	if(closedir(olist)!=0)
		printf("closedir  default!\n");
}

void copy_()
{
	char cp1[30],cp2[30],buf[buffsize];
	int fd1,fd2;
	int n;
	scanf("%s",cp1);
    	fflush(stdin);
	scanf("%s",cp2);
   	if((fd1=open(cp1,O_RDWR|O_CREAT,0664))==-1)
		printf("open the file false!\n");
	if((n=read(fd1,buf,buffsize))==-1)
		printf("read the file false!\n");
	if((fd2=open(cp2,O_RDWR|O_CREAT,0664))==-1)
		printf("open the file false!\n");
	if(write(fd2,buf,n)==-1)
		printf("open the file false!\n");
	if(close(fd1)==-1)
		printf("close false!\n");
	if(close(fd2)==-1)
		printf("close false!\n");
}
void find_()
{
	char str1[30],str2[30];
	scanf("%s",str1);
	fflush(stdin);
	scanf("%s",str2);
	fflush(stdin);
	List(str1,str2);
}
void List(char *path,char *name)
{
	struct dirent* ent = NULL;
	DIR *pDir;
	char dir[512];
	struct stat statbuf;  
	if((pDir=opendir(path))==NULL)
	{
		return;
	}
	while((ent=readdir(pDir))!=NULL)
	{
		snprintf( dir, 512,"%s/%s", path, ent->d_name );   
		lstat(dir, &statbuf);
		if(S_ISDIR(statbuf.st_mode))
		{
			if(strncmp(ent->d_name,".",1) == 0 )  
				continue;
			List(dir,name);               
		}
		else
		{
			if(strcmp(name,ent->d_name) == 0 )  
				printf("%s\n",dir);
		}       
	}
	closedir(pDir);
}
void touch_()
{
	char str1[30];
	scanf("%s",str1);
	fflush(stdin);
	if(access(str1,F_OK)==0){
		struct timespec newtime[2];
		newtime[0].tv_nsec=UTIME_NOW;
		newtime[1].tv_nsec=UTIME_NOW;
		utimensat(AT_FDCWD,str1,newtime,0);
	}else{
		open(str1,O_CREAT,0644);
	}
}
void whoami_()
{
	uid_t id;
	struct passwd * pa;
	id=geteuid();
	pa=getpwuid(id);
	printf("%s\n",pa->pw_name);
	
}
void remove_()
{
	char str1[30];
	scanf("%s",str1);
	fflush(stdin);
	remove_dir(str1);
	
}
int remove_dir(const char *dir)
{
	char cur_dir[] = ".";
	char up_dir[] = "..";
	char dir_name[512];
	DIR *dirp;
	struct dirent *dp;
	struct stat dir_stat;
	if ( 0 != access(dir, F_OK) ) {
		return 0;
	}
	if ( 0 > stat(dir, &dir_stat) ) {
		return -1;
	}
	if ( S_ISREG(dir_stat.st_mode) ) {
		remove(dir);
	} else if ( S_ISDIR(dir_stat.st_mode) ) { 
		dirp = opendir(dir);
		while ( (dp=readdir(dirp)) != NULL ) {
			if ( (0 == strcmp(cur_dir, dp->d_name)) || (0 == strcmp(up_dir, dp->d_name)) ) {
				continue;
			}
			sprintf(dir_name, "%s/%s", dir, dp->d_name);
			remove_dir(dir_name);
       	}
        	closedir(dirp);
        	rmdir(dir);
	} else {
		perror("unknow file type!");    
	}
}
void error_()
{
	printf("command not found !\n");
}
void date(){
	time_t t;
	time(&t);
	printf("%s",ctime(&t));
}
void clear(){
	printf("\x1b[H\x1b[2J");
}
