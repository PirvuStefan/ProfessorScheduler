//
// Created by Stefan Pirvu on 15.11.2025.
//

#ifndef PROFESSORSCHEDULER_PUBLIC__PROFESSOR_H
#define PROFESSORSCHEDULER_PUBLIC__PROFESSOR_H

#include "User.h"


class Professor : public User {
    public:
    void AccountCreated() override;
};


#endif //PROFESSORSCHEDULER_PUBLIC__PROFESSOR_H