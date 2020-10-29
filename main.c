#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <ctype.h>

void welcome();
int get_word(char *, int);
int run_game(char *, int);
void put_into_string(char, char *);
int is_blank_available(char *);

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

    // Run the game and Get if the user got the word
    check_ok = run_game(game_word, word_len);
    if (check_ok)
    {
        printf("WORD: %s\n", game_word);
        puts("You've won the game. Run it to play again.");
    }
    else
    {
        puts("You've lost the game. Try again.");
        printf("Correct WORD: %s\n", game_word);
    }

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

int run_game(char game_word[], int l)
{
    char word_guessed[60];
    int life_left = 6;
    int correct_guess;
    char input_c, char_flush;
    char blanks[l];

    for (int i = 0; i < l; i++)
    {
        blanks[i] = '_';
    }
    blanks[l] = '\0';
    word_guessed[0] = '\0';

    while (life_left != 0 && is_blank_available(blanks))
    {
        correct_guess = 0;
        puts("Enter a character, Try to guess the word.");
        printf("So far you've guessed: %s\n", word_guessed);
        printf("WORD: %s\n", blanks);
        printf("INPUT: ");
        scanf("%c", &input_c);
        scanf("%c", &char_flush);
        put_into_string(input_c, word_guessed);
        for (int i = 0; i < l; i++)
        {
            if (game_word[i] == input_c && blanks[i] == '_')
            {
                blanks[i] = input_c;
                correct_guess = 1;
                printf("\n\n");
            }
        }
        if (!correct_guess)
        {
            puts("You've guessed wrong.");
            life_left--;
            printf("LIFE LEFT: %d\n\n", life_left);
        }
    }
    if (life_left == 0)
    {
        return 0;
    }
    else
    {
        return 1;
    }
}

void put_into_string(char c, char word[])
{
    int i = strlen(word);
    word[i] = toupper(c);
    word[i + 1] = ',';
    word[i + 2] = '\0';
    return;
}

int is_blank_available(char word[])
{
    int a_blank_available = 0;
    int l = strlen(word);
    for (int i = 0; i < l; i++)
    {
        if (word[i] == '_')
        {
            a_blank_available = 1;
        }
    }
    return a_blank_available;
}
