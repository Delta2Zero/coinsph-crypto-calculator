#include <iostream>
#include <limits>
#include <string>
#include <iomanip>  // For controlling output precision

int main()
{
    long double MarketP, AmountP, CoinA;
    int choice;
    std::string userInput;

    while (true) {
        // Step 1: Input Market Price
        std::cout << "*******************************************\n";
        std::cout << "Enter the current market price of the coin: ";
        std::getline(std::cin, userInput);
        
        // Check if user wants to exit
        if (userInput == "exit" || userInput == "Exit") {
            break;  // Exit the loop if user types "exit"
        }
        
        // Convert the input string to a long double (market price)
        try {
            MarketP = std::stold(userInput);  // Use stold for long double
        } catch (...) {
        	std::cout << "******************************************************************\n";
            std::cout << "\nInvalid input. Please enter a valid number for the market price.\n";
        	std::cout << "\n****************************************************************\n";
            continue;  // Restart the loop for correct input
        }

        // Step 2: Ask user for capital or coin choice
        std::cout << "***********************************************************************************\n";
        std::cout << "Do you want to use amount in capital PHP or amount of coin? (1 = Capital, 2 = Coin): ";
        std::getline(std::cin, userInput);
        
        // Check if user wants to exit
        if (userInput == "exit" || userInput == "Exit") {
            break;  // Exit the loop if user types "exit"
        }

        // Convert to choice
        try {
            choice = std::stoi(userInput);
        } catch (...) {
        	std::cout << "**********************************************************************\n";
            std::cout << "\nInvalid input. Please choose either 1 (for Capital) or 2 (for Coin).\n";
        	std::cout << "\n********************************************************************\n";
            continue;  // Restart the loop for correct input
        }

        // Output precision formatting
        std::cout << std::fixed << std::setprecision(10); // Set precision to 10 decimals

        if (choice == 1) {
            // If the user wants to use Capital
        	std::cout << "***********************\n";
            std::cout << "Enter the amount in PHP: ";
            std::getline(std::cin, userInput);

            // Check if user wants to exit
            if (userInput == "exit" || userInput == "Exit") {
                break;  // Exit the loop if user types "exit"
            }

            // Convert the input string to a long double (capital amount)
            try {
                AmountP = std::stold(userInput);  // Use stold for long double
            } catch (...) {
        		std::cout << "***********************************************************************\n";
                std::cout << "\nInvalid input. Please enter a valid number for the amount of capital.\n";
        		std::cout << "\n*********************************************************************\n";
                continue;  // Restart the loop for correct input
            }

            // Calculate amount of coins
            CoinA = AmountP / MarketP;

            // Output
       		 std::cout << "******************************************\n";
            std::cout << "\nMarket price Entry: " << MarketP << "\n";
            std::cout << "Amount of coin bought: " << CoinA << "\n";
            std::cout << "Amount of capital used: " << AmountP << "\n";
       	    std::cout << "\n*****************************************\n";
        } 
        else if (choice == 2) {
            // If the user wants to use Coin amount
       		std::cout << "************************\n";
            std::cout << "Enter the amount of coin: ";
            std::getline(std::cin, userInput);

            // Check if user wants to exit
            if (userInput == "exit" || userInput == "Exit") {
                break;  // Exit the loop if user types "exit"
            }

            // Convert the input string to a long double (coin amount)
            try {
                CoinA = std::stold(userInput);  // Use stold for long double
            } catch (...) {
        		std::cout << "********************************************************************\n";
                std::cout << "\nInvalid input. Please enter a valid number for the amount of coin.\n";
        		std::cout << "\n******************************************************************\n";
                continue;  // Restart the loop for correct input
            }

            // Calculate the amount of capital
            AmountP = CoinA * MarketP;

            // Output
        	std::cout << "*******************************************\n";
            std::cout << "\nMarket price Entry: " << MarketP << "\n";
            std::cout << "Amount of coin bought: " << CoinA << "\n";
            std::cout << "Amount of capital used: " << AmountP << "\n";
        	std::cout << "\n*****************************************\n";
        } else {
        	std::cout << "***********************************************************************\n";
            std::cout << "\nInvalid choice. Please choose either 1 (for Capital) or 2 (for Coin).\n";
        	std::cout << "\n*********************************************************************\n";
        }
    }

    std::cout << "Exiting the program. Goodbye!\n";
    return 0;
}

