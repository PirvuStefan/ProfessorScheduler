//
// Created by Stefan Pirvu on 13.11.2025.
//

#ifndef CREATEACCOUNT_H
#define CREATEACCOUNT_H

#include <QMainWindow>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>

class CreateAccount : public QMainWindow {
    Q_OBJECT

public:
    explicit CreateAccount(QWidget *parent = nullptr);
    ~CreateAccount();

private slots:
    void onCreateAccountClicked();
    void onBackToLoginClicked();

private:
    void setupUi();
    void applyStyles();

    QLineEdit *fullNameLineEdit;
    QLineEdit *emailLineEdit;
    QLineEdit *passwordLineEdit;
    QLineEdit *confirmPasswordLineEdit;
    QCheckBox *professorCheckBox;
    QPushButton *createAccountButton;
};

#endif //CREATEACCOUNT_H
