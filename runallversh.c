/*read buildexe.origin.sh ,then assembly to buildexe.sh(v1)  buildexe.sh(v2)  buildexe.sh(v3)....*/
/*read getcovs.origin.sh ,then assembly to getcovs.sh(v1)  getcovs.sh(v2)  getcovs.sh(v3)....*/

#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stdlib.h>

#define CommandLen 500

void ReplaceSerVer(char[],char[],int ,int );

void ReplaceSerVer(char *fileOrigin,char *fileAllver,int specialLine,int verTh)
{
	int k=1;//line no.
	char strCommand[CommandLen];
	FILE *fdRead,*fdWrite; /*fdead:read file; fdwrite:write file*/
	fdRead = fopen(fileOrigin,"r");
	fdWrite = fopen(fileAllver,"w");
	if( fdRead==NULL || fdWrite==NULL )
	{
		fprintf(stdout, "Error: file open or file write.\n");
		exit(0);
	}

	while( !feof(fdRead) )
	{
		if( NULL==fgets(strCommand,CommandLen,fdRead) )
			break;
		if( strlen(strCommand)<5 )  
			break; //maybe blank line.
		//fgets(strCommand,CommandLen,fdRead);
		if( k==specialLine )
		{
			if( strCommand[0]!='s' || strCommand[1]!='t' || strCommand[2]!='r' || strCommand[3]!='V'
                 || strCommand[4]!='e' || strCommand[5]!='r' || strCommand[6]!='='|| strCommand[7]!='v' )
			{
				printf("%s setVer is error.strCommand=%s",fileOrigin,strCommand);
				exit(0);
			}
			else
				sprintf((char *)strCommand,"strVer=v%d\n",verTh);
		}
		fputs(strCommand,fdWrite);
		k++;
	}
	//close file
	fclose(fdRead);
	fclose(fdWrite);
}

/*************
      main
******************/
int main(int argc, char **argv)
{
	int k,verNum=-1;//version no.

	if( argc<2 )
	{
		fprintf(stdout, "Error: Command line arguments are (SIR object name).\n");
		exit(0);
	}
	sscanf(argv[1],"%d",&verNum);	
	for( k=1;k<=verNum;k++ )
	{
		ReplaceSerVer("buildexe.origin.sh","buildexe.sh",1,k);
		system("bash buildexe.sh");
		ReplaceSerVer("getcovs.origin.sh","getcovs.sh",2,k);	
		system("bash getcovs.sh");
	}
	return 0;
}
