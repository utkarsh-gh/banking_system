#include<stdio.h>
#include<string.h>
#define BUFF 100

int num_accounts;
struct Accounts{
	int Role;                        // Role = 1 for customer Role = 2 for administrator
	int Count;
	char AccountNo[10];
	char Password[10];
	char UserName[10];
};
void write_to_file(struct Accounts a1[])
{
	int size=num_accounts;
	int i;
	FILE *fp;
	fp = fopen("Files/AccountDetails.csv", "w");
	if (fp == NULL)
	{
		printf("Failed to open Account Details");
	}
	else
	{
		fprintf(fp,"AccountNo,UserName,Password,Role,Count\n");
		for(i=0;i<size;i++)
		{
			fprintf(fp,"%s,%s,%s,%d,%d\n",a1[i].AccountNo,a1[i].UserName,a1[i].Password,a1[i].Role,a1[i].Count);
		}
	}
	fclose(fp);
}
void unblock_user(struct Accounts a1[])
{
	char acc_no[10];
	printf("ENTER CUSTOMER ACCOUNT NUMBER TO UNBLOCK\n");
	scanf("%10s",&acc_no);
	int size=num_accounts;
	int i;
	for(i=0;i<size;i++)
	{
		if(strcmp(a1[i].AccountNo,acc_no)==0){
			a1[i].Count=0;
			write_to_file(a1);
			return;
		}
	}
	printf("ENTER A VALID ACCOUNT NUMBER\n");
}
void disp_blocked_users(struct Accounts a1[])
{
	int size=num_accounts;
	int i;
	for(i=0;i<size;i++)
	{
		if((a1[i].Role==1)&&(a1[i].Count>=3))
		printf("%s %s %s %d\n",a1[i].AccountNo,a1[i].UserName,"USER   ATTEMPTS ->",a1[i].Count);
	}
}
struct Accounts* read(){
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
			 i++;
		}
		fclose(fp);
		num_accounts = i;
	}
	return(a1);
}

int main()
{
	struct Accounts *a1;
	a1 = read();
	disp_blocked_users(a1);
	unblock_user(a1);
	disp_blocked_users(a1);
}
