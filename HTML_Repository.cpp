//
// Created by Robi on 4/20/2024.
//

#include <fstream>
#include <windows.h>

#include <iostream>

#include "HTML_Repository.h"
#include "Exceptions.h"

HTML_Repository::HTML_Repository(const std::string filename) : Repository(filename , "noread"){

}

void HTML_Repository::write_to_file() {

    std::ofstream fout(this->fileName);
    if (!fout.is_open())
        throw FileException("File could not open!");
    fout << "<!DOCTYPE html> <html> <head> <title> Movie WatchList</title> </head > <body> <table border=\1\>";
    fout << "<tr> <td> Title </td> <td> Presenter </td> <td> Duration </td> <td> Likes </td> <td> Link </td> </tr>";
    for (auto it : this->repo_array) {
        fout << "<tr> <td>" << it.get_title() << "</td> <td>" << it.get_presenter() << "</td> <td>" << it.get_duration()
             << "</td> <td>" << it.get_likes() << "</td> <td> <a href=\""<< it.get_link() << "\"> Link</a></ td> </tr>";
    }
    fout << "</table>\n"
            "</body>\n"
            "</html>";
}

std::vector<Tutorial> HTML_Repository::get_tutorials() {



    ShellExecute(NULL, L"open", reinterpret_cast<LPCWSTR>(this->fileName.c_str()), NULL, NULL, SW_SHOWNORMAL);
    return this->repo_array;
}
