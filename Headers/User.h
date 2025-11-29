//
// Created by Stefan Pirvu on 13.11.2025.
//

#ifndef USER_H
#define USER_H

#include <qstring.h>
#include <string>
#include <vector>
#include "Schedule.h"
#include <QWidget>


class User {

    enum Day { MONDAY = 0, TUESDAY = 1, WEDNESDAY = 2, THURSDAY = 3, FRIDAY = 4};



protected:
    std::string fullName;
    std::string email;
    std::string password;
    std::vector < Schedule > schedules; // each user can have multiple schedules,
    // for example a professor can have multiple courses he is teaching, and each course has its own schedule,
    // the courses that he does not teach will appear to the professor as being occupied or not ( black / grey )
    // on the other hand, for students, all the schedules will load, since they attend all the courses, and the 'non-occupied'
    // slots will be the free time they have for studying, doing homework, projects etc. ( white )
    // so the both professors and students will have a vector of schedules associated with their accounts
    // but the initialisation of those schedules will differ depending on the type of user
    // that is the implementation that i currently have in mind


public:
    virtual ~User() = default;

    User(std::string fullName, std::string email, std::string password);
    User(QString fullName, QString email, QString password);

    void Print();

    std::string getName();
    std::string getEmail();
    std::string getPassword();

    virtual void AccountCreated() ; // we do want to have a different print message when a professor or a student creates an account
    virtual QWidget createWidget(QWidget *parent) = 0 ; // we will override this method in derived classes to set the user interface depending on the type of user
};

#endif //USER_H
