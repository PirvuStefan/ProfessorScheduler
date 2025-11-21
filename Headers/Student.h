//
// Created by Stefan Pirvu on 15.11.2025.
//
#ifndef PROFESSORSCHEDULER_PUBLIC__STUDENT_H
#define PROFESSORSCHEDULER_PUBLIC__STUDENT_H

#pragma once

#include "User.h"


class Student : public User {




public:
    void AccountCreated() override;

    Student(const User &user);
};


#endif //PROFESSORSCHEDULER_PUBLIC__STUDENT_H