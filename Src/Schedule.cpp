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

Schedule::Schedule(std::string professor, std::string subject, std::string type, TimeUtilis::Day day, std::pair <int, int > period, std::string room, bool optional = false) {
    this->professor = professor;
    this->subject = subject;
    this->type = type;
    this->day = day;
    this->period = period;
    this->room = room;
    this->optional = optional;
}

void Schedule::setOptional(bool optional = true) {
    this->optional = optional;
}