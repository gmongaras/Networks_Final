#include <bitset>
#include "Correct_Algorithm3.h"

Correct_Algorithm3::Correct_Algorithm3() {
}

Correct_Algorithm3::~Correct_Algorithm3() {
}

std::string Correct_Algorithm3::prep(const std::string message) {
    algorithm_name = "Binary convolutional codes";
    std::string prepped_message;

    // Triple bits stuffing
    for (int i = 0; i < message.size(); i++) {
        std::string convoluted_string = convolution(message[i]);
        std::cout << convoluted_string;
        prepped_message.push_back(message[i]);
        prepped_message.push_back(message[i]);
        prepped_message.push_back(message[i]);
    }
    std::cout << std::endl;
    return prepped_message;
}

std::string Correct_Algorithm3::correct(const std::string message) {
    std::string corrected_message;

    // Push back each character if it appears as a majority of the representations
    for (int i = 0; i < message.size(); i+=3) {
        if (message[i] == message[i + 1] || message[i] == message[i + 2]){
            corrected_message.push_back(message[i]);
        }
        else if (message[i + 1] == message[i + 2]){
            corrected_message.push_back(message[i + 1]);
        }
        else {
            // If they are all different, just pick the first one
            corrected_message.push_back(message[i]);
        }
    }

    return corrected_message;
}

std::string Correct_Algorithm3::convolution(char shift){
    //std::cout << shift;
    char parity1 = 0, parity2 = 0, parity3 = 0;
    char temp_parity1 = 0, temp_parity2 = 0, temp_parity3 = 0;
    char shift_register = 0;
    for (int i = 0; i < 8; i++){
        shift_register = shift & 0b00000111;
        if (shift_register == 0b00000101 || shift_register == 0b00000011 || shift_register == 0b00000110){
            temp_parity1 = 0;
        }
        else {
            temp_parity1 = 1;
        }

        shift_register = shift & 0b00000011;
        if (shift_register == 0b00000011 || shift_register == 0b00000000){
            temp_parity2 = 0;
        }
        else {
            temp_parity2 = 1;
        }

        shift_register = shift & 0b00000101;
        if (shift_register == 0b00000101 || shift_register == 0b00000000){
            temp_parity3 = 0;
        }
        else {
            temp_parity3 = 1;
        }
        parity1 |= (temp_parity1 << i);
        parity2 |= (temp_parity2 << i);
        parity3 |= (temp_parity3 << i);

        shift = shift >> 1;
    }

    //std::cout << std::bitset<8>(parity1) << std::endl;
    //std::cout << std::bitset<8>(parity2) << std::endl;
    //std::cout << std::bitset<8>(parity3) << std::endl;
    // Convert it all back into a string
    char returning_char[3] = {parity1, parity2, parity3};
    std::string returning = returning_char;
    return returning;
}