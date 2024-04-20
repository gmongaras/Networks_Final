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

    static std::vector<int> textToBits(const std::string& text);
    static std::string bitsToText(const std::vector<int>& bits);
    static std::string encode(const std::string message, const std::vector<std::vector<int>>& filters);

    static int hamming_distance(const std::vector<int>& a, const std::vector<int>& b);
    static std::string viterbi_decode(const std::string message, const std::vector<std::vector<int>>& filters);
};