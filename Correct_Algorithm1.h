/*

Simple triple bits stuffing
message: 01001
prepped: 000 111 000 0000 111


*/



#include <iostream>

#include "Algorithm.h"

class Correct_Algorithm1 : public Algorithm {
public:
    Correct_Algorithm1();
    virtual ~Correct_Algorithm1();

    std::string prep(const std::string message) override;
    std::string correct(const std::string message) override;
    std::vector<bool> detect(const std::string message) override {return {};}
    std::vector<float> calculate_error_rate_detect(const std::string original_message, const std::string corrupted_message, const std::vector<bool> detected_errors) override {return {0.0f};}
    virtual std::string remove_correct_frames(const std::vector<bool> detected_errors, const std::string corrupted_message, const std::string prepared_message) override {return "";};
};