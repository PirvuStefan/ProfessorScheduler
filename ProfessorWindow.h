#ifndef PROFESSORWINDOW_H
#define PROFESSORWINDOW_H

#include <QWidget>
#include <QLabel>
#include <string>

class QPushButton;

// Custom label for gradient text
class GradientLabel : public QLabel
{
    Q_OBJECT

public:
    explicit GradientLabel(const QString &text, QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;
};

class ProfessorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ProfessorWindow(const std::string& professorName,
                             QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private slots:
    void onScheduleButtonClicked();

private:
    GradientLabel *m_greetingLabel;
    QLabel *m_nameLabel;
    QPushButton *m_scheduleButton;

    void setupUi(const QString &professorName);
};

#endif // PROFESSORWINDOW_H
