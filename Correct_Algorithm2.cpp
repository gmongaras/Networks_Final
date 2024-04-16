#include "Correct_Algorithm2.h"

Correct_Algorithm2::Correct_Algorithm2() {
}

Correct_Algorithm2::~Correct_Algorithm2() {
}

std::string Correct_Algorithm2::prep(const std::string message) {
    algorithm_name = "Quintuple Bit Packing";
    std::string prepped_message;

    // Triple bits stuffing
    for (int i = 0; i < message.size(); i++) {
        prepped_message.push_back(message[i]);
        prepped_message.push_back(message[i]);
        prepped_message.push_back(message[i]);
        prepped_message.push_back(message[i]);
        prepped_message.push_back(message[i]);
    }

    return prepped_message;
}

std::string Correct_Algorithm2::correct(const std::string message) {
    std::string corrected_message;

    // Push back each character if it appears as a majority of the representations
    for (int i = 0; i < message.size(); i += 5) {
        int arr[] = { message[i], message[i + 1], message[i + 2], message[i + 3], message[i + 4]};
        int len = sizeof(arr);
        int n = len / sizeof(arr[0]);
        // Variable to calculate majority element
        int number = 0;

        // Loop to iterate through all the bits of number
        for (int i = 0; i < len; i++) {
            int count = 0;
            // Loop to iterate through all elements in array
            // to count the total set bit
            // at position i from right
            for (int j = 0; j < n; j++) {
                if (arr[j] & (1 << i))
                    count++;
            }
            // If the total set bits exceeds n/2,
            // this bit should be present in majority Element.
            if (count > (n / 2))
                number += (1 << i);
        }

        int count = 0;

        // iterate through array get
        // the count of candidate majority element
        for (int i = 0; i < n; i++)
            if (arr[i] == number)
                count++;

        // Verify if the count exceeds n/2
        if (count > (n / 2))
            corrected_message.push_back(number);
        else
            corrected_message.push_back(message[i]);
    }

    return corrected_message;
}