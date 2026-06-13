#ifndef SCORE_MANAGER_H_422211
#define SCORE_MANAGER_H_422211
#include <string>

//manages reading and writing the personal record to a file
class ScoreManager {
    int personalRecord_ = 0;

public:
    ScoreManager(); //loads personal record from file on construction
    int getPersonalRecord() const;
    bool updateRecord(int score); //writes new record to file if score beats current PR
};
#endif