#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void welcome();

int main(int argc, char const *argv[])
{
    welcome();

    // Choosing difficulity in Game
    int difficulity = 1;
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
    return 0;
}

void welcome()
{
    puts("Welcome to the game of Hangman");
    sleep(1);
}