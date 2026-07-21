#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include<stdbool.h>
#include<limits.h>

#define EASY_MAX 10
#define MEDIUM_MAX 100
#define HARD_MAX 1000


int maxScore(int score, int max)
{
    int easy = 0;
    int medium = 0;
    int hard = 0;

    char buffer[100];
    char difficulty[20];
    int oldScore;

    FILE *pF = fopen("score.txt", "r");
    if (pF != NULL) 
    { 
       while (fgets(buffer, sizeof(buffer), pF) != NULL)
        {
            sscanf(buffer, "%d %s", &oldScore, difficulty);
            if (strcmp(difficulty, "easy") == 0)
                easy = oldScore;
            if (strcmp(difficulty, "medium") == 0)
                medium = oldScore;
            if (strcmp(difficulty, "hard") == 0)
                hard = oldScore;
        }
        fclose(pF);
    }

    if (max == EASY_MAX && (easy == 0 || score<easy))
        easy = score;
    if (max == MEDIUM_MAX && (medium == 0 || score<medium))
        medium = score;
    if (max == HARD_MAX && (hard == 0 || score<hard))
        hard = score;
    
    pF = fopen("score.txt", "w");

    if (pF == NULL)
    {
        printf("Error\n");
        return 1;
    }

    fprintf(pF, "%d easy\n", easy);
    fprintf(pF, "%d medium\n", medium);
    fprintf(pF, "%d hard\n", hard);

    fclose(pF);
    return 0;
}


int checkScore()
{
    char buffer[255];
    char difficulty[20];
    int score;
    int easy;
    int medium;
    int hard;
    
    FILE *pF = fopen("score.txt", "r");

    if (pF == NULL) 
    { 
        printf("No save file detected. Press any key to continue game: "); 
        getchar(); 
        getchar(); 
        return 1; 
    }
    else
    { 
       while (fgets(buffer, sizeof(buffer), pF) != NULL)
        {
            sscanf(buffer, "%d %s", &score, difficulty);
            if (strcmp(difficulty, "easy") == 0)
                easy = score;
            if (strcmp(difficulty, "medium") == 0)
                medium = score;
            if (strcmp(difficulty, "hard") == 0)
                hard = score;
        }
        fclose(pF);
    }
    
    printf("- Easy Best Score: %d\n"
           "- Medium Best Score: %d\n"
           "- Hard Best Score: %d\n"
           "Press any key to continue game...", easy, medium, hard);

    getchar();
    getchar();
    return 0;
}


int readInt(int min, int max, const char* messange)
{
    int x;

    while (scanf("%d", &x) != 1 || x < min || x > max)
    {
        printf("%s", messange);

        while (getchar() != '\n');
    }

    return x;
}


int doYouPlayAgain()
{
    char answer;

    while (getchar() != '\n');

    printf("Do you wanna play again? (Y/n): ");
    answer = getchar();

    if (answer == 'n' || answer == 'N')
        return EXIT_SUCCESS;

    return 1;
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
    while (1)
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

    return doYouPlayAgain();
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
    
    while (1)
    {
        printf("\033[2J"); 
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
