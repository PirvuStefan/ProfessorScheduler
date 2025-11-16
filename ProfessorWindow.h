#ifndef PROFESSORWINDOW_H
#define PROFESSORWINDOW_H

#include <QWidget>
#include <string>

class QLabel;

class ProfessorWindow : public QWidget
{
    Q_OBJECT

public:
    explicit ProfessorWindow(const std::string& professorName,
                             QWidget *parent = nullptr);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QLabel *m_greetingLabel;
    QLabel *m_nameLabel;

    void setupUi(const QString &professorName);
};

#endif // PROFESSORWINDOW_H
