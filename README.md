# Professor Scheduler

Professor Scheduler is a Qt desktop application designed to help university professors and students manage their academic timetables. Think of it as a digital calendar specifically built for academic life, where everyone can view their class schedules, see when and where their classes take place, and avoid scheduling conflicts.

## Who is it for?

This application serves two main groups:

### **Professors**
- View all the classes you teach
- See your weekly teaching schedule at a glance
- Add new classes to your teaching schedule
- Manage lecture times, lab sessions, and seminars
- Check classroom availability

### **Students**
- View your entire class schedule for the week
- See all your lectures, labs, and seminars
- Know which rooms your classes are in
- Keep track of mandatory and optional courses
- Plan your free time between classes

## Key Features

### 🔐 **Account System**
- Create a personal account as either a professor or student
- Secure login to access your personalized schedule
- Each user type sees information relevant to their role

### 📅 **Weekly Schedule View**
- Visual calendar showing Monday through Friday
- Time slots displayed from 8 AM onwards (2-hour blocks)
- Color-coded classes for easy identification:
  - **Blue**: Lectures
  - **Orange**: Lab sessions
  - **Yellow**: Seminars
  - **Purple**: Project sessions
  - **Blue-Green**: Optional classes
  - **Dark**: Defined/occupied slots (exclusively for professors)
  - **Transparent**: Free slots

### ⏰ **Schedule Management**
- **For Professors**: Add new classes you'll be teaching, delete existing ones
- **For Students**: See all classes you're enrolled in
- Each class shows:
  - Course name
  - Professor's name (for students)
  - Room number
  - Day and time
  - Class type (lecture, lab, or seminar)
  - Whether it's mandatory or optional

### 🚫 **Conflict Prevention**
The system automatically prevents scheduling conflicts:
- No two classes can use the same room at the same time
- Student groups can't have overlapping classes
- The system checks for conflicts before allowing a new class to be added/deleted
- The system notifies users of any scheduling issues
- Professors can only schedule classes in available time slots

### 👥 **Group Management**
- Supports different student groups (like "1A", "1B", "2A", etc.)
- Handles whole-year courses (when all students attend together)
- Ensures subgroups don't conflict with their parent groups

## How It Works

### Getting Started
1. **Launch the Application**: Open Professor Scheduler on your computer
2. **Create an Account**: 
   - Enter your full name
   - Provide your email address
   - Choose a secure password
   - Select whether you're a professor or student
3. **Log In**: Use your email and password to access your account
4. **View the accounts.txt file** in the project directory to see pre-created accounts for testing

### Viewing Your Schedule
Once logged in, you'll see:
- A personalized welcome message with your name
- A button to view your complete weekly schedule
- A clean, easy-to-read calendar layout

### For Professors: Adding a Class
1. Click to add a new schedule entry
2. Fill in the details:
   - Subject/course name
   - Type (lecture, lab, or seminar)
   - Day of the week
   - Time slot
   - Room number
   - Which student group(s) will attend
   - Whether it's mandatory or optional
3. The system will check for conflicts and confirm your entry

### For Students: Understanding Your Schedule
- All your enrolled classes appear automatically
- Colors help you quickly identify different types of classes
- Empty slots show your free time for studying or breaks
- You can see the full week at a glance

## Technical Information

**Built With:**
- C++ programming language
- Qt framework for the graphical interface
- File-based storage for schedules and accounts

**Platform:**
- Desktop application for Windows, macOS, and Linux

## Privacy & Security

- Your account information is stored securely
- Each user only sees their own relevant schedule information
- Professors see the classes they teach
- Students see the classes they attend
- Private information is protected from unauthorized access

## Setup

1. Ensure you have a C++ development environment set up with Qt installed.
2. Clone the repository to your local machine:
   - Command: `git clone https://github.com/PirvuStefan/ProfessorScheduler.git`
3. Open the project and build it using your IDE.
4. Make sure to have the Qt libraries linked properly.

## Note

This application is a prototype and may require further enhancements for production use. This is strictly a college project, not meant to be production ready or to be used in a real academic context.Feedback and contributions are welcome.