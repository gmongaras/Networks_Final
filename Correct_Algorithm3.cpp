#include <bitset>
#include "Correct_Algorithm3.h"


#include <iostream>
#include <vector>
#include <bitset>
#include <limits>
#include <algorithm>



Correct_Algorithm3::Correct_Algorithm3() {
}

Correct_Algorithm3::~Correct_Algorithm3() {
}

std::string Correct_Algorithm3::prep(const std::string message) {
    algorithm_name = "Binary convolutional codes";
    std::string prepped_message;

    // Convolutional encoding using convolutionEncoder function
    std::vector<std::vector<int>> filters = {
        {1, 1, 1},  // Filter [111]
        {0, 1, 1},  // Filter [011]
        {1, 0, 1},  // Filter [101]
        {1, 1, 0}   // Filter [110]
    };
    prepped_message = encode(message, filters);

    return prepped_message;
}

std::string Correct_Algorithm3::correct(const std::string message) {
    // Correct the message
    std::vector<std::vector<int>> filters = {
        {1, 1, 1},  // Filter [111]
        {0, 1, 1},  // Filter [011]
        {1, 0, 1},  // Filter [101]
        {1, 1, 0}   // Filter [110]
    };
    return viterbi_decode(message, filters);
}

// Function to convert text to a vector of bits
std::vector<int> Correct_Algorithm3::textToBits(const std::string& text) {
    std::vector<int> bitVector;

    // Convert each character to 8 bits
    for (char c : text) {
        // Get the binary representation of the character
        std::bitset<8> bits(static_cast<unsigned char>(c));

        // Append the bits to the vector
        for (int i = 7; i >= 0; --i) {  // Ensure that bits are added in the correct order (MSB to LSB)
            bitVector.push_back(bits[i]);
        }
    }
    return bitVector;
}

// Function to convert a vector of bits back to text
std::string Correct_Algorithm3::bitsToText(const std::vector<int>& bits) {
    std::string text;
    std::bitset<8> charBits;

    // Ensure the number of bits is a multiple of 8
    if (bits.size() % 8 != 0) {
        std::cerr << "Error: Number of bits is not a multiple of 8." << std::endl;
        return "";
    }

    // Decode each multiple of 8 bits to a character
    for (size_t i = 0; i < bits.size(); i += 8) {
        // Get the bitset for the next character
        for (int j = 0; j < 8; ++j) {
            charBits[7 - j] = bits[i + j];  // Fill bitset from MSB to LSB
        }

        // Decode to a character
        text += static_cast<char>(charBits.to_ulong());
    }

    return text;
}




// Function to encode a bit sequence using given filters
std::string Correct_Algorithm3::encode(const std::string message, const std::vector<std::vector<int>>& filters) {
    // Encode the input string to a vector of integers
    std::vector<int> bits = textToBits(message);

    int n = filters.size(); // Number of outputs
    int k = filters[0].size(); // Number of taps in each filter - size of each filter
    std::vector<std::vector<int>> encoded(n, std::vector<int>(bits.size(), 0));

    // Padded bits array. We need to pad the input bits with k-1 zeros at the beginning
    // so that the convolution can be applied to the first k bits
    std::vector<int> padded_bits(k - 1, 0);
    padded_bits.insert(padded_bits.end(), bits.begin(), bits.end());

    // Apply each filter to the input bit sequence
    for (int i = 0; i < bits.size(); ++i) {
        for (int j = 0; j < n; ++j) {
            int output_bit = 0;
            for (int m = 0; m < k; ++m) {
                output_bit ^= padded_bits[i + m] * filters[j][m];
            }
            encoded[j][i] = output_bit % 2;
        }
    }

    // Interleave outputs for transmission
    std::vector<int> interleaved;
    interleaved.reserve(n * bits.size());
    for (int i = 0; i < bits.size(); ++i) {
        for (int j = 0; j < n; ++j) {
            interleaved.push_back(encoded[j][i]);
        }
    }

    // Convert to a string
    std::string encoded_string = bitsToText(interleaved);

    return encoded_string;
}













