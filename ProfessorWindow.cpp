#include "professorwindow.h"

#include <QLabel>
#include <QVBoxLayout>
#include <QPainter>
#include <QPaintEvent>
#include <QFont>
#include <QPainterPath>


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

    // ----- Labels -----
    m_greetingLabel = new QLabel("Glad to see you back", this);
    m_nameLabel     = new QLabel(professorName, this);

    // Colors matching the screenshot
    // Greeting: light teal #76B2BC approx
    QPalette greetPal = m_greetingLabel->palette();
    greetPal.setColor(QPalette::WindowText, QColor("#76B2BC"));
    m_greetingLabel->setPalette(greetPal);

    // Name: white
    QPalette namePal = m_nameLabel->palette();
    namePal.setColor(QPalette::WindowText, Qt::white);
    m_nameLabel->setPalette(namePal);

    // Fonts
    QFont greetingFont;
    greetingFont.setPointSize(26);
    greetingFont.setBold(false);
    m_greetingLabel->setFont(greetingFont);

    QFont nameFont;
    nameFont.setPointSize(26);
    nameFont.setBold(true);
    m_nameLabel->setFont(nameFont);

    // Remove label backgrounds
    m_greetingLabel->setAttribute(Qt::WA_TranslucentBackground);
    m_nameLabel->setAttribute(Qt::WA_TranslucentBackground);

    // Layout: put them in upper left, similar to mockup
    auto *layout = new QVBoxLayout(this);
    layout->setContentsMargins(180, 130, 0, 0);  // tune for exact look
    layout->setSpacing(18);

    layout->addWidget(m_greetingLabel, 0, Qt::AlignLeft | Qt::AlignTop);
    layout->addWidget(m_nameLabel, 0, Qt::AlignLeft | Qt::AlignTop);
    layout->addStretch();

    setLayout(layout);
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
    QColor bottomColor("#006A5C");
    QColor topColor("#E7E9B5");

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
    QPointF c1(w * 0.75, waveYRight + h * 0.05);  // first control
    QPointF c2(w * 0.40, waveYLeft  - h * 0.10);  // second control
    QPointF end(0, waveYLeft);

    topPath.cubicTo(c1, c2, end);

    // Close path up the left edge
    topPath.lineTo(0, 0);
    topPath.closeSubpath();

    painter.fillPath(topPath, topColor);
}
