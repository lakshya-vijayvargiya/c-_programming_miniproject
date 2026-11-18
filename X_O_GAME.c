
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define LEADERBOARD_FILE "leaderboard.txt"
#define MAX_PLAYERS 100

// Struct for Leaderboard
typedef struct {
    char name[50];
    int score;
} PlayerScore;

// Function Declarations
int playCoinToss();
int playRockPaperScissors();
int playNumberGuessing();
int playMathQuiz();
void clearScreen();
void displayLeaderboard();
void saveScore(const char *name, int score);

int main() {
    int choice;
    char playerName[50];
    int currentScore = 0;

    // Seed the random number generator
    srand(time(NULL));

    clearScreen();

    printf("=========================================\n");
    printf("        WELCOME TO THE ARCADE!           \n");
    printf("=========================================\n");

    printf("Enter your player name: ");
    scanf("%49s", playerName);

    // Clear input buffer
    while(getchar() != '\n');

    while (1) {
        clearScreen();

        printf("=========================================\n");
        printf("          ULTIMATE CONSOLE ARCADE        \n");
        printf("=========================================\n");

        printf(" Player: %s | Current Score: %d\n",
               playerName, currentScore);

        printf("-----------------------------------------\n");
        printf("  Select a game to play:\n\n");

        printf("  1. Coin Toss Challenge (3 Rounds)\n");
        printf("  2. Rock, Paper, Scissors\n");
        printf("  3. Number Guessing Game\n");
        printf("  4. Math Quiz Challenge\n");
        printf("  5. View Leaderboard\n");
        printf("  6. Exit Arcade\n");

        printf("=========================================\n");
        printf("Enter your choice (1-6): ");

        if (scanf("%d", &choice) != 1) {
            while(getchar() != '\n');
            continue;
        }

        switch (choice) {

            case 1:
                currentScore += playCoinToss();
                break;

            case 2:
                currentScore += playRockPaperScissors();
                break;

            case 3:
                currentScore += playNumberGuessing();
                break;

            case 4:
                currentScore += playMathQuiz();
                break;

            case 5:
                displayLeaderboard();
                break;

            case 6:
                printf("\nSaving your score of %d...\n", currentScore);

                if (currentScore > 0) {
                    saveScore(playerName, currentScore);
                }

                printf("Thanks for playing, %s! Goodbye.\n",
                       playerName);

                return 0;

            default:
                printf("\nInvalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}


// Helper function to clear the screen
void clearScreen() {

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


// LEADERBOARD FUNCTIONS

void saveScore(const char *name, int score) {

    FILE *file = fopen(LEADERBOARD_FILE, "a");

    if (file == NULL) {
        printf("Error: Could not save score.\n");
        return;
    }

    fprintf(file, "%s %d\n", name, score);

    fclose(file);
}


void displayLeaderboard() {

    FILE *file = fopen(LEADERBOARD_FILE, "r");

    PlayerScore players[MAX_PLAYERS];

    int count = 0;

    clearScreen();

    printf("\n=========================================\n");
    printf("             ARCADE LEADERBOARD          \n");
    printf("=========================================\n");

    if (file == NULL) {

        printf(" No scores recorded yet. Be the first!\n");

    } else {

        // Read scores from file
        while (fscanf(file, "%49s %d",
                      players[count].name,
                      &players[count].score) == 2) {

            count++;

            if (count >= MAX_PLAYERS)
                break;
        }

        fclose(file);

        // Sort scores in descending order (Bubble Sort)
        for (int i = 0; i < count - 1; i++) {

            for (int j = 0; j < count - i - 1; j++) {

                if (players[j].score < players[j + 1].score) {

                    PlayerScore temp = players[j];

                    players[j] = players[j + 1];

                    players[j + 1] = temp;
                }
            }
        }

        // Display Top 10
        printf(" RANK  | PLAYER NAME          | SCORE\n");
        printf("-------|----------------------|------\n");

        int displayCount = (count < 10) ? count : 10;

        for (int i = 0; i < displayCount; i++) {

            printf("  #%02d  | %-20s | %d\n",
                   i + 1,
                   players[i].name,
                   players[i].score);
        }
    }

    printf("\nPress Enter to return to menu...");

    while(getchar() != '\n');

    getchar();
}


// GAME 1: COIN TOSS CHALLENGE

int playCoinToss() {

    int userChoice;
    int computerToss;
    int pointsEarned = 0;

    clearScreen();

    printf("\n=========================================\n");
    printf("          COIN TOSS CHALLENGE            \n");
    printf("=========================================\n");

    printf("You have 3 rounds to play!\n");
    printf("Correct prediction = 10 points\n\n");

    // Repeat the game for 3 rounds
    for (int i = 1; i <= 3; i++) {

        printf("\n---------- ROUND %d ----------\n", i);

        printf("Choose your prediction:\n");
        printf("1. Heads\n");
        printf("2. Tails\n");

        printf("Enter your choice: ");
        scanf("%d", &userChoice);

        // Check whether the choice is valid
        if (userChoice != 1 && userChoice != 2) {

            printf("Invalid choice! No points awarded.\n");

        } else {

            // Generate random number: 1 or 2
            computerToss = (rand() % 2) + 1;

            printf("\nThe coin is tossed...\n");

            // Display computer's result
            if (computerToss == 1) {
                printf("Result: HEADS\n");
            } else {
                printf("Result: TAILS\n");
            }

            // Compare player's choice with coin result
            if (userChoice == computerToss) {

                printf("Congratulations! Correct prediction!\n");

                pointsEarned = pointsEarned + 10;

                printf("+10 Points!\n");

            } else {

                printf("Wrong prediction! Better luck next time.\n");

                printf("+0 Points!\n");
            }
        }
    }

    // Display final result
    printf("\n=========================================\n");
    printf("             GAME OVER                   \n");
    printf("=========================================\n");

    printf("Your total score: %d out of 30\n", pointsEarned);

    printf("\nPress Enter to return to menu...");

    while(getchar() != '\n');

    getchar();

    return pointsEarned;
}


// GAME 2: ROCK, PAPER, SCISSORS

int playRockPaperScissors() {

    int userChoice, computerChoice;
    int pointsEarned = 0;

    const char *choices[] = {
        "Rock", "Paper", "Scissors"
    };

    clearScreen();

    printf("\n--- ROCK, PAPER, SCISSORS ---\n");

    printf("1. Rock\n2. Paper\n3. Scissors\n");

    printf("Enter your choice (1-3): ");
    scanf("%d", &userChoice);

    if(userChoice < 1 || userChoice > 3) {

        printf("Invalid choice!\n");

    } else {

        computerChoice = (rand() % 3) + 1;

        printf("\nYou chose: %s\n", choices[userChoice - 1]);

        printf("Computer chose: %s\n",
               choices[computerChoice - 1]);

        if (userChoice == computerChoice) {

            printf("It's a Tie! +2 Points.\n");

            pointsEarned = 2;

        } else if ((userChoice == 1 && computerChoice == 3) ||
                   (userChoice == 2 && computerChoice == 1) ||
                   (userChoice == 3 && computerChoice == 2)) {

            printf("You Win! +10 Points.\n");

            pointsEarned = 10;

        } else {

            printf("Computer Wins! +0 Points.\n");
        }
    }

    printf("\nPress Enter to return to menu...");

    while(getchar() != '\n');

    getchar();

    return pointsEarned;
}


// GAME 3: NUMBER GUESSING

int playNumberGuessing() {

    int target = (rand() % 100) + 1;

    int guess = 0;
    int attempts = 0;
    int pointsEarned = 0;

    clearScreen();

    printf("\n--- NUMBER GUESSING GAME ---\n");

    printf("I have picked a number between 1 and 100.\n");

    while (guess != target) {

        printf("Enter your guess: ");

        scanf("%d", &guess);

        attempts++;

        if (guess > target) {

            printf("Too high! Try again.\n");

        } else if (guess < target) {

            printf("Too low! Try again.\n");

        } else {

            printf("\nCorrect! You found the number %d in %d attempts.\n",
                   target, attempts);

            // Calculate points
            pointsEarned = 25 - attempts;

            if (pointsEarned < 5)
                pointsEarned = 5;

            printf("You earned +%d Points!\n", pointsEarned);
        }
    }

    printf("\nPress Enter to return to menu...");

    while(getchar() != '\n');

    getchar();

    return pointsEarned;
}


// GAME 4: MATH QUIZ

int playMathQuiz() {

    int num1, num2, answer, userAnswer, score = 0;

    clearScreen();

    printf("\n--- MATH QUIZ CHALLENGE ---\n");

    printf("Answer 3 quick math questions!\n\n");

    for (int i = 1; i <= 3; i++) {

        num1 = (rand() % 20) + 1;

        num2 = (rand() % 20) + 1;

        answer = num1 + num2;

        printf("Question %d: What is %d + %d?\n",
               i, num1, num2);

        printf("Your answer: ");

        scanf("%d", &userAnswer);

        if (userAnswer == answer) {

            printf("Correct!\n\n");

            score++;

        } else {

            printf("Wrong! The correct answer was %d.\n\n",
                   answer);
        }
    }

    int pointsEarned = score * 5;

    printf("Quiz Over! You scored %d out of 3.\n", score);

    printf("You earned +%d Points!\n", pointsEarned);

    printf("\nPress Enter to return to menu...");

    while(getchar() != '\n');

    getchar();

    return pointsEarned;
}
