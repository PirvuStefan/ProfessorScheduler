//
// Created by Stefan Pirvu on 13.11.2025.
//

#include "Schedule.h"
#include <string>

Schedule::Schedule(std::string subject, std::string day, std::string type, bool optional = true ) {
    this->type = type;
    this->day = day;
    this->subject = subject;
    this->optional = optional;
}