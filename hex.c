#include <stdio.h>
#include <string.h>
#include <sys/ioctl.h>
#include <unistd.h>

int main(int argc, char* argv[])
{
	struct winsize term;
	ioctl(STDOUT_FILENO, TIOCGWINSZ, &term);
	int w = term.ws_col - 10; // width of terminal
	if (argc == 3)
	{
		FILE* f;
		if ((f = fopen(argv[1],"rb+")) == NULL)
		{
			fprintf(stderr,"Opening file error!\n");
			return 0;
		}
		unsigned int counter = 0;
		unsigned int number = 0;
		while(!feof(f))
		{
			if (strcmp(argv[2],"-h") == 0) 
			{
				if (counter == 0)
				{
					printf("%6d| ", number++);
				}
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
				if (counter == 0)
				{
					printf("%6d| ", number++);
				}

				char sym;
				fread(&sym, sizeof(char), 1, f);
				printf("%4d ", sym);	
				counter += 6;
				if (counter >= w) 
				{
					counter = 0;
					printf("\n");
				}
			}
			else if (strcmp(argv[2],"-u8") == 0)
			{	
				if (counter == 0)
				{
					printf("%6d| ", number++);
				}

				unsigned char sym;
				fread(&sym, sizeof(char), 1, f);
				printf("%3d ", sym);
				counter += 5;
				if (counter >= w) 
				{
					counter = 0;
					printf("\n");
				}
			}	
			else if (strcmp(argv[2],"-s") == 0)
			{	
				if (counter == 0)
				{
					printf("%6d| ", number++);
				}

				char sym;
				fread(&sym, sizeof(char), 1, f);
				if (sym != 10)
				{
					printf("%c ", sym);
				}
				else
				{
					counter = w + 1;
				}
				counter += 2;
				if (counter >= w) 
				{
					counter = 0;
					printf("\n");
				}
			}
			else if (strcmp(argv[2],"-r") == 0)
			{
				char sym;
				fread(&sym, sizeof(char), 1, f);
				printf("%c", sym);
			}
			else
			{
				fprintf(stderr, "Wrong flag!\n");
				return 0;
			}
		}
	}
	else
	{
		fprintf(stderr, "Incorrect input!\nhexfc <path> -flag");
	}
	printf("\n");
	return 0;
}
