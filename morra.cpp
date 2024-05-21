#include <iostream>
#include <cstdio>

// Funzione per ottenere l'input di un giocatore senza visualizzare l'input
int getPlayerSecretInput(int playerNumber) {
    int num;
    std::cout << "Player " << playerNumber << ", enter a number between 1 and 5 (keep it secret): ";

    char c;
    int count = 0;
    do {
        c = std::getchar();
        if (c >= '1' && c <= '5') {
            std::cout << '*'; // Visualizza un asterisco al posto del numero inserito
            num = c - '0'; // Converte il carattere ASCII in intero
            count++;
        }
    } while (count == 0); // Continua fino a quando non viene inserito un numero valido

    std::cout << std::endl; // Vai a capo dopo aver terminato l'input
    return num;
}

// Funzione per ottenere l'input di un giocatore
int getPlayerInput(int playerNumber) {
    int num;
    std::cout << "Player " << playerNumber << ", guess the sum of both numbers: ";
    std::cin >> num;
    return num;
}

int main() {
    int player1Score = 0, player2Score = 0;
    const int winningScore = 3;

    // Inizio del gioco
    while (player1Score < winningScore && player2Score < winningScore) {
        int secretNumber1, secretNumber2, guess1, guess2;

        // Input dei numeri segreti dei giocatori
        secretNumber1 = getPlayerSecretInput(1);
        secretNumber2 = getPlayerSecretInput(2);

        // Input dei numeri dei giocatori per indovinare la somma
        guess1 = getPlayerInput(1);
        guess2 = getPlayerInput(2);

        // Verifica dei numeri indovinati
        int actualSum = secretNumber1 + secretNumber2;
        if (guess1 == actualSum && guess2 == actualSum) {
            std::cout << "Both players guessed correctly. Continuing the game.\n";
        } else if (guess1 != actualSum && guess2 != actualSum) {
            std::cout << "Neither player guessed the sum correctly. Continuing the game.\n";
        } else if (guess1 == actualSum && guess2 != actualSum) {
            std::cout << "Player 1 wins this round!\n";
            player1Score++;
        } else {
            std::cout << "Player 2 wins this round!\n";
            player2Score++;
        }

        // Stampa dei punteggi
        std::cout << "Player 1 Score: " << player1Score << "\n";
        std::cout << "Player 2 Score: " << player2Score << "\n";
    }

    // Dichiarazione del vincitore
    if (player1Score == winningScore) {
        std::cout << "Player 1 is the overall winner!\n";
    } else {
        std::cout << "Player 2 is the overall winner!\n";
    }

    return 0;
}

