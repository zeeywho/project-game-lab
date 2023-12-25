#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define MAX_TRIES 10          // Maximal percobaan
#define BASE_SCORE 0          // score 
#define MAX_STRING_LENGTH 50  // panjang string maksimal


int generateRandomNumber() {
    srand(time(NULL));
    return (rand() % 100) + 1;
}

//function untuk menentukan tebakan pengguna
int getUserGuess(int random_number, int *guesses_history, int tries, int isFirstGuess) {
    int user_guess;

    if (isFirstGuess) {
        printf("Enter a guess for the number between 1 and 100\n");
    }

    scanf("%d", &user_guess);
    guesses_history[tries] = user_guess;

    if (user_guess > random_number) {
        printf("The number you entered is greater\n");
    } else if (user_guess < random_number) {
        printf("The number you entered is smaller\n");
    } else {
        printf("Yay! Correct Guess, You Won in %d tries!\n", tries + 1);
        return 1; 
    }

    return 0;  
}

//array untuk menampilkan history tebakan
void displayGuessesHistory(int *guesses_history, int tries) {
    int i;
    printf("Guesses History: ");
    for (i = 0; i < tries; i++) {
        printf("%d ", guesses_history[i]);
    }
    printf("\n");
}

//alur game
void playGame() {
    char keepPlaying = 'Y';

    while (keepPlaying == 'Y' || keepPlaying == 'y') {
        int random_number = generateRandomNumber();
        int user_guess, tries = 0;
        int guesses_history[MAX_TRIES];
        int score = BASE_SCORE;

        // Get player name only once at the beginning
        char playerName[MAX_STRING_LENGTH];
        if (keepPlaying == 'Y' || keepPlaying == 'y') {  // Check if it's the first round
            printf("Enter your name: ");
            fgets(playerName, sizeof(playerName), stdin);
            playerName[strcspn(playerName, "\n")] = '\0';
        }

        do {
            int isFirstGuess = (tries == 0);
            int correct_guess = getUserGuess(random_number, guesses_history, tries, isFirstGuess);

            if (correct_guess) {
                score += (MAX_TRIES - tries) * 10;
                break;  // Exit the loop if correct guess is made
            } else {
                tries++;
            }

        } while (tries < MAX_TRIES);  // Removed extra getUserGuess call

        if (tries == MAX_TRIES) {
            printf("Sorry, you've reached the maximum number of tries. The correct number was %d\n", random_number);
        }

        displayGuessesHistory(guesses_history, tries);

        printf("\nYour Score: %d\n", score);

        printf("Do you want to keep playing? [Y/N]: "); //pertanyaan agar dapat me re-play game
        scanf(" %c", &keepPlaying);

        system("@cls||clear");
    }
}

int main(void) {
    playGame();
    printf("Thankyou for playing ^_^ Goodbye!\n");

    return 0;
}

