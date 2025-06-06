#include "Word.h"
#include <stdexcept>

Word::Word(const std::string& id, const std::string& text, const std::string& category, int difficulty)
    : id(id), text(text), category(category), difficulty(difficulty) {
    if (text.empty()) throw std::invalid_argument("Word text cannot be empty");
    if (difficulty < 1 || difficulty > 3) throw std::invalid_argument("Difficulty must be between 1 and 3");
}

std::string Word::getId() const { return id; }
std::string Word::getText() const { return text; }
std::string Word::getCategory() const { return category; }
int Word::getDifficulty() const { return difficulty; }
void Word::setText(const std::string& newText) {
    if (newText.empty()) throw std::invalid_argument("New word text cannot be empty");
    text = newText;
}
void Word::setDifficulty(int newDifficulty) {
    if (newDifficulty < 1 || newDifficulty > 3) throw std::invalid_argument("New difficulty must be between 1 and 3");
    difficulty = newDifficulty;
}