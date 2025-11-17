//
// Created by Stefan Pirvu on 17.11.2025.
//

#ifndef PROFESSORSCHEDULER_PUBLIC__SCHEDULESWINDOW_H
#define PROFESSORSCHEDULER_PUBLIC__SCHEDULESWINDOW_H

#include <QWidget>
#include <QGridLayout>
#include <QLabel>
#include <QFrame>
#include <QScrollArea>
#include <vector>
#include <string>

class SchedulesWindow : public QWidget {
    Q_OBJECT

public:
    explicit SchedulesWindow(QWidget *parent = nullptr);
    ~SchedulesWindow() override = default;

private:
    void setupUI();
    void createScheduleGrid();
    QFrame* createCourseBox(const QString& courseName = "");

    QGridLayout* mainLayout;
    QGridLayout* scheduleGrid;
    QScrollArea* scrollArea;

    // Color palette
    const QString COLOR_PRIMARY = "#016B61";
    const QString COLOR_SECONDARY = "#70B2B2";
    const QString COLOR_TERTIARY = "#9ECFD4";
    const QString COLOR_LIGHT = "#E5E9C5";

    const std::vector<QString> days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"};
    const std::vector<QString> timeSlots = {"8-10", "10-12", "12-14", "14-16", "16-18", "18-20"};
    const int NUM_GROUPS = 3;
    const int SUBGROUPS_PER_GROUP = 2;
};

#endif //PROFESSORSCHEDULER_PUBLIC__SCHEDULESWINDOW_H