//
// Created by Robi on 3/22/2024.
//

#include "Repository.h"
#include "Exceptions.h"
#include <fstream>
#include <iostream>
Repository::Repository() {

}

Repository::Repository(const std::string& Filename , const std::string& read) : fileName(Filename){
    if (read == "read") {
        this->read_from_file();
    }
}

void Repository::add_repository(std::string title, std::string presenter, int duration,
                                int likes, std::string link){
    Tutorial elem = Tutorial{title , presenter , duration , likes , link};

    for (auto & it : this->repo_array){
        if (it.get_link() == link)
            throw RepositoryException("A tutorial with this link already exits!");
    }
    this->repo_array.push_back(elem);
    this->write_to_file();
}

void Repository::update_repository(std::string old_link , std::string title , std::string presenter, int duration,int likes, std::string link){
    Tutorial elem = Tutorial{title , presenter , duration , likes , link};

    int found = 0;
    for (auto it = this->repo_array.begin() ; it != this->repo_array.end() ; ++it){
        if (it->get_link() == old_link){
            *it = elem;
            found = 1;
        }
    }

    if (found == 0)
        throw RepositoryException("There is no tutorial with this link!");
    this->write_to_file();
}

void Repository::delete_repository(std::string link) {

    int found = 0;
    for (auto it = this->repo_array.begin() ; it != this->repo_array.end() ; ++it){
        if (it->get_link() == link){
            this->repo_array.erase(it);
            found = 1;
            break;
        }
    }

    if (found == 0)
        throw RepositoryException("There is no tutorial with this link!");

    this->write_to_file();
}

std::vector<Tutorial> Repository::get_tutorials() {
    return this->repo_array;
}

Tutorial Repository::get_tutorial_by_link(std::string link) {
    int found = 0;
    for (auto it = this->repo_array.begin() ; it != this->repo_array.end() ; ++it){
        if (it->get_link() == link){
            found = 1;
            return *it;
        }
    }
//TODO throw exception if the element does not exist
    throw RepositoryException("There is no tutorial with this link!");
}

void Repository::read_from_file() {
    std::ifstream fin(this->fileName);
    if(fin.is_open()){
        char title[256];
        char presenter[256];
        char link[256];
        int duration, likes;
        char comma;
        while (true){
            if(!fin.getline(title , 256 , ','))
                break;
            fin.getline(presenter , 256 ,',');
            fin >> duration >> comma;
            fin >> likes >> comma;
            if(!fin.getline(link , 256 ,'\n'))
                break;

            Tutorial elem = Tutorial{title , presenter , duration , likes , link};
            this->repo_array.push_back(elem);
        }
    }
    fin.close();
}

void Repository::write_to_file() {
    std::ofstream fout(this->fileName);
    if (!fout.is_open())
        throw FileException("File could not open!");
    for (auto it = this->repo_array.begin() ; it != this->repo_array.end() ; ++it){
        fout << it->get_title() <<",";
        fout << it->get_presenter() <<",";
        fout << it->get_duration() <<",";
        fout << it->get_likes() <<",";
        fout << it->get_link() <<"\n";
    }
    fout.close();
}

Repository::~Repository() = default;
