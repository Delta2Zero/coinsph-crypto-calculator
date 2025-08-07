#include <iostream>
#include <string>
#include <limits>
#include <cmath>

#ifdef _WIN32
#include <windows.h>
#endif

void resizeConsoleWindow() {
#ifdef _WIN32
    HWND console = GetConsoleWindow();
    if (console != NULL) {
        // MoveWindow(hwnd, x, y, width_px, height_px, repaint)
        MoveWindow(console, 100, 100, 725, 500, TRUE); // Width and height in pixels
    }

    // Set the screen buffer size so lines don't wrap or scroll unnecessarily
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    if (hOut != INVALID_HANDLE_VALUE) {
        CONSOLE_SCREEN_BUFFER_INFO csbi;
        GetConsoleScreenBufferInfo(hOut, &csbi);
        COORD newSize = {120, 500}; // Width in characters, height in lines
        SetConsoleScreenBufferSize(hOut, newSize);
    }
#endif
}

bool getInput(const std::string& prompt, double& value) {
    std::string input;
    std::cout << prompt;
    std::getline(std::cin, input);
    if (input == "exit") return false;

    try {
        value = std::stod(input);
    } catch (...) {
        std::cerr << "[!] Invalid input. Restarting...\n\n";
        return getInput(prompt, value); // Retry
    }
    return true;
}

int main() {
    resizeConsoleWindow(); // set up console size
    
    while (true) {
        std::cout << "\n********************************************************************************\n";
        std::cout << "Type 'exit' at any input field to exit the program\n";
        std::cout << "Note: Please do not use big gaps between the Market start and end to avoid crashes\n";
        std::cout << "**********************************************************************************\n";

        double totalCapital, capitalUsed, coinAmount, totalFeesSoFar, targetNetProfit, sellFeeRate;

        if (!getInput("Total Wallet Capital (PHP): ", totalCapital)) break;
        if (!getInput("Capital Used (PHP): ", capitalUsed)) break;
        if (!getInput("Coin Amount to be Sold: ", coinAmount)) break;
        if (!getInput("Total Fees So Far (PHP): ", totalFeesSoFar)) break;
        if (!getInput("Target Net Profit (PHP): ", targetNetProfit)) break;
        if (!getInput("Sell Fee Rate (e.g., 0.25 for 0.25%): ", sellFeeRate)) break;

        sellFeeRate /= 100.0;  // convert to decimal

        double netTargetCalc = targetNetProfit;
        double estimatedPrice = 0.0;
        const double maxIterations = 1000000;
        const double priceIncrement = 0.01;
        int counter = 0;
        bool found = false;

        while (counter < maxIterations) {
            estimatedPrice = (netTargetCalc + capitalUsed + totalFeesSoFar) / (coinAmount * (1 - sellFeeRate));
            double grossSale = estimatedPrice * coinAmount;
            double sellFee = grossSale * sellFeeRate;
            double totalOverallFees = sellFee + totalFeesSoFar;
            double netSale = grossSale - totalOverallFees;
            double netProfit = netSale - capitalUsed;

            if (netProfit >= targetNetProfit) {
                found = true;
                std::cout << "\n==== Target Exit Found ====\n";
                std::cout << "Market Price Target:     " << estimatedPrice << "\n";
                std::cout << "Coin Amount to be Sold:  " << coinAmount << std::endl;
                std::cout << "Total Fees So Far:       " << totalFeesSoFar << std::endl;
                std::cout << "Sell Fee (" << (sellFeeRate * 100) << "%):        " << sellFee << "\n";
                std::cout << "Total Overall Fees:      " << totalOverallFees << std::endl;
                std::cout << "Gross Sale:               " << grossSale << "\n";
                std::cout << "Net Sale:                " << netSale << std::endl;
                std::cout << "Net Profit:               " << netProfit << "\n";
                std::cout << "Total Capital Original:  " << totalCapital << std::endl;
                std::cout << "Total Capital After:     " << totalCapital + netProfit << std::endl;
                std::cout << "===========================\n\n";
                break;
            }

            netTargetCalc += priceIncrement;
            counter++;
        }

        if (!found) {
            std::cout << "[!] No matching price found to meet or exceed the target net profit within iteration limit.\n\n";
        }
    }

    std::cout << "Program exited.\n";
    return 0;
}

