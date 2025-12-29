//
// Created by Stefan Pirvu on 13.11.2025.
//

#include "../Headers/Schedule.h"
#include <string>

#include "../Headers/TimeUtilis.h"

Schedule::Schedule(std::string subject, std::string type, bool optional = false ) {
    this->type = type;
    this->subject = subject;
    this->optional = optional;
}

Schedule::Schedule(std::string professor, std::string subject, std::string type, TimeUtilis::Day day, int period, std::string room, bool optional, std::string group = "all") {
    this->professor = professor;
    this->subject = subject;
    this->type = type;
    this->day = day;
    this->period = period;
    this->room = room;
    this->optional = optional;
    this->group = group;

}

void Schedule::setOwnership(bool ownership = true) {
    this->ownership = ownership;
}

bool Schedule::getOwnership() const {
    return this->ownership;
}

void Schedule::setOptional(bool optional = true) {
    this->optional = optional;
}

bool Schedule::compareSchedulesByPeriod(const Schedule &a, const Schedule &b) {
    if (a.period == b.period) {
    //if periods are equal, we can further sort them by group
    return a.group < b.group;
    }
    return a.period < b.period;
}

std::string Schedule::getSubject() const {
    return subject;
}

std::string Schedule::getProfessor() const {
    return professor;
}

int Schedule::getTimeSlot() const {
    return period;
}

std::string Schedule::getGroup() const {
    return group;
}

std::string Schedule::getRoom() const {
    return room;
}

std::string Schedule::getColor() const {

    if (type == "lecture") return "#0F8CBD";
    if (type == "lab") return "#D16924";
    if (type == "seminar") return "#EDDD53";
    return "#762BC2"; // project or other types

}