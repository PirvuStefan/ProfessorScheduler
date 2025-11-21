#include "professorwindow.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QFont>
#include <QPainterPath>
#include <QPushButton>
#include <QLinearGradient>

#include "SchedulesWindow.h"

// GradientLabel implementation
GradientLabel::GradientLabel(const QString &text, QWidget *parent)
    : QLabel(text, parent)
{
    setAttribute(Qt::WA_TranslucentBackground);
}

void GradientLabel::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    // Create gradient from teal to green to yellow
    QLinearGradient gradient(0, 0, width(), 0);
    gradient.setColorAt(0.0, QColor("#70B2B2"));   // Teal
    gradient.setColorAt(0.5, QColor("#57C785"));   // Green
    gradient.setColorAt(1.0, QColor("#EDDD53"));   // Yellow

    QBrush gradientBrush(gradient);
    painter.setBrush(gradientBrush);
    painter.setPen(QPen(gradientBrush, 0));

    // Set font
    painter.setFont(font());

    // Draw text with gradient
    painter.drawText(rect(), alignment(), text());
}


ProfessorWindow::ProfessorWindow(const std::string &professorName,
                                 QWidget *parent)
    : QWidget(parent)
{
    QString nameQString = QString::fromStdString(professorName);
    setupUi(nameQString);
}

void ProfessorWindow::setupUi(const QString &professorName)
{
    // Size similar to your mockup (800x600)
    resize(800, 600);
    setWindowTitle("Professor");

    // Transparent base; everything drawn in paintEvent
    setAttribute(Qt::WA_OpaquePaintEvent);
    setAutoFillBackground(false);

    QString textStyle = R"(
        #brandSubtitle {
            color: #E5E9C5;
            font-size: 16px;
            line-height: 24px;
        }
    )";

    // ----- Labels -----
    m_greetingLabel = new GradientLabel("Hello, " + professorName + ", \nwelcome back ☀", this);
    m_nameLabel     = new QLabel("Manage your schedules and teaching resources", this);

    // Colors matching the screenshot
    // Greeting: light teal #76B2BC approx
    QPalette greetPal = m_greetingLabel->palette();
    greetPal.setColor(QPalette::WindowText, QColor("#76B2BC"));
    m_greetingLabel->setPalette(greetPal);


    // Name: white (this is now the subtitle)
    QPalette namePal = m_nameLabel->palette();
    namePal.setColor(QPalette::WindowText, Qt::white);
    m_nameLabel->setPalette(namePal);

    // Fonts
    QFont greetingFont;
    greetingFont.setPointSize(26);
    greetingFont.setBold(true);
    m_greetingLabel->setFont(greetingFont);

    QFont nameFont;
    nameFont.setPointSize(18);
    nameFont.setBold(false);
    m_nameLabel->setFont(nameFont);

    // Remove label backgrounds
    m_greetingLabel->setAttribute(Qt::WA_TranslucentBackground);
    m_nameLabel->setAttribute(Qt::WA_TranslucentBackground);

    // ----- Buttons -----
    m_scheduleButton = new QPushButton("View My Schedules", this);


    // Button styling matching MainWindow
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

        QPushButton:hover {
            background-color: #70B2B2;
        }

        QPushButton:pressed {
            background-color: #9ECFD4;
        }
    )";



    m_scheduleButton->setStyleSheet(buttonStyle);
    m_scheduleButton->setCursor(Qt::PointingHandCursor);
    // Layout: text at top, buttons below the curve
    auto *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    mainLayout->setSpacing(0);

    // Top section for text - centered
    auto *topWidget = new QWidget(this);
    topWidget->setAttribute(Qt::WA_TranslucentBackground);
    auto *topLayout = new QVBoxLayout(topWidget);
    topLayout->setContentsMargins(50, 130, 50, 0);
    topLayout->setSpacing(18);
    topLayout->addWidget(m_greetingLabel, 0, Qt::AlignCenter);
    topLayout->addWidget(m_nameLabel, 0, Qt::AlignCenter);
    topLayout->addStretch();

    // Bottom section for buttons - centered
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

    setLayout(mainLayout);



    connect(m_scheduleButton, &QPushButton::clicked, this, &ProfessorWindow::onScheduleButtonClicked);

}

void ProfessorWindow::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    const int w = width();
    const int h = height();

    // Colors from mockup:
    // bottom: dark teal  #006A5C (approx)
    // top: light cream   #E7E9B5 (approx)
    QColor bottomColor("#E7E9B5");
    QColor topColor("#006A5C");

    // ---- Paint bottom solid color ----
    painter.fillRect(rect(), bottomColor);

    // ---- Paint top wavy shape ----
    QPainterPath topPath;

    // Start from left top
    topPath.moveTo(0, 0);
    topPath.lineTo(w, 0);

    // Right edge down a bit where wave touches
    int waveYRight = h * 0.30;        // ~30% from top on right
    int waveYLeft  = h * 0.55;        // ~55% from top on left (lower)

    topPath.lineTo(w, waveYRight);

    // Draw smooth wave from right to left using a cubic Bezier curve.
    // Tune control points to match screenshot curvature.
    QPointF c1(w * 0.75, waveYRight + h * 0.25);  // first control
    QPointF c2(w * 0.40, waveYLeft  - h * 0.10);  // second control
    QPointF end(0, waveYLeft);

    topPath.cubicTo(c1, c2, end);

    // Close path up the left edge
    topPath.lineTo(0, 0);
    topPath.closeSubpath();

    painter.fillPath(topPath, topColor);
}


void ProfessorWindow::onScheduleButtonClicked() {
    auto *schedulesWindow = new SchedulesWindow(nullptr);
    schedulesWindow->setAttribute(Qt::WA_DeleteOnClose);

    connect(schedulesWindow, &QWidget::destroyed, this, [this]() {
        this->show();
    });

    schedulesWindow->show();
    this->hide();
}
