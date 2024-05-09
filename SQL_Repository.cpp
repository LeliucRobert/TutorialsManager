#include "SQL_Repository.h"
#include <iostream>
#include <stdexcept>

SQL_Repository::SQL_Repository(MYSQL* conn) : conn(conn)  , Repository(){
    const char* server = "localhost";
    const char* user = "root";
    const char* password = "sql123";
    const char* database = "tutorials_schema";


    if (!conn) {
        throw std::runtime_error("Failed to initialize MySQL connection.");
    }

    if (!mysql_real_connect(conn, server, user, password, database, 0, NULL, 0)) {
        std::string error = "Connection failed: ";
        error += mysql_error(conn);
        mysql_close(conn);
        throw std::runtime_error(error);
    }

    std::cout << "Connected successfully\n";

    const char* create_table_query =
            "CREATE TABLE IF NOT EXISTS TUTORIALS ("
            "title VARCHAR(255), "
            "presenter VARCHAR(255), "
            "duration INT, "
            "likes INT, "
            "link VARCHAR(255))";

    if (mysql_query(conn, create_table_query)) {
        std::string error = "Failed to create table: ";
        error += mysql_error(conn);
        mysql_close(conn);
        throw std::runtime_error(error);
    }

    const char* select_query = "SELECT title, presenter, duration, likes, link FROM TUTORIALS";
    if (mysql_query(conn, select_query)) {
        std::cerr << "Failed to retrieve tutorials: " << mysql_error(conn) << std::endl;
    } else {
        MYSQL_RES *result = mysql_store_result(conn);
        MYSQL_ROW row;
        while ((row = mysql_fetch_row(result))) {
            int duration = atoi(row[2]);
            int likes = atoi(row[3]);

            Tutorial tutorial(row[0], row[1], duration, likes, row[4]);
            this->repo_array.push_back(tutorial);
        }
        mysql_free_result(result);
    }
}

SQL_Repository::~SQL_Repository() {
    if (conn) {
        mysql_close(conn);
        conn = NULL;
    }
}

void SQL_Repository::write_to_file() {
    const char* deleteQuery = "DELETE FROM TUTORIALS";
    if (mysql_query(conn, deleteQuery)) {
        std::cerr << "Failed to clear the table: " << mysql_error(conn) << std::endl;
        return;
    }

    for (auto & it : this->repo_array){
        std::string query = "INSERT INTO TUTORIALS (title, presenter, duration, likes, link) VALUES ('" +
                            it.get_title() + "', '" +
                            it.get_presenter() + "', " +
                            std::to_string(it.get_duration()) + ", " +
                            std::to_string(it.get_likes()) + ", '" +
                            it.get_link() + "')";

        if (mysql_query(conn, query.c_str())) {
            std::cerr << "Failed to insert tutorial: " << mysql_error(conn) << std::endl;
        } else {
//            std::cout << "Tutorial added successfully" << std::endl;
        }
    }

}

std::vector<Tutorial> SQL_Repository::get_tutorials() {

    std::vector <Tutorial> tutorials;
    if (mysql_query(conn, "SELECT title, presenter, duration, likes, link FROM tutorials")) {
        std::cerr << "MySQL query failed: " << mysql_error(conn) << std::endl;
        return tutorials;
    }

    MYSQL_RES* result = mysql_store_result(conn);
    if (result == nullptr) {
        std::cerr << "MySQL store result failed: " << mysql_error(conn) << std::endl;
        return tutorials;
    }

    MYSQL_ROW row;
    while ((row = mysql_fetch_row(result))) {
        Tutorial tutorial {row[0] , row[1] , std::stoi(row[2]) , std::stoi(row[3]) , row[4]};
        tutorials.push_back(tutorial);
    }

    mysql_free_result(result);

    return tutorials;
}
