#include <mysql.h>
#include "UI.h"
#include "Repository.h"
#include "Controller.h"
#include "Tests.h"
#include "CSV_Repository.h"
#include "HTML_Repository.h"
#include "windows.h"
#include "SQL_Repository.h"
#include "GUI.h"
#include <QtWidgets/QApplication>

int main(int argc , char* argv[]){
//    std::string option;
//    std::cout << "What type of database you want to use?(file/SQL) ";
//    std::getline(std::cin , option);
//        test_all();
//
//    if (option == "file") {
//        Repository repository{"database.txt", "read"};
//        std::cout << "Where do you want to store the watchlist? (memory/html/csv) ";
//        std::getline(std::cin , option);
//        if (option == "memory"){
//            Repository repository_watch_list{"watch_list.csv" , "read"};
//            Controller controller_watch_list{repository_watch_list};
//            Controller controller{repository};
//            UI ui{controller , controller_watch_list};
//            ui.start_app();
//        }
//        else if (option == "html") {
//            HTML_Repository html_repository{"database.html"};
//            Controller controller_watch_list(html_repository);
//            Controller controller{repository};
//            UI ui{controller , controller_watch_list};
//            ui.start_app();
//        }
//        else if (option == "csv") {
//            CSV_Repository csv_repository{"database.csv"};
//            Controller controller_watch_list(csv_repository);
//            Controller controller{repository};
//            UI ui{controller , controller_watch_list};
//            ui.start_app();
//        }
//
//
//    }
//    else if (option == "SQL"){
//        MYSQL* conn;
//        conn = mysql_init(NULL);
//        SQL_Repository sql_repo(conn);
//
//        std::cout << "Where do you want to store the watchlist? (memory/html/csv) ";
//        std::getline(std::cin , option);
//        if (option == "memory"){
//            Repository repository_watch_list{"watch_list.csv" , "read"};
//            Controller controller_watch_list{sql_repo};
//            Controller controller{sql_repo};
//            UI ui{controller , controller_watch_list};
//            ui.start_app();
//        }
//        else if (option == "html") {
//            HTML_Repository html_repository{"database.html"};
//            Controller controller_watch_list(html_repository);
//            Controller controller{sql_repo};
//            UI ui{controller , controller_watch_list};
//            ui.start_app();
//        }
//        else if (option == "csv") {
//            CSV_Repository csv_repository{"database.csv"};
//            Controller controller_watch_list(csv_repository);
//            Controller controller{sql_repo};
//            UI ui{controller , controller_watch_list};
//            ui.start_app();
//        }
//    }


    QApplication app(argc , argv);
    GUI gui;
    gui.show();
    return app.exec();

}