//
// Created by james on 4/14/2024.
//

#include "Detect_Algorithm4.h"

Detect_Algorithm4::Detect_Algorithm4() {
}

Detect_Algorithm4::~Detect_Algorithm4() {
}

std::string Detect_Algorithm4::prep(const std::string message) {
    algorithm_name = "4-char Checksum";
    std::string expanded_message = message;
    std::string prepped_message = "";
    int extra_padding = message.size() % 4;
    for(int i = 0; i < extra_padding; i++){
        expanded_message.append(" ");
    }
    for (int i = 0; i < expanded_message.size(); i += 4) {
        char checksum = expanded_message[i] + expanded_message[i + 1] + expanded_message[i + 2] + expanded_message[i + 3];
        prepped_message.append(expanded_message.substr(i, 4));
        prepped_message.append(1u, checksum);
    }

    return prepped_message;
}

std::vector<bool> Detect_Algorithm4::detect(const std::string message) {
    std::vector<bool> detected_errors;
    for (int i = 0; i < message.size(); i += 5) {
        char checksum = message[i] + message[i + 1] + message[i + 2] + message[i + 3];
        if (checksum == message[i + 4]){
            detected_errors.push_back(false);
        }
        else {
            detected_errors.push_back(true);
        }

    }
    return detected_errors;
}


std::vector<float> Detect_Algorithm4::calculate_error_rate_detect(const std::string original_message, const std::string corrupted_message, const std::vector<bool> detected_errors) {
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


std::string Detect_Algorithm4::remove_correct_frames(const std::vector<bool> detected_errors, const std::string corrupted_message, const std::string prepared_message) {
    std::string trimmed_message = "";
    for(int i = 0; i < detected_errors.size(); i++){
        if (detected_errors[i] == true){
            trimmed_message.append(prepared_message.substr((i * 5), 5));
        }
    }
    return trimmed_message;
}

