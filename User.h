//
// Created by Stefan Pirvu on 13.11.2025.
//

#ifndef USER_H
#define USER_H

#include <string>

class User {

protected:
    std::string fullName;
    std::string email;
    std::string password;
    bool isProfessor;

public:
    User(std::string fullName, std::string email, std::string password, bool isProfessor = false);

    std::string getName();
    std::string getEmail();
    std::string getPassword();
    bool getIsProfessor() const;
};

#endif //USER_H