// Function to calculate Hamming distance
// This metric is used to determine how similar two bit sequences are
// that is, how far are the convolutional codes from each other
int Correct_Algorithm3::hamming_distance(const std::vector<int>& a, const std::vector<int>& b) {
    int distance = 0;
    for (size_t i = 0; i < a.size(); ++i) {
        if (a[i] != b[i]) {
            distance++;
        }
    }
    return distance;
}

// Decoder function using the Viterbi algorithm
std::string Correct_Algorithm3::viterbi_decode(const std::string message, const std::vector<std::vector<int>>& filters) {
    // Convert the input string to a vector of integers
    std::vector<int> encoded = textToBits(message);

    int n = filters.size();  // Number of filters
    int k = filters[0].size();  // Number of taps in each filter - size of each filter
    int num_states = 1 << (k - 1);  // 2^(k-1) states - number of states in the trellis diagram

    // Transition matrix and next state matrix
    std::vector<std::vector<int>> transitions(num_states * 2, std::vector<int>(n));
    std::vector<std::vector<int>> next_state(num_states * 2, std::vector<int>(2));

    // Generate transitions and next states
    for (int state = 0; state < num_states; ++state) {
        for (int input_bit = 0; input_bit < 2; ++input_bit) {
            int ns = ((state << 1) | input_bit) & (num_states - 1);
            next_state[state * 2 + input_bit] = {ns, ns};
            for (int j = 0; j < n; ++j) {
                int output_bit = 0;
                for (int m = 0; m < k; ++m) {
                    int bit = (state >> (k - m - 2)) & 1;
                    if (m == k - 1) bit = input_bit;
                    output_bit ^= bit * filters[j][m];
                }
                transitions[state * 2 + input_bit][j] = output_bit % 2;
            }
        }
    }




    //// Viterbi algorithm

    // All states have a path metric of infinity representing high cost
    // and that those states are not likely to go to.
    std::vector<double> path_metrics(num_states, std::numeric_limits<double>::infinity());
    // The current state has a path metric of 0 meaning there is no error
    path_metrics[0] = 0;
    std::vector<std::vector<int>> paths(num_states);

    // Iterate over all recieved bits
    for (int i = 0; i < encoded.size(); i += n) {
        // Get the received bits for each filter
        std::vector<int> received_bits(encoded.begin() + i, encoded.begin() + i + n);

        // Create new path metrics and paths
        std::vector<double> new_path_metrics(num_states, std::numeric_limits<double>::infinity());
        std::vector<std::vector<int>> new_paths(num_states);

        // Iterate over all states and inputs
        for (int state = 0; state < num_states; ++state) {
            for (int input_bit = 0; input_bit < 2; ++input_bit) {
                // The next state is determined by the current state and the input bit
                // This means we look at a total of two transition states for each state
                int next = next_state[state * 2 + input_bit][0];
                std::vector<int> output_bits;
                for (int j = 0; j < n; j++){
                    output_bits.push_back(transitions[state * 2 + input_bit][j]);
                }

                // Update the cost for the next state with the new path metric
                double metric = path_metrics[state] + hamming_distance(received_bits, output_bits);

                // If the new path metric is less than the current path metric, update the path
                if (metric < new_path_metrics[next]) {
                    new_path_metrics[next] = metric;
                    new_paths[next] = paths[state];
                    new_paths[next].push_back(input_bit);
                }
            }
        }

        // Swap the path metrics and paths to the new values
        // This is done to avoid copying the values
        path_metrics.swap(new_path_metrics);
        paths.swap(new_paths);
    }

    // Find the best path with the minimum metric
    double min_metric = *std::min_element(path_metrics.begin(), path_metrics.end());
    int best_state = std::distance(path_metrics.begin(), std::find(path_metrics.begin(), path_metrics.end(), min_metric));

    std::vector<int> best_path = paths[best_state];

    // Convert to a string
    std::string decoded_string = bitsToText(best_path);

    return decoded_string;
}