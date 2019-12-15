#include <stdio.h>
#include <string.h>

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		unsigned int counter = 0;
		FILE* f;
		if ((f = fopen(argv[1],"rb+")) == NULL)
		{
			fprintf(stderr,"Opening file error!\n");
		}
		while(!feof(f))
		{
			if (strcmp(argv[2],"-hex") == 0) 
			{
				unsigned char sym;
				fread(&sym, sizeof(char), 1, f);
				printf("%x ", sym);			
			}
			else if (strcmp(argv[2],"-8") == 0)
			{
				char sym;
				fread(&sym, sizeof(char), 1, f);
				printf("%d ", sym);		
			}
			else if (strcmp(argv[2],"-u8") == 0)
			{	
				unsigned char sym;
				fread(&sym, sizeof(char), 1, f);
				printf("%d ", sym);
			}
			else
			{
				printf("Incorrect input!\n");
				return 0;
			}
		}
		printf("\n");
	}
	else
	{
		printf("Incorrect input!\n");
	}
	return 0;
}
