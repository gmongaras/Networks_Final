#include "Detect_Algorithm1.h"

Detect_Algorithm1::Detect_Algorithm1() {
}

Detect_Algorithm1::~Detect_Algorithm1() {
}

std::string Detect_Algorithm1::prep(const std::string message) {

    algorithm_name = "Single Parity Bit";
    parityBit = false;
    for (int i = 0; i < message.size(); i++) {
        char check_character = message[i];
        if (getParityBit(check_character)){
            parityBit != parityBit;
        }
    }

    return message;
}

std::string Detect_Algorithm1::detect(const std::string message) {
    checkedParityBit = false;
    for (int i = 0; i < message.size(); i++) {
        char check_character = message[i];
        if (getParityBit(check_character)){
            checkedParityBit = !checkedParityBit;
        }
    }
    if (checkedParityBit == parityBit){
        return "true";
    }
    else{
        return "false";
    }
}


float Detect_Algorithm1::calculate_error_rate_detect(const std::string detected_errors) {
    if (detected_errors == "false"){
        return 0.0f;
    }
    else {
        return 1.0f;
    }
}


bool Detect_Algorithm1::getParityBit(char n){
    bool parity = 0;
    while (n)
    {
        parity = !parity;
        n &= (n - 1);
    }
    return parity;
}