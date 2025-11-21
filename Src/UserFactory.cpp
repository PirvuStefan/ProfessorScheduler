//
// Created by Stefan Pirvu on 21.11.2025.
//

// C++
#include "../Headers/UserFactory.h"
#include "../Headers/Professor.h"
#include "../Headers/Student.h"

User* UserFactory::createUser(User user, bool isProfessor) {
    if (isProfessor)
    return new Professor(user);
    return new Student(user);
}
