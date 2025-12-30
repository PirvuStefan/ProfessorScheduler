//
// Created by Stefan Pirvu on 13.11.2025.
//

#include "../Headers/Schedule.h"
#include <string>
#include <QFile>
#include <qtextstream.h>

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

std::optional<bool> Schedule::getOwnership() const {
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
    if (ownership == false) return "";
    return subject;
}

std::string Schedule::getProfessor() const {
    if (ownership == false) return "";
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

    if (ownership == false) return "#302825"; // dark color for non-owned schedules ( highest priority to show they are not available )
    if (type == "lecture") return "#0F8CBD";
    if (type == "lab") return "#D16924";
    if (type == "seminar") return "#EDDD53";
    return "#762BC2"; // project or other types

}

bool Schedule::testValability(){


    QFile file("Schedules/schedules.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return false;
    }

    //check if the current schedule conflicts with an existing one



    QTextStream in(&file);

    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");


        //Stefan Groia,Matematica Speciala,lecture,Monday,8,B302,mandatory,1A
        // parts[0] to parts[7]
        if (parts.size() < 4) continue;

        if ( day != TimeUtilis::stringToDayEnum(parts[2].toStdString())) continue; // different day, no conflict

        if ( room == parts[4] and period == parts[4].toInt()) {
            type = "full_conflict";
            return false;
        }

        // either room, time or day conflicts, we cannot have two schedules in the same room at the same time on the same day


    }

    return true;

}