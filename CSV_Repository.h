//
// Created by Robi on 4/19/2024.
//

#ifndef OOP_A4_5_LELIUCROBERT_CSV_REPOSITORY_H
#define OOP_A4_5_LELIUCROBERT_CSV_REPOSITORY_H


#include "Repository.h"
#include <fstream>

class CSV_Repository : public Repository {
public:
    CSV_Repository(const std::string& filename);
    void write_to_file() override;
    std::vector<Tutorial> get_tutorials() override;

};


#endif //OOP_A4_5_LELIUCROBERT_CSV_REPOSITORY_H
