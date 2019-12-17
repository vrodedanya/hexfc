#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	struct winsize term;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &term);
	int w = term.ws_col - 1;
	if (argc != 2)
	{
		unsigned int counter = 0;
		FILE* f;
		if ((f = fopen(argv[1],"rb+")) == NULL)
		{
			fprintf(stderr,"Opening file error!\n");
			return 0;
		}
		while(!feof(f))
		{
			if (strcmp(argv[2],"-hex") == 0) 
			{
				unsigned char sym;
				fread(&sym, sizeof(char), 1, f);
				if (sym < 16)
				{
					printf("0");
				}
				printf("%x ", sym);		
				counter += 3;
				if (counter >= w) 
				{
					counter = 0;
					printf("\n");
				}
			}
			else if (strcmp(argv[2],"-8") == 0)
			{
				char sym;
				fread(&sym, sizeof(char), 1, f);
				printf("%4d ", sym);	
				counter += 5;
				if (counter >= w) 
				{
					counter = 0;
					printf("\n");
				}
			}
			else if (strcmp(argv[2],"-u8") == 0)
			{	
				unsigned char sym;
				fread(&sym, sizeof(char), 1, f);
				printf("%3d ", sym);
				counter += 4;
				if (counter >= w) 
				{
					counter = 0;
					printf("\n");
				}
			}	
			else if (strcmp(argv[2],"-sym") == 0)
			{	
				char sym;
				fread(&sym, sizeof(char), 1, f);
				printf("%c", sym);
				counter += 1;
				if (counter >= w) 
				{
					counter = 0;
					printf("\n");
				}
			}
			else
			{
				fprintf(stderr, "Incorrect input!\nhexfc <path> -flag\n");
				return 0;
			}
		}
		printf("\n");
	}
	else
	{
		fprintf(stderr, "Incorrect input!\nhexfc <path> -flag\n");
	}
	return 0;
}
