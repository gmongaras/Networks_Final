#include "Detect_Algorithm5.h"

Detect_Algorithm5::Detect_Algorithm5() {
}

Detect_Algorithm5::~Detect_Algorithm5() {
}

std::string Detect_Algorithm5::prep(const std::string message) {
    algorithm_name = "Cyclic Redundancy Check";
    key = 0b11011101;
    keyLength = 8;
    std::string expanded_message = message;
    std::string prepped_message = "";
    int extra_padding = message.size() % 3;
    for(int i = 0; i < extra_padding; i++){
        expanded_message.append(" ");
    }

    for (int i = 0; i < expanded_message.size(); i += 3) {
        int divisor = expanded_message[i + 2];
        divisor = divisor << 8;
        divisor |= expanded_message[i + 1];
        divisor = divisor << 8;
        divisor |= expanded_message[i];
        char remainder = modulo2div(divisor, key, 24, keyLength);
        prepped_message.append(1u, message[i]);
        prepped_message.append(1u, message[i + 1]);
        prepped_message.append(1u, message[i + 2]);
        prepped_message.append(1u, remainder);
    }
    return prepped_message;
}

std::vector<bool> Detect_Algorithm5::detect(const std::string message) {
    std::vector<bool> detected_errors;

    for (int i = 0; i < message.size(); i += 4) {
        int divisor = message[i + 2];
        divisor = divisor << 8;
        divisor |= message[i + 1];
        divisor = divisor << 8;
        divisor |= message[i];
        char remainder = modulo2div(divisor, key, 24, keyLength);
//        std::cout << message[i] << message[i + 1] << message[i + 2] << std::endl;
//        std::bitset<24> x(divisor);
//        std::cout << x << '\n';
//        std::bitset<8> y(message[i + 3]);
//        std::cout << y << '\n';
//        std::bitset<8> z(remainder);
//        std::cout << z << '\n';
        if (remainder == message[i + 3]){
            detected_errors.push_back(false);
        }
        else {
            detected_errors.push_back(true);
        }
    }
    return detected_errors;
}


std::vector<float> Detect_Algorithm5::calculate_error_rate_detect(const std::string original_message, const std::string corrupted_message, const std::vector<bool> detected_errors) {
    // If the frame is detected as incorrect, return no error
    if (detected_errors[0] == false){
        return {};
    }

    // Iterate over the string and see how many are incorrect
    int error_count = 0;
    for (int i = 0; i < original_message.size(); i++) {
        if (original_message[i] != corrupted_message[i]) {
            error_count++;
        }
    }
    return {static_cast<float>(error_count) / original_message.size()};
}


std::string Detect_Algorithm5::remove_correct_frames(const std::vector<bool> detected_errors, const std::string corrupted_message, const std::string prepared_message) {
    std::string trimmed_message = "";
    for(int i = 0; i < detected_errors.size(); i++){
        if (detected_errors[i] == true){
            trimmed_message.append(prepared_message.substr((i * 4), 4));
        }
    }
    return trimmed_message;
}

unsigned char Detect_Algorithm5::modulo2div(unsigned int data, unsigned char key, int datalen, int keylen){
    data = data << keylen;
    unsigned int finalBit = 1 << ((datalen + keylen) - 1);

    unsigned int tempKey = 0;
    for(int i = datalen + keylen; i >= (keylen * 2); i--){
        if (data & finalBit){
            tempKey = key << (i - keylen);
        }
        else {
            tempKey = 0;
        }
        // Uncomment this to show your work
//        std::bitset<32> x(data);
//        std::cout << x << '\n';
//        std::bitset<32> z(finalBit);
//        std::cout << z << '\n';
//        std::bitset<32> y(tempKey);
//        std::cout << y << '\n';
//        std::cout << "________" << std::endl;
        data ^= tempKey;
        finalBit /= 2;
    }

    unsigned char remainder = (data >> 8);
    return remainder;
}

