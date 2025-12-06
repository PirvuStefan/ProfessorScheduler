//
// Created by Stefan Pirvu on 04.12.2025.
//

#ifndef PROFESSORSCHEDULER_PUBLIC__TIMEUTILIS_H
#define PROFESSORSCHEDULER_PUBLIC__TIMEUTILIS_H



namespace TimeUtilis {

    enum class Day{
        MONDAY = 0,
        TUESDAY = 1,
        WEDNESDAY = 2,
        THURSDAY = 3,
        FRIDAY = 4

    }; // more modern and future proof way of defining enums, compared to the traditional one ( no more conflicts between different enums with same values cause they are inside a namespace and scoped )

    inline Day stringToDayEnum(const std::string &dayStr) {
        if (dayStr == "MONDAY") return TimeUtilis::Day::MONDAY;
        if (dayStr == "TUESDAY") return TimeUtilis::Day::TUESDAY;
        if (dayStr == "WEDNESDAY") return TimeUtilis::Day::WEDNESDAY;
        if (dayStr == "THURSDAY") return TimeUtilis::Day::THURSDAY;
        if (dayStr == "FRIDAY") return TimeUtilis::Day::FRIDAY;

        throw std::invalid_argument("Invalid day string: " + dayStr);
    }
}

#endif //PROFESSORSCHEDULER_PUBLIC__TIMEUTILIS_H