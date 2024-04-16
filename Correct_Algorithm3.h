/*

Binary convolutional code

*/



#include <iostream>

#include "Algorithm.h"

class Correct_Algorithm3 : public Algorithm {
public:
    Correct_Algorithm3();
    virtual ~Correct_Algorithm3();

    std::string prep(const std::string message) override;
    std::string correct(const std::string message) override;
    std::vector<bool> detect(const std::string message) override {return {};}
    std::vector<float> calculate_error_rate_detect(const std::string original_message, const std::string corrupted_message, const std::vector<bool> detected_errors) override {return {0.0f};}
    virtual std::string remove_correct_frames(const std::string message, const std::vector<bool> detected_errors) override {return "";};
    static std::string convolution(char shift);
};