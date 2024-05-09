//
// Created by Robi on 3/22/2024.
//

#ifndef OOP_A4_5_LELIUCROBERT_DOMAIN_H
#define OOP_A4_5_LELIUCROBERT_DOMAIN_H
#include <string>

class Tutorial {
    private:
        std::string title;
        std::string link;
        std::string presenter;
        int likes , duration;
    public:
        Tutorial();
        Tutorial(std::string title, std::string presenter,
                 int duration, int likes, std::string link);
        int get_likes()const;
        int get_duration()const;
        std::string get_title();
        std::string get_presenter();
        std::string get_link();

        void set_likes(int likes);
        void set_duration(int duration);
        void set_title(std::string title);
        void set_presenter(std::string presenter);
        void set_link(std::string link);

};


#endif //OOP_A4_5_LELIUCROBERT_DOMAIN_H
