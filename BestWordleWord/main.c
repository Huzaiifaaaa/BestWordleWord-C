//including related libraries(start)
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//including related libraries(end)

//user defined data types(start)
struct data
{
    char word[100];
    int score;
};
//user defined data types(end)

//implicit function declarations(start)
int mainMenu();
int getWordsCount();
void calculateScore(int words,struct data *input);
void readFile(char *firstFile,char *secondFile,int firstCount,int secondCount,struct data *input);
//implicit function declarations(end)

//main function, executiion starts here
//returns 0 if program executes successfully
int main()
{
    //predefined constants(start)
    char GUESSESFILE[81]= "guessesTiny.txt";
    char ANSWERSFILE[81]= "answersTiny.txt";
    //predefined constants(end)

    //infinte loop to keep the program running
    while(1)
    {
        printf("Default file names are %s and %s\n\n", GUESSESFILE, ANSWERSFILE);
        int option=mainMenu();
        int guesses=getWordsCount(GUESSESFILE);
        int answers=getWordsCount(ANSWERSFILE);

        struct data *input;
        input = (struct data*) malloc((guesses+answers) * sizeof(struct data));

        readFile(GUESSESFILE,ANSWERSFILE,guesses,answers,input);

        if(option==1)
        {
            printf("%s has %d words\n",ANSWERSFILE,answers);
            printf("%s has %d words\n\n",GUESSESFILE,guesses);
            printf("Words and scores for top first words:\n");
            calculateScore(guesses+answers,input);
            printf("\nDone");
        }
        else if(option==2)
        {
            printf("%s has %d words\n",ANSWERSFILE,answers);
            printf("%s has %d words\n\n",GUESSESFILE,guesses);
            printf("Words and scores for top first words and second words:\n");
            calculateScore(guesses+answers,input);
            printf("\nDone");
        }
        else if(option==3)//if user wants to change the file names
        {
            printf("Enter new answers and guesses filenames: ");//ask for new file names
            ANSWERSFILE[81]='\0';
            GUESSESFILE[81]='\0';
            scanf("%s %s", &ANSWERSFILE, &GUESSESFILE);//store new file names
        }
        printf("\n\n");//for spacing
    }//end of while loop
    
    return 0;
}//end main

//function to calculate score of each word
//takes number of words and array of words as input
//returns nothing
void calculateScore(int words,struct data *input)
{

}//end calculateScore

//funciton to read files
//returns nothing
void readFile(char *firstFile,char *secondFile,int firstCount,int secondCount,struct data *input)
{
    int i=0;//declaring and initializing variables
    char line[10];

    FILE *filePointer;//file pointer
    filePointer=fopen(firstFile,"r");//reading file
    for(i=0;i<firstCount;i++)//reading file
    {
        fgets(line,10,filePointer);
        strcpy(input[i].word,line);
        strcpy(input[i].word,strtok(input[i].word,"\n"));//removing new line character
        input[i].score=0;//setting score to 0
    }
    fclose(filePointer);//closing file

    filePointer=fopen(secondFile,"r");//reading file
    for(int j=i;j<secondCount+firstCount;j++)//reading file
    {
        fgets(line,10,filePointer);
        strcpy(input[j].word,line);
        strcpy(input[j].word,strtok(input[j].word,"\n"));//removing new line character
        input[j].score=0;//setting score to 0
    }
    fclose(filePointer);//closing file
}//end readFile

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

//main menu function
//prints main menu and returns user's choice
int mainMenu()
{
    int choice=0;
    do
    {
        //print main menu
        printf("Menu Options:\n");
        printf("1. Display best first words only\n");
        printf("2. Display best first and best second words\n");
        printf("3. Change answers and guesses filenames\n");
        printf("4. Exit\n");
        printf("Your choice: ");
        scanf("%d", &choice);
    } while (choice<1 || choice>4);

    if(choice==4)//if user chooses to exit
    {
        exit(0);
    }
    return choice;//returning user's choice
}//end mainmenu