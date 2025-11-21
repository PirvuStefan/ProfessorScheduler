## Login Page

The first page when you do run the program, loads the GUI and asks for email and password, if the user does not currently have an account, he does have an option to create one

## Create Account Page
This page allows the user to create a new account by providing necessary details such as email, password, and other required information. Once the account is created, the user can log in using the newly created credentials.

## User Class Attributes

The `User` class contains the following attributes:

```cpp
protected:
    std::string fullName;    // Full name of the user
    std::string email;       // Email address for login
    std::string password;    // User password (stored as plain text)
    bool isProfessor;        // Flag indicating if user is a professor (true) or student (false)
    bool isProfessor;         // Flag indicating if user is a professor (true) or student (false)
};

```

## Main Page

Based on the login credentials, the user is directed to the main page which varies depending on whether the user is a professor or a student.
For that logic , the program uses an intermediate class `UserFactory` that checks the credentials and returns the appropriate derived class.
(Factory Design Pattern)

```cpp

User* UserFactory::createUser(User user, bool isProfessor) {
    if (isProfessor)
    return new Professor(user);
    return new Student(user);
} // the factory method that creates either a Professor or Student object based on the isProfessor flag
// we do test if the logic is successful in the main function

```

