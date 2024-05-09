//
// Created by Robi on 3/22/2024.
//

#ifndef OOP_A4_5_LELIUCROBERT_CONTROLLER_H
#define OOP_A4_5_LELIUCROBERT_CONTROLLER_H


#include "Repository.h"

class Controller {
    private:
        Repository& repository;
    public:
        Controller(Repository& repository);
        void add_controller(std::string title, std::string presenter, int duration,
                            int likes, std::string link);

        void update_controller(std::string old_link , std::string title, std::string presenter, int duration,
                        int likes, std::string link);

        void delete_controller(std::string link);

        Tutorial get_tutorial(std::string link);

        std::vector<Tutorial> get_tutorials();
};


#endif //OOP_A4_5_LELIUCROBERT_CONTROLLER_H
