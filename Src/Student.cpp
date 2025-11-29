//
// Created by Stefan Pirvu on 15.11.2025.
//

#include "../Headers/Student.h"
#include <QBoxLayout>
#include <QLabel>
#include <QWidget>

void Student::AccountCreated() {

    printf("Student Account Created\n");
}

Student::Student(const User& user) : User(user) {}

Student::Student( QString email, QString password, QString name) : User(name, email, password) {}

QWidget* Student::createWidget(QWidget *parent) {
    // If parent is null we want a top-level window; otherwise keep it as child (rare)
    QWidget* w = new QWidget(parent);
    if (parent == nullptr) {
        // ensure it's a top-level window
        w->setWindowFlags(Qt::Window);
        w->setWindowTitle("Student - Professor Scheduler");
        w->resize(800, 600);
        w->setMinimumSize(600, 400);
    }

    auto layout = new QVBoxLayout(w);
    layout->addWidget(new QLabel("Student view"));

    return w;
}
