/*

Simple triple bits stuffing
message: 01001
prepped: 000 111 000 0000 111






#include <iostream>

#include "Algorithm.h"

class Correct_Algorithm1 : public Algorithm {
public:
    Correct_Algorithm1();
    virtual ~Correct_Algorithm1();

    std::string prep(const std::string message) override;
    std::string correct(const std::string message) override;
    std::string detect(const std::string message) override {return {};}
    float calculate_error_rate_detect(const std::string corrupted_bits, const std::string detected_errors) override {return 0.0f;}
};*/