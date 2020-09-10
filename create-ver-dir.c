/*create sub-directory in current dir ' traces from 1 to verno*/
#include <stdio.h>
#include <sys/stat.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	int verno = 0;
	int k;
	char path[100];
	if( argc<2 )
	{
		fprintf(stdout, "Error: Command line arguments are (ver numbers).\n");
		exit(0);
	}
	verno = atoi(argv[1]);	
	fprintf(stdout, "%d\n", verno);
	for( k=1;k<=verno;k++ )
	{
		sprintf(path,"../traces/v%d",k);
		mkdir(path, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	}
	return 0;
}


