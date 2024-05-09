//
// Created by Robi on 3/22/2024.
//

#include "Domain.h"

Tutorial::Tutorial(std::string title, std::string presenter, int duration, int likes, std::string link){
    this->duration = duration;
    this->likes = likes;
    this->title = title;
    this->presenter = presenter;
    this->link = link;
}

Tutorial::Tutorial() {
    this->duration = 0;
    this->likes = 0;
    this->title = "0";
    this->presenter = "0";
    this->link = "0";
}

//Getters

int Tutorial::get_likes() const{
    return this->likes;
}

int Tutorial::get_duration() const{
    return this->duration;
}

std::string Tutorial::get_title() {
    return this->title;
}

std::string Tutorial::get_presenter() {
    return this->presenter;
}

std::string Tutorial::get_link() {
    return this->link;
}

//Setters

void Tutorial::set_likes(int likes){
    this->likes = likes;
}
void Tutorial::set_duration(int duration){
    this->duration = duration;
}
void Tutorial::set_title(std::string title){
    this->title = title;
}
void Tutorial::set_presenter(std::string presenter){
    this->presenter = presenter;
}
void Tutorial::set_link(std::string link){
    this->link = link;
}