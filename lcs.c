#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char *compareFiles(char *fileName1, char *fileName2, int verbose);
void save_string(const char *filepath, const char *data);
char *getFileContents(char *fileName, size_t verbose);
char *LCS(char *str1, char *str2, size_t verbose);
void generateTables(size_t **lengths, char **directions, char *str1, char *str2);
void getLCS(char **directions, char *str1, size_t i, size_t j, char *buffer);
void printLengthsTable(size_t **lengths, size_t len1, size_t len2);
void printDirectionsTable(char **directions, size_t len1, size_t len2);

int main(size_t argc, char **argv)
{
	if(argc == 3){
		printf("The longest substring is 2:\n%s\n", LCS(argv[1], argv[2], 0));
	}
	else if(argc >= 4){
		if(!strcmp(argv[1], "-f")){
			if(argc == 5){
				save_string(argv[4], compareFiles(argv[2], argv[3], 0));
			}	
			else
				compareFiles(argv[2],argv[3], 1);
		}
		else{
			printf("The longest substring is:\n%s\n", LCS(argv[2], argv[3], 0));
		}
	}
	else{
		printf("Incorrect amount of arguments. Please try again.\n");
		return 0;	
	}
	
	
	
	
}


char *compareFiles(char *fileName1, char *fileName2, int verbose)
{
	char *string1 = getFileContents(fileName1,1);
	char *string2 = getFileContents(fileName2,1);

	char *result = LCS(string1, string2, 0);
	if(verbose)
		printf("The longest substring between the two strings: \n%s\n", result);
	return result;
	
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

// Found from http://stackoverflow.com/questions/2029103/correct-way-to-read-a-text-file-size_to-a-buffer-in-c
char *getFileContents(char *fileName, size_t verbose)
{
	char *source = NULL;
	printf("***********************************************************************\n");
	printf("File Name: %s. Contents: \n", fileName);
	FILE *fp = fopen(fileName, "r");
	if (fp != NULL) {
	    /* Go to the end of the file. */
	    if (fseek(fp, 0L, SEEK_END) == 0) {
		/* Get the size of the file. */
		long bufsize = ftell(fp);
			if (bufsize == -1) { /* Error */ }

			/* Allocate our buffer to that size. */
			source = malloc(sizeof(char) * (bufsize + 1));

			/* Go back to the start of the file. */
			if (fseek(fp, 0L, SEEK_SET) == 0) { /* Error */ }

			/* Read the entire file size_to memory. */
			size_t newLen = fread(source, sizeof(char), bufsize, fp);
			if (newLen == 0) {
			    fputs("Error reading file", stderr);
			} else {
			    source[++newLen] = '\0'; /* Just to be safe. */
			}
		}
		fclose(fp);
	}
	printf("%s\n\n", source);
	printf("***********************************************************************\n\n");
	return source;
}


// REQUIRES: Two valid strings, str1, str2
// MODIFIES: none
// EFFECTS: Determines the longest common subsequence of characters
// and returns a posize_ter to that string
char *LCS(char *str1, char *str2, size_t verbose)
{

	// x corresponds to the horizontal size of the array,
	// and y corresponds to the vertical size of the array
	// They are 1 size bigger to accommodate for an empty row
	// at x = 0  and y = 0
	size_t x = strlen(str1) + 1, y = strlen(str2) + 1;

	
	printf("String 1 size: %ld, String 2 size: %ld\n", x, y);
	//return;

	

	size_t i,j;

	// Allocate memory for tables to compare the strings
	size_t **lengths = malloc(sizeof(void *) * x);
	char **directions = malloc(sizeof(void *) * x);
	for(i = 0; i < x; i++){
		lengths[i] = malloc(sizeof(size_t) * y);
		directions[i] = malloc(sizeof(char) * y);
	}

	
	

	// Generate two tables, one with the maximum count possible
	// per starting posize_t, and one with a direction map of matching
	// strings
	generateTables(lengths, directions, str1, str2);
	
	// Prsize_t out the generated tables
	if(verbose){
		printLengthsTable(lengths, x, y);
		printDirectionsTable(directions, x, y);
	}

	// Call this recursive function to navigate through the directions
	char *lcs = malloc(strlen(str1));
	getLCS(directions,str1,x-1,y-1,lcs);
	
	if(verbose){
		printf("Longest matching string: %s\n", lcs);
		printf("\n");
	}


	// Free used memory
	for(i = 0; i < x; i++){
		free(lengths[i]);
		free(directions[i]);
	}
	free(lengths);
	free(directions);

	printf("Longest common subsequence length: %d\n", strlen(lcs));

	return lcs;
}

// REQUIRES: lengths and directions are initialized to be length(str1) + 1 by
// length(str2) + 1
// MODIFIES: lengths, directions
// EFFECTS: Generates values of the best matching string from the beginning to the end
// of each string in a Dynamic Programming fashion (bottoms up), and indicates a direction
// in the direction table to follow to reach the longest matching string 
void generateTables(size_t **lengths, char **directions, char *str1, char *str2)
{
	
	size_t len1 = strlen(str1) + 1 , len2 = strlen(str2) + 1;
	size_t i, j;

	for(i = 1; i < len1; i++)
	{
		for(j = 1; j < len2; j++)
		{
			// If the strings match, place an incremented count of the upleft array member
			// in the current [i][j] array
			if(str1[i-1] == str2[j-1]){
				lengths[i][j] = lengths[i-1][j-1] + 1;
				directions[i][j] = 'D';	
			}		
			// The next best path is up, so posize_t upwards and put the same count
			// in the current place
			else if(lengths[i-1][j] >= lengths[i][j-1]){
				lengths[i][j] = lengths[i-1][j];
				directions[i][j] = 'U';
			}
			// The next best path is left, so posize_t leftwards and put the same count 
			// in the current array
			else{
				lengths[i][j] = lengths[i][j-1];
				directions[i][j] = 'L';
			}
		}
	}
	
	
}

// REQUIRES: Fully set directions table thats i by j corresponding with str1, 
// and a buffer thats been allocated memory corresponding to the length of str1
// MODIFIES: buffer
// EFFECTS: Follows the directions table to allocate the buffer with the longest
// common substring
void getLCS(char **directions, char *str1, size_t i, size_t j, char *buffer)
{
	// If the cursor has reached the left or top edge of the graph, return
	if(!i || !j){
		return;
	}
	
	// If the direction is a Diagonal, it means there is a new match,
	// so allocate it to the next cursor in the buffer
	if(directions[i][j] == 'D')
	{
		getLCS(directions, str1, i-1, j-1, buffer);
		size_t len = strlen(buffer);
		if(len == 0)
			buffer[0] = str1[i-1];
		else	
			buffer[len] = str1[i-1];
	}

	// The closest direction to the next diagonal is upwards 
	else if(directions[i][j] == 'U')
	{
		getLCS(directions, str1, i-1, j, buffer);
	}
	// The closest direction to the next diagonal is leftwards
	else if(directions[i][j] == 'L')
	{
		getLCS(directions, str1, i, j-1, buffer);
	}
}


// REQUIRES: Fully initialized lengths table, that is len1 by len2
// MODIFIES: none
// EFFECTS: Iterates and prsize_ts out the entire lengths table
void printLengthsTable(size_t **lengths, size_t len1, size_t len2)
{
	size_t i, j;

	for(i = 0; i < len1; i++)
	{
		for(j = 0; j < len2; j++)
		{
			if(!i || !j)
				printf("0 ");
			else
				printf("%d ", lengths[i][j]);
		}
		printf("\n\n");
	}
	printf("\n");

}

// REQUIRES: Fully initialized directions table, that is len1 by len2
// MODIFIES: none
// EFFECTS: Iterates and prsize_ts out the entire directions table
void printDirectionsTable(char **directions, size_t len1, size_t len2)
{
	size_t i, j;

	char c;

	for(i = 0; i < len1; i++)
	{
		for(j = 0; j < len2; j++)
		{
			if(!i || !j)
				printf("B ");
			else{
				c = directions[i][j];
				if(c == 'U')
					printf("^ ");
				else if(c == 'L')
					printf("< ");
				else
					printf("\\ ");		
			}			
		}
		printf("\n\n");
	}
	printf("\n");

}
