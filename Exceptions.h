//
// Created by Robi on 4/19/2024.
//

#ifndef OOP_A4_5_LELIUCROBERT_EXCEPTIONS_H
#define OOP_A4_5_LELIUCROBERT_EXCEPTIONS_H


#include <exception>
#include <string>


class RepositoryException : public std::exception {

private:
    const std::string error_message;
public:
    RepositoryException(const std::string& message);
    const char* what() const noexcept override;
};

class InputException : public std::exception {
private:
    const std::string error_message;
public:
    InputException(const std::string& message);
    const char* what() const noexcept override;
};

class FileException : public std::exception {
private:
    const std::string error_message;
public:
    FileException(const std::string& message);
    const char* what() const noexcept override;
};

#endif //OOP_A4_5_LELIUCROBERT_EXCEPTIONS_H
