//
// Created by Stefan Pirvu on 17.11.2025.
//

#include "SchedulesWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>

SchedulesWindow::SchedulesWindow(QWidget *parent) : QWidget(parent) {
    setupUI();
}

void SchedulesWindow::setupUI() {
    mainLayout = new QGridLayout(this);

    // Title
    QLabel* title = new QLabel("Weekly Schedule", this);
    title->setStyleSheet(QString("font-size: 24px; font-weight: bold; color: %1; padding: 10px;").arg(COLOR_PRIMARY));
    title->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(title, 0, 0);

    // Create scroll area for the schedule grid
    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    scrollArea->setStyleSheet(QString("background-color: white; border: 2px solid %1;").arg(COLOR_TERTIARY));

    QWidget* scheduleContainer = new QWidget();
    scheduleGrid = new QGridLayout(scheduleContainer);
    scheduleGrid->setSpacing(2);

    createScheduleGrid();

    scrollArea->setWidget(scheduleContainer);
    mainLayout->addWidget(scrollArea, 1, 0);

    setLayout(mainLayout);
    resize(1200, 700);
}

void SchedulesWindow::createScheduleGrid() {
    // Header: Empty corner cell
    QLabel* corner = new QLabel("");
    corner->setStyleSheet(QString("background-color: %1; border: 1px solid %2;").arg(COLOR_LIGHT).arg(COLOR_PRIMARY));
    scheduleGrid->addWidget(corner, 0, 0);

    // Column headers: Time slots and groups
    int col = 1;
    for (const QString& timeSlot : timeSlots) {
        // Time slot header spanning all subgroups
        QLabel* timeHeader = new QLabel(timeSlot);
        timeHeader->setAlignment(Qt::AlignCenter);
        timeHeader->setStyleSheet(QString("background-color: %1; color: white; font-weight: bold; padding: 8px; border: 1px solid %1;").arg(COLOR_PRIMARY));
        scheduleGrid->addWidget(timeHeader, 0, col, 1, NUM_GROUPS * SUBGROUPS_PER_GROUP);

        // Group and subgroup headers
        for (int group = 1; group <= NUM_GROUPS; ++group) {
            QLabel* groupHeader = new QLabel(QString("Group %1").arg(group));
            groupHeader->setAlignment(Qt::AlignCenter);
            groupHeader->setStyleSheet(QString("background-color: %1; color: white; font-weight: bold; padding: 5px; border: 1px solid %2;").arg(COLOR_SECONDARY).arg(COLOR_PRIMARY));
            scheduleGrid->addWidget(groupHeader, 1, col, 1, SUBGROUPS_PER_GROUP);

            for (int subgroup = 1; subgroup <= SUBGROUPS_PER_GROUP; ++subgroup) {
                QLabel* subgroupHeader = new QLabel(QString("SG %1").arg(subgroup));
                subgroupHeader->setAlignment(Qt::AlignCenter);
                subgroupHeader->setStyleSheet(QString("background-color: %1; color: %2; padding: 3px; border: 1px solid %2; font-size: 11px;").arg(COLOR_TERTIARY).arg(COLOR_PRIMARY));
                scheduleGrid->addWidget(subgroupHeader, 2, col);
                col++;
            }
        }
    }

    // Row headers: Days and schedule cells
    int row = 3;
    for (const QString& day : days) {
        // Day label
        QLabel* dayLabel = new QLabel(day);
        dayLabel->setAlignment(Qt::AlignCenter | Qt::AlignVCenter);
        dayLabel->setStyleSheet(QString("background-color: %1; color: white; font-weight: bold; padding: 10px; border: 1px solid %1;").arg(COLOR_PRIMARY));
        scheduleGrid->addWidget(dayLabel, row, 0);

        // Create course boxes for each time slot and subgroup
        col = 1;
        for (int timeSlot = 0; timeSlot < timeSlots.size(); ++timeSlot) {
            for (int group = 1; group <= NUM_GROUPS; ++group) {
                for (int subgroup = 1; subgroup <= SUBGROUPS_PER_GROUP; ++subgroup) {
                    QFrame* courseBox = createCourseBox();
                    scheduleGrid->addWidget(courseBox, row, col);
                    col++;
                }
            }
        }
        row++;
    }
}

QFrame* SchedulesWindow::createCourseBox(const QString& courseName) {
    QFrame* box = new QFrame();
    box->setFrameStyle(QFrame::Box);
    box->setMinimumSize(80, 60);
    box->setStyleSheet(QString(
        "QFrame {"
        "   background-color: white;"
        "   border: 2px solid %1;"
        "   border-radius: 4px;"
        "}"
        "QFrame:hover {"
        "   background-color: %2;"
        "   border: 2px solid %3;"
        "}"
    ).arg(COLOR_TERTIARY).arg(COLOR_LIGHT).arg(COLOR_SECONDARY));

    QVBoxLayout* boxLayout = new QVBoxLayout(box);
    QLabel* courseLabel = new QLabel(courseName.isEmpty() ? "" : courseName);
    courseLabel->setAlignment(Qt::AlignCenter);
    courseLabel->setWordWrap(true);
    courseLabel->setStyleSheet(QString("color: %1; font-size: 10px; border: none;").arg(COLOR_PRIMARY));
    boxLayout->addWidget(courseLabel);

    return box;
}
