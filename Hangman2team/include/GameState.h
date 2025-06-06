#ifndef GAME_STATE_H
#define GAME_STATE_H
#include "Word.h"
#include <string>
#include <vector>

class GameState {
private:
    std::string attemptId;
    std::string playerName;
    Word* word;
    std::string guessedLetters;
    int attemptsLeft;
    std::string date;

public:
    GameState(const std::string& attemptId, const std::string& playerName, Word* word, const std::string& date);
    std::string getAttemptId() const;
    std::string getPlayerName() const;
    Word* getWord() const;
    std::string getGuessedLetters() const;
    int getAttemptsLeft() const;
    std::string getDate() const;
    void guessLetter(char letter);
    bool isGameWon() const;
    bool isGameLost() const;
    void updateLeaderboard();
};

#endif