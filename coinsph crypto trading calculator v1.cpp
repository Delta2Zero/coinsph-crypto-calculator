#include <iostream>
#include <iomanip>
#include <cstdlib>   // for atof
#include <cstring>   // for strcmp
#include <cmath>     // for floating point rounding

int main() {
    const double buyFeeRate = 0.0025;
    const double sellFeeRate = 0.0025;
    char input[100];

    while (true) {
        std::cout << "\nEnter market price (or 'exit' to quit): ";
        std::cin >> input;

        if (std::strcmp(input, "exit") == 0) {
            break;
        }

        // Validate numeric input
        bool isNumeric = true;
        for (int i = 0; input[i] != '\0'; ++i) {
            if (!std::isdigit(input[i]) && input[i] != '.' && input[i] != '-') {
                isNumeric = false;
                break;
            }
        }
        if (!isNumeric) {
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        double marketPrice = std::atof(input);

        std::cout << "Enter coin amount: ";
        std::cin >> input;

        if (std::strcmp(input, "exit") == 0) {
            break;
        }

        isNumeric = true;
        for (int i = 0; input[i] != '\0'; ++i) {
            if (!std::isdigit(input[i]) && input[i] != '.' && input[i] != '-') {
                isNumeric = false;
                break;
            }
        }
        if (!isNumeric) {
            std::cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        double coinAmount = std::atof(input);
        double rawBuyAmount = marketPrice * coinAmount;
        double buyFee = rawBuyAmount * buyFeeRate;
		//this is a wrong formula as this pegs the fees on the buy in price which is wrong
		//it should be pegged at the market price exit instead
        double breakEven = marketPrice + (marketPrice * (buyFeeRate + sellFeeRate));
		
		//this is wrong because of the breakEven formula
        // Exit price levels
        double price_0_5 = breakEven * 1.005; // this should be just 
        double price_1_0 = breakEven * 1.01;
        double price_3_0 = breakEven * 1.03;

        // Gross profit (sell value)
        double gross_0_5 = price_0_5 * coinAmount;
        double gross_1_0 = price_1_0 * coinAmount;
        double gross_3_0 = price_3_0 * coinAmount;

        // Sell fees
        double sellFee_0_5 = gross_0_5 * sellFeeRate;
        double sellFee_1_0 = gross_1_0 * sellFeeRate;
        double sellFee_3_0 = gross_3_0 * sellFeeRate;

        // Total amount involved
        double total_0_5 = rawBuyAmount + sellFee_0_5 + buyFee;
        double total_1_0 = rawBuyAmount + sellFee_1_0 + buyFee;
        double total_3_0 = rawBuyAmount + sellFee_3_0 + buyFee;

        // Net profit (gross + fees - raw capital)
        double net_0_5 = gross_0_5 - total_0_5;
        double net_1_0 = gross_1_0 - total_1_0;
        double net_3_0 = gross_3_0 - total_3_0;

        // Output
        std::cout << std::fixed << std::setprecision(6);
        std::cout << "\nBuy Price: PHP" << marketPrice << std::endl;
        std::cout << "Buy Amount: " << coinAmount << " coins\n";
        std::cout << "Buy-in Fee: PHP" << buyFee << std::endl;
        std::cout << "Total Buy-in Cost: PHP" << rawBuyAmount + buyFee << std::endl;
        std::cout << "Break-even Price per Coin: PHP" << breakEven << std::endl;

        std::cout << "\n--- Profit Exit Points ---\n";
        std::cout << "Price +0.5%: PHP" << price_0_5 << std::endl;
        std::cout << "Price +1.0%: PHP" << price_1_0 << std::endl;
        std::cout << "Price +3.0%: PHP" << price_3_0 << std::endl;

        std::cout << "\n--- Sell Fees ---\n";
        std::cout << "0.5% Exit Fee: PHP" << sellFee_0_5 << std::endl;
        std::cout << "1.0% Exit Fee: PHP" << sellFee_1_0 << std::endl;
        std::cout << "3.0% Exit Fee: PHP" << sellFee_3_0 << std::endl;

        std::cout << "\n--- Net Profits ---\n";
        std::cout << "Gross at 0.5%: PHP" << gross_0_5 << std::endl;
        std::cout << "Gross at 1.0%: PHP" << gross_1_0 << std::endl;
        std::cout << "Gross at 3.0%: PHP" << gross_3_0 << std::endl;
        
        std::cout << "\n--- Net Profits ---\n";
        std::cout << "Net at 0.5%: PHP" << net_0_5 << std::endl;
        std::cout << "Net at 1.0%: PHP" << net_1_0 << std::endl;
        std::cout << "Net at 3.0%: PHP" << net_3_0 << std::endl;
    
        std::cout << "\n*********************************************************************\n" << std::endl;
        std::cout << "OUTDATED ONLY KEPT FOR SOURCE CODE TRACKING PLEASE USE LATEST VERSION" << std::endl;
        std::cout << "\n*********************************************************************\n" << std::endl;
    }

    std::cout << "Exited calculator.\n";
    return 0;
}

