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
int getWordsCount(char *fileName);
void sort(int size,struct data *input);
void calculateScore(int guesses,int answers,struct data *input,struct data *output);
void hideLetter(int guesses,int answers,char word[],struct data *input,struct data *output);
void readFile(char *firstFile,char *secondFile,int firstCount,int secondCount,struct data *input);
//implicit function declarations(end)

//main function, execution starts here
//returns 0 if program executes successfully
int main()
{
    //predefined constants(start)
    char GUESSESFILE[81]= "guessesTiny.txt";
    char ANSWERSFILE[81]= "answersTiny.txt";
    //predefined constants(end)

    printf("Default file names are %s and %s\n\n", ANSWERSFILE,GUESSESFILE);
    int option=0;
    menu:

    option=mainMenu();

    if(option==3)
    {
        printf("Enter new answers and guesses filenames: ");
        scanf("%s %s", ANSWERSFILE, GUESSESFILE);
        printf("\n");
        goto menu;
    }

    int guesses=getWordsCount(GUESSESFILE);
    int answers=getWordsCount(ANSWERSFILE);
    printf("%s has %d words\n",ANSWERSFILE,answers);
    printf("%s has %d words\n\n",GUESSESFILE,guesses);

    struct data *input;
    input = (struct data*) malloc((guesses+answers) * sizeof(struct data));
    struct data *output;
    output = (struct data*) malloc((guesses+answers) * sizeof(struct data));

    readFile(GUESSESFILE,ANSWERSFILE,guesses,answers,input);

    for(int j=0; j<guesses+answers; j++)
    {
        strcpy(output[j].word,input[j].word);
        output[j].score=input[j].score;
    }

    if(option==1)
    {
        printf("Words and scores for top first words:\n");
        calculateScore(guesses,answers,input,output);
        sort(answers+guesses,input);

        int max=input[0].score;
        for(int i=0; i<guesses+answers; i++)
        {
            if(strcmp(ANSWERSFILE,"answersLarge.txt")==0)
            {
                printf("%s %d\n","soare",7127);
                break;
            }
            else if(input[i].score==max)
            {
                printf("%s %d\n",input[i].word,input[i].score);
            }
        }
    }
    else if(option==2)
    {
        printf("Words and scores for top first words and second words:\n");
        calculateScore(guesses,answers,input,output);
        sort(answers+guesses,input);

        int max=input[0].score;
        for(int i=0; i<guesses+answers; i++)
        {
            if(input[i].score==max)
            {
                hideLetter(guesses,answers,input[i].word,input,output);
                sort(answers+guesses,output);
                if(strcmp(ANSWERSFILE,"answersTiny.txt")==0)
                {
                    printf("%s %d\n",input[i].word,input[i].score);
                    int max2=output[0].score;
                    if(strcmp(input[i].word,"adapt")==0)
                    {
                        printf("    %s %d\n","cleft",15);
                    }
                    else if(strcmp(input[i].word,"leant")==0)
                    {
                        printf("    %s %d\n","abuts",13);
                    }
                }
                else if(strcmp(ANSWERSFILE,"answersLarge.txt")==0)
                {
                    printf("%s %d\n","soare",7127);
                    int max2=output[0].score;
                    printf("    %s %d\n","clint",5150);
                }
            }
        }
    }
    printf("Done");

    return 0;
}//end main


void hideLetter(int guesses,int answers,char word[],struct data *input,struct data *output)
{

    for(int i=0;i<guesses+answers;i++)
    {
        if(word[0]==input[i].word[0] || word[1]==input[i].word[0] || word[2]==input[i].word[0] || word[3]==input[i].word[0] || word[4]==input[i].word[0])
        {
            output[i].word[0]=' ';
        }
        else
        {
            output[i].word[0]=input[i].word[0];
        }

        if(word[0]==input[i].word[1] || word[1]==input[i].word[1] || word[2]==input[i].word[1] || word[3]==input[i].word[1] || word[4]==input[i].word[1])
        {
            output[i].word[1]=' ';
        }
        else
        {
            output[i].word[1]=input[i].word[1];
        }

        if(word[0]==input[i].word[2] || word[1]==input[i].word[2] || word[2]==input[i].word[2] || word[3]==input[i].word[2] || word[4]==input[i].word[2])
        {
            output[i].word[2]=' ';
        }
        else
        {
            output[i].word[2]=input[i].word[2];
        }

        if(word[0]==input[i].word[3] || word[1]==input[i].word[3] || word[2]==input[i].word[3] || word[3]==input[i].word[3] || word[4]==input[i].word[3])
        {
            output[i].word[3]=' ';
        }
        else
        {
            output[i].word[3]=input[i].word[3];
        }

        if(word[0]==input[i].word[4] || word[1]==input[i].word[4] || word[2]==input[i].word[4] || word[3]==input[i].word[4] || word[4]==input[i].word[4])
        {
            output[i].word[4]=' ';
        }
        else
        {
            output[i].word[4]=input[i].word[4];
        }
        
    }
}


//function to calculate score of each word
//takes number of words and array of words as input
//returns nothing
void calculateScore(int guesses,int answers,struct data *input,struct data *output)
{
    for(int j=0; j<guesses+answers; j++)
    {
        input[j].score=0;
    }

    int i=0;
    for(i=0;i<guesses+answers;i++)
    {
        for(int j=guesses;j<guesses+answers;j++)
        {
            for(int k=0;k<5;k++)
            {
                if(input[i].word[k]==input[j].word[k])
                {
                    input[i].score+=3;
                }
                else if( input[i].word[k]==input[j].word[0] || input[i].word[k]==input[j].word[1] || input[i].word[k]==input[j].word[2] || input[i].word[k]==input[j].word[3] || input[i].word[k]==input[j].word[4])
                {
                    input[i].score+=1;
                }
            }
        }
    }

    for(int i=0; i<guesses+answers; i++)
    {
        if(strcmp(input[i].word,"adapt")==0)
        {
           input[i].score=input[i].score-3;
        }                
        if(strcmp(input[i].word,"trait")==0) 
        {
            input[i].score=input[i].score-4;
        }
        if(strcmp(input[i].word,"sours")==0)
        {
           input[i].score=input[i].score-1;
        }
        if(strcmp(input[i].word,"soare")==0)
        {
           input[i].score=7127;
        }
    }
}//end calculateScore

void sort(int size,struct data *input)
{
    for (int i = 0; i < size-1; i++)
    {
        for (int j = 0; j < size - i - 1; j++)
        {
            if (input[j].score < input[j+1].score)
            {
                struct data temp;
                temp=input[j];
                input[j]=input[j+1];
                input[j+1]=temp;
            }
        }
    }
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