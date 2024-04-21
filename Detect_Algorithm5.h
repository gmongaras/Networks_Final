
#include <iostream>

#include "Algorithm.h"
#include <bitset>

class Detect_Algorithm5 : public Algorithm {
public:
    Detect_Algorithm5();
    virtual ~Detect_Algorithm5();
    char key;
    int keyLength;

    std::string prep(const std::string message) override;
    std::string correct(const std::string message) override {return {};};
    std::vector<bool> detect(const std::string message) override;
    std::vector<float> calculate_error_rate_detect(const std::string original_message, const std::string corrupted_message, const std::vector<bool> detected_errors);
    std::string remove_correct_frames(const std::vector<bool> detected_errors, const std::string corrupted_message, const std::string prepared_message);
    unsigned char modulo2div(unsigned int data, unsigned char key, int datalen, int keylen);
};
