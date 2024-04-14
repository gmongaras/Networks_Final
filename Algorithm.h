#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
#include <vector>

// pure virtual class so that it can be inherited by other classes
class Algorithm {
public:
    // Prep takes a copy of a message and returns a new message with added
    // bits for error correction/detection.
    virtual std::string prep(const std::string message) = 0;

    // Takes a copy of a message and returns the corrected message.
    virtual std::string correct(const std::string message) = 0;

    // Takes a copy of a message and returns bits corresponding to
    // which parts of the message are incorrect.
    virtual std::string detect(const std::string message) = 0;

    // Used to calculate the error rate of the detection algorithm.
    virtual float calculate_error_rate_detect(const std::string detected_errors) = 0;
};

#endif // ALGORITHM_H