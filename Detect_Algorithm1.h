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

    std::vector<bool> prep(const std::vector<bool> message) override;
    std::vector<bool> correct(const std::vector<bool> message) override {return {};};
    std::vector<bool> detect(const std::vector<bool> message) override;
    float calculate_error_rate_detect(const std::vector<bool> corrupted_bits, const std::vector<bool> detected_errors) override;
};