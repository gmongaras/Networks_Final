//
// Created by james on 4/14/2024.
//

#include "Detect_Algorithm2.h"

Detect_Algorithm2::Detect_Algorithm2() {
}

Detect_Algorithm2::~Detect_Algorithm2() {
}

std::string Detect_Algorithm2::prep(const std::string message) {

    algorithm_name = "Single Checksum";
    originalChecksum = 0;
    for (int i = 0; i < message.size(); i++) {
        originalChecksum += message[i];
    }

    return message;
}

std::vector<bool> Detect_Algorithm2::detect(const std::string message) {
    newChecksum = 0;
    for (int i = 0; i < message.size(); i++) {
        newChecksum += message[i];
    }
    if (originalChecksum != newChecksum){
        return {true};
    }
    else{
        return {false};
    }
}


std::vector<float> Detect_Algorithm2::calculate_error_rate_detect(const std::string original_message, const std::string corrupted_message, const std::vector<bool> detected_errors) {
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


std::string Detect_Algorithm2::remove_correct_frames(const std::string message, const std::vector<bool> detected_errors) {
    if (detected_errors[0] == false){
        return message;
    }
    else{
        return "";
    }
}