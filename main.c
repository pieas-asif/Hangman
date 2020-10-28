#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>

void welcome();
int get_word(char *, int);

int main(int argc, char const *argv[])
{
    welcome();

    // Setting up variables
    char game_word[256];
    int difficulity = 1;
    int check_ok;
    int word_len;

    // Choosing difficulity in Game
    if (argc != 1)
    {
        switch (argv[1][1])
        {
        case 'e':
            difficulity = 1;
            break;
        case 'm':
            difficulity = 2;
            break;
        case 'h':
            difficulity = 3;
            break;
        default:
            puts("Wrong argument(s) were passed.");
            puts("  run \"./hangman -e\" for easy difficulity");
            puts("  run \"./hangman -m\" for medium difficulity");
            puts("  run \"./hangman -h\" for hard difficulity");
            break;
        }
    }
    else
    {
        puts("No argument(s) were passed.");
        puts("  run \"./hangman -e\" for easy difficulity");
        puts("  run \"./hangman -m\" for medium difficulity");
        puts("  run \"./hangman -h\" for hard difficulity");
    }

    // Getting a Random Word For Hangman
    check_ok = get_word(game_word, difficulity);
    if (!check_ok)
    {
        puts("ERROR: Unable to get word. Exiting...");
        sleep(1);
    }
    word_len = (int)strlen(game_word);
    printf("WORD: %s\n", game_word);
    printf("WORD_LEN: %d\n", word_len);
    return 0;
}

void welcome()
{
    puts("Welcome to the game of Hangman");
    sleep(1);
}

int get_word(char game_word[], int d)
{
    FILE *file;
    int n_words, i = 0, random_n;
    char line[256];
    switch (d)
    {
    case 1:
        file = fopen("easy.txt", "r");
        break;
    case 2:
        file = fopen("medium.txt", "r");
        break;
    case 3:
        file = fopen("hard.txt", "r");
        break;
    default:
        file = fopen("easy.txt", "r");
        break;
    }
    if (file == NULL)
    {
        return 0;
    }
    while (fgets(line, 255, file))
    {
        if (i == 0)
        {
            sscanf(line, "%d", &n_words);
            srand((unsigned)time(NULL));
            random_n = (rand() % n_words) + 1;
            i++;
        }
        else
        {
            if (i == random_n)
            {
                sscanf(line, "%s", game_word);
                break;
            }
            i++;
        }
    }
    fclose(file);
    return 1;
}