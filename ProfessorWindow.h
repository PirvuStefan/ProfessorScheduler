//
// Created by Stefan Pirvu on 15.11.2025.
//

#ifndef PROFESSORSCHEDULER_PUBLIC__PROFESSORWINDOW_H
#define PROFESSORSCHEDULER_PUBLIC__PROFESSORWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QLabel>
#include <string>

class ProfessorWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit ProfessorWindow(const std::string& professorName, QWidget *parent = nullptr);
    ~ProfessorWindow();

private slots:
    void onViewScheduleClicked();
    void onViewResourcesClicked();
    void onProfileClicked();

private:
    void setupUI();
    void applyStyles();

    std::string professorName;

    // UI Components
    QLabel* welcomeLabel;
    QLabel* subtitleLabel;
    QLabel* idiomLabel;
    QPushButton* viewScheduleButton;
    QPushButton* viewResourcesButton;
    QPushButton* profileButton;
};

#endif //PROFESSORSCHEDULER_PUBLIC__PROFESSORWINDOW_H