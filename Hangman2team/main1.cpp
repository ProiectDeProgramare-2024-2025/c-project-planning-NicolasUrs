#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "Word.h"

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define YELLOW  "\033[33m"

void viewWords() {
    std::ifstream file("words.txt");
    if (!file.is_open()) {
        std::cerr << RED << "Error: Could not open words.txt" << RESET << std::endl;
        return;
    }
    int numWords;
    file >> numWords;
    std::vector<Word> words;
    for (int i = 0; i < numWords; ++i) {
        std::string id, text, category;
        int difficulty;
        file >> id >> text >> category >> difficulty;
        words.emplace_back(id, text, category, difficulty);
    }
    file.close();
    std::cout << GREEN << "Words in stock:" << RESET << std::endl;
    for (const auto& word : words) {
        std::cout << YELLOW << "ID: " << word.getId() << ", Text: " << word.getText()
                  << ", Category: " << word.getCategory() << ", Difficulty: " << word.getDifficulty() << RESET << std::endl;
    }
}

void addWord(const std::string& id, const std::string& text, const std::string& category, int difficulty) {
    try {
        Word word(id, text, category, difficulty);
        std::ofstream file("words.txt", std::ios::app);
        if (!file.is_open()) throw std::runtime_error("Could not open words.txt");
        file << id << " " << text << " " << category << " " << difficulty << "\n";
        file.close();
        std::cout << GREEN << "Word added successfully!" << RESET << std::endl;
    } catch (const std::exception& e) {
        std::cerr << RED << "Error: " << e.what() << RESET << std::endl;
    }
}

void deleteWord(const std::string& id) {
    std::ifstream file("words.txt");
    if (!file.is_open()) {
        std::cerr << RED << "Error: Could not open words.txt" << RESET << std::endl;
        return;
    }
    int numWords;
    file >> numWords;
    std::vector<Word> words;
    bool found = false;
    for (int i = 0; i < numWords; ++i) {
        std::string wid, text, category;
        int difficulty;
        file >> wid >> text >> category >> difficulty;
        if (wid != id) words.emplace_back(wid, text, category, difficulty);
        else found = true;
    }
    file.close();
    std::ofstream outFile("words.txt");
    outFile << words.size() << "\n";
    for (const auto& word : words) {
        outFile << word.getId() << " " << word.getText() << " " << word.getCategory() << " " << word.getDifficulty() << "\n";
    }
    outFile.close();
    std::cout << (found ? GREEN + std::string("Word deleted successfully!") : RED + std::string("Word not found!")) << RESET << std::endl;
}

void modifyWord(const std::string& field, const std::string& id, const std::string& newValue) {
    std::ifstream file("words.txt");
    if (!file.is_open()) {
        std::cerr << RED << "Error: Could not open words.txt" << RESET << std::endl;
        return;
    }
    int numWords;
    file >> numWords;
    std::vector<Word> words;
    bool found = false;
    for (int i = 0; i < numWords; ++i) {
        std::string wid, text, category;
        int difficulty;
        file >> wid >> text >> category >> difficulty;
        Word word(wid, text, category, difficulty);
        if (wid == id) {
            found = true;
            try {
                if (field == "text") word.setText(newValue);
                else if (field == "difficulty") word.setDifficulty(std::stoi(newValue));
                else throw std::invalid_argument("Invalid field");
            } catch (const std::exception& e) {
                std::cerr << RED << "Error: " << e.what() << RESET << std::endl;
                file.close();
                return;
            }
        }
        words.push_back(word);
    }
    file.close();
    if (!found) {
        std::cerr << RED << "Error: Word not found" << RESET << std::endl;
        return;
    }
    std::ofstream outFile("words.txt");
    outFile << words.size() << "\n";
    for (const auto& word : words) {
        outFile << word.getId() << " " << word.getText() << " " << word.getCategory() << " " << word.getDifficulty() << "\n";
    }
    outFile.close();
    std::cout << GREEN << "Word modified successfully!" << RESET << std::endl;
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

int main(int argc, char* argv[]) {
    if (argc < 2) {
        std::cerr << RED << "Usage: ./main1.exe <command> [args]" << RESET << std::endl;
        return 1;
    }
    std::string command = argv[1];
    try {
        if (command == "view_words") {
            viewWords();
        } else if (command == "add_word" && argc == 6) {
            addWord(argv[2], argv[3], argv[4], std::stoi(argv[5]));
        } else if (command == "delete_word" && argc == 3) {
            deleteWord(argv[2]);
        } else if (command == "modify_word" && argc == 5) {
            modifyWord(argv[2], argv[3], argv[4]);
        } else if (command == "view_history") {
            viewHistory();
        } else if (command == "view_leaderboard") {
            viewLeaderboard();
        } else {
            std::cerr << RED << "Invalid command or arguments" << RESET << std::endl;
            return 1;
        }
    } catch (const std::exception& e) {
        std::cerr << RED << "Error: " << e.what() << RESET << std::endl;
        return 1;
    }
    return 0;
}