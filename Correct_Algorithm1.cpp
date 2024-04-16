#include "Correct_Algorithm1.h"

Correct_Algorithm1::Correct_Algorithm1() {
}

Correct_Algorithm1::~Correct_Algorithm1() {
}

std::string Correct_Algorithm1::prep(const std::string message) {
    algorithm_name = "Triple Bit Packing";
    std::string prepped_message;

    // Triple bits stuffing
    for (int i = 0; i < message.size(); i++) {
        prepped_message.push_back(message[i]);
        prepped_message.push_back(message[i]);
        prepped_message.push_back(message[i]);
    }

    return prepped_message;
}

std::string Correct_Algorithm1::correct(const std::string message) {
    std::string corrected_message;

    // Push back each character if it appears as a majority of the representations
    for (int i = 0; i < message.size(); i+=3) {
        if (message[i] == message[i + 1] || message[i] == message[i + 2]){
            corrected_message.push_back(message[i]);
        }
        else if (message[i + 1] == message[i + 2]){
            corrected_message.push_back(message[i + 1]);
        }
        else {
            // If they are all different, just pick the first one
            corrected_message.push_back(message[i]);
        }
    }

    return corrected_message;
}