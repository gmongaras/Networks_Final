
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
    std::vector<bool> detect(const std::string message) override;
    std::vector<float> calculate_error_rate_detect(const std::string original_message, const std::string corrupted_message, const std::vector<bool> detected_errors);
    std::string remove_correct_frames(const std::string message, const std::vector<bool> detected_errors);
};

