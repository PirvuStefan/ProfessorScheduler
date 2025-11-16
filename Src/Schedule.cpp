//
// Created by Stefan Pirvu on 13.11.2025.
//

#include "../Headers/Schedule.h"
#include <string>

Schedule::Schedule(std::string subject, std::string type, bool optional = true ) {
    this->type = type;
    this->subject = subject;
    this->optional = optional;
}