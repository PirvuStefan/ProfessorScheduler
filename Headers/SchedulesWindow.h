//
// Created by Stefan Pirvu on 17.11.2025.
//

#ifndef PROFESSORSCHEDULER_PUBLIC__SCHEDULESWINDOW_H
#define PROFESSORSCHEDULER_PUBLIC__SCHEDULESWINDOW_H

#include <QWidget>
#include <QTableWidget>
#include <QComboBox>
#include <QPushButton>

class SchedulesWindow : public QWidget
{
    Q_OBJECT

public:
    explicit SchedulesWindow(QWidget *parent = nullptr);

private:
    void setupUi();
    void populateScheduleTable();
    void updateScheduleForDay(const QString &day);

    QComboBox *m_daySelector;  // Changed from m_groupSelector
    QTableWidget *m_scheduleTable;
    QPushButton *m_backButton;

    // Time slots from 8:00 to 20:00
    QStringList m_timeSlots;
    QStringList m_subGroups;  // Changed from m_daysOfWeek
};

#endif //PROFESSORSCHEDULER_PUBLIC__SCHEDULESWINDOW_H