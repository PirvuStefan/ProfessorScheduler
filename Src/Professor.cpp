//
// Created by Stefan Pirvu on 15.11.2025.
//

#include "../Headers/Professor.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QPainter>
#include <QPaintEvent>
#include <QPainterPath>
#include <QLinearGradient>
#include <QFont>
#include <QPalette>
#include <QDebug>
#include <QTableWidget>
#include <QComboBox>
#include <QHeaderView>
#include <vector>

void Professor::AccountCreated()  {
    printf("Professor Account Created\n");
}

void Professor::AccountLogin() {
    printf("Professor Logged In\n");
}



Professor::Professor(const User& user) : User(user) {}

Professor::Professor( QString email, QString password, QString name) : User(name, email, password) {}

QWidget* Professor::createWidget(QWidget* parent,User* user) {


    // Local gradient-text label
    class GradientLabel : public QLabel {
    public:
        explicit GradientLabel(const QString &text, QWidget *parent = nullptr) : QLabel(text, parent) {
            setAttribute(Qt::WA_TranslucentBackground);
        }
    protected:
        void paintEvent(QPaintEvent *event) override {
            Q_UNUSED(event);
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing, true);

            QLinearGradient gradient(0, 0, width(), 0);
            gradient.setColorAt(0.0, QColor("#70B2B2"));
            gradient.setColorAt(0.5, QColor("#57C785"));
            gradient.setColorAt(1.0, QColor("#EDDD53"));

            painter.setPen(QPen(QBrush(gradient), 0));
            painter.setFont(font());
            painter.drawText(rect(), alignment(), text());
        }
    };

    // Local view widget that paints the background/wave and hosts the controls
    class LocalProfessorView : public QWidget {
    public:
        explicit LocalProfessorView(QWidget *parent = nullptr) : QWidget(parent) {
            setAttribute(Qt::WA_OpaquePaintEvent);
            setAutoFillBackground(false);

            // Labels
            m_greeting = new GradientLabel("", this);
            m_subtitle = new QLabel("", this);

            QFont greetFont; greetFont.setPointSize(26); greetFont.setBold(true);
            m_greeting->setFont(greetFont);
            m_greeting->setAlignment(Qt::AlignCenter);

            QFont subFont; subFont.setPointSize(18);
            m_subtitle->setFont(subFont);
            m_subtitle->setAlignment(Qt::AlignCenter);
            QPalette subPal = m_subtitle->palette();
            subPal.setColor(QPalette::WindowText, Qt::white);
            m_subtitle->setPalette(subPal);
            m_subtitle->setAttribute(Qt::WA_TranslucentBackground);

            resize(900, 600);
            setMinimumSize(900, 600);

            // Button
            m_scheduleButton = new QPushButton("View My Schedules", this);
            QString buttonStyle = R"(
                QPushButton {
                    background-color: #016B61;
                    color: white;
                    font-size: 16px;
                    font-weight: 600;
                    padding: 12px 20px;
                    border: none;
                    border-radius: 5px;
                    min-height: 48px;
                    min-width: 200px;
                }
                QPushButton:hover { background-color: #70B2B2; }
                QPushButton:pressed { background-color: #9ECFD4; }
            )";
            m_scheduleButton->setStyleSheet(buttonStyle);
            m_scheduleButton->setCursor(Qt::PointingHandCursor);

            // Layout: top text, bottom centered button
            auto *mainLayout = new QVBoxLayout(this);
            mainLayout->setContentsMargins(0, 0, 0, 0);
            mainLayout->setSpacing(0);

            auto *topWidget = new QWidget(this);
            topWidget->setAttribute(Qt::WA_TranslucentBackground);
            auto *topLayout = new QVBoxLayout(topWidget);
            topLayout->setContentsMargins(50, 130, 50, 0);
            topLayout->setSpacing(18);
            topLayout->addWidget(m_greeting, 0, Qt::AlignCenter);
            topLayout->addWidget(m_subtitle, 0, Qt::AlignCenter);
            topLayout->addStretch();

            auto *buttonWidget = new QWidget(this);
            buttonWidget->setAttribute(Qt::WA_TranslucentBackground);
            auto *buttonLayout = new QHBoxLayout(buttonWidget);
            buttonLayout->setContentsMargins(50, 50, 50, 100);
            buttonLayout->setSpacing(30);
            buttonLayout->addStretch();
            buttonLayout->addWidget(m_scheduleButton);
            buttonLayout->addStretch();

            mainLayout->addWidget(topWidget);
            mainLayout->addWidget(buttonWidget);

            // sensible defaults; caller may update text or connect the button



            m_greeting->setText("Hello, professor,\nwelcome back ☀");
            m_subtitle->setText("Manage your schedules and teaching resources");
        }

        QPushButton* scheduleButton() const { return m_scheduleButton; }

    protected:
        void paintEvent(QPaintEvent *event) override {
            Q_UNUSED(event);
            QPainter painter(this);
            painter.setRenderHint(QPainter::Antialiasing, true);

            const int w = width();
            const int h = height();

            QColor bottomColor("#E7E9B5");
            QColor topColor("#006A5C");

            // Fill base
            painter.fillRect(rect(), bottomColor);

            // Top wavy shape
            QPainterPath topPath;
            topPath.moveTo(0, 0);
            topPath.lineTo(w, 0);

            int waveYRight = int(h * 0.30);
            int waveYLeft  = int(h * 0.55);

            topPath.lineTo(w, waveYRight);

            QPointF c1(w * 0.75, waveYRight + h * 0.25);
            QPointF c2(w * 0.40, waveYLeft  - h * 0.10);
            QPointF end(0, waveYLeft);

            topPath.cubicTo(c1, c2, end);
            topPath.lineTo(0, 0);
            topPath.closeSubpath();

            painter.fillPath(topPath, topColor);
        }

    private:
        GradientLabel *m_greeting = nullptr;
        QLabel *m_subtitle = nullptr;
        QPushButton *m_scheduleButton = nullptr;
    };

    // create and return the local view; caller can further customize or connect the button
    auto *view = new LocalProfessorView(parent);

    // Connect the schedule button to create and show the schedule widget
    QObject::connect(view->scheduleButton(), &QPushButton::clicked, [this, view, user]() {
    QWidget* scheduleWidget = this->createScheduleWidget(nullptr, user);
    scheduleWidget->setAttribute(Qt::WA_DeleteOnClose);
    scheduleWidget->show();
});

    return view;
}

