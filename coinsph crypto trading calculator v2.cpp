#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits>

int main() {
    std::string input;
    double marketPrice, coinAmount, customExitPrice, sellCoinAmount;

    const double feeRate = 0.0025; // 0.25% buy and sell fee

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

        std::cout << "Enter the amount of coin you bought: ";
        std::getline(std::cin, input);
        std::stringstream coinStream(input);
        if (!(coinStream >> coinAmount)) {
            std::cout << "Invalid input. Please enter a valid number for coin amount.\n";
            continue;
        }

        std::cout << "Enter your planned custom exit price: ";
        std::getline(std::cin, input);
        std::stringstream customExitStream(input);
        if (!(customExitStream >> customExitPrice)) {
            std::cout << "Invalid input. Please enter a valid number for custom exit price.\n";
            continue;
        }

        std::cout << "Enter how many coins you plan to sell (can be less than bought): ";
        std::getline(std::cin, input);
        std::stringstream sellAmountStream(input);
        if (!(sellAmountStream >> sellCoinAmount)) {
            std::cout << "Invalid input. Please enter a valid number for selling coin amount.\n";
            continue;
        }

        // --- Buy Calculations ---
        double rawBuyCost = marketPrice * coinAmount;
        double buyFee = rawBuyCost * feeRate;
        double totalBuyCost = rawBuyCost + buyFee;

        std::cout << std::fixed << std::setprecision(6);
        std::cout << "\n--- Buy Information ---\n";
        std::cout << "Market Price: PHP " << marketPrice << "\n";
        std::cout << "Coin Amount Bought: " << coinAmount << "\n";
        std::cout << "Raw Buy Cost (Capital): PHP " << rawBuyCost << "\n";
        std::cout << "Buy Fee (0.25%): PHP " << buyFee << "\n";
        std::cout << "Total Buy Cost (Including Fee): PHP " << totalBuyCost << "\n";

        // --- Break Even Calculation ---
        double breakEvenGrossSale = totalBuyCost / (1.0 - feeRate);
        double breakEvenPrice = breakEvenGrossSale / coinAmount;
        double bEvenFeeA = breakEvenGrossSale * feeRate;
        double bEvenTC = totalBuyCost + bEvenFeeA;
        double bEvenNetPL = breakEvenGrossSale - bEvenTC;

        std::cout << "\n--- Break Even ---\n";
        std::cout << "Break Even Sell Price: PHP " << breakEvenPrice << "\n";
        std::cout << "Break Even Gross Sale: PHP " << breakEvenGrossSale << "\n";
        std::cout << "Break Even Sell Fee: PHP " << bEvenFeeA << "\n";
        std::cout << rawBuyCost << " + " << buyFee << " + " << bEvenFeeA << " = " << bEvenTC << "\n";
        std::cout << breakEvenGrossSale << " - " << bEvenTC << " = " << bEvenNetPL << "\n";

        // --- Target Exit Calculations (1.6% and 2.6%) ---
		// target price is based on market movement, not profit padding
		std::cout << "\n--- Target Exit Prices ---\n";

		double targetRates[2];
		targetRates[0] = 0.016;  // 1.6%
		targetRates[1] = 0.026;  // 2.6%

		const char* targetLabels[2];
		targetLabels[0] = "1.6%";
		targetLabels[1] = "2.6%";

		for (int i = 0; i < 2; ++i) {
    	// target market price movement applied to the entry unit price (totalBuyCost / coinAmount)
    	double marketExitPrice = marketPrice * (1.0 + targetRates[i]);
	
    	double grossProfit = marketExitPrice * coinAmount;
    	double sellFee = grossProfit * feeRate;
    	double netProfit = grossProfit - totalBuyCost - sellFee;

	    std::cout << "(" << targetLabels[i] << ") Target Market Exit Price: PHP " << marketExitPrice << "\n";
    	std::cout << "Gross Profit: PHP " << grossProfit << "\n";
    	std::cout << "Net Profit: PHP " << netProfit << "\n";
		}

        // --- Custom Exit Simulation ---
        std::cout << "\n--- Custom Exit Simulation ---\n";
        std::cout << "Custom Exit Price: PHP " << customExitPrice << "\n";
        std::cout << "Coin Amount to Sell: " << sellCoinAmount << "\n";

        double customGrossSale = customExitPrice * sellCoinAmount;
        double customSellFee = customGrossSale * feeRate;
        double proportionalBuyCost = (totalBuyCost / coinAmount) * sellCoinAmount;
        double customNetProfit = customGrossSale - proportionalBuyCost - customSellFee;

        std::cout << "Gross Sale: PHP " << customGrossSale << "\n";
        std::cout << "Sell Fee (0.25%): PHP " << customSellFee << "\n";
        std::cout << "Proportional Buy Cost: PHP " << proportionalBuyCost << "\n";
        std::cout << "Net Profit (After Buy + Sell Fees): PHP " << customNetProfit << "\n";

        // --- Custom Exit Percent Gain ---
        double percentGain = (customNetProfit / rawBuyCost) * 100.0;
        std::cout << "Custom Exit is a " << percentGain << "% gain from initial capital buy amount.\n";
        // (((custom exit price - market buy in price = market difference) / market buy in price) * 100)
        double percentGain2 = ((customExitPrice - marketPrice) / marketPrice) * 100;
        std::cout << "Custom Exit is a " << percentGain2 << "% Market movement\n";
        
        std::cout << "\n*********************************************************************\n" << std::endl;
        std::cout << "OUTDATED ONLY KEPT FOR SOURCE CODE TRACKING PLEASE USE LATEST VERSION" << std::endl;
        std::cout << "\n*********************************************************************\n" << std::endl;
        
        std::cout << "\n\n";
    }

    return 0;
}

