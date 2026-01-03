## Login Page

The first page when you do run the program, loads the GUI and asks for email and password, if the user does not currently have an account, he does have an option to create one

## Create Account Page
This page allows the user to create a new account by providing necessary details such as email, password, and other required information. Once the account is created, the user can log in using the newly created credentials.

## User Class Attributes

The `User` abstract class contains the following attributes:

```cpp
std::string fullName;
std::string email;
std::string password;
std::map < TimeUtilis::Day, std::vector < Schedule > > schedules; 

virtual void initialiseSchedules() = 0 ; 
    virtual void AccountCreated() ;    
    virtual void AccountLogin()  = 0 ;
    virtual QWidget* createWidget(QWidget *parent) = 0 ; // we will override this method in derived classes to set the user interface depending on the type of user
    virtual QWidget* createScheduleWidget(QWidget *parent) = 0 ; // we will override this method in derived classes to set the schedule interface depending on the type of user


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

### Modern C++ Enums

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

**Note on Privacy**: The `getSubject()` and `getProfessor()` methods implement an ownership check. If `ownership` is `std::nullopt`, these methods return an empty string to protect the data of classes that the user does not have access.
We use std::optional<bool> for that purpose to represent three states: owned, not owned, and not applicable (for students), similar to Boolean in Java (tertiary logic).

```cpp
std::string Schedule::getSubject() const {
if (ownership == false) return "";
return subject;
}

std::string Schedule::getProfessor() const {
if (ownership == false) return "";
return professor;
}
```

The description of the schedules is displayed based on the attributes ownership ( polymorphic behavior depending on the user type, but without any dynamic cast or override in the derived class).

## Data Strorage

The program uses txt files to store user data and schedules.Every information is stored in a CSV format to make if future migrations easier if needed. (e.g. moving to a database system later on).

```cpp  
void Schedule::addScheduleToFile() {
QFile file("Schedules/schedules.txt");
if (!file.open(QIODevice::Append | QIODevice::Text)) {
return;
}

    QTextStream out(&file);
    out << QString::fromStdString(professor) << ","
        << QString::fromStdString(subject) << ","
        << QString::fromStdString(type) << ","
        << QString::fromStdString( (day == TimeUtilis::Day::MONDAY) ? "Monday" :
                                    (day == TimeUtilis::Day::TUESDAY) ? "Tuesday" :
                                    (day == TimeUtilis::Day::WEDNESDAY) ? "Wednesday" :
                                    (day == TimeUtilis::Day::THURSDAY) ? "Thursday" :
                                    "Friday") << ","
        << QString::number(period) << ","
        << QString::fromStdString(room) << ","
        << (optional ? "optional" : "mandatory") << ","
        << QString::fromStdString(group) << "\n";

    std::cout << "Succesfully added the following schedule to the system";
    print();

    file.close();
    // example of a standard write operation to a text file in C++ using Qt framework
    // each attribute is separated by a comma to follow the CSV format
}
```
