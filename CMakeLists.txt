cmake_minimum_required(VERSION 3.29)
project(ProfessorScheduler_Public_)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)


find_package(Qt6 COMPONENTS
        Core
        Gui
        Widgets
        REQUIRED)

add_executable(ProfessorScheduler_Public_ Src/main.cpp
        Src/MainWindow.cpp
        Headers/MainWindow.h
        Src/Schedule.cpp
        Headers/Schedule.h
        Src/CreateAccount.cpp
        Headers/CreateAccount.h
        Src/User.cpp
        Headers/User.h
        Src/Student.cpp
        Headers/Student.h
        Src/Professor.cpp
        Headers/Professor.h
        Src/SchedulesWindow.cpp
        Headers/SchedulesWindow.h
        Src/UserFactory.cpp
        Headers/UserFactory.h
        Headers/TimeUtilis.h)
target_link_libraries(ProfessorScheduler_Public_
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

