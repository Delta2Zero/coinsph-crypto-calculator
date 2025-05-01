#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits>

int main() {
    std::string input;
    double marketPrice, coinAmount;

    const double feeRate = 0.0025;

    while (true) {
        std::cout << "Enter the market price or type 'exit': ";
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }

        std::stringstream priceStream(input);
        if (!(priceStream >> marketPrice)) {
            std::cout << "Invalid input. Please enter a valid number for market price.\n";
            continue;
        }

        std::cout << "Enter the amount of coin: ";
        std::getline(std::cin, input);
        std::stringstream coinStream(input);
        if (!(coinStream >> coinAmount)) {
            std::cout << "Invalid input. Please enter a valid number for amount of coin.\n";
            continue;
        }

        // Calculate total buy-in
        double grossBuy = marketPrice * coinAmount;
        double buyFee = grossBuy * feeRate;
        double totalBuyCost = grossBuy + buyFee;

        double testSellGross = totalBuyCost;
        double sellFee, netAfterSell;
        double step = 0.01;
        int loops = 0;

        while (true) {
            sellFee = testSellGross * feeRate;
            netAfterSell = testSellGross - sellFee;

            if (netAfterSell >= totalBuyCost) {
                break;
            }

            testSellGross += step;
            loops++;

            // To prevent infinite loops on extremely small coin amounts
            if (loops > 1000000) {
                std::cout << "Calculation took too long, likely due to very small coin amount.\n";
                break;
            }
        }

        double breakEvenPrice = testSellGross / coinAmount;
        double netprofitoverall = testSellGross - buyFee - sellFee - grossBuy;
        double totalcostoverall = grossBuy + buyFee + sellFee;

        std::cout << std::fixed << std::setprecision(6);
        std::cout << "\n--- Break Even Calculation ---\n";
        std::cout << "Market Price: PHP " << marketPrice << "\n";
        std::cout << "Coin Amount: " << coinAmount << "\n";
        std::cout << "Buy Amount: " << grossBuy << "\n";
        std::cout << "Buy Fee: PHP " << buyFee << "\n";
        std::cout << "Total Buy-in Cost: PHP " << totalBuyCost << "\n";
        std::cout << "Calculated Break Even Exit Price: PHP " << breakEvenPrice << "\n";

        std::cout << "\nCounter-check:\n";
        std::cout << "Gross Sell: PHP " << testSellGross << "\n";
        std::cout << "Total Cost: PHP " << totalcostoverall << "\n";
        std::cout << "Sell Fee: PHP " << sellFee << "\n";
        std::cout << "Net After Sell: PHP " << netprofitoverall << "\n";
        std::cout << "Total Loop Steps Taken: " << loops << "\n\n";
    }

    return 0;
}

