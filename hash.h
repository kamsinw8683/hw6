#ifndef HASH_H
#define HASH_H

#include <iostream>
#include <cmath>
#include <random>
#include <chrono>

typedef std::size_t HASH_INDEX_T;

struct MyStringHash {
    HASH_INDEX_T rValues[5] { 983132572, 1468777056, 552714139, 984953261, 261934300 };
    MyStringHash(bool debug = true)
    {
        if(false == debug){
            generateRValues();
        }
    }
    // hash function entry point (i.e. this is h(k))
    HASH_INDEX_T operator()(const std::string& k) const
    {
        // Add your code here
        std::vector<HASH_INDEX_T> wordParts(5, 0);
        const int partSize = 6;
        const int totalParts = (k.length() + partSize - 1) / partSize;

        for (int part = 0; part < totalParts; ++part)
        {
            int right = k.length() - partSize * part;
            int left = std::max(0, static_cast<int>(k.length() - partSize * (part + 1)));
            std::string slice = k.substr(left, right - left);

            HASH_INDEX_T partialValue = 0;
            int exp = 0;
            for (int j = slice.length() - 1; j >= 0; --j)
            {
                HASH_INDEX_T num = letterDigitToNumber(slice[j]);
                if (num > 0)
                {
                    partialValue += num * static_cast<HASH_INDEX_T>(std::pow(36, exp));
                }
                ++exp;
            }

            wordParts[4 - part] = partialValue;
        }

        HASH_INDEX_T finalHash = 0;
        for (int i = 0; i < 5; ++i)
        {
            finalHash += rValues[i] * wordParts[i];
            std::cout << "Segment[" << i << "] = " << wordParts[i] << std::endl;
        }

        return finalHash;



    }

    // A likely helper function is to convert a-z,0-9 to an integral value 0-35
    HASH_INDEX_T letterDigitToNumber(char letter) const
    {
        // Add code here or delete this helper function if you do not want it
        if (letter >= 'A' && letter <= 'Z')
        {
            return letter - 'A';
        }
        else if (letter >= 'a' && letter <= 'z')
        {
            return letter - 'a';
        }
        else if (letter >= '0' && letter <= '9')
        {
            return letter - '0' + 26;
        }
        else
        {
            return 0;
        }
    }

    // Code to generate the random R values
    void generateRValues()
    {
        // obtain a seed from the system clock:
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator (seed);  // mt19937 is a standard random number generator

        // Simply call generator() [it has an operator()] to get another random number
        for(int i{ 0 }; i < 5; ++i)
        {
            rValues[i] = generator();
        }
    }
};

#endif
