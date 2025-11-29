//
// Created by Stefan Pirvu on 15.11.2025.
//

#include "../Headers/Professor.h"
#include <QBoxLayout>
#include <QLabel>

void Professor::AccountCreated() {
    printf("Professor Account Created\n");
}


Professor::Professor(const User& user) : User(user) {}

Professor::Professor( QString email, QString password, QString name) : User(name, email, password) {}

QWidget User::createWidget(QWidget* parent) {
    QWidget* w = new QWidget(parent);
    auto layout = new QVBoxLayout(w);
    layout->addWidget(new QLabel("Professor view"));
    return QWidget(w);


}
