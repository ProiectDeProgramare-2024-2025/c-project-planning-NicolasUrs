#ifndef WORD_H
#define WORD_H
#include <string>

class Word {
private:
    std::string id;
    std::string text;
    std::string category;
    int difficulty;

public:
    Word(const std::string& id, const std::string& text, const std::string& category, int difficulty);
    std::string getId() const;
    std::string getText() const;
    std::string getCategory() const;
    int getDifficulty() const;
    void setText(const std::string& newText);
    void setDifficulty(int newDifficulty);
};

#endif