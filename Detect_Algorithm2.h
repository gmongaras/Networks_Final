
#include <iostream>

#include "Algorithm.h"

class Detect_Algorithm2 : public Algorithm {
public:
    Detect_Algorithm2();
    virtual ~Detect_Algorithm2();
    char originalChecksum;
    char newChecksum;

    std::string prep(const std::string message) override;
    std::string correct(const std::string message) override {return {};};
    std::string detect(const std::string message) override;
    float calculate_error_rate_detect(const std::string detected_errors) override;
};

