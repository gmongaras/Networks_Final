#include "Correct_Algorithm1.h"
/*
Correct_Algorithm1::Correct_Algorithm1() {
}

Correct_Algorithm1::~Correct_Algorithm1() {
}

std::vector<bool> Correct_Algorithm1::prep(const std::vector<bool> message) {
    std::vector<bool> prepped_message;

    // Triple bits stuffing
    for (int i = 0; i < message.size(); i++) {
        prepped_message.push_back(message[i]);
        prepped_message.push_back(message[i]);
        prepped_message.push_back(message[i]);
    }

    return prepped_message;
}

std::vector<bool> Correct_Algorithm1::correct(const std::vector<bool> message) {
    std::vector<bool> corrected_message;

    for (int i = 0; i < message.size(); i+=3) {
        int sum = message[i] + message[i + 1] + message[i + 2];

        if (sum >= 2) {
            corrected_message.push_back(1);
        } else {
            corrected_message.push_back(0);
        }
    }

    return corrected_message;
}*/