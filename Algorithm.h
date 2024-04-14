#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
#include <vector>

// pure virtual class so that it can be inherited by other classes
class Algorithm {
public:
    // Prep takes a copy of a message and returns a new message with added
    // bits for error correction/detection.
    virtual std::vector<bool> prep(const std::vector<bool> message) = 0;

    // Takes a copy of a message and returns the corrected message.
    virtual std::vector<bool> correct(const std::vector<bool> message) = 0;

    // Takes a copy of a message and returns bits corresponding to
    // which parts of the message are incorrect.
    virtual std::vector<bool> detect(const std::vector<bool> message) = 0;

    // Used to calculate the error rate of the detection algorithm.
    virtual float calculate_error_rate_detect(const std::vector<bool> corrupted_bits, const std::vector<bool> detected_errors) = 0;
};

#endif // ALGORITHM_H