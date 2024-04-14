/*

Simple single parity bit
message: 01001
prepped: 010011


*/




#include <iostream>

#include "Algorithm.h"

class Detect_Algorithm1 : public Algorithm {
public:
    Detect_Algorithm1();
    virtual ~Detect_Algorithm1();
    bool parityBit;
    bool checkedParityBit;

    std::string prep(const std::string message) override;
    std::string correct(const std::string message) override {return {};};
    std::string detect(const std::string message) override;
    float calculate_error_rate_detect(const std::string detected_errors) override;
    bool getParityBit(char);
};