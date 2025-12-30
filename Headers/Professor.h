//
// Created by Stefan Pirvu on 15.11.2025.
//

#ifndef PROFESSORSCHEDULER_PUBLIC__PROFESSOR_H
#define PROFESSORSCHEDULER_PUBLIC__PROFESSOR_H

#include "User.h"


class Professor : public User {
    public:
    void AccountCreated() override;

    void AccountLogin() override;

    Professor(const User &user);

    Professor(QString email, QString password, QString name);

    bool testValability(QString room, QString hour, QString day);


    void initialiseSchedules() override;
    QWidget* createWidget(QWidget *parent) override;
    QWidget* createScheduleWidget(QWidget *parent) override;


};


#endif //PROFESSORSCHEDULER_PUBLIC__PROFESSOR_H