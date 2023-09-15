#include "high_score.h"


HighScoreData HighScore::GetHighScore()
{
    return this->high_score;
}

void HighScore::SetHighScore(int high, std::string name)
{
    this->high_score.high_score = high;
    this->high_score.name = name;
}

void HighScore::ReadHighScoreFromFile()
{
    std::cout << "Searching: " << kHighScorePath << " for high score\n";
    std::string line;
    int score;
    std::string name;
    std::ifstream stream(kHighScorePath);
    if (!stream.is_open()) {
        std::cerr << "Error: Unable to open file " << kHighScorePath << std::endl;
        return; // or handle the error in another way
    }

    std::cout << "getting high score\n";
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> score >> name;

    SetHighScore(score, name);
}

void HighScore::WriteHighScoreToFile(int high, std::string name)
{
    SetHighScore(high, name);

    std::ofstream outputFile(kHighScorePath);
    if (!outputFile.is_open()) {
        std::cerr << "Error: Unable to open file " << kHighScorePath << std::endl;
        return; // or handle the error in another way
    }
    std::cout << "setting high score\n";
    outputFile << high << " " << name;

    outputFile.close();
}

