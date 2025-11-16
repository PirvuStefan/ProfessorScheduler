#include "MainWindow.h"
#include "CreateAccount.h"
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QFrame>
#include <QMessageBox>
#include <QWidget>

#include <optional>
#include <QFile>

#include "ProfessorWindow.h"
#include "Headers/User.h"

std::optional<User> MainWindow::authenticateUser(const QString &email, const QString &password) {

    // If valid, return User object; otherwise return std::nullopt, indicating login failure, that why we use optional here

    QFile file("Accounts/accounts.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        return std::nullopt;
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList parts = line.split(",");
        if (parts.size() < 4) continue;

        if (parts[1] == email && parts[2] == password) {
            bool isProfessor = (parts[3] == "1");
            return User(parts[0], parts[1], parts[2], isProfessor);
        }
    }
    return std::nullopt;
}



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent) {
    setupUi();
    applyStyles();
}

MainWindow::~MainWindow() {
}

void MainWindow::setupUi() {
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

    auto *brandSubtitle = new QLabel("Manage your academic\nschedule efficiently ✓", this);
    brandSubtitle->setObjectName("brandSubtitle");
    brandSubtitle->setWordWrap(true);

    leftLayout->addStretch();
    leftLayout->addWidget(brandTitle);
    leftLayout->addSpacing(20);
    leftLayout->addWidget(brandSubtitle);
    leftLayout->addStretch();

    // Right panel - Login form
    auto *rightPanel = new QWidget(this);
    rightPanel->setObjectName("rightPanel");

    auto *rightLayout = new QVBoxLayout(rightPanel);
    rightLayout->setAlignment(Qt::AlignCenter);

    auto *formWidget = new QWidget(this);
    formWidget->setMaximumWidth(350);
    auto *formLayout = new QVBoxLayout(formWidget);
    formLayout->setSpacing(0);

    // Welcome header
    auto *welcomeLabel = new QLabel("Welcome Back", this);
    welcomeLabel->setObjectName("welcomeLabel");

    auto *subtitleLabel = new QLabel("Please login to your account", this);
    subtitleLabel->setObjectName("subtitleLabel");

    formLayout->addWidget(welcomeLabel);
    formLayout->addSpacing(10);
    formLayout->addWidget(subtitleLabel);
    formLayout->addSpacing(40);

    // Email field
    auto *emailLabel = new QLabel("Email", this);
    emailLabel->setObjectName("fieldLabel");
    emailLineEdit = new QLineEdit(this);
    emailLineEdit->setObjectName("inputField");
    emailLineEdit->setPlaceholderText("Enter your email");

    formLayout->addWidget(emailLabel);
    formLayout->addSpacing(8);
    formLayout->addWidget(emailLineEdit);
    formLayout->addSpacing(25);

    // Password field
    auto *passwordLabel = new QLabel("Password", this);
    passwordLabel->setObjectName("fieldLabel");
    passwordLineEdit = new QLineEdit(this);
    passwordLineEdit->setObjectName("inputField");
    passwordLineEdit->setEchoMode(QLineEdit::Password);
    passwordLineEdit->setPlaceholderText("Enter your password");

    formLayout->addWidget(passwordLabel);
    formLayout->addSpacing(8);
    formLayout->addWidget(passwordLineEdit);
    formLayout->addSpacing(15);

    // Forgot password link
    auto *forgotLabel = new QLabel("<a href='#' style='color: #70B2B2; text-decoration: underline;'>Forgot password?</a>", this);
    forgotLabel->setObjectName("linkLabel");
    forgotLabel->setAlignment(Qt::AlignRight);
    forgotLabel->setTextFormat(Qt::RichText);
    forgotLabel->setOpenExternalLinks(false);

    formLayout->addWidget(forgotLabel);
    formLayout->addSpacing(30);

    // Login button
    loginButton = new QPushButton("Login", this);
    loginButton->setObjectName("loginButton");
    loginButton->setCursor(Qt::PointingHandCursor);
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::onLoginClicked);

    formLayout->addWidget(loginButton);
    formLayout->addSpacing(20);

    // Sign up link
    auto *signupLayout = new QHBoxLayout();
    auto *signupText = new QLabel("Don't have an account? ", this);
    signupText->setObjectName("normalText");
    auto *signupLink = new QLabel("<a href='#' style='color: #016B61; font-weight: 600; text-decoration: underline;'>Sign up</a>", this);
    signupLink->setObjectName("linkLabel");
    signupLink->setTextFormat(Qt::RichText);
    signupLink->setOpenExternalLinks(false);
    connect(signupLink, &QLabel::linkActivated, this, &MainWindow::onSignUpClicked);

    signupLayout->addStretch();
    signupLayout->addWidget(signupText);
    signupLayout->addWidget(signupLink);
    signupLayout->addStretch();

    formLayout->addLayout(signupLayout);

    rightLayout->addWidget(formWidget);

    // Add panels to main layout
    mainLayout->addWidget(leftPanel, 1);
    mainLayout->addWidget(rightPanel, 1);

    setWindowTitle("Professor Scheduler - Login");
    resize(900, 600);
    setMinimumSize(900, 600);
}

void MainWindow::applyStyles() {
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

void MainWindow::onLoginClicked() {
    QString email = emailLineEdit->text().trimmed();
    QString password = passwordLineEdit->text();

    // Basic validation
    if (email.isEmpty()) {
        QMessageBox::warning(this, "Validation Error",
                           "Please enter your email address.");
        return;
    }

    if (password.isEmpty()) {
        QMessageBox::warning(this, "Validation Error",
                           "Please enter your password.");
        return;
    }

    auto userResult = authenticateUser(email, password);
    if (!userResult.has_value()) {
        QMessageBox::warning(this, "Login Failed",
                           "Invalid email or password. Please try again.");
        return;
    }

    User actual = userResult.value();
    actual.Print();

    // Open Professor Window after successful login
    auto *professorWindow = new ProfessorWindow(actual.getName());
    professorWindow->setAttribute(Qt::WA_DeleteOnClose);
    professorWindow->show();
    this->hide();

    // Show main window again when professor window is closed
    connect(professorWindow, &QWidget::destroyed, this, [this]() {
        this->show();
    });
}

void MainWindow::onSignUpClicked() {
    auto *createAccountWindow = new CreateAccount(this);
    createAccountWindow->setAttribute(Qt::WA_DeleteOnClose);
    createAccountWindow->show();
    this->hide();

    connect(createAccountWindow, &QMainWindow::destroyed, this, [this]() {
        this->show();
    });
}
