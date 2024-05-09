//
// Created by Robi on 4/19/2024.
//

#include "Exceptions.h"

RepositoryException::RepositoryException(const std::string& message) : error_message(message) {}

const char *RepositoryException::what()  const noexcept{
    return this->error_message.c_str();
}

InputException::InputException(const std::string& message) : error_message(message){}

const char* InputException::what() const noexcept{
    return this->error_message.c_str();
}

FileException::FileException(const std::string &message) : error_message(message){}

const char *FileException::what() const noexcept {
    return this->error_message.c_str();
}
