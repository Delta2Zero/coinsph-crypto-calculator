#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <limits>

int main() {
    std::string input;
    double marketPrice, coinAmount, customExitPrice, sellCoinAmount, totalCapital = 0.0;

    while (true) {
        // Step 1: Ask for total capital or exit
        std::cout << "***************************************************************************\n";
        std::cout << "***************************************************************************\n";
        std::cout << "\n Written by Chatgpt, Prompt and code checking and testing my DeltaTwoZero \n";
        std::cout << "\n Coinsph Crypto Trading Calculator Version 5 \n";
        std::cout << "\n Enter your total capital or type 'exit' to quit \n";
        std::cout << "\n***************************************************************************\n";
        std::cout << "***************************************************************************\n";
        std::cout << "Capital: ";
        
        std::getline(std::cin, input);

        if (input == "exit") {
            break;
        }
        
        std::stringstream capitalStream(input);
        if (!(capitalStream >> totalCapital) || totalCapital <= 0) {
            std::cout << "Invalid input. Please enter a valid number for total capital.\n";
            continue;
        }

        // Step 2: Ask for VIP tier level
        int vipLevel;
        std::cout << "\n***************************************************************************\n";
        std::cout << "***************************************************************************\n";
        std::cout << "\n--- Select Your Coins.ph VIP Tier Level (0-9) ---\n";
        std::cout << "VIP 0: Maker 0.25%\n";
        std::cout << "VIP 1: Maker 0.22%\n";
        std::cout << "VIP 2: Maker 0.18%\n";
        std::cout << "VIP 3: Maker 0.15%\n";
        std::cout << "VIP 4: Maker 0.12%\n";
        std::cout << "VIP 5: Maker 0.10%\n";
        std::cout << "VIP 6: Maker 0.08%\n";
        std::cout << "VIP 7: Maker 0.07%\n";
        std::cout << "VIP 8: Maker 0.06%\n";
        std::cout << "VIP 9: Maker 0.05%\n";
        std::cout << "Enter VIP Tier (0-9): ";
        
        std::getline(std::cin, input);
        std::stringstream vipStream(input);
        if (!(vipStream >> vipLevel) || vipLevel < 0 || vipLevel > 9) {
            std::cout << "Invalid VIP tier selected. Defaulting to VIP 0.\n";
            vipLevel = 0;
        }

        // Set the VIP maker fee
        double makerRates[] = {0.0025, 0.0022, 0.0018, 0.0015, 0.0012, 0.0010, 0.0008, 0.0007, 0.0006, 0.0005};
        double makerFeeRate = makerRates[vipLevel];
        std::cout << "\n***************************************************************************\n";
        std::cout << "\nMaker Fee: " << makerFeeRate * 100 << "%\n";
        std::cout << "\n***************************************************************************\n";

		double feeRate = makerFeeRate * 100;
		
        // Step 3: Ask for the market price
        std::cout << "\nEnter the market price: ";
        std::getline(std::cin, input);
        std::stringstream priceStream(input);
        if (!(priceStream >> marketPrice)) {
            std::cout << "Invalid input. Please enter a valid number for market price.\n";
            continue;
        }

        // Step 4: Ask for the coin amount to buy
        std::cout << "Enter the amount of coin you bought: ";
        std::getline(std::cin, input);
        std::stringstream coinStream(input);
        if (!(coinStream >> coinAmount)) {
            std::cout << "Invalid input. Please enter a valid number for coin amount.\n";
            continue;
        }

        // Step 5: Ask for the exit market price
        std::cout << "Enter your planned custom exit price: ";
        std::getline(std::cin, input);
        std::stringstream customExitStream(input);
        if (!(customExitStream >> customExitPrice)) {
            std::cout << "Invalid input. Please enter a valid number for custom exit price.\n";
            continue;
        }

        // Step 6: Ask for how many coins to sell
        std::cout << "Enter how many coins you plan to sell (can be less than bought): ";
        std::getline(std::cin, input);
        std::stringstream sellAmountStream(input);
        if (!(sellAmountStream >> sellCoinAmount)) {
            std::cout << "Invalid input. Please enter a valid number for selling coin amount.\n";
            continue;
        }

        // --- Perform Calculations ---
        double rawBuyCost = marketPrice * coinAmount;
        double buyFee = rawBuyCost * makerFeeRate;
        double totalBuyCost = rawBuyCost + buyFee;

        std::cout << std::fixed << std::setprecision(6);
        std::cout << "\n***************************************************************************\n";
        std::cout << "\n--- Buy Information ---\n";
        std::cout << "Market Price: PHP " << marketPrice << "\n";
        std::cout << "Coin Amount Bought: " << coinAmount << "\n";
        std::cout << "Raw Buy Cost (Capital): PHP " << rawBuyCost << "\n";
        std::cout << "Buy Fee (" << feeRate << "%): PHP " << buyFee << "\n";
        std::cout << "Total Buy Cost: PHP " << totalBuyCost << "\n";
        std::cout << "\n***************************************************************************\n";
		
		// --- Brute-Force Break Even Calculation ---
        double testSellGross = totalBuyCost;
        double sellFee, netAfterSell;
        double step = 0.01;
        int loops = 0;

        while (true) {
            sellFee = testSellGross * makerFeeRate;
            netAfterSell = testSellGross - sellFee;

            if (netAfterSell >= totalBuyCost) {
                break;
            }

            testSellGross += step;
            loops++;

            // Prevent infinite loops on extremely small coin amounts
            if (loops > 1000000) {
                std::cout << "Brute-force calculation took too long, likely due to very small coin amount.\n";
                break;
            }
        }

        double breakEvenPriceBruteForce = testSellGross / coinAmount;
		double BEtotalcost = totalBuyCost + sellFee;
		double NetPL = testSellGross - BEtotalcost;

        std::cout << "\n--- Brute-Force Break Even ---\n";
        std::cout << "Brute Force Break Even Sell Price: PHP " << breakEvenPriceBruteForce << "\n";
        std::cout << "Gross Sell at Break Even: PHP " << testSellGross << "\n";
        std::cout << "Sell Fee (" << feeRate << "%): PHP " << sellFee << "\n";
        std::cout << "Net After Sell: PHP " << netAfterSell << "\n";
        std::cout << "Total Loop Steps Taken: " << loops << "\n";
		std::cout << rawBuyCost << " + " << buyFee << " + " << sellFee << " = " << BEtotalcost << "\n";
		std::cout << testSellGross << " - " << BEtotalcost << " = " << NetPL << "\n";

        // --- Target Exit Calculations (1.6% and 2.6%) --- tier fee padded by 1.1% and 2.1% 
        
        std::cout << "\n***************************************************************************";
		std::cout << "\n--- Target Exit Prices ---\n";
		std::cout << "***************************************************************************\n";

		double targetRates[2];
		// Calculate the target rates, including maker fee adjustment
		targetRates[0] = 0.011 + (makerFeeRate + makerFeeRate);  // 1.1% plus the tiered fee respectively
		targetRates[1] = 0.021 + (makerFeeRate + makerFeeRate);  // 2.1% plus the tiered fee respectively

		for (int i = 0; i < 2; ++i) {
    	// Calculate market exit price, based on the target rate (with fee adjustment)
    	double marketExitPrice = marketPrice * (1.0 + targetRates[i]);

	    double grossProfit = marketExitPrice * coinAmount;
    	double sellFee = grossProfit * makerFeeRate;
    	double netProfit = grossProfit - totalBuyCost - sellFee;

	    // Print the target exit price as a percentage (converted from decimal)
    	double targetLabel = 100 * targetRates[i]; // Calculate percentage
    	std::cout << targetLabel << "% Target Market Exit Price: PHP " << marketExitPrice << "\n";
    	std::cout << "Gross Profit: PHP " << grossProfit << "\n";
    	std::cout << "Net Profit: PHP " << netProfit << "\n";
    	std::cout << "***************************************************************************\n";
		}


        // --- Custom Exit Calculation ---
        std::cout << "\n--- Custom Exit Simulation ---\n";
        std::cout << "Custom Exit Price: PHP " << customExitPrice << "\n";
        std::cout << "Coin Amount to Sell: " << sellCoinAmount << "\n";

        double customGrossSale = customExitPrice * sellCoinAmount;
        double customSellFee = customGrossSale * makerFeeRate;
        double proportionalBuyCost = (totalBuyCost / coinAmount) * sellCoinAmount;
        double customNetProfit = customGrossSale - proportionalBuyCost - customSellFee;

        std::cout << "Gross Sale: PHP " << customGrossSale << "\n";
        std::cout << "Sell Fee (" << feeRate << "%): PHP " << customSellFee << "\n";
        std::cout << "Proportional Buy Cost: PHP " << proportionalBuyCost << "\n";
        std::cout << "Net Profit (After Buy + Sell Fees): PHP " << customNetProfit << "\n";

        // --- Custom Exit Percent Gain ---
        double percentGain = (customNetProfit / rawBuyCost) * 100.0;
        std::cout << "Custom Exit is a " << percentGain << "% gain from initial capital buy amount.\n";

        // --- Custom Exit Market Movement ---
        double percentGain2 = ((customExitPrice - marketPrice) / marketPrice) * 100;
        std::cout << "Custom Exit is a " << percentGain2 << "% Market movement\n";

        // Update total capital after profit/loss
        totalCapital += customNetProfit;
        std::cout << "Updated Total Capital: PHP " << totalCapital << "\n";
        std::cout << "***************************************************************************\n";

        // Program loops back to asking total capital
    }

    return 0;
}

