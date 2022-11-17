//including related libraries(start)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include<time.h>
//including related libraries(end)

//variables definations(start)
//#define filename "wordsLarge.txt"
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
void sort(struct data *input,int size);
int getOccurance(char letter,int *counter);
int compareWords(char word[],char guess[]);
void findCommonLetters(char word[],char guess[]);
int readFile(char *fileName,int words,struct data *input);
void setOccurences(int count, struct data *words, int *counter);
void findSecretWord(int count, char word[],int counter[], struct data* input);
//implicit function declarations(end)


//main function
//execution starts here
//no cmd line arguments
//returns 0 if program executes successfully
int main()
{
    srand(time(0));
    int counter[26]={0};
    int count=getWordsCount(filename);//getting number of words in file

    printf("Using file %s with %d words.\n",filename,count);
    printf("-----------------------------------------------------------\n\n");

    struct data *input;//declaring pointer to struct data
    input = (struct data*) malloc((count) * sizeof(struct data));//allocating memory for struct data

    count=readFile(filename,count,input);//reading file and storing words in struct data

    sort(input,count);//sorting struct data
    setOccurences(count,input,&counter[0]);//getting occurences of each letter

    for(int i=0;i<3;i++)//running game 3 times
    {
        char word[wordlength+1];

        for(int i=0;i<wordlength;i++)//generating random word
        {
            word[i]='*';
        }

        printf("Enter a secret word or just r to choose one at random: ");
        scanf("%s",word);

        if(word[0]=='r' &&  strcmp(word,"r")==0)//selecting random word
        {
            strcpy(word,input[rand()%count].word);
        }

        findSecretWord(count,word,counter,input);//finding secret word
        printf("-----------------------------------------------------------\n\n");
    }
    
    printf("Done\n");
    return 0;//return 0 on successful execution
}//end of main


//function to get index of words starting with letter
//takes word & counter array as argument
//returns index of first word starting with letter
int getOccurance(char letter,int *counter)
{
    if(letter=='a')
    {
        return 0;
    }

    int count=0;
    for(int i=0;i<letter-'a';i++)
    {
        count+=counter[i];
    }

    return count;
}//end of getOccurance


//function to find secret word
//takes number of words as input & struct data pointer
//return nothing
void findSecretWord(int count, char word[],int counter[],struct data* input)
{
    printf("Trying to find secret word:\n   ");
    printWord(word);
    printf("\n\n");

    int start=getOccurance(word[0],counter);//getting position of first letter in struct data

    int guess=1;
    for(int i=start;i<count;i++)
    {
        if(word[1]==input[i].word[1])
        {
            if(guess<10)
            {
                printf(" %d.",guess);
            }
            else
            {   
                printf("%d.",guess);
            }
            int status=compareWords(word,input[i].word);//comparing words, sets capital letters in word

            if(status==1)//if word found
            {
                printf("\n\nGot it!\n");
                break;
            }

            if(guess<10)
            {
                printf("\n   ");
            }
            else
            {   
                printf("\n   ");
            }
            findCommonLetters(word,input[i].word);//sets asteriks in word
            guess++;
        }
    }
}//end of findSecretWord


//function to sort dataset
//takes number of words as input & struct data pointer
//return nothing
void sort(struct data *input,int size)
{
    struct data temp;
    for(int i=0; i<size; i++)
    {
        for(int j=0; j<size-1-i; j++)
        {
            if(strcmp(input[j].word, input[j+1].word) > 0)
            {
                strcpy(temp.word, input[j].word);
                strcpy(input[j].word, input[j+1].word);
                strcpy(input[j+1].word, temp.word);
            }
        }
    }
}//end of sort


//function to find common letters
//takes two words as input
//return nothing
void findCommonLetters(char word[],char guess[])
{
    char tempword[wordlength+1];
    for(int i=0;i<wordlength;i++)//initializing tempword
    {
        tempword[i]=' ';
    }

    char capital[wordlength+1];
    strcpy(capital,guess);//copying word

    for(int i=0;i<wordlength;i++)
    {
        if(word[i]==guess[i])//if matches, set to upper
        {
            capital[i]=toupper(guess[i]);
        }
    }

    //for(int j=0;j<wordlength;j++)
    {
        for(int k=0;k<wordlength;k++)
        {
            if( guess[k]==word[0] || guess[k]==word[1] || guess[k]==word[2] || guess[k]==word[3] || guess[k]==word[4])
            {
                if(capital[k]!=toupper(guess[k]))
                {
                    tempword[k]='*';
                } 
            }
        }
    }

    printWord(tempword);
    printf("\n");
}//end of findCommonLetters


//function to compare words
//takes two words as input
//return status
int compareWords(char word[],char guess[])
{
    char tempword[wordlength+1];
    strcpy(tempword,guess);

    for(int i=0;i<wordlength;i++)
    {
        if(word[i]==guess[i])//if matches, set upper
        {
            tempword[i]=toupper(guess[i]);
        }
    }

    printWord(tempword);
    int status=allUpper(tempword);//checking if all letters are upper
    return status;
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


//function to count words starting with a letter
//returns nothing
void setOccurences(int count, struct data *words, int *counter)
{
    char temp[wordlength+1]="";
    strcpy(temp,words[0].word);

    for(int i=0;i<count;i++)
    {
        if(words[i].word[0]=='a')
        {
            counter[0]++;
        }
        else if(words[i].word[0]=='b')
        {
            counter[1]++;
        }
        else if(words[i].word[0]=='c')
        {
            counter[2]++;
        }
        else if(words[i].word[0]=='d')
        {
            counter[3]++;
        }
        else if(words[i].word[0]=='e')
        {
            counter[4]++;
        }
        else if(words[i].word[0]=='f')
        {
            counter[5]++;
        }
        else if(words[i].word[0]=='g')
        {
            counter[6]++;
        }
        else if(words[i].word[0]=='h')
        {
            counter[7]++;
        }
        else if(words[i].word[0]=='i')
        {
            counter[8]++;
        }
        else if(words[i].word[0]=='j')
        {
            counter[9]++;
        }
        else if(words[i].word[0]=='k')
        {
            counter[10]++;
        }
        else if(words[i].word[0]=='l')
        {
            counter[11]++;
        }
        else if(words[i].word[0]=='m')
        {
            counter[12]++;
        }
        else if(words[i].word[0]=='n')
        {
            counter[13]++;
        }
        else if(words[i].word[0]=='o')
        {
            counter[14]++;
        }
        else if(words[i].word[0]=='p')
        {
            counter[15]++;
        }
        else if(words[i].word[0]=='q')
        {
            counter[16]++;
        }
        else if(words[i].word[0]=='r')
        {
            counter[17]++;
        }
        else if(words[i].word[0]=='s')
        {
            counter[18]++;
        }
        else if(words[i].word[0]=='t')
        {
            counter[19]++;
        }
        else if(words[i].word[0]=='u')
        {
            counter[20]++;
        }
        else if(words[i].word[0]=='v')
        {
            counter[21]++;
        }
        else if(words[i].word[0]=='w')
        {
            counter[22]++;
        }
        else if(words[i].word[0]=='x')
        {
            counter[23]++;
        }
        else if(words[i].word[0]=='y')
        {
            counter[24]++;
        }
        else if(words[i].word[0]=='z')
        {
            counter[25]++;
        }
    }
}//end of setOccurences