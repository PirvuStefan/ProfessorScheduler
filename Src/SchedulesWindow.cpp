//
// Created by Stefan Pirvu on 17.11.2025.
//

#include "../Headers/SchedulesWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QHeaderView>
#include <QPainter>

SchedulesWindow::SchedulesWindow(QWidget *parent)
    : QWidget(parent)
{
    // Initialize time slots (8:00 to 20:00)
    m_timeSlots = {"08:00-10:00", "10:00-12:00", "12:00-14:00",
                   "14:00-16:00", "16:00-18:00", "18:00-20:00"};

    // 6 sub-groups (3 groups with 2 divisions each)
    m_subGroups = {"Group 1A", "Group 1B", "Group 2A",
                   "Group 2B", "Group 3A", "Group 3B"};

    setupUi();
}

void SchedulesWindow::setupUi()
{
    resize(1200, 800);  // Wider to accommodate 6 columns
    setWindowTitle("My Schedules");

    // Set background color to match palette
    setStyleSheet("background-color: #E5E9C5;");

    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(30, 30, 30, 30);
    mainLayout->setSpacing(20);

    // Title
    auto *titleLabel = new QLabel("Weekly Schedule", this);
    QFont titleFont;
    titleFont.setPointSize(24);
    titleFont.setBold(true);
    titleLabel->setFont(titleFont);
    titleLabel->setStyleSheet("color: #016B61; background-color: transparent;");

    // Day selector
    auto *selectorLayout = new QHBoxLayout();
    auto *dayLabel = new QLabel("Select Day:", this);
    dayLabel->setStyleSheet("color: #016B61; font-size: 14px; background-color: transparent;");

    m_daySelector = new QComboBox(this);
    // Days of the week selector
    m_daySelector->addItems({"Monday", "Tuesday", "Wednesday", "Thursday", "Friday"});
    m_daySelector->setStyleSheet(R"(
        QComboBox {
            background-color: white;
            border: 2px solid #016B61;
            border-radius: 5px;
            padding: 8px;
            min-width: 150px;
            font-size: 14px;
            color: #016B61;
        }
        QComboBox:hover {
            border-color: #70B2B2;
        }
        QComboBox::drop-down {
            border: none;
        }
        QComboBox QAbstractItemView {
            background-color: white;
            selection-background-color: #9ECFD4;
            selection-color: #016B61;
        }
    )");

    selectorLayout->addWidget(dayLabel);
    selectorLayout->addWidget(m_daySelector);
    selectorLayout->addStretch();

    // Schedule table - Hours on left, Sub-groups as columns
    m_scheduleTable = new QTableWidget(this);
    m_scheduleTable->setRowCount(m_timeSlots.size());
    m_scheduleTable->setColumnCount(m_subGroups.size());

    // Set headers
    m_scheduleTable->setVerticalHeaderLabels(m_timeSlots);
    m_scheduleTable->setHorizontalHeaderLabels(m_subGroups);

    // Style the table
    m_scheduleTable->setStyleSheet(R"(
        QTableWidget {
            background-color: white;
            gridline-color: #70B2B2;
            border: 2px solid #016B61;
            border-radius: 8px;
        }
        QTableWidget::item {
            padding: 10px;
            border: 1px solid #E5E9C5;
        }
        QHeaderView::section {
            background-color: #016B61;
            color: white;
            font-weight: bold;
            font-size: 13px;
            padding: 12px;
            border: 1px solid #70B2B2;
        }
    )");

    // Set column widths (wider for content)
    for (int col = 0; col < m_subGroups.size(); ++col) {
        m_scheduleTable->setColumnWidth(col, 180);
    }

    // Set row heights (taller for subject + professor)
    for (int row = 0; row < m_timeSlots.size(); ++row) {
        m_scheduleTable->setRowHeight(row, 100);
    }

    // Configure headers
    m_scheduleTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    m_scheduleTable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
    m_scheduleTable->verticalHeader()->setDefaultSectionSize(100);

    // Make table non-editable
    m_scheduleTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    m_scheduleTable->setSelectionMode(QAbstractItemView::SingleSelection);

    // Back button
    m_backButton = new QPushButton("← Back", this);
    m_backButton->setStyleSheet(R"(
        QPushButton {
            background-color: #016B61;
            color: white;
            font-size: 14px;
            font-weight: 600;
            padding: 10px 24px;
            border: none;
            border-radius: 5px;
            min-height: 40px;
        }
        QPushButton:hover {
            background-color: #70B2B2;
        }
        QPushButton:pressed {
            background-color: #9ECFD4;
        }
    )");
    m_backButton->setCursor(Qt::PointingHandCursor);

    // Add widgets to layout
    mainLayout->addWidget(titleLabel);
    mainLayout->addLayout(selectorLayout);
    mainLayout->addWidget(m_scheduleTable, 1); // Stretch factor 1
    mainLayout->addWidget(m_backButton, 0, Qt::AlignLeft);

    // Populate initial data
    populateScheduleTable();

    // Connections
    connect(m_daySelector, &QComboBox::currentTextChanged,
            this, &SchedulesWindow::updateScheduleForDay);
    connect(m_backButton, &QPushButton::clicked, this, &QWidget::close);
}

void SchedulesWindow::populateScheduleTable()
{
    // Sample data - each cell contains subject and professor
    // This will change based on the selected day
    for (int row = 0; row < m_scheduleTable->rowCount(); ++row) {
        for (int col = 0; col < m_scheduleTable->columnCount(); ++col) {
            auto *cellWidget = new QWidget();
            auto *cellLayout = new QVBoxLayout(cellWidget);
            cellLayout->setContentsMargins(5, 5, 5, 5);
            cellLayout->setSpacing(5);

            // Subject label
            auto *subjectLabel = new QLabel("Mathematics", cellWidget);
            subjectLabel->setStyleSheet("font-weight: bold; font-size: 13px; color: #016B61; background-color: transparent;");
            subjectLabel->setAlignment(Qt::AlignCenter);

            // Professor label
            auto *profLabel = new QLabel("Prof. John Smith", cellWidget);
            profLabel->setStyleSheet("font-size: 11px; color: #70B2B2; background-color: transparent;");
            profLabel->setAlignment(Qt::AlignCenter);
            profLabel->setWordWrap(true);

            cellLayout->addWidget(subjectLabel);
            cellLayout->addWidget(profLabel);
            cellLayout->addStretch();

            m_scheduleTable->setCellWidget(row, col, cellWidget);
        }
    }
}

void SchedulesWindow::updateScheduleForDay(const QString &day)
{
    // Update schedule based on selected day
    // This is where you'd load specific schedule data for each day
    // Different courses and professors for Monday, Tuesday, etc.
    populateScheduleTable();
}
