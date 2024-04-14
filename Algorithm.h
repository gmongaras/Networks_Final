#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
#include <vector>

// pure virtual class so that it can be inherited by other classes
class Algorithm {
public:
    // Every algorithm needs a name
    std::string algorithm_name;

    // Prep takes a copy of a message and returns a new message with added
    // bits for error correction/detection.
    virtual std::string prep(const std::string message) = 0;

    // Takes a copy of a message and returns the corrected message.
    virtual std::string correct(const std::string message) = 0;

    // Takes a copy of a message and returns bits corresponding to
    // which parts of the message are incorrect.
    virtual std::vector<bool> detect(const std::string message) = 0;

    // Used to calculate the per-frame error rate (how many bits are incorrect) for frames detected as correct.
    virtual std::vector<float> calculate_error_rate_detect(const std::string original_message, const std::string corrupted_message, const std::vector<bool> detected_errors) = 0;

    // Given a message and the detected errors, this function is used to
    // remove the frames that are correct and return the message with
    // only the frames that have a detected error.
    virtual std::string remove_correct_frames(const std::string message, const std::vector<bool> detected_errors) = 0;
};

#endif // ALGORITHM_H