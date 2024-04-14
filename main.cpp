#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <vector>

#include "Algorithm.h"
#include "Correct_Algorithm1.h"
#include "Detect_Algorithm1.h"



// Corrupt a message based on probability p
std::vector<std::vector<bool>> corrupt_message(const std::vector<bool>& message, double p) {
    // New corrupted message
    std::vector<bool> corrupted = message;

    // Stores which bits were corrupted
    std::vector<bool> corrupted_bits(message.size(), false);

    // Iterate over all bits in the message and corrupt them with probability p
    for (int i = 0; i < corrupted.size(); i++) {
        double rand_prob = static_cast<double>(rand()) / RAND_MAX;
        if (rand_prob < p) {
            corrupted[i] = !corrupted[i];

            corrupted_bits[i] = true;
        }
        else {
            corrupted_bits[i] = false;
        }
    }
    return {corrupted, corrupted_bits};
}



// Convert a string to a vector of bits
std::vector<bool> stringToBits(const std::string& input) {
    std::vector<bool> bits;

    // Iterate over each character and convert it to bits
    for (char c : input) {
        // Get the ASCII value of the character and convert it to binary with 8 bits
        std::bitset<8> charBits(c);

        for (int i = 7; i >= 0; i--) {
            bits.push_back(charBits.test(i));
        }
    }

    return bits;
}


// Converts a vector of bits back to a string
std::string bitsToString(const std::vector<bool>& bits) {
    std::string output;
    std::bitset<8> charBits;

    // Ensure the vector size is a multiple of 8
    if (bits.size() % 8 != 0) {
        std::cerr << "Invalid bit vector size. Must be a multiple of 8." << std::endl;
        return "";
    }

    // Process each group of 8 bits
    for (size_t i = 0; i < bits.size(); i += 8) {
        // Set each bit in the bitset
        for (int j = 0; j < 8; ++j) {
            charBits[j] = bits[i + 7 - j]; // Access bits in reverse order to reconstruct the character
        }

        // Convert the bits to a character
        output.push_back(static_cast<char>(charBits.to_ulong()));
    }
    
    return output;
}



void test_correction_algorithm(Algorithm* algorithm, std::string original_message, double corruption_probability) {
    // Turn the message into an array of bits
    std::vector<bool> bits = stringToBits(original_message);

    // Prepare the message for error correction
    std::vector<bool> prepared_message = algorithm->prep(bits);

    // Corrupt the message
    // srand(time(nullptr)); // Seed random number generator
    std::vector<std::vector<bool>> _ = corrupt_message(prepared_message, corruption_probability);
    std::vector<bool> corrupted_message = _[0];
    std::vector<bool> corrupted_bits = _[1];

    // Time how long it takes to correct the message
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<bool> corrected_message = algorithm->correct(corrupted_message);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    // Get the error rate
    int errors = 0;
    for (int i = 0; i < bits.size(); i++) {
        if (bits[i] != corrected_message[i]) {
            errors++;
        }
    }
    double error_rate = static_cast<double>(errors) / bits.size();

    // Convert the corrected message back to a string
    std::string output_message = bitsToString(corrected_message);

    std::cout << "Corrected message: " << output_message << std::endl;
    std::cout << "Time taken: " << elapsed.count() << " milliseconds." << std::endl;
    std::cout << "Error rate: " << error_rate << std::endl;
}



void test_detection_algorithm(Algorithm* algorithm, std::string original_message, double corruption_probability) {
    // Turn the message into an array of bits
    std::vector<bool> bits = stringToBits(original_message);

    // Prepare the message for error correction
    std::vector<bool> prepared_message = algorithm->prep(bits);

    // Corrupt the message
    std::vector<std::vector<bool>> _ = corrupt_message(prepared_message, corruption_probability);
    std::vector<bool> corrupted_message = _[0];
    std::vector<bool> corrupted_bits = _[1];

    // Time how long it takes to detect errors in the message
    auto start = std::chrono::high_resolution_clock::now();
    std::vector<bool> detected_errors = algorithm->detect(corrupted_message);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    // Get the error rate
    int errors = algorithm->calculate_error_rate_detect(corrupted_bits, detected_errors);

    std::cout << "Time taken: " << elapsed.count() << " milliseconds." << std::endl;
    std::cout << "Error rate: " << errors << std::endl;
}

int main(int argc, char* argv[]) {
    std::string original_message = "This is a test message for error correction.";
    double corruption_probability = 0.01;

    srand(time(nullptr)); // Seed random number generator

    // List of algorithms to test
    Algorithm* correcting_algorithms[] = {
        new Correct_Algorithm1(),
        new Correct_Algorithm1(),
    };
    Algorithm* detecting_algorithms[] = {
        new Detect_Algorithm1(),
        new Detect_Algorithm1(),
    };

    // Test each algorithm
    for (Algorithm* algorithm : correcting_algorithms) {
        test_correction_algorithm(algorithm, original_message, corruption_probability);
    }
    for (Algorithm* algorithm : detecting_algorithms) {
        test_detection_algorithm(algorithm, original_message, corruption_probability);
    }

    // Clear mem
    for (Algorithm* algorithm : correcting_algorithms) {
        delete algorithm;
    }

    return 0;
}