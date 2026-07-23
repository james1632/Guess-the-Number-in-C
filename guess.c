#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
#include<limits.h>

#define EASY_MAX 10
#define MEDIUM_MAX 100
#define HARD_MAX 1000
#define BUFFER_SIZE 256


typedef struct
{
    int easy;
    int medium;
    int hard;
} Scores;


int loadScores(Scores *scores)
{
    char buffer[BUFFER_SIZE];
    char difficulty[20];
    int score;

    FILE *pF = fopen("score.txt", "r");

    if (pF == NULL)
    {
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), pF) != NULL)
    {
        if (sscanf(buffer, "%d %19s", &score, difficulty) != 2)
        {
            continue;
        }

        if (strcmp(difficulty, "easy") == 0)
        {
            scores->easy = score;
        }
        else if (strcmp(difficulty, "medium") == 0)
        {
            scores->medium = score;
        }
        else if (strcmp(difficulty, "hard") == 0)
        {
            scores->hard = score;
        }
    }

    fclose(pF);

    return 1;
}


int saveScores(const Scores *scores)
{
    FILE *pF = fopen("score.txt", "w");

    if (pF == NULL)
    {
        return 0;
    }

    fprintf(pF, "%d easy\n", scores->easy);
    fprintf(pF, "%d medium\n", scores->medium);
    fprintf(pF, "%d hard\n", scores->hard);

    fclose(pF);

    return 1;
}


int maxScore(int score, int max)
{
    Scores scores = {0, 0, 0};

    loadScores(&scores);

    if (max == EASY_MAX && (scores.easy == 0 || score < scores.easy))
    {
        scores.easy = score;
    }

    else if (max == MEDIUM_MAX && (scores.medium == 0 || score < scores.medium))
    {
        scores.medium = score;
    }

    else if (max == HARD_MAX && (scores.hard == 0 || score < scores.hard))
    {
        scores.hard = score;
    }

    if (saveScores(&scores) == 0)
    {
        printf("Error saving scores.\n");
        return 0;
    }

    return 1;
}


int checkScore()
{
    Scores scores = {0, 0, 0};

    if (loadScores(&scores) == 0)
    {
        printf("No save file detected.\n");
        printf("Press any key to continue playing...");
        getchar();
        getchar();

        return 0;
    }

    printf(
        "- Easy Best Score: %d\n"
        "- Medium Best Score: %d\n"
        "- Hard Best Score: %d\n"
        "Press any key to continue playing...",
        scores.easy,
        scores.medium,
        scores.hard
    );

    getchar();
    getchar();

    return 1;
}


int readInt(int min, int max, const char* messange)
{
    int x;
    int c;
    while (scanf("%d", &x) != 1 || x < min || x > max)
    {
        printf("%s", messange);

        while ((c = getchar()) != '\n' && c != EOF);
    }

    return x;
}


bool playAgain()
{
    char answer;

    while (getchar() != '\n');

    printf("Do you wanna play again? (Y/n): ");
    answer = getchar();

    if (answer == 'n' || answer == 'N')
        return false;

    return true;
}

void screen()
{
    static const char menu[] =
    "=====================\n"
    " Guess the Number\n"
    "=====================\n"
    "1. Easy\n"
    "2. Medium\n"
    "3. Hard\n"
    "4. Custom\n"
    "5. Check max score\n"
    "6. Exit\n";

    puts(menu);
    printf("Choice: ");
}


int game(int max, bool ranked)
{

    int secret = (rand() % max) + 1;

    int guess, tries = 0;
    printf("Guess the number from 1 to %d!: ", max); 
    while (true)
    {
        guess = readInt(1, max, "Input not allowed.\nTry again:");

        if (ranked) tries++;

        if (guess>secret) printf("Too big!\nTry again: ");
        else if (guess<secret) printf("Too small!\nTry again: ");
        else 
        {
            if (ranked)
            {
                printf("You got it! The number was: %d. Tries amount: %d\n\n\n", secret, tries);
                maxScore(tries, max);
            }
            else
            {
             printf("You got it! The number was: %d\n\n\n", secret);
            }
            break;
        }
    } 

    return playAgain();
}

int custom()
{
    int max;

    printf("Set maximum value (greater than zero): ");
    
    max = readInt(1, INT_MAX, "Input not allowed, try again: ");

    return max;
}

int main()
{
    srand(time(NULL));
    
    while (true)
    {
        //printf("\033[2J"); 
            
        #ifdef _WIN32
        system("cls");
        #else
        system("clear");
        #endif    

        screen();

        int level;
        
        level = readInt(1, 6, "Pick correct option: ");
 
        switch(level)
        {
            case 1: if (game(EASY_MAX, true) == 0)
                        return EXIT_SUCCESS; 
                    break; 
            case 2: if (game(MEDIUM_MAX, true) == 0)
                        return EXIT_SUCCESS; 
                    break;
            case 3: if (game(HARD_MAX, true) == 0)
                        return EXIT_SUCCESS; 
                    break;
            case 4: if (game(custom(), false) == 0)
                        return EXIT_SUCCESS; 
                    break;
            case 5: checkScore(); break;
            case 6: return EXIT_SUCCESS;
        } 
    }
}
