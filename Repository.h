//
// Created by Robi on 3/22/2024.
//

#ifndef OOP_A4_5_LELIUCROBERT_REPOSITORY_H
#define OOP_A4_5_LELIUCROBERT_REPOSITORY_H


#include "DynamicArray.h"
#include <vector>

class Repository {
    protected:
//        DynamicArray<Tutorial> repo_array;
        std::vector <Tutorial> repo_array;
        std::string fileName;
    public:
        Repository();
        Repository(const std::string& Filename , const std::string& read);
        virtual std::vector<Tutorial> get_tutorials();
        void read_from_file();
        virtual void write_to_file();
        void add_repository(std::string title, std::string presenter, int duration,
                            int likes, std::string link);
        void update_repository(std::string old_link , std::string title,
                               std::string presenter, int duration,int likes, std::string link);
        void delete_repository(std::string link);
        Tutorial get_tutorial_by_link(std::string link);
        ~Repository();


};


#endif //OOP_A4_5_LELIUCROBERT_REPOSITORY_H
