#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Word.h"
#include "GameState.h"
#include <ctime>
#include <sstream>
#include <random>

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

std::vector<Word> loadWords() {
    std::ifstream file("words.txt");
    std::vector<Word> words;
    if (!file.is_open()) return words;
    int numWords;
    file >> numWords;
    for (int i = 0; i < numWords; ++i) {
        std::string id, text, category;
        int difficulty;
        file >> id >> text >> category >> difficulty;
        words.emplace_back(id, text, category, difficulty);
    }
    file.close();
    return words;
}

void viewHistory() {
    std::ifstream file("history.txt");
    if (!file.is_open()) {
        std::cerr << RED << "Error: Could not open history.txt" << RESET << std::endl;
        return;
    }
    std::string line;
    std::cout << GREEN << "Game history:" << RESET << std::endl;
    while (std::getline(file, line)) {
        std::cout << YELLOW << line << RESET << std::endl;
    }
    file.close();
}

void viewLeaderboard() {
    std::ifstream file("leaderboard.txt");
    if (!file.is_open()) {
        std::cerr << RED << "Error: Could not open leaderboard.txt" << RESET << std::endl;
        return;
    }
    std::string name;
    int wins;
    std::cout << GREEN << "Leaderboard:" << RESET << std::endl;
    while (file >> name >> wins) {
        std::cout << YELLOW << name << ": " << wins << " wins" << RESET << std::endl;
    }
    file.close();
}

void addAttempt(const std::string& wordId, int quantity) {
    try {
        std::ofstream file("history.txt", std::ios::app);
        if (!file.is_open()) throw std::runtime_error("Could not open history.txt");
        time_t now = time(0);
        std::string date = ctime(&now);
        date.pop_back();
        file << "attempt_" << wordId << "_" << now << " " << wordId << "