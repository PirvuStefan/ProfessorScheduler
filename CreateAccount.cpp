//
// Created by Stefan Pirvu on 13.11.2025.
//

#include "CreateAccount.h"

#include <fstream>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QCheckBox>
#include <QMessageBox>
#include <QWidget>
#include <QDir>
#include <QFile>

void CreateAccount::storeAccountDetails(const QString &fullName,const QString &email,const QString &password,bool isProfessor) {
    // Ensure the Accounts directory exists
    QDir dir;
    if (!dir.exists("Accounts")) {
        if (!dir.mkpath("Accounts")) {
            qWarning("Could not create Accounts directory.");
            return;
        }
    }

    QFile file("Accounts/accounts.txt");


    if (!file.open(QIODevice::Append | QIODevice::Text)) {
        qWarning("Could not open accounts.txt for writing.");
        return;
    }

    QTextStream out(&file);


    out << fullName << ","
        << email << ","
        << password << ","
        << (isProfessor ? "1" : "0")   // store bool as 1/0
        << "\n";
    // we do store the data in the text file comma delimited for future purposes, if in the near future we want to store them in a database or in an excel sheet, the CSV format will do the job


    file.close();
}


CreateAccount::CreateAccount(QWidget *parent)
    : QMainWindow(parent) {
    setupUi();
    applyStyles();
}

CreateAccount::~CreateAccount() {
}

void CreateAccount::setupUi() {
    auto *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    auto *mainLayout = new QHBoxLayout(centralWidget);
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);

    // Left panel - Branding
    auto *leftPanel = new QWidget(this);
    leftPanel->setObjectName("leftPanel");
    leftPanel->setMinimumWidth(350);

    auto *leftLayout = new QVBoxLayout(leftPanel);
    leftLayout->setContentsMargins(40, 40, 40, 40);

    auto *brandTitle = new QLabel("Professor\nScheduler", this);
    brandTitle->setObjectName("brandTitle");
    brandTitle->setWordWrap(true);

    auto *brandSubtitle = new QLabel("Join us to organize your\nacademic life better", this);
    brandSubtitle->setObjectName("brandSubtitle");
    brandSubtitle->setWordWrap(true);

    leftLayout->addStretch();
    leftLayout->addWidget(brandTitle);
    leftLayout->addSpacing(20);
    leftLayout->addWidget(brandSubtitle);
    leftLayout->addStretch();

    // Right panel - Create Account form
    auto *rightPanel = new QWidget(this);
    rightPanel->setObjectName("rightPanel");

    auto *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setAlignment(Qt::AlignCenter);

    auto *formWidget = new QWidget(this);
    formWidget->setMaximumWidth(350);
    auto *formLayout = new QVBoxLayout(formWidget);
    formLayout->setSpacing(0);

    // Header
    auto *headerLabel = new QLabel("Create Account", this);
    headerLabel->setObjectName("welcomeLabel");

    auto *subtitleLabel = new QLabel("Fill in your details to get started", this);
    subtitleLabel->setObjectName("subtitleLabel");

    formLayout->addWidget(headerLabel);
    formLayout->addSpacing(10);
    formLayout->addWidget(subtitleLabel);
    formLayout->addSpacing(35);

    // Full Name field
    auto *nameLabel = new QLabel("Full Name", this);
    nameLabel->setObjectName("fieldLabel");
    fullNameLineEdit = new QLineEdit(this);
    fullNameLineEdit->setObjectName("inputField");
    fullNameLineEdit->setPlaceholderText("Enter your full name");
    fullNameLineEdit->setMinimumHeight(50);

    formLayout->addWidget(nameLabel);
    formLayout->addSpacing(8);
    formLayout->addWidget(fullNameLineEdit);
    formLayout->addSpacing(20);

    // Email field
    auto *emailLabel = new QLabel("Email", this);
    emailLabel->setObjectName("fieldLabel");
    emailLineEdit = new QLineEdit(this);
    emailLineEdit->setObjectName("inputField");
    emailLineEdit->setPlaceholderText("Enter your email");
    emailLineEdit->setMinimumHeight(50);

    formLayout->addWidget(emailLabel);
    formLayout->addSpacing(8);
    formLayout->addWidget(emailLineEdit);
    formLayout->addSpacing(20);

    // Password field
    auto *passwordLabel = new QLabel("Password", this);
    passwordLabel->setObjectName("fieldLabel");
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setObjectName("inputField");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setPlaceholderText("Enter your password");
    passwordLineEdit->setMinimumHeight(50);

    formLayout->addWidget(passwordLabel);
    formLayout->addSpacing(8);
    formLayout->addWidget(passwordLineEdit);
    formLayout->addSpacing(20);

    // Confirm Password field
    auto *confirmPasswordLabel = new QLabel("Confirm Password", this);
    confirmPasswordLabel->setObjectName("fieldLabel");
    confirmPasswordLineEdit = new QLineEdit(this);
    confirmPasswordLineEdit->setObjectName("inputField");
    confirmPasswordLineEdit->setEchoMode(QLineEdit::Password);
    confirmPasswordLineEdit->setPlaceholderText("Confirm your password");
    confirmPasswordLineEdit->setMinimumHeight(50);

    formLayout->addWidget(confirmPasswordLabel);
    formLayout->addSpacing(8);
    formLayout->addWidget(confirmPasswordLineEdit);
    formLayout->addSpacing(20);

    // Professor checkbox
    professorCheckBox = new QCheckBox("I am a Professor", this);
    professorCheckBox->setObjectName("professorCheckBox");

    formLayout->addWidget(professorCheckBox);
    formLayout->addSpacing(25);

    // Create Account button
    createAccountButton = new QPushButton("Create Account", this);
    createAccountButton->setObjectName("loginButton");
    createAccountButton->setCursor(Qt::PointingHandCursor);
    connect(createAccountButton, &QPushButton::clicked, this, &CreateAccount::onCreateAccountClicked);

    formLayout->addWidget(createAccountButton);
    formLayout->addSpacing(20);

    // Back to login link
    auto *loginLayout = new QHBoxLayout();
    auto *loginText = new QLabel("Already have an account? ", this);
    loginText->setObjectName("normalText");
    auto *loginLink = new QLabel("<a href='#' style='color: #016B61; font-weight: 600; text-decoration: underline;'>Login</a>", this);
    loginLink->setObjectName("linkLabel");
    loginLink->setTextFormat(Qt::RichText);
    loginLink->setOpenExternalLinks(false);
    connect(loginLink, &QLabel::linkActivated, this, &CreateAccount::onBackToLoginClicked);

    loginLayout->addStretch();
    loginLayout->addWidget(loginText);
    loginLayout->addWidget(loginLink);
    loginLayout->addStretch();

    formLayout->addLayout(loginLayout);

    rightLayout->addWidget(formWidget);

    // Add panels to main layout
    mainLayout->addWidget(leftPanel, 1);
    mainLayout->addWidget(rightPanel, 1);

    setWindowTitle("Professor Scheduler - Create Account");
    resize(900, 600);
    setMinimumSize(900, 700);
}

