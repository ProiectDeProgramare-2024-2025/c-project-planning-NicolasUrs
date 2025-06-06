#include "GameState.h"
#include <algorithm>
#include <stdexcept>
#include <fstream>
#include <sstream>

GameState::GameState(const std::string& attemptId, const std::string& playerName, Word* word, const std::string& date)
    : attemptId(attemptId), playerName(playerName), word(word), attemptsLeft(6), date(date) {
    if (!word) throw std::invalid_argument("Word cannot be null");
    if (playerName.empty()) throw std::invalid_argument("Player name cannot be empty");
}

std::string GameState::getAttemptId() const { return attemptId; }
std::string GameState::getPlayerName() const { return playerName; }
Word* GameState::getWord() const { return word; }
std::string GameState::getGuessedLetters() const { return guessedLetters; }
int GameState::getAttemptsLeft() const { return attemptsLeft; }
std::string GameState::getDate() const { return date; }

void GameState::guessLetter(char letter) {
    letter = std::tolower(letter);
    if (guessedLetters.find(letter) != std::string::npos) return;
    guessedLetters += letter;
    if (word->getText().find(letter) == std::string::npos) {
        attemptsLeft--;
    }
}

bool GameState::isGameWon() const {
    for (char c : word->getText()) {
        if (guessedLetters.find(std::tolower(c)) == std::string::npos) return false;
    }
    return true;
}

bool GameState::isGameLost() const {
    return attemptsLeft <= 0;
}

void GameState::updateLeaderboard() {
    if (!isGameWon()) return;
    std::ifstream file("leaderboard.txt");
    std::vector<std::pair<std::string, int>> leaderboard;
    std::string name;
    int wins;
    bool found = false;
    while (file >> name >> wins) {
        if (name == playerName) {
            found = true;
            leaderboard.emplace_back(name, wins + 1);
        } else {
            leaderboard.emplace_back(name, wins);
        }
    }
    if (!found) {
        leaderboard.emplace_back(playerName, 1);
    }
    file.close();
    std::ofstream outFile("leaderboard.txt");
    for (const auto& entry : leaderboard) {
        outFile << entry.first << " " << entry.second << "\n";
    }
    outFile.close();
}