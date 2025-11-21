//
// Created by Stefan Pirvu on 15.11.2025.
//

#include "../Headers/Professor.h"

void Professor::AccountCreated() {
    printf("Professor Account Created\n");
}


Professor::Professor(const User& user) : User(user) {}