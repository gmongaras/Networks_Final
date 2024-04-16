#include <iostream>
#include <chrono>
#include <string>
#include <cstdlib>
#include <ctime>
#include <bitset>
#include <vector>

#include "Algorithm.h"
#include "Correct_Algorithm1.h"
#include "Correct_Algorithm2.h"
#include "Detect_Algorithm1.h"
#include "Detect_Algorithm2.h"


// Corrupt a message based on probability p
std::string corrupt_message(const std::string& message, double p) {
    // New corrupted message
    std::string corrupted = message;

    // Iterate over all bits in the message and corrupt them with probability p
    for (int i = 0; i < corrupted.size(); i++) {
        for(int j = 0; j < 8; j++){
            double rand_prob = static_cast<double>(rand()) / RAND_MAX;
            if (rand_prob < p) {
                corrupted[i] ^= (1 << j);
            }
        }
    }
    return corrupted;
}

void test_correction_algorithm(Algorithm* algorithm, std::string original_message, double corruption_probability) {

    // Prepare the message for error correction
    std::string prepared_message = algorithm->prep(original_message);

    // Corrupt the message
    // srand(time(nullptr)); // Seed random number generator
    std::string corrupted_message = corrupt_message(prepared_message, corruption_probability);

    // Time how long it takes to correct the message
    auto start = std::chrono::high_resolution_clock::now();
    std::string corrected_message = algorithm->correct(corrupted_message);
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double, std::milli> elapsed = end - start;

    // Get the error rate
    int errors = 0;
    for (int i = 0; i < original_message.size(); i++) {
        if (original_message[i] != corrected_message[i]) {
            errors++;
        }
    }
    double error_rate = static_cast<double>(errors) / original_message.size();

    std::cout << "Algorithm name: " << algorithm->algorithm_name << std::endl;
    std::cout << "Prepared message: " << prepared_message << std::endl;
    std::cout << "Corrupted message: " << corrupted_message << std::endl;
    std::cout << "Corrected message: " << corrected_message << std::endl;
    std::cout << "Time taken: " << elapsed.count() << " milliseconds." << std::endl;
    std::cout << "Error rate: " << error_rate << std::endl;
}



void test_detection_algorithm(Algorithm* algorithm, std::string original_message, double corruption_probability) {

    // Prepare the message for error correction
    std::string prepared_message = algorithm->prep(original_message);

    // Iterate until the algorithm has no errors
    bool has_errors = true;
    float total_time = 0.0f;
    std::vector<float> errors;
    while (has_errors) {
        // Corrupt the message
        std::string corrupted_message = corrupt_message(prepared_message, corruption_probability);

        // Time how long it takes to detect errors in the message
        auto start = std::chrono::high_resolution_clock::now();
        std::vector<bool> detected_errors = algorithm->detect(corrupted_message);
        auto end = std::chrono::high_resolution_clock::now();
        std::chrono::duration<double, std::milli> elapsed = end - start;

        // Get the per-frame error
        std::vector<float> new_errors = algorithm->calculate_error_rate_detect(original_message, corrupted_message, detected_errors);
        for (float error : new_errors) {
            errors.push_back(error);
        }

        // After making a detection, remove frames that are correct and
        // keep the frames that have a detected error
        prepared_message = algorithm->remove_correct_frames(corrupted_message, detected_errors);

        // If the length of the prepared message is 0, then there are no more detected errors
        if (prepared_message.size() == 0) {
            has_errors = false;
        }

        // Add the time taken to the total time
        total_time += elapsed.count();
    }

    // Take the mean of the errors
    float mean_error = 0.0f;
    for (float error : errors) {
        mean_error += error;
    }
    mean_error /= errors.size();

    std::cout << "Algorithm name: " << algorithm->algorithm_name << std::endl;
    std::cout << "Time taken: " << total_time << " milliseconds." << std::endl;
    std::cout << "Error rate: " << mean_error << std::endl;
}

int main(int argc, char* argv[]) {
    std::string original_message = "Nya UwU UwU N...nya? ^w^";
    double corruption_probability = 0.01;

    srand(time(nullptr)); // Seed random number generator

    // List of algorithms to test
    Algorithm* correcting_algorithms[] = {
        new Correct_Algorithm1(),
        new Correct_Algorithm1(),
        new Correct_Algorithm2(),
        new Correct_Algorithm2(),
    };
    Algorithm* detecting_algorithms[] = {
        new Detect_Algorithm1(),
        new Detect_Algorithm1(),
        new Detect_Algorithm2(),
        new Detect_Algorithm2()
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