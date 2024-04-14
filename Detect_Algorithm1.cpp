#include "Detect_Algorithm1.h"

Detect_Algorithm1::Detect_Algorithm1() {
}

Detect_Algorithm1::~Detect_Algorithm1() {
}

std::vector<bool> Detect_Algorithm1::prep(const std::vector<bool> message) {

    std::vector<bool> prepped_message = message;

    // Add one bit to the end of the message which is the parity of the entire message
    int sum = 0;
    for (int i = 0; i < message.size(); i++) {
        sum += message[i];
    }
    if (sum % 2 == 0) {
        prepped_message.push_back(0);
    } else {
        prepped_message.push_back(1);
    }

    return prepped_message;
}

std::vector<bool> Detect_Algorithm1::detect(const std::vector<bool> message) {
    std::vector<bool> errors;

    // Get the sum of the message bits
    int sum = 0;
    for (int i = 0; i < message.size()-1; i++) {
        sum += message[i];
    }

    // Check if the parity bit matches the sum
    if (sum % 2 != message[message.size()-1]) {
        errors.push_back(true);
    } else {
        errors.push_back(false);
    }

    return errors;
}


float Detect_Algorithm1::calculate_error_rate_detect(const std::vector<bool> corrupted_bits, const std::vector<bool> detected_errors) {
    // How many bits were corrupted
    int num_errors = 0;
    for (bool bit : corrupted_bits) {
        if (bit) {
            num_errors++;
        }
    }

    // If the number of errors is 0 and the detected errors is 0, then the error rate is 0
    if (num_errors == 0 && detected_errors[0] == 0) {
        return 0.0f;
    }

    // If the number of errors is 0 and the detected errors is 1, then the error rate is 1
    else if (num_errors == 0 && detected_errors[0] == 1) {
        return 1.0f;
    }

    // If the number of errors is greater than 0 and the detected errors is 0, then the error rate is 1
    else if (num_errors > 0 && detected_errors[0] == 0) {
        return 1.0f;
    }

    // If the number of errors is greater than 0 and the detected errors is 1, then the error rate is 0
    else if (num_errors > 0 && detected_errors[0] == 1) {
        return 0.0f;
    }
}