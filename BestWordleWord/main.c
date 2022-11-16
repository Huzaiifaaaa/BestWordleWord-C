//including related libraries(start)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<time.h>
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
void printWord(char word[]);
int allUpper(char word[]);
int compareWords(char word[],char guess[]);
int readFile(char *fileName,int words,struct data *input);
void findSecretWord(int count, char word[], struct data* input);
//implicit function declarations(end)


//main function
//execution starts here
//no cmd line arguments
//returns 0 if program executes successfully
int main()
{
    srand(time(0));
    int count=getWordsCount(filename);//getting number of words in file

    struct data *input;//declaring pointer to struct data
    input = (struct data*) malloc((count) * sizeof(struct data));//allocating memory for struct data

    count=readFile(filename,count,input);//reading file and storing words in struct data

    for(int i=0;i<3;i++)
    {
        char word[wordlength+1]="";
        printf("Enter a secret word or just r to choose one at random: ");
        scanf("%s",word);
        
        if(word[0]=='r')
        {
            strcpy(word,input[rand()%count].word);
        }

        findSecretWord(count,word,input);
        printf("-----------------------------------------------------------\n\n");
    }
    
    printf("Done\n");
    return 0;//return 0 on successful execution
}//end of main


//function to find secret word
//takes number of words as input & struct data pointer
//return nothing
void findSecretWord(int count, char word[],struct data* input)
{
    printf("Trying to find secret word:\n   ");
    printWord(word);
    printf("\n\n");

    int guess=1;
    for(int i=0;i<count;i++)
    {
        if(guess<10)
        {
            printf(" %d.",guess);
        }
        else
        {   
            printf("%d.",guess);
        }
        int status=compareWords(word,input[i].word);

        if(status==1)
        {
            printf("\n\nGot it!\n");
           break;
        }

        printf("\n\n");
        guess++;
    }


}//end of findSecretWord


//function to compare words
//takes two words as input
//return status
int compareWords(char word[],char guess[])
{
    char tempword[wordlength+1];
    strcpy(tempword,guess);

    for(int i=0;i<wordlength;i++)
    {
        if(word[i]==guess[i])
        {
            tempword[i]=toupper(guess[i]);
        }
    }

    printWord(tempword);
    int status=allUpper(tempword);

}//end of compareWords


//function to print word
//takes word as input
//return nothing
void printWord(char word[])
{
    printf("   ");
    for(int i=0;i<wordlength;i++)
    {
        printf("%c ",word[i]);
    }
}//end of printWord


//function to check if word is all upper case
//takes word as input
//return 1 if word is all upper case
int allUpper(char word[])
{
    for(int i=0;i<wordlength;i++)
    {
        if(islower(word[i]))
        {
            return 0;
        }
    }
    return 1;
}//end of allUpper


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