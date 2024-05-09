//
// Created by Robi on 3/22/2024.
//

#include "Controller.h"

Controller::Controller(Repository& repository) : repository(repository){
//    this->repository = repository;
}

void Controller::add_controller(std::string title, std::string presenter, int duration,int likes, std::string link) {

    this->repository.add_repository(title , presenter , duration , likes , link);
}

void Controller::update_controller(std::string old_link , std::string title, std::string presenter, int duration, int likes, std::string link){
    this->repository.update_repository(old_link , title , presenter , duration , likes , link);
}

void Controller::delete_controller(std::string link) {
    this->repository.delete_repository(link);
}

std::vector<Tutorial> Controller::get_tutorials(){
    return this->repository.get_tutorials();
}

Tutorial Controller::get_tutorial(std::string link){
    return this->repository.get_tutorial_by_link(link);
}

