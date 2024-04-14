#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <string>
#include <vector>

// pure virtual class so that it can be inherited by other classes
class Algorithm {
public:
    // Prep takes a copy of a message and returns a new message with added
    // bits for error correction.
    virtual std::vector<bool> prep(const std::vector<bool> message) = 0;

    // Run takes a copy of a message and returns the corrected message.
    virtual std::vector<bool> run(const std::vector<bool> message) = 0;
};

#endif // ALGORITHM_H