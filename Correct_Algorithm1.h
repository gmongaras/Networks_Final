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

    std::vector<bool> prep(const std::vector<bool> message) override;
    std::vector<bool> correct(const std::vector<bool> message) override;
    std::vector<bool> detect(const std::vector<bool> message) override {return {};}
    float calculate_error_rate_detect(const std::vector<bool> corrupted_bits, const std::vector<bool> detected_errors) override {return 0.0f;}
};