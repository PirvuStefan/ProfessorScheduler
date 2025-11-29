//
// Created by Stefan Pirvu on 15.11.2025.
//

#include "../Headers/Student.h"
#include <QBoxLayout>
#include <QLabel>

void Student::AccountCreated() {

    printf("Student Account Created\n");
}

Student::Student(const User& user) : User(user) {}

Student::Student( QString email, QString password, QString name) : User(name, email, password) {}

QWidget User::createWidget(QWidget *parent) {
    QWidget* w = new QWidget(parent);
    auto layout = new QVBoxLayout(w);
    layout->addWidget(new QLabel("Student view"));
    return QWidget(w);


}