void CreateAccount::applyStyles() {
    QString style = R"(
        QMainWindow {
            background-color: #E5E9C5;
        }

        #leftPanel {
            background-color: #016B61;
        }

        #rightPanel {
            background-color: #E5E9C5;
        }

        #brandTitle {
            color: white;
            font-size: 32px;
            font-weight: bold;
        }

        #brandSubtitle {
            color: #E5E9C5;
            font-size: 16px;
            line-height: 24px;
        }

        #welcomeLabel {
            color: #016B61;
            font-size: 28px;
            font-weight: bold;
        }

        #subtitleLabel {
            color: #70B2B2;
            font-size: 14px;
        }

        #fieldLabel {
            color: #016B61;
            font-size: 14px;
            font-weight: 600;
        }

        #inputField {
            padding: 12px;
            font-size: 16px;
            border: 2px solid #70B2B2;
            border-radius: 4px;
            background-color: white;
            color: #016B61;
        }

        #inputField:focus {
            border: 2px solid #016B61;
            outline: none;
        }

        #professorCheckBox {
            color: #016B61;
            font-size: 14px;
            font-weight: 500;
        }

        #professorCheckBox::indicator {
            width: 20px;
            height: 20px;
            border: 2px solid #70B2B2;
            border-radius: 4px;
            background-color: white;
        }

        #professorCheckBox::indicator:checked {
            background-color: #016B61;
            border: 2px solid #016B61;
        }

        #loginButton {
            background-color: #016B61;
            color: white;
            font-size: 18px;
            font-weight: 600;
            padding: 12px 20px;
            border: none;
            border-radius: 5px;
            min-height: 48px;
        }

        #loginButton:hover {
            background-color: #70B2B2;
        }

        #loginButton:pressed {
            background-color: #9ECFD4;
        }

        #linkLabel {
            font-size: 12px;
        }

        #normalText {
            color: #70B2B2;
            font-size: 12px;
        }
    )";
    this->setStyleSheet(style);
}

void CreateAccount::onCreateAccountClicked() {
    QString fullName = fullNameLineEdit->text().trimmed();
    QString email = emailLineEdit->text().trimmed();
    QString password = passwordLineEdit->text();
    QString confirmPassword = confirmPasswordLineEdit->text();
    bool isProfessor = professorCheckBox->isChecked();

    // Validation
    if (fullName.isEmpty()) {
        QMessageBox::warning(this, "Validation Error",
                           "Please enter your full name.");
        return;
    }

    if (email.isEmpty()) {
        QMessageBox::warning(this, "Validation Error",
                           "Please enter your email address.");
        return;
    }

    if (password.isEmpty()) {
        QMessageBox::warning(this, "Validation Error",
                           "Please enter a password.");
        return;
    }

    if (password.length() < 6) {
        QMessageBox::warning(this, "Validation Error",
                           "Password must be at least 6 characters long.");
        return;
    }

    bool digit_found = false;

    for( QChar c : password ) {
        if( c >= '0' && c <= '9' ) {
            digit_found = true;
            break;
        }

    }
    if(!digit_found) {
        QMessageBox::warning(this, "Validation Error",
                           "Password must contain at least one digit.");
        return;
    }

    if (password != confirmPassword) {
        QMessageBox::warning(this, "Validation Error",
                           "Passwords do not match.");
        return;
    }

    // TODO: Implement actual account creation logic here
    QString accountType = isProfessor ? "Professor" : "Student";
    QMessageBox::information(this, "Account Created",
                            QString("Account created for %1\nEmail: %2\nType: %3")
                            .arg(fullName).arg(email).arg(accountType));

    // After successful creation, go back to login
    storeAccountDetails(fullName, email, password, isProfessor);
    onBackToLoginClicked();
}

void CreateAccount::onBackToLoginClicked() {
    close();
}

