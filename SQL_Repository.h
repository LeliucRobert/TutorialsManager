

#ifndef OOP_A4_5_LELIUCROBERT_SQL_REPOSITORY_H
#define OOP_A4_5_LELIUCROBERT_SQL_REPOSITORY_H

#include <mysql.h>
#include "Repository.h"

class SQL_Repository : public Repository{
private:
    MYSQL* conn;
public:
    SQL_Repository(MYSQL* conn);
    ~SQL_Repository();
    void write_to_file() override;
    std::vector<Tutorial> get_tutorials() override;

};


#endif //OOP_A4_5_LELIUCROBERT_SQL_REPOSITORY_H
