## Login Page

The first page when you do run the program, loads the GUI and asks for email and password, if the user does not currently have an account, he does have an option to create one

## Create Account Page
This page allows the user to create a new account by providing necessary details such as email, password, and other required information. Once the account is created, the user can log in using the newly created credentials.

## User Class Attributes

The `User` class contains the following attributes:

```cpp
class User {
private:
    std::string fullName;     // Full name of the user
    std::string email;        // User's email address
    std::string password;     // User's password
    bool isProfessor;         // Flag indicating if user is a professor (true) or student (false)
};
```

**Attribute Details:**
- `fullName` - Stores the complete name of the user
- `email` - Stores the user's email address for authentication
- `password` - Stores the user's password for authentication
- `isProfessor` - Boolean flag to distinguish between professors and students
