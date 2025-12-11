//
// Created by Stefan Pirvu on 13.11.2025.
//

#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <string>

#include "TimeUtilis.h"


class Schedule {
    public:
    std::string professor; // name of the professor teaching the schedule
    TimeUtilis::Day day; // Monday, Tuesday, Wednesday, Thursday, Friday
    std::string room; // room number where the schedule takes place
    std::string type; // if it is a lecture, lab, seminar, project etc.
    std::pair <int, int> period; // from when to when (eg. 8-10)
    std::string subject;
    std::string group; // which group is attending the schedule ( for example group 1A , this is a subgroup, one cell in the schedule table represents a subgroup, but a whole group can attend the same , seminar, or even the whole year in case we do have a course)
    // so here we parse : 1A , 2B etc. or 1,2,3 for whole group attending , or all or other keyword to represent the whole year attending
    bool optional; // if the schedule is optional or mandatory ( we should assign by default that it is mandatory)
    Schedule(std::string subject, std::string type, bool optional);

    Schedule(std::string professor, std::string subject, std::string type, TimeUtilis::Day day,
             std::pair<int, int> period,
             std::string room, bool optional);


    void setOptional(bool optional);
};



#endif //SCHEDULE_H
