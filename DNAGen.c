#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


void save_string(const char *filepath, const char *data);

int main(size_t argc, char **argv)
{
	if(argc != 3 && argc != 2){
		printf("Incorrect number of arguments.\nUsage: ./DNAGen length filename.txt\n\n");	
		return 0;
	}

	
	
	srand(time(NULL));

	size_t length = atoi(argv[1]);
	char *buffer = malloc(sizeof(char) * length);
	
	int i, temp;
	for(i = 0; i < length; i++)
	{
		temp = rand() % 4;
		if(temp  == 0)
			buffer[i] = 'A';
		else if(temp == 1)
			buffer[i] = 'U';
		else if(temp == 2)
			buffer[i] = 'G';
		else if(temp == 3)
			buffer[i] = 'C';
	}

	if(argc == 3){
		save_string(argv[2], buffer);
		//printf("DNA subsequence saved to %s!\n", argv[2]);
	}
	else{
		printf("Result: %s\n", buffer);
	}
	free(buffer);
}

// From: http://stackoverflow.com/questions/4182876/how-to-write-a-string-to-a-file-in-c-programming
void save_string(const char *filepath, const char *data)
{
    FILE *fp = fopen(filepath, "ab");
    if (fp != NULL)
    {
        fputs(data, fp);
        fclose(fp);
    }
}
