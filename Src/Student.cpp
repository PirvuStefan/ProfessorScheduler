//
// Created by Stefan Pirvu on 15.11.2025.
//

#include "../Headers/Student.h"
#include <QBoxLayout>
#include <QLabel>
#include <QPainter>
#include <QPainterPath>
#include <QPushButton>
#include <QWidget>

void Student::AccountCreated() {

    printf("Student Account Created\n");
}

Student::Student(const User& user) : User(user) {}

Student::Student( QString email, QString password, QString name) : User(name, email, password) {}

QWidget* Student::createWidget(QWidget* parent) {
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
            m_scheduleButton = new QPushButton("View Schedule", this);
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

    return view;
}
