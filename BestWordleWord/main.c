//including related libraries(start)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//including related libraries(end)

//variables definations(start)
#define filename "wordsTiny.txt"
#define wordlength 5
//variables definations(end)


//user defined data types(start)
struct data
{
    char word[wordlength+1];
    int score;
};
//user defined data types(end)


//implicit function declarations(start)
int getWordsCount(char *fileName);
int readFile(char *fileName,int words,struct data *input);
//implicit function declarations(end)


//main function
//execution starts here
//no cmd line arguments
//returns 0 if program executes successfully
int main()
{
    int count=getWordsCount(filename);//getting number of words in file

    struct data *input;//declaring pointer to struct data
    input = (struct data*) malloc((count) * sizeof(struct data));//allocating memory for struct data

    count=readFile(filename,count,input);//reading file and storing words in struct data

    for(int i=0;i<3;i++)
    {

    }
    
    printf("Done\n");
    printf("\n");
    return 0;//return 0 on successful execution
}//end of main


//function to read file
//returns number of words read
//stores words in input(struct pointer)
int readFile(char *fileName,int words,struct data *input)
{
    FILE *filePointer;//file pointer
    filePointer=fopen(fileName,"r");//reading file

    for(int i=0;i<words;i++)//reading file
    {
        char line[10];
        fgets(line,10,filePointer);
        strcpy(input[i].word,line);
        strcpy(input[i].word,strtok(input[i].word,"\n"));//removing new line character
        input[i].score=0;//setting score to 0
    }
    fclose(filePointer);//closing file
    return words;//returning number of words read
}


//function to get the number of words in the file
//gets file name as input/argument
//returns the number of words in the file
int getWordsCount(char *fileName)
{
    int count=0;
    char line[10];
    FILE *filePointer;//file pointer
    filePointer=fopen(fileName,"r");//reading file

    if( filePointer == NULL )
    {
        printf("Error: could not open %s for reading\n", fileName);
        exit(-1);
    }

    while (fgets(line, sizeof(line), filePointer))
    {
        count++;//incrementing count
    }
    fclose(filePointer);//closing file
    return count;//returning count
}//end getWordsCount