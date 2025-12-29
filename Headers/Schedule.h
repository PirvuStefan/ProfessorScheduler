//
// Created by Stefan Pirvu on 13.11.2025.
//

#ifndef SCHEDULE_H
#define SCHEDULE_H
#include <string>

#include "TimeUtilis.h"


class Schedule {
    protected:
    std::string professor; // name of the professor teaching the schedule
    TimeUtilis::Day day; // Monday, Tuesday, Wednesday, Thursday, Friday
    std::string room; // room number where the schedule takes place
    std::string type; // if it is a lecture, lab, seminar, project etc.
    int period; // from when ( we do not need to store 8-10, 10-12 etc. just the starting hour is enough, since we have fixed time slots in the schedule, so we can deduce the ending hour from the starting hour , each slot is 2 hours long )
    std::string subject;
    std::string group; // which group is attending the schedule ( for example group 1A , this is a subgroup, one cell in the schedule table represents a subgroup, but a whole group can attend the same , seminar, or even the whole year in case we do have a course)
    // so here we parse : 1A , 2B etc. or 1,2,3 for whole group attending , or all or other keyword to represent the whole year attending
    bool optional; // if the schedule is optional or mandatory ( we should assign by default that it is mandatory)
    bool ownership = false; // if the user owns this schedule ( for professors, they own the schedules they teach, for students, they do now own anything, so this will be false by default )
    public:
    Schedule(std::string subject, std::string type, bool optional);

    Schedule(std::string professor, std::string subject, std::string type, TimeUtilis::Day day, int period,
             std::string room, bool optional, std::string group);

    void setOwnership(bool ownership);

    bool getOwnership() const;

    bool getOwnership();

    static bool compareSchedulesByPeriod(const Schedule &a, const Schedule &b);

    std::string getSubject() const;

    std::string getProfessor() const;

    int getTimeSlot() const;

    std::string getGroup() const;

    std::string getRoom() const;

    std::string getColor() const;



    void setOptional(bool optional);
};



#endif //SCHEDULE_H
