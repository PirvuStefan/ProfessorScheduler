//
// Created by Stefan Pirvu on 13.11.2025.
//

#ifndef USER_H
#define USER_H

#include <qstring.h>
#include <string>

class User {

protected:
    std::string fullName;
    std::string email;
    std::string password;
    bool isProfessor;

public:
    virtual ~User() = default;

    User(std::string fullName, std::string email, std::string password, bool isProfessor = false);
    User(QString fullName, QString email, QString password, bool isProfessor = false);

    void Print();

    std::string getName();
    std::string getEmail();
    std::string getPassword();
    bool getIsProfessor() const;

    virtual void AccountCreated() ; // we do want to have a different print message when a professor or a student creates an account
};

#endif //USER_H
