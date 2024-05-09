//
// Created by Robi on 3/23/2024.
//

#include <cassert>
#include "Tests.h"
#include "Domain.h"
#include "Repository.h"
#include "Controller.h"
#include <iostream>

void test_domain() {
    Tutorial elem {"c++" , "andrei" , 60 , 155 , "yt.c++"};
    assert(elem.get_title() == "c++");
    assert(elem.get_presenter() == "andrei");
    assert(elem.get_duration() == 60);
    assert(elem.get_likes() == 155);
    assert(elem.get_link() == "yt.c++");

    elem.set_title("A C++");
    assert(elem.get_title() == "A C++");

    elem.set_presenter("Bje");
    assert(elem.get_presenter() == "Bje");

    elem.set_duration(120);
    assert(elem.get_duration() == 120);

    elem.set_likes(200);
    assert(elem.get_likes() == 200);

    elem.set_link("yt.advanced_cpp");
    assert(elem.get_link() == "yt.advanced_cpp");

    Tutorial elem2;
    assert(elem2.get_title() == "0");
    assert(elem2.get_presenter() == "0");
    assert(elem2.get_duration() == 0);
    assert(elem2.get_likes() == 0);
    assert(elem2.get_link() == "0");

}

void test_repository(){
    Repository repo("test_data.txt" , "read");
    repo.add_repository("C++ ", "Andrei", 60, 100, "cpp.com");

    std::vector<Tutorial> tutorials = repo.get_tutorials();
    assert(tutorials.size() == 1);


    assert(tutorials[0].get_title() == "C++ ");
    assert(tutorials[0].get_presenter() == "Andrei");
    assert(tutorials[0].get_duration() == 60);
    assert(tutorials[0].get_likes() == 100);
    assert(tutorials[0].get_link() == "cpp.com");

    repo.update_repository("cpp.com", "Advanced C++", "Andrei Alexandrescu", 120, 200, "adv_cpp.com");
    tutorials = repo.get_tutorials();
    assert(tutorials[0].get_title() == "Advanced C++");
    assert(tutorials[0].get_presenter() == "Andrei Alexandrescu");
    assert(tutorials[0].get_duration() == 120);
    assert(tutorials[0].get_likes() == 200);
    assert(tutorials[0].get_link() == "adv_cpp.com");

    Tutorial tutorial = repo.get_tutorial_by_link("adv_cpp.com");
    assert(tutorial.get_title() == "Advanced C++");
    assert(tutorial.get_presenter() == "Andrei Alexandrescu");
    assert(tutorial.get_duration() == 120);
    assert(tutorial.get_likes() == 200);
    assert(tutorial.get_link() == "adv_cpp.com");

    try {
        repo.get_tutorial_by_link("cpp.com");
        assert(false);
    }
    catch(...){
        assert(true);
    }

    repo.delete_repository("adv_cpp.com");
    tutorials = repo.get_tutorials();
    assert(tutorials.size() == 0);

}

void test_dynamic_array(){
    DynamicArray<Tutorial> array;
    Tutorial tutorial1("C++ for Beginners", "John Doe", 30, 100, "link.com");
    array.add_element(tutorial1);

    assert(array.get_size() == 1);
    assert(array[0].get_link() == "link.com");

    bool exist = false;
    try {
        array.add_element(tutorial1);
    } catch (...) {
        exist = true;
    }
    assert(exist);

    Tutorial tutorial2("Advanced C++", "Jane Doe", 60, 200, "link2.com");
    array.update_element("link.com", tutorial2);
    assert(array[0].get_title() == "Advanced C++");
    assert(array[0].get_presenter() == "Jane Doe");
    assert(array[0].get_duration() == 60);
    assert(array[0].get_likes() == 200);

    array.remove_element("link2.com");

    assert(array.get_size() == 0);

    exist = false;
    try {
        array.remove_element("nonexistent");
    } catch (...) {
        exist = true;
    }
    assert(exist);
}

void test_controller(){
    Repository repo{"test_data.txt" , "noread"};
    Controller ctrl(repo);
    ctrl.add_controller("C++ Basics", "Jane Doe", 120, 150, "link.com");

    std::vector<Tutorial> tutorials = ctrl.get_tutorials();
    assert(tutorials.size() == 1);
    assert(tutorials[0].get_title() == "C++ Basics");
    assert(tutorials[0].get_presenter() == "Jane Doe");

    ctrl.update_controller("link.com", "Advanced C++", "John Doe", 180, 250, "link2.com");
    tutorials = ctrl.get_tutorials();
    assert(tutorials.size() == 1);
    assert(tutorials[0].get_title() == "Advanced C++");
    assert(tutorials[0].get_presenter() == "John Doe");

    Tutorial tutorial = ctrl.get_tutorial("link2.com");
    assert(tutorial.get_title() == "Advanced C++");
    assert(tutorial.get_presenter() == "John Doe");
    assert(tutorial.get_duration() == 180);
    assert(tutorial.get_likes() == 250);
    assert(tutorial.get_link() == "link2.com");


    ctrl.delete_controller("link2.com");

    tutorials = ctrl.get_tutorials();
    assert(tutorials.size() == 0);


}


void test_all(){
    test_domain();
//    test_repository();
    test_dynamic_array();
    test_controller();
}