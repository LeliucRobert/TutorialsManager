//
// Created by Robi on 3/22/2024.
//

#include "UI.h"

#include <cstring>

#include <windows.h>

UI::UI(Controller& controller1, Controller& controllerWatchList1): controller(controller1), controller_watch_list(controllerWatchList1) {

}

void UI::print_welcome() {
    std::cout << "--------------------------------------------------\n"
           "* Hello! Welcome to the Master C++ Application!* \n"
           "--------------------------------------------------\n";
    std::cout << "Would you like to enter as an administrator(1) , user(2) , or to exit(0) ?\n\n\n";
}

void UI::print_admin_options(){
    std::cout << "\n\n\n-------Admin mode------\n"
                 "1. Add a new tutorial\n"
                 "2. Delete a tutorial\n"
                 "3. Update a tutorial\n"
                 "4. See all the tutorials\n"
                 "0. Exit\n\n";
}

void UI::print_user_options(){
    std::cout << "\n\n\n-------User mode------\n"
                 "1. Browse through the tutorials having a given presenter\n"
                 "2. Delete a tutorial from the watch list\n"
                 "3. See the watch list\n"
                 "0. Exit\n";
}

void UI::user_mode(){

    while (true) {
        int option = 0;
        std::string str_option;
        NumberValidator number_validate;

        this->print_user_options();


        std::cout << ">";
        std::getline(std::cin, str_option);

        check_input(str_option, number_validate);

        option = std::stoi(str_option);
        if (option == 0)
            break;
        else{
            switch (option) {
                case 1:
                    this->browse_tutorials();
                    break;
                case 2:
                    this->delete_tutorial_from_watch_list();
                    break;
                case 3:
                    this->see_tutorials_from_watch_list();
                    break;
                default:
                    throw InputException("Invalid input!\n\n");
            }
        }
    }
}

void UI::browse_tutorials(){
    std::string name;
    std::cout << "Enter the name of the presenter:";
    std::getline(std::cin , name);
    std::vector<Tutorial> arr;
    arr = this->controller.get_tutorials();
    for (int i = 0 ; i < arr.size() ; i++){
        if ((arr[i].get_presenter() == name) || (name.empty())){
        std::cout << "\nTitle: " << arr[i].get_title();
        std::cout << "\nPresenter: " << arr[i].get_presenter();
        std::cout << "\nDuration: " << arr[i].get_duration() << " minutes";
        std::cout << "\nLikes: " << arr[i].get_likes();
        std::cout << "\nLink: " << arr[i].get_link();

        ShellExecute(NULL, L"open", reinterpret_cast<LPCWSTR>(arr[i].get_link().c_str()), NULL, NULL, SW_SHOWNORMAL);


        while(1) {
            std::string input;
            std::cout << "\n\n\nDo you want to add the tutorial to the watch list?(yes/no)";
            std::getline(std::cin, input);
            if (input == "yes" or input == "YES") {
                this->controller_watch_list.add_controller(arr[i].get_title(), arr[i].get_presenter(),
                                                           arr[i].get_duration(), arr[i].get_likes(),
                                                           arr[i].get_link());
                std::cout << "\nTutorial succsessfully added to the watch list!";
                break;
            }
            else if (input == "no" or input == "NO")
                break;
            else
                std::cout <<"\nInvalid option!";
        }
        
        while(1) {
            std::string input;
            std::cout << "\nWould you like to see the next tutorial?(yes/no)";
            std::getline(std::cin, input);
            if (input == "yes" or input == "YES") {
                if (i == arr.size() - 1)
                    i = 0;
                break;
            }
            else if (input == "no" or input == "NO")
                return;
            else
                std::cout <<"\nInvalid option!";
        }
        }

    }

}

void UI::delete_tutorial_from_watch_list(){
    char link[256];
    std::cout << "\nEnter the link of the tutorial you want to remove:";
    std::cin.getline(link , 256);
    LinkValidator link_validator;
    check_input(link , link_validator);

    this->controller_watch_list.delete_controller(link);
    std::cout <<"\nTutorial successfully removed from watch list!";

    std::string input;
    std::cout <<"\nDid you like the tutorial?(yes/no):";

    std::getline(std::cin, input);
    if (input == "yes" or input == "YES") {
        Tutorial tutorial = this->controller.get_tutorial(link);
        this->controller.update_controller(link , tutorial.get_title() ,
                                           tutorial.get_presenter() , tutorial.get_duration() ,
                                           tutorial.get_likes() + 1 , tutorial.get_link());
    }
    else
        throw InputException("Only yes or no!!!");
}

void UI::see_tutorials_from_watch_list() {
    std::vector<Tutorial> arr;
    arr = this->controller_watch_list.get_tutorials();

    std::cout << "-----Watch List------\n\n";

    for (int i = 0 ; i < arr.size() ; i++){
        std::cout << "\n\n\n\n------Tutorial number "<<i <<"------";
        std::cout << "\nTitle: " << arr[i].get_title();
        std::cout << "\nPresenter: " << arr[i].get_presenter();
        std::cout << "\nDuration: " << arr[i].get_duration() << " minutes";
        std::cout << "\nLikes: " << arr[i].get_likes();
        std::cout << "\nLink: " << arr[i].get_link();
    }
}



void UI::admin_mode(){

    while (true) {
        int option = 0;
        this->print_admin_options();
        try {
            std::cout << ">";
            std::cin >> option;
            if(std::cin.fail()){
                std::cin.clear();
                std::cin.ignore(255 , '\n');
                throw std::exception();
            }
            std::cin.ignore(255, '\n');
        }
        catch(...){
            std::cout<<"\nInvalid input!\n\n";
            continue;
        }
        if (option == 0)
            break;
        else{
            switch (option) {
                case 1:
                    this->add_tutorial();
                    break;
                case 2:
                    this->delete_tutorial();
                    break;
                case 3:
                    this->update_tutorial();
                    break;
                case 4:
                    this->see_tutorials();
                    break;
            }
        }
    }
}

void UI::add_tutorial(){

    std::string old_link;
    std::string title;
    std::string presenter;
    std::string str_duration;
    std::string str_likes;
    std::string link;

    NumberValidator number_validator;
    LinkValidator link_validator;


    std::cout << "Enter the new title:";
    std::getline(std::cin , title);


    std::cout << "Enter the new presenter:";
    std::getline(std::cin , presenter);


    std::cout << "Enter the duration(minutes):";
    std::getline(std::cin , str_duration);
    check_input(str_duration , number_validator);


    std::cout << "Enter the new number of likes:";
    std::getline(std::cin , str_likes);
    check_input(str_likes , number_validator);

    std::cout << "Enter the link:";
    std::getline(std::cin , link);
    check_input(link , link_validator);


    int duration = stoi(str_duration);
    int likes = stoi(str_likes);


    this->controller.add_controller(title, presenter, duration, likes, link);
    std::cout <<"\nTutorial successfully addes!";
}

void UI::delete_tutorial(){
    std::string link;
    LinkValidator link_validator;

    std::cout << "\nEnter the link of the tutorial you want to remove:";
    std::getline(std::cin , link);
    check_input(link , link_validator);


    this->controller.delete_controller(link);
    std::cout <<"\nTutorial successfully removed!";

}

void UI::update_tutorial(){
    std::string old_link;
    std::string title;
    std::string presenter;
    std::string str_duration;
    std::string str_likes;
    std::string link;

    NumberValidator number_validator;
    LinkValidator link_validator;

    std::cout << "\nEnter the link of the tutorial you want to update:";
    std::getline(std::cin , old_link);
    check_input(old_link , link_validator);

    std::cout << "Enter the new title:";
    std::getline(std::cin , title);


    std::cout << "Enter the new presenter:";
    std::getline(std::cin , presenter);


    std::cout << "Enter the duration(minutes):";
    std::getline(std::cin , str_duration);
    check_input(str_duration , number_validator);

    std::cout << "Enter the new number of likes:";
    std::getline(std::cin , str_likes);
    check_input(str_likes , number_validator);


    std::cout << "Enter the new link:";
    std::getline(std::cin , link);
    check_input(link , link_validator);

    int duration = stoi(str_duration);
    int likes = stoi(str_likes);


    this->controller.update_controller(old_link, title, presenter, duration, likes, link);
    std::cout <<"\nTutorial successfully updated!";

}

void UI::see_tutorials(){
    std::vector<Tutorial> arr;
    arr = this->controller.get_tutorials();
    for (int i = 0 ; i < arr.size() ; i++){
        std::cout << "\n\n\n\n------Tutorial number "<<i <<"------";
        std::cout << "\nTitle: " << arr[i].get_title();
        std::cout << "\nPresenter: " << arr[i].get_presenter();
        std::cout << "\nDuration: " << arr[i].get_duration() << " minutes";
        std::cout << "\nLikes: " << arr[i].get_likes();
        std::cout << "\nLink: " << arr[i].get_link();
    }
}


void UI::start_app(){

    while(true){
        this->print_welcome();
        std::string str_option;
        try {
            NumberValidator number_validate;
            std::cout << ">";
            std::getline(std::cin, str_option);

            check_input(str_option, number_validate);

            int option = std::stoi(str_option);
            if (option == 0)
                break;
            switch (option) {
                case 1:
                    this->admin_mode();
                    break;
                case 2:
                    this->user_mode();
                    break;
                default:
                    throw InputException("Invalid input!\n\n");
            }
        }
        catch(std::exception& e){
            std::cout << e.what();
            continue;
        }

    }
}

void UI::check_input(const std::string& data , Validator& validator) {
    if (validator.validate(data) == 1)
        return;
    throw InputException("Invalid input!\n\n");
}

