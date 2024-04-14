#include "Algorithm1.h"

Algorithm1::Algorithm1() {
}

Algorithm1::~Algorithm1() {
}

std::vector<bool> Algorithm1::prep(const std::vector<bool> message) {
    // Do some preparation on the message
    std::cout << "Preparation complete." << std::endl;

    std::vector<bool> prepped_message;

    // Triple bits stuffing
    for (int i = 0; i < message.size(); i++) {
        prepped_message.push_back(message[i]);
        prepped_message.push_back(message[i]);
        prepped_message.push_back(message[i]);
    }

    return prepped_message;
}

std::vector<bool> Algorithm1::run(const std::vector<bool> message) {
    // Run the algorithm on the message
    std::cout << "Algorithm 1 running..." << std::endl;

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
}