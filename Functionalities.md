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

## Schedule Management & Composition

To manage academic timeframes, the User class uses **Composition** by holding a collection of Schedule objects. This allows each professor or student to maintain their own personalized timetable.

### Schedule Class Attributes

The `Schedule` class encapsulates all data relevant to a specific academic slot, including the subject, location, and the type of activity (lecture, lab, or seminar).

```cpp
class Schedule {
private:
    std::string subject;    // Name of the course
    std::string professor;  // Name of the instructor
    std::string type;       // Type of class: "lecture", "lab", "seminar"
    std::string room;       // Physical or virtual classroom
    int period;             // Time slot index
    bool optional;          // Flag for optional courses
    std::optional<bool> ownership; // Ownership status of the class ( true if owned, false if not, std::nullopt if student)
    TimeUtilis::Day day;    // Enumerated day of the week
};
```

### Modern C++ Implementation: TimeUtilis

The program utilizes a dedicated namespace `TimeUtilis` to handle temporal logic. By using `enum class`, we ensure type safety and prevent naming conflicts between different parts of the system.

- **Scoped Enums**: `Day` is defined as an `enum class`, meaning values must be accessed via `Day::MONDAY` rather than just `MONDAY`.
- **Namespace Protection**: All time-related utilities are wrapped in `TimeUtilis` to keep the global namespace clean and future-proof the codebase.

```cpp
namespace TimeUtilis {
    enum class Day {
        MONDAY = 0, TUESDAY = 1, WEDNESDAY = 2, THURSDAY = 3, FRIDAY = 4
    };
}
```

### GUI Logic & Visual Representation

The `Schedule` class includes a `getColor()` method that directly supports the GUI rendering. This logic determines the visual identity of a schedule block based on its type and the user's relationship to it:

| Class Type  | Hex Color Code | Priority |
|-------------|---------|----------|
| Lecture     | #0F8CBD | Standard |
| Lab         | #D16924 | Standard |
| Seminar     | #EDDD53 | Standard |
| Non-Owned   | #302825 | High     |

### Data Organization

To ensure the schedule is displayed chronologically, the class provides a static helper `compareSchedulesByPeriod`. This allows the program to sort schedules first by their period and subsequently by their group designation.

```cpp
bool Schedule::compareSchedulesByPeriod(const Schedule &a, const Schedule &b) {
if (a.period == b.period) {
//if periods are equal, we can further sort them by group
return a.group < b.group;
}
return a.period < b.period;
}
```

**Note on Privacy**: The `getSubject()` and `getProfessor()` methods implement an ownership check. If `ownership` is `false`, these methods return an empty string to protect the data of classes the user is not part of.
