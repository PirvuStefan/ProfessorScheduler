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
### Attribute Details:
- **fullName**: Stores the complete name of the user
- **email**: Used as the unique identifier for login
- **password**: Authentication credential
- **isProfessor**: Determines user role and access level
- `password` - Stores the user's password for authentication
- `isProfessor` - Boolean flag to distinguish between professors and students
