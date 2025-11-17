//
// Created by Stefan Pirvu on 13.11.2025.
//

#include "../Headers/Schedule.h"
#include <string>

Schedule::Schedule(std::string subject, std::string type, bool optional = false ) {
    this->type = type;
    this->subject = subject;
    this->optional = optional;
}

void Schedule::setOptional(bool optional = true) {
    this->optional = optional;
}