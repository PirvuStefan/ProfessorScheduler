//
// Created by Stefan Pirvu on 21.11.2025.
//

// C++
#include "../Headers/UserFactory.h"
#include "../Headers/Professor.h"
#include "../Headers/Student.h"

User* UserFactory::createUser(QString email, QString password, QString name, bool isProfessor) {
    if (isProfessor)
    return new Professor(email, password, name);
    return new Student(email, password, name);
}
