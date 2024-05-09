//
// Created by Robi on 4/19/2024.
//

#ifndef OOP_A4_5_LELIUCROBERT_VALIDATOR_H
#define OOP_A4_5_LELIUCROBERT_VALIDATOR_H


#include <string>

class Validator {
public:
        virtual bool validate(const std::string& data) = 0;
        virtual ~Validator();
};

class LinkValidator : public Validator {
public:
    bool validate(const std::string& email) override;
};

class NumberValidator : public Validator {
public:
    bool validate(const std::string& number) override;
};
#endif //OOP_A4_5_LELIUCROBERT_VALIDATOR_H
