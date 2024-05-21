#include <iostream>
#include <string>

#ifdef _WIN32
#include <conio.h>
#else
#include <termios.h>
#include <unistd.h>
#endif

void ClearScreen() {
#ifdef _WIN32
    std::system("cls");
#else
    std::system("clear");
#endif
}

char GetHiddenInput() {
#ifdef _WIN32
    return _getch();
#else
    struct termios oldt, newt;
    char ch;
    tcgetattr(STDIN_FILENO, &oldt);
    newt = oldt;
    newt.c_lflag &= ~(ICANON | ECHO);
    tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    ch = getchar();
    tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
    return ch;
#endif
}

int GetPlayerInput(int playerNumber) {
    int num;
    std::string input;
    std::cout << "Player " << playerNumber << ", enter a number: ";
    
    // Get hidden input
    char ch;
    while (true) {
        ch = GetHiddenInput();
        if (ch == '\n' || ch == '\r') {
            break;
        }
        if (isdigit(ch)) {
            input += ch;
            std::cout << '*';  // Print asterisk instead of the actual character
        }
    }
    
    num = std::stoi(input);
    std::cout << std::endl;
    ClearScreen();
    return num;
}

int main() {
    int player1Number, player2Number, player1Guess, player2Guess;
    int player1Score = 0, player2Score = 0;

    // Get numbers from both players
    ClearScreen();
    player1Number = GetPlayerInput(1);

    ClearScreen();
    player2Number = GetPlayerInput(2);

    int sum = player1Number + player2Number;

    // Get guesses from both players
    std::cout << "Player 1, guess the sum of both numbers: ";
    std::cin >> player1Guess;
    ClearScreen();
    
    std::cout << "Player 2, guess the sum of both numbers: ";
    std::cin >> player2Guess;
    ClearScreen();

    // Check guesses
    bool player1Correct = (player1Guess == sum);
    bool player2Correct = (player2Guess == sum);

    if (player1Correct && !player2Correct) {
        std::cout << "Player 1 wins!\n";
        player1Score++;
    } else if (!player1Correct && player2Correct) {
        std::cout << "Player 2 wins!\n";
        player2Score++;
    } else if (player1Correct && player2Correct) {
        std::cout << "It's a tie! Both players guessed correctly.\n";
    } else {
        std::cout << "No one guessed the sum correctly.\n";
    }

    std::cout << "Player 1 Score: " << player1Score << "\n";
    std::cout << "Player 2 Score: " << player2Score << "\n";

    return 0;
}

