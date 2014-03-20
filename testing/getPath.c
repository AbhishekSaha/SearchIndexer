#include <stdio.h>
#include <stdlib.h>

int getLineCount(FILE *myFile)
{
	char c;
	int charCount;
	charCount = 0;

	while((c = getc(myFile)) != '\n')
		charCount++;

	rewind(myFile);
	
	return charCount;
}

int getListingLength(char *beg)
{
	int charCount;
	charCount = 0;

	while(*beg != ')')
	{
		charCount++;
		beg++;
	}

	return charCount;
}

int extractFrequency(char *listing,int frequency)
{

	int counter;
	counter = 0;

	while(listing[counter] != ',')
		counter++;
/*
	1) Count the number of characters that make up the frequency.
	2) create an array that holds that many elements
	3) Copy the characters into that array
	4) Terminate it with a null string.
	5) Use atoi
	6) Return the int.
*/	
	int i;
	i = 0;
	counter++;

	while(isdigit(listing[counter])!= 0)
	{
		i++;
		counter++;
	}

	char freq[i+1]; // make space for the null character

	counter -= i;
	i = 0;
	while(isdigit(listing[counter]) != 0)
	{
		freq[i] = listing[counter];
		i++;
		counter++;
	}

	freq[i] = '\0';



	frequency = atoi(freq);


	return frequency;	
}

char *extractPath(char *listing, char *listStart)
{
	int pathCount;
	pathCount = 0;

	while(*listStart != ' ')
	{
		pathCount++;
		listStart++;
	}
	
	while(*listStart != '(') // rewind
		listStart--;
	
	listStart++;
	char path[pathCount];
	int i;
	i = 0;
	
	while(*listStart != ' ')
	{
		path[i] = *listStart; // copying it into the array
		i++;
		listStart++;
	}
	path[pathCount] = '\0';

	char *myPath;
	myPath = path;

	return myPath;
}

void extractListing(char *line, char *listStart,char *listing)
{

	int counter;
	counter = 0;

	while(*listStart != ')')
	{
		listing[counter] = *listStart;
		counter++;
		listStart++;
	}
	listing[counter] = '\0';

}

char *moveToNextListing(char *listStart)
{
	
	while((*listStart != '(') && (*listStart != '\n'))
		listStart++;
	

	if(*listStart == '\n')
		return listStart;
	
	listStart++;
/*
	while(*listStart != ')')
	{
		printf("%c",*listStart);
		listStart++;
	}
	printf("\n");
*/
	return listStart;
	
}

int getMaxLineCount(FILE *filePtr)
{
	char c;
        int lineCount;
        int maxCount;
        lineCount = 0;
        maxCount = 0;
        while(c != EOF)
        {
                c = fgetc(filePtr);
                lineCount++;
                if((c == '\n') && (lineCount > maxCount))
                {
                        maxCount = lineCount;
                        lineCount = 0;
                }
	}

	rewind(filePtr);
	return maxCount;
}

int main(int argc, char **argv)
{
	char *file = argv[1];
	FILE *filePtr = fopen(file,"r");


	// get the line
	int lineCount;
	lineCount = getMaxLineCount(filePtr);
	char line[lineCount];

	int listingLength;
	listingLength = lineCount;
	char listing[lineCount];
	while((fgets(line,lineCount,filePtr) != NULL))
	{	
		char *listStart;
		int position;
		position = 1;
		listStart = &line[position];
	
		int frequency;
		char *path;

		extractListing(line,listStart,listing);
	
		while(*listStart != '\n')
		{
			printf("The listing is: %s\n",listing);
			frequency = extractFrequency(listing,frequency);	
			path = extractPath(listing,listStart);
			printf("The path is %s and the frequency is %d\n\n",path,frequency);
		
			listStart = moveToNextListing(listStart);
		}
	}

	


	return 0;
}

