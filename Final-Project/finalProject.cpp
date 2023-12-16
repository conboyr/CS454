//************************************************************************
// Assignment: Final Project
// Authors: Hanpei Zhang and Roy Conboy
// Date: December 15th, 2023
// File: finalProject.cpp
// 
// Description: Allows the execution of final project.
//************************************************************************

#include "projectHelper.h"
#include <iostream>
#include <sstream>

int main() {
    int sigmaSize;
    std::string inputLine;
    std::vector<char> sigma;
    std::set<char> sigmaSet;
    std::string x, y;

    while (true) {
        std::cout << "Enter the number of characters in the alphabet sigma: \n";
        std::cin >> sigmaSize;

        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // Ignore leftover newline

        std::cout << "Enter the characters of the alphabet sigma: \n";
        std::getline(std::cin, inputLine);
        std::istringstream iss(inputLine);

        sigma.clear();
        sigmaSet.clear();
        char ch;
        while (iss >> ch) {
            if (sigmaSet.find(ch) != sigmaSet.end()) {
                std::cout << "Duplicate character found. Please enter unique characters.\n" << std::endl;
                goto tryAgainSigma;
            }
            sigma.push_back(ch);
            sigmaSet.insert(ch);
        }

        if (sigma.size() != sigmaSize) {
            std::cout << "Number of characters entered does not match the specified size. Please try again.\n" << std::endl;
            goto tryAgainSigma;
        }

        break;
        tryAgainSigma:;
    }

    while (true) {
        std::cout << "Enter player A's string: \n";
        std::cin >> x;
        std::cout << "Enter player B's string: \n";
        std::cin >> y;

        if (x.length() != y.length()) {
            std::cout << "The strings must be of equal length. Please try again.\n" << std::endl;
            continue;
        }

        if (!containsOnlySigma(x, sigmaSet) || !containsOnlySigma(y, sigmaSet)) {
            std::cout << "Invalid input. Strings contain characters not in sigma. Please try again.\n" << std::endl;
            continue;
        }

        break;
    }

    auto states = createStates(x, y);
    auto transitionTable = createTransitionTable(x, y, states, sigma);

    int acceptingStateX = states.at(x); // State for complete string x (Player A)
    int deadStateY = states.at(y);      // State for complete string y (Player B)

    auto result = simulateGame(transitionTable, sigma, acceptingStateX, deadStateY);
    if (result.first) {
        std::cout << "Player A wins!" << std::endl;
    } else {
        std::cout << "Player A loses." << std::endl;
    }

    auto winRates = calculateWinRates(transitionTable, acceptingStateX, deadStateY, sigma.size());
    std::cout << "Win rate for Player A: " << winRates[0] << std::endl; // Win rate from the starting state


    char userChoice;
    std::cout << "Do you want to see the generated string? (y/n): \n";
    std::cin >> userChoice;

    if (userChoice == 'y' || userChoice == 'Y') {
        std::cout << "Generated String: " << result.second << std::endl;
    }

    return 0;
}