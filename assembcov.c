/*read scripts/runall.sh ,then assembly to getcovs.sh*/
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

#define CommandLen 5000

void replaceFirst(char *str1,char *str2,char *str3);
 
/*将str1字符串中第一次出现的str2字符串替换成str3*/  
void replaceFirst(char *str1,char *str2,char *str3)  
{  
    char str4[strlen(str1)+1];  
    char *p;  
    strcpy(str4,str1);  
    if((p=strstr(str1,str2))!=NULL)/*p指向str2在str1中第一次出现的位置*/  
    {  
        while(str1!=p&&str1!=NULL)/*将str1指针移动到p的位置*/  
        {  
            str1++;  
        }  
        str1[0]='\0';/*将str1指针指向的值变成/0,以此来截断str1,舍弃str2及以后的内容，只保留str2以前的内容*/  
        strcat(str1,str3);/*在str1后拼接上str3,组成新str1*/  
		/*strstr(str4,str2)是指向str2及以后的内容(包括str2),strstr(str4,str2)+strlen(str2)就是将指针向前移动strlen(str2)位，跳过str2*/  
        strcat(str1,strstr(str4,str2)+strlen(str2));
    }  
}  

/*************
      main
******************/
int main(int argc, char **argv)
{
	int k=1;//testcase no.
	int lenStr; //string length;
	int bFirst = 1; /*judge object name is or not correct*/
	char strObject[30],strCommand[CommandLen];/*strObject:SIR object name,strCommand:shell command name*/
	char strNewShell[CommandLen]; /*getcovs ' new shell command*/
	char strTmp[CommandLen],*pStr; //temp string

	FILE *fdRead,*fdWrite; /*fdead:read file; fdwrite:write file*/
	if( argc<2 )
	{
		fprintf(stdout, "Error: Command line arguments are (SIR object name).\n");
		exit(0);
	}
	strcpy(strObject,argv[1]);	
	fprintf(stdout, "%s\n", strObject);
	
	fdRead = fopen("../scripts/runall.sh","r");
	fdWrite = fopen("./getcovs.sh","w");
	if( fdRead==NULL || fdWrite==NULL )
	{
		fprintf(stdout, "Error: file open or file write.\n");
		exit(0);
	}
	//read "echo script type:"
	fgets(strCommand,CommandLen,fdRead);
	fputs(strCommand,fdWrite);
	fputs("strVer=v?\n",fdWrite);//define v1-v(xxx) and vok

	while( !feof(fdRead) )
	{
		//read "echo ">>>>>>>>running test XXX" "
		if( NULL==fgets(strCommand,CommandLen,fdRead) )
			break;
		if( strlen(strCommand)<20 )  //20< len of "echo ">>>>>>>>running test XXX" "
			break; //maybe blank line.
		fputs(strCommand,fdWrite);

		sprintf((char *)strNewShell,"rm %s.gcda\n",strObject);
		fputs(strNewShell,fdWrite);

		//read shell command 
		if( NULL==fgets(strCommand,CommandLen,fdRead) )
			break;
		if( bFirst>0 ) /*first,check this sh file pertain to  strObject*/
		{
			if( strstr(strCommand,strObject)==NULL )
			{
				fclose(fdRead);
				fclose(fdWrite);
				return -1;
			}
			bFirst = -1;
		}
		replaceFirst(strCommand,"../source/","./");
		fputs(strCommand,fdWrite);
		//mv ../outputs/t1 ../outputs/v(xxx)/t1
		sprintf((char *)strNewShell,"mv ../outputs/t%d ../outputs/${strVer}/t%d\n",k,k);
		fputs(strNewShell,fdWrite);

		//sprintf((char *)strNewShell,"mv %s.c.gcov ../newoutputs/t%d.gcov\n",strObject,k);
		sprintf((char *)strNewShell,"gcov %s.c\n",strObject);
		fputs(strNewShell,fdWrite);

		sprintf((char *)strNewShell,"mv %s.c.gcov ../traces/${strVer}/t%d.gcov\n",strObject,k);
		fputs(strNewShell,fdWrite);

		k++;
		//if( k>=3 ) //for test.
		//	break;
	}
	fputs("echo ${strVer} is finished.\n",fdWrite);//prompt
	//close file
	fclose(fdRead);
	fclose(fdWrite);
	return 0;
}
