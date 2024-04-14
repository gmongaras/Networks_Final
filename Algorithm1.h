/*

Simple triple bits stuffing
message: 01001
preped: 000 111 000 0000 111


*/



#ifndef ALGORITHM1_H
#define ALGORITHM1_H

#include <iostream>

#include "Algorithm.h"

class Algorithm1 : public Algorithm {
public:
    Algorithm1();
    virtual ~Algorithm1();

    std::vector<bool> prep(const std::vector<bool> message) override;
    std::vector<bool> run(const std::vector<bool> message) override;
};

#endif // ALGORITHM1_H