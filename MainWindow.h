#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>

#include "Headers/User.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    std::optional<User> authenticateUser(const QString &email, const QString &password);

    void onLoginClicked();
    void onSignUpClicked();

private:
    void setupUi();
    void applyStyles();

    QLineEdit *emailLineEdit;
    QLineEdit *passwordLineEdit;
    QPushButton *loginButton;
};

#endif // MAINWINDOW_H
