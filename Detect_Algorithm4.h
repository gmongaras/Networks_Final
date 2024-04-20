
#include <iostream>

#include "Algorithm.h"

class Detect_Algorithm4 : public Algorithm {
public:
    Detect_Algorithm4();
    virtual ~Detect_Algorithm4();

    std::string prep(const std::string message) override;
    std::string correct(const std::string message) override {return {};};
    std::vector<bool> detect(const std::string message) override;
    std::vector<float> calculate_error_rate_detect(const std::string original_message, const std::string corrupted_message, const std::vector<bool> detected_errors);
    std::string remove_correct_frames(const std::vector<bool> detected_errors, const std::string corrupted_message, const std::string prepared_message);
};

