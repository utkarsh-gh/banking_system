#include<stdio.h>
#include<string.h>
#define BUFF 100
struct Accounts{
	int Role;
	int Count;
	char AccountNo[10];
	char Password[10];
	char UserName[10];
} a1[100];
void disp(struct Accounts a1[],int size)
{
	int i;
	for(i=0;i<size;i++)
	{
		printf("%s %s %s %d %d\n",a1[i].AccountNo,a1[i].UserName,a1[i].Password,a1[i].Role,a1[i].Count);
	}
}

int main()
{
	struct Accounts a1[100];
	int i=0;
	FILE *fp;
	fp = fopen("Files/AccountDetails.csv", "a+");
	if (fp == NULL)
	{
		printf("Failed to open Account Details");
	}
	else
	{
		char str[BUFF];
		fgets(str, BUFF, fp);
		while(fgets(str, BUFF, fp)!=NULL)
		{
			 strcpy(a1[i].AccountNo,strtok(str,","));
			 strcpy(a1[i].UserName,strtok(NULL,","));
			 strcpy(a1[i].Password,strtok(NULL,","));
			 a1[i].Role=atoi(strtok(NULL,","));
			 a1[i].Count=atoi(strtok(NULL,"\n"));
			// printf("%s %s %d %d\n",a1[i].AccountNo,a1[i].UserName,a1[i].Role,a1[i].Count);
			 i++;
		}
		fclose(fp);
	}
	disp(a1,i);
}
