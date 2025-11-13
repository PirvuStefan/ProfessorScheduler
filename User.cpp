//
// Created by Stefan Pirvu on 13.11.2025.
//

#include "User.h"

User::User(std::string fullName, std::string email, std::string password, bool isProfessor) {
    this->fullName = fullName;
    this->email = email;
    this->password = password;
    this->isProfessor = isProfessor;
}

std::string User::getName() {
    return this->fullName;
}

std::string User::getEmail() {
    return this->email;
}

std::string User::getPassword() {
    return this->password;
}

bool User::getIsProfessor() const {
    return this->isProfessor;
}