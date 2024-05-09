//
// Created by Robi on 3/22/2024.
//

#ifndef OOP_A4_5_LELIUCROBERT_UI_H
#define OOP_A4_5_LELIUCROBERT_UI_H
#include <iostream>
#include <exception>
#include <cstring>
#include "Controller.h"
#include "Exceptions.h"
#include "Validator.h"

#define MAX_LINK_LEN 60

class UI {
    private:

    Controller controller;
    Controller controller_watch_list;
    public:
        UI(Controller& controller1 , Controller& controller_watch_list1);
        void start_app();
        static void print_welcome();
        static void print_admin_options();
        static void print_user_options();

        void user_mode();
        void browse_tutorials();
        void delete_tutorial_from_watch_list();
        void see_tutorials_from_watch_list();

        void admin_mode();
        void add_tutorial();
        void update_tutorial();
        void delete_tutorial();
        void see_tutorials();

        void check_input(const std::string& data , Validator& validator);
};


#endif //OOP_A4_5_LELIUCROBERT_UI_H
