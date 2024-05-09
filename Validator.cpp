//
// Created by Robi on 4/19/2024.
//

#include <algorithm>
#include "Validator.h"

bool LinkValidator::validate(const std::string &link) {
    return link.find('.') != std::string::npos && link.find("www") != std::string::npos;
}

bool NumberValidator::validate(const std::string &number) {
    return std::all_of(number.begin(), number.end(), ::isdigit);
}

Validator::~Validator() {

}
