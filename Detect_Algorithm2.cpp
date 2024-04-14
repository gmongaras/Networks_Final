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

std::string Detect_Algorithm2::detect(const std::string message) {
    newChecksum = 0;
    for (int i = 0; i < message.size(); i++) {
        newChecksum += message[i];
    }
    if (originalChecksum != newChecksum){
        return "true";
    }
    else{
        return "false";
    }
}


float Detect_Algorithm2::calculate_error_rate_detect(const std::string detected_errors) {
    if (detected_errors == "false"){
        return 0.0f;
    }
    else {
        return 1.0f;
    }
}