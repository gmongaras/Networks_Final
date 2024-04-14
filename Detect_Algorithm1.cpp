#include "Detect_Algorithm1.h"

Detect_Algorithm1::Detect_Algorithm1() {
}

Detect_Algorithm1::~Detect_Algorithm1() {
}

std::string Detect_Algorithm1::prep(const std::string message) {

    algorithm_name = "Single Parity Bit";
    parityBit = false;
    for (int i = 0; i < message.size(); i++) {
        char check_character = message[i];
        if (getParityBit(check_character)){
            parityBit != parityBit;
        }
    }

    return message;
}

std::vector<bool> Detect_Algorithm1::detect(const std::string message) {
    checkedParityBit = false;
    for (int i = 0; i < message.size(); i++) {
        char check_character = message[i];
        if (getParityBit(check_character)){
            checkedParityBit = !checkedParityBit;
        }
    }
    if (checkedParityBit == parityBit){
        return {true};
    }
    else{
        return {false};
    }
}


std::vector<float> Detect_Algorithm1::calculate_error_rate_detect(const std::string original_message, const std::string corrupted_message, const std::vector<bool> detected_errors) {
    // If the frame is detected as incorrect, return no error
    if (detected_errors[0] == false){
        return {};
    }

    // Iterate over the string and see how many are incorrect
    int error_count = 0;
    for (int i = 0; i < original_message.size(); i++) {
        if (original_message[i] != corrupted_message[i]) {
            error_count++;
        }
    }
    return {static_cast<float>(error_count) / original_message.size()};
}


bool Detect_Algorithm1::getParityBit(char n){
    bool parity = 0;
    while (n)
    {
        parity = !parity;
        n &= (n - 1);
    }
    return parity;
}


std::string Detect_Algorithm1::remove_correct_frames(const std::string message, const std::vector<bool> detected_errors) {
    if (detected_errors[0] == false){
        return message;
    }
    else{
        return "";
    }
}