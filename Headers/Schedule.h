//
// Created by Stefan Pirvu on 13.11.2025.
//

#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <string>


class Schedule {
    public:
    std::string day; // Monday, Tuesday, Wednesday, Thursday, Friday
    std::string room; // room number where the schedule takes place
    std::string type; // if it is a lecture, lab, seminar, project etc.
    std::pair <int, int> period; // from when to when (eg. 8-10)
    std::string subject;
    bool optional; // if the schedule is optional or mandatory ( we should assign by default that it is mandatory)
    Schedule(std::string subject, std::string type, bool optional);

    void setOptional(bool optional);
};



#endif //SCHEDULE_H