QWidget* Professor::createScheduleWidget(QWidget *parent, User *user) {
    // Create a schedule widget similar to SchedulesWindow but as a QWidget
    class ProfessorScheduleWidget : public QWidget {
    public:
        explicit ProfessorScheduleWidget(QWidget *parent = nullptr) : QWidget(parent) {
            setupUi();
        }

    private:
        void setupUi() {
            resize(1200, 800);
            setWindowTitle("My Schedules");
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

            // Schedule table
            m_scheduleTable = new QTableWidget(this);
            QStringList timeSlots = {"08:00-10:00", "10:00-12:00", "12:00-14:00",
                                     "14:00-16:00", "16:00-18:00", "18:00-20:00"};
            QStringList subGroups = {"Group 1A", "Group 1B", "Group 2A",
                                     "Group 2B", "Group 3A", "Group 3B"};

            m_scheduleTable->setRowCount(timeSlots.size());
            m_scheduleTable->setColumnCount(subGroups.size());
            m_scheduleTable->setVerticalHeaderLabels(timeSlots);
            m_scheduleTable->setHorizontalHeaderLabels(subGroups);

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

            for (int col = 0; col < subGroups.size(); ++col) {
                m_scheduleTable->setColumnWidth(col, 180);
            }

            for (int row = 0; row < timeSlots.size(); ++row) {
                m_scheduleTable->setRowHeight(row, 100);
            }

            m_scheduleTable->horizontalHeader()->setSectionResizeMode(QHeaderView::Fixed);
            m_scheduleTable->verticalHeader()->setSectionResizeMode(QHeaderView::Fixed);
            m_scheduleTable->verticalHeader()->setDefaultSectionSize(100);
            m_scheduleTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
            m_scheduleTable->setSelectionMode(QAbstractItemView::SingleSelection);



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
                QTableWidget::item:selected {
                    background-color: #9ECFD4;
                    border: 2px solid #016B61;
                }
                QTableWidget::item:focus {
                    border: 2px solid #016B61;
                    outline: none;
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

            mainLayout->addWidget(titleLabel);
            mainLayout->addLayout(selectorLayout);
            mainLayout->addWidget(m_scheduleTable, 1);
            mainLayout->addWidget(m_backButton, 0, Qt::AlignLeft);

            // Populate with sample data
            populateScheduleTable();

            // Connect signals
            connect(m_daySelector, &QComboBox::currentTextChanged,
                    this, &ProfessorScheduleWidget::updateScheduleForDay);
            connect(m_backButton, &QPushButton::clicked, this, &QWidget::close);
        }

        void populateScheduleTable() {
            for (int row = 0; row < m_scheduleTable->rowCount(); ++row) {
                for (int col = 0; col < m_scheduleTable->columnCount(); ++col) {
                    auto *cellWidget = new QWidget();
                    auto *cellLayout = new QVBoxLayout(cellWidget);
                    cellLayout->setContentsMargins(5, 5, 5, 5);
                    cellLayout->setSpacing(5);

                    auto *subjectLabel = new QLabel("Mathematics", cellWidget);
                    subjectLabel->setStyleSheet("font-weight: bold; font-size: 13px; color: #016B61; background-color: transparent;");
                    subjectLabel->setAlignment(Qt::AlignCenter);

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

        void updateScheduleForDay(const QString &day) {
            Q_UNUSED(day);
            populateScheduleTable();
        }

        QComboBox *m_daySelector;
        QTableWidget *m_scheduleTable;
        QPushButton *m_backButton;
    };

    return new ProfessorScheduleWidget(parent);
}


std::map<TimeUtilis::Day, std::vector<Schedule>> Professor::initialiseSchedules(){
    return std::map<TimeUtilis::Day, std::vector<Schedule>>();
}


