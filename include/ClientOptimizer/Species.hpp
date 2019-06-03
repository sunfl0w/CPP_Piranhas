#pragma once

#include <vector>

namespace Optimization {
    class Species {
    public:
        std::vector<float> weightData;
        unsigned int weigthDataLenght;
        int toralFitness;
        int age;

        Species(unsigned int weightDataLength) {
            this->weigthDataLenght = weightDataLength;
            this->weightData = std::vector<float>(weightDataLength);
        }
    };
} // namespace Optimization