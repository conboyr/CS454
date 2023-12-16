//************************************************************************
// Assignment: Fianl Project
// Authors: Hanpei Zhang and Roy Conboy
// Date: December 15th, 2023
// File: projectHelper.h
// 
// Description: Header file for all the function definitions 
// in projectHelper.cpp.
//************************************************************************

#ifndef PROJECT_HELPER_H
#define PROJECT_HELPER_H

#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <random>
#include <set>
#include <sstream>

std::unordered_map<std::string, int> createStates(const std::string& x, const std::string& y);

std::vector<std::vector<int>> createTransitionTable(const std::string& x, const std::string& y, const std::unordered_map<std::string, int>& states, const std::vector<char>& sigma);

std::pair<bool, std::string> simulateGame(const std::vector<std::vector<int>>& transitionTable, const std::vector<char>& sigma, int acceptingStateX, int deadStateY);

std::vector<double> calculateWinRates(const std::vector<std::vector<int>>& transitionTable, int acceptingStateX, int deadStateY, int sigmaSize);

bool containsOnlySigma(const std::string& str, const std::set<char>& sigmaSet);

#endif // HELPER_FUNCTIONS_H

