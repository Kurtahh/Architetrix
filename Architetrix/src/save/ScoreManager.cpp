#include "ScoreManager.h"
#include <fstream>
#include <vector>

const std::string HIGHSCORE_FILE = "src/data/highscore.txt";

ScoreManager::ScoreManager() {
    std::ifstream file(HIGHSCORE_FILE);
    int score;
    if (file.is_open() && file >> score) {
        personalRecord_ = score;
    }
}

int ScoreManager::getPersonalRecord() const {
    return personalRecord_;
}

bool ScoreManager::updateRecord(int score) {
    if (score <= personalRecord_) return false;
    personalRecord_ = score;

    //read existing history
    std::vector<int> history;
    std::ifstream inFile(HIGHSCORE_FILE);
    int existing;
    while (inFile >> existing) {
        history.push_back(existing);
    }
    inFile.close();

    //insert new score at the top
    personalRecord_ = score;
    history.insert(history.begin(), score);

    //write back, new score first
    std::ofstream outFile(HIGHSCORE_FILE);
    for (int s : history) {
        outFile << s << "\n";
    }

    return true;
}