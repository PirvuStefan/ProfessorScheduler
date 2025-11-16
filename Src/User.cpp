//
// Created by Stefan Pirvu on 13.11.2025.
//

#include "../Headers/User.h"

#include <iostream>

User::User(std::string fullName, std::string email, std::string password, bool isProfessor) {
    this->fullName = fullName;
    this->email = email;
    this->password = password;
    this->isProfessor = isProfessor;
}

User::User(QString fullName, QString email, QString password, bool isProfessor) {
    this->fullName = fullName.toStdString();
    this->email = email.toStdString();
    this->password = password.toStdString();
    this->isProfessor = isProfessor; // we cast them to vanilla string
}

void User::Print() {
    std::cout << this->fullName << "\n";
    std::cout << this->email << "\n";
    std::cout << this->password << "\n";
    std::cout << (this->isProfessor ? "Professor" : "Student") << "\n";

}

void User::AccountCreated() { // base class implementation, we will override it in derived classes
    printf("Base Account Created\n");
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

