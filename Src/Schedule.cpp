//
// Created by Stefan Pirvu on 13.11.2025.
//

#include "../Headers/Schedule.h"
#include <string>
#include <QFile>
#include <qtextstream.h>
#include <iostream>

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

void Schedule::setType(std::string type) {
    this->type = type;
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
    if (type == "lecture" and optional) return "#70B2B2";
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

        if ( day != TimeUtilis::stringToDayEnum(parts[3].toStdString())) continue; // different day, no conflict




        if ( room == parts[5] and period == parts[4].toInt()) {
            type = "full_conflict";
            return false;
        }

        if ( period == parts[4].toInt() ) {
            // same time slot, check for group conflicts
            std::string existingGroup = parts[7].toStdString();

            if ( existingGroup == "all" or group == "all") {
                type = "year_conflict";
                return false; // whole year conflict
            }

            if ( existingGroup == group ) {
                type = "group_conflict";
                return false; // same group conflict
            }

            // 1A dar 1 are curs la aceeasi ora
            // 1 dar 1A are curs la aceeasi ora


            if (existingGroup[0] == group[0] and (existingGroup.length() > 1 xor group.length() > 1) ){
                type = "overlap_conflict";
                return false;
            } //  1 overlapps with 1A, but 1A does not overlap with 1B

        }

        // we need to check if the groups overlap as well, the room conflict may not happen, but we cant assign for example
        // group 1A to a schedule if group 1 already has a schedule at the same time, because group 1A is part of group 1 and group 1 is part of "all"

        // either room, time or day conflicts, we cannot have two schedules in the same room at the same time on the same day


    }

    return true;

}

void Schedule::addScheduleToFile() {
    QFile file("Schedules/schedules.txt");
    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        return;
    }

    QTextStream out(&file);
    out << QString::fromStdString(professor) << ","
        << QString::fromStdString(subject) << ","
        << QString::fromStdString(type) << ","
        << QString::fromStdString( (day == TimeUtilis::Day::MONDAY) ? "Monday" :
                                    (day == TimeUtilis::Day::TUESDAY) ? "Tuesday" :
                                    (day == TimeUtilis::Day::WEDNESDAY) ? "Wednesday" :
                                    (day == TimeUtilis::Day::THURSDAY) ? "Thursday" :
                                    "Friday") << ","
        << QString::number(period) << ","
        << QString::fromStdString(room) << ","
        << (optional ? "optional" : "mandatory") << ","
        << QString::fromStdString(group) << "\n";

    std::cout << "Succesfully added the following schedule to the system";
    print();

    file.close();
}

void Schedule::print() {
    std::cout << "Schedule Details:\n";
    std::cout << "Professor: " << professor << "\n";
    std::cout << "Subject: " << subject << "\n";
    std::cout << "Type: " << type << "\n";
    std::cout << "Day: " << (day == TimeUtilis::Day::MONDAY ? "Monday" :
                             day == TimeUtilis::Day::TUESDAY ? "Tuesday" :
                             day == TimeUtilis::Day::WEDNESDAY ? "Wednesday" :
                             day == TimeUtilis::Day::THURSDAY ? "Thursday" :
                             "Friday") << "\n";
    std::cout << "Period: " << period << "\n";
    std::cout << "Room: " << room << "\n";
    std::cout << "Optional: " << (optional ? "Yes" : "No") << "\n";
    std::cout << "Group: " << group << "\n";
}

std::string Schedule::getErrorDescription() const {
    if (type == "full_conflict") return "Schedule conflicts with existing schedule in the same room at the same time.";
    if (type == "year_conflict") return "Schedule conflicts with existing schedule for the whole year at the same time.";
    if (type == "group_conflict") return "Schedule conflicts with existing schedule for the same group at the same time.";
    if (type == "overlap_conflict") return "Schedule conflicts with existing schedule for overlapping groups at the same time.";
    return "No conflict."; // this should be unreachable
}

QString Schedule::getErrorDescriptionQString() const {
    if (type == "full_conflict") return "Schedule conflicts with existing schedule in the same room at the same time.";
    if (type == "year_conflict") return "Schedule conflicts with existing schedule for the whole year at the same time.";
    if (type == "group_conflict") return "Schedule conflicts with existing schedule for the same group at the same time.";
    if (type == "overlap_conflict") return "Schedule conflicts with existing schedule for overlapping groups at the same time.";
    return "No conflict."; // this should be unreachable
}
