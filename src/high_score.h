#ifndef HIGH_SCORE_H
#define HIGH_SCORE_H

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

struct HighScoreData 
{
    int high_score;
    std::string name;
};

class HighScore
{
    public:
        HighScore() { this->high_score.high_score = 0; this->high_score.name = ""; }
        
        HighScoreData GetHighScore();
        void SetHighScore(int high, std::string name);

        void WriteHighScoreToFile(int high, std::string name);
        void ReadHighScoreFromFile();

    private:

        std::string name;
        const std::string kHighScorePath = {"../highscore.txt"};
        HighScoreData high_score; 
    
};

#endif
