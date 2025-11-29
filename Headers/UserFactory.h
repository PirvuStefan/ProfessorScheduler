//
// Created by Stefan Pirvu on 21.11.2025.
//

#ifndef PROFESSORSCHEDULER_PUBLIC__USERFACTORY_H
#define PROFESSORSCHEDULER_PUBLIC__USERFACTORY_H


#include "../Headers/User.h"



class UserFactory{

    public:
    static User* createUser(QString email, QString password, QString name, bool isProfessor);
};


#endif //PROFESSORSCHEDULER_PUBLIC__USERFACTORY_H