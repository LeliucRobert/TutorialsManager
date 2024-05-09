//
// Created by Robi on 4/19/2024.
//

#include <iostream>
#include "CSV_Repository.h"
#include "Exceptions.h"


CSV_Repository::CSV_Repository(const std::string& filename) : Repository(filename , "noread") {

}

void CSV_Repository::write_to_file() {
    std::ofstream fout(this->fileName);
    if (!fout.is_open())
        throw FileException("File could not open!");
    for (auto & it : this->repo_array){
        fout << it.get_title() <<",";
        fout << it.get_presenter() <<",";
        fout << it.get_duration() <<",";
        fout << it.get_likes() <<",";
        fout << it.get_link() <<"\n";
    }
    fout.close();
}

std::vector<Tutorial> CSV_Repository::get_tutorials() {
    std::string path = this->fileName;
//    std::string command = "\"C:\\Program Files\\Microsoft Office\\root\\Office16\\EXCEL.EXE\" ";
//    command += path;
//    system(command.c_str());
    return this->repo_array;
}
