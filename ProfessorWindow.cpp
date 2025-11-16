//
// Created by Stefan Pirvu on 15.11.2025.
//

#include "ProfessorWindow.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QWidget>
#include <QFont>

ProfessorWindow::ProfessorWindow(const std::string& professorName, QWidget *parent)
    : QMainWindow(parent), professorName(professorName) {
    setupUI();
    applyStyles();
}

ProfessorWindow::~ProfessorWindow() {
}

void ProfessorWindow::setupUI() {
    setWindowTitle("Professor Dashboard");
    setMinimumSize(800, 600);

    QWidget* centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout* mainLayout = new QVBoxLayout(centralWidget);
    mainLayout->setContentsMargins(40, 30, 40, 40);
    mainLayout->setSpacing(30);

    // Top bar with profile button
    QHBoxLayout* topBar = new QHBoxLayout();
    topBar->addStretch();

    profileButton = new QPushButton("👤", this);
    profileButton->setFixedSize(50, 50);
    profileButton->setCursor(Qt::PointingHandCursor);
    connect(profileButton, &QPushButton::clicked, this, &ProfessorWindow::onProfileClicked);
    topBar->addWidget(profileButton);

    mainLayout->addLayout(topBar);

    // Welcome text
    welcomeLabel = new QLabel(QString::fromStdString("Hello, " + professorName + ", welcome back"), this);
    welcomeLabel->setAlignment(Qt::AlignCenter);
    QFont welcomeFont("Arial", 32, QFont::Bold);
    welcomeLabel->setFont(welcomeFont);
    mainLayout->addWidget(welcomeLabel);

    // Subtitle
    subtitleLabel = new QLabel("Manage your schedules and teaching resources", this);
    subtitleLabel->setAlignment(Qt::AlignCenter);
    QFont subtitleFont("Arial", 16);
    subtitleLabel->setFont(subtitleFont);
    mainLayout->addWidget(subtitleLabel);

    mainLayout->addSpacing(20);

    // Buttons layout
    QHBoxLayout* buttonsLayout = new QHBoxLayout();
    buttonsLayout->setSpacing(20);

    viewScheduleButton = new QPushButton("View My Schedule", this);
    viewScheduleButton->setMinimumSize(200, 50);
    viewScheduleButton->setCursor(Qt::PointingHandCursor);
    connect(viewScheduleButton, &QPushButton::clicked, this, &ProfessorWindow::onViewScheduleClicked);

    viewResourcesButton = new QPushButton("View Teaching Resources", this);
    viewResourcesButton->setMinimumSize(200, 50);
    viewResourcesButton->setCursor(Qt::PointingHandCursor);
    connect(viewResourcesButton, &QPushButton::clicked, this, &ProfessorWindow::onViewResourcesClicked);

    buttonsLayout->addStretch();
    buttonsLayout->addWidget(viewScheduleButton);
    buttonsLayout->addWidget(viewResourcesButton);
    buttonsLayout->addStretch();

    mainLayout->addLayout(buttonsLayout);
    mainLayout->addStretch();

    // Teaching idiom with gradient text
    idiomLabel = new QLabel("\"The art of teaching is the art of assisting discovery.\"", this);
    idiomLabel->setAlignment(Qt::AlignCenter);
    QFont idiomFont("Arial", 14, QFont::Normal, true);
    idiomLabel->setFont(idiomFont);
    mainLayout->addWidget(idiomLabel);
}

void ProfessorWindow::applyStyles() {
    // Color palette: #016B61 #70B2B2 #9ECFD4 #E5E9C5

    setStyleSheet(
        "QMainWindow {"
        "   background-color: #E5E9C5;"
        "}"
        "QPushButton {"
        "   background-color: #016B61;"
        "   color: white;"
        "   border: none;"
        "   border-radius: 8px;"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   padding: 12px 24px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #70B2B2;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #9ECFD4;"
        "}"
        "QPushButton#profileButton {"
        "   background-color: #9ECFD4;"
        "   border-radius: 25px;"
        "   font-size: 24px;"
        "}"
        "QPushButton#profileButton:hover {"
        "   background-color: #70B2B2;"
        "}"
    );

    profileButton->setObjectName("profileButton");

    // Gradient effect for welcome label
    welcomeLabel->setStyleSheet("color: #016B61;");
    subtitleLabel->setStyleSheet("color: #70B2B2;");

    // Gradient effect for idiom label
    idiomLabel->setStyleSheet(
        "QLabel {"
        "   color: qlineargradient(x1:0, y1:0, x2:1, y2:0,"
        "       stop:0 #016B61, stop:0.5 #70B2B2, stop:1 #9ECFD4);"
        "}"
    );
}

void ProfessorWindow::onViewScheduleClicked() {
    // TODO: Implement schedule view
}

void ProfessorWindow::onViewResourcesClicked() {
    // TODO: Implement resources view
}

void ProfessorWindow::onProfileClicked() {
    // TODO: Implement profile menu
}
