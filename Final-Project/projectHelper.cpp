//************************************************************************
// Assignment: Final Project
// Authors: Hanpei Zhang and Roy Conboy
// Date: December 15th, 2023
// File: projectHelper.cpp
// 
// Description: Has all the function definitions outside of the main file.
//************************************************************************

#include "projectHelper.h"

//**********************************************************************
// Function: createStates
// In: Strings x and y
// Return: An unordered map from string to int
// DESC: Creates states for a DFA where each state represents a unique prefix 
// of the strings x and y. The initial state is represented by an empty string.
//**********************************************************************

std::unordered_map<std::string, int> createStates(const std::string& x, const std::string& y) {
    std::unordered_map<std::string, int> stateMap;
    int stateId = 0;

    // Initial state
    stateMap[""] = stateId++;

    // Create states for each prefix of x
    std::string prefix = "";
    for (char ch : x) {
        prefix += ch;
        stateMap[prefix] = stateId++;
    }

    // Create states for each prefix of y
    prefix = "";
    for (char ch : y) {
        prefix += ch;
        if (stateMap.find(prefix) == stateMap.end()) { // Check if not already added
            stateMap[prefix] = stateId++;
        }
    }

    return stateMap;
}

//**********************************************************************
// Function: createTransitionTable
// In: Strings x and y, a map of states, and the alphabet sigma
// Return: A 2D vector representing the DFA's transition table
// DESC: Constructs the transition table for the DFA. Each table cell
// indicates the next state based on the current state and input character.
// Special handling for accepting and dead states.
//**********************************************************************

std::vector<std::vector<int>> createTransitionTable(const std::string& x, const std::string& y, const std::unordered_map<std::string, int>& states, const std::vector<char>& sigma) {
    std::vector<std::vector<int>> transitionTable(states.size(), std::vector<int>(sigma.size()));

    int acceptingStateX = states.at(x);  // State for complete string x
    int deadStateY = states.at(y);       // State for complete string y

    for (const auto& state : states) {
        for (size_t charIndex = 0; charIndex < sigma.size(); ++charIndex) {
            if (state.second == acceptingStateX || state.second == deadStateY) {
                // Stay in the same state if x or y is completed
                transitionTable[state.second][charIndex] = state.second;
            } else {
                char nextChar = sigma[charIndex];
                std::string nextPrefix = state.first + nextChar;

                // Find the longest suffix of nextPrefix that is also a prefix of x or y
                while (states.find(nextPrefix) == states.end() && !nextPrefix.empty()) {
                    nextPrefix.erase(0, 1); // Remove the first character
                }

                transitionTable[state.second][charIndex] = states.at(nextPrefix);
            }
        }
    }

    return transitionTable;
}

//**********************************************************************
// Function: simulateGame
// In: Transition table, alphabet sigma, accepting state index, dead state index
// Return: A pair of bool and string indicating the game's outcome and the generated string
// DESC: Simulates the game by generating a random string from sigma. Determines 
// the outcome (win or loss for Player A) based on the state transitions in the DFA.
//**********************************************************************

std::pair<bool, std::string> simulateGame(const std::vector<std::vector<int>>& transitionTable, const std::vector<char>& sigma, int acceptingStateX, int deadStateY) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(0, sigma.size() - 1);

    int currentState = 0; // Start at the initial state
    std::string generatedString;

    while (true) {
        int charIndex = dis(gen); // Randomly pick a character from Σ
        char nextChar = sigma[charIndex];
        generatedString += nextChar;

        currentState = transitionTable[currentState][charIndex];

        if (currentState == acceptingStateX) {
            return {true, generatedString}; // Player A wins
        } else if (currentState == deadStateY) {
            return {false, generatedString}; // Player A loses
        }
    }
}

//**********************************************************************
// Function: calculateWinRates
// In: Transition table, accepting state index, dead state index, size of sigma
// Return: A vector of double representing win rates for each state
// DESC: Calculates the win rates for Player A from each state in the DFA
// using an iterative approach.
//**********************************************************************

std::vector<double> calculateWinRates(const std::vector<std::vector<int>>& transitionTable, int acceptingStateX, int deadStateY, int sigmaSize) {
    std::vector<double> winRates(transitionTable.size(), 0.0);
    winRates[acceptingStateX] = 1.0; // Win rate for accepting state
    winRates[deadStateY] = 0.0; // Win rate for dead state

    bool changed;
    do {
        changed = false;
        for (int state = 0; state < transitionTable.size(); ++state) {
            if (state == acceptingStateX || state == deadStateY) continue;

            double newWinRate = 0.0;
            for (int charIndex = 0; charIndex < sigmaSize; ++charIndex) {
                newWinRate += winRates[transitionTable[state][charIndex]] / sigmaSize;
            }

            if (std::abs(newWinRate - winRates[state]) > 1e-6) {
                winRates[state] = newWinRate;
                changed = true;
            }
        }
    } while (changed);

    return winRates;
}

//**********************************************************************
// Function: containsOnlySigma
// In: A string and a set of characters (sigmaSet)
// Return: True if the string contains only characters in sigmaSet, false otherwise
// DESC: Checks if the given string consists exclusively of characters 
// that are in the given set (sigmaSet).
//**********************************************************************

bool containsOnlySigma(const std::string& str, const std::set<char>& sigmaSet) {
    for (char ch : str) {
        if (sigmaSet.find(ch) == sigmaSet.end()) {
            return false;
        }
    }
    return true;
}