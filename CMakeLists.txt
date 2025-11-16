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

add_executable(ProfessorScheduler_Public_ main.cpp
        MainWindow.cpp
        MainWindow.h
        Src/Schedule.cpp
        Headers/Schedule.h
        CreateAccount.cpp
        CreateAccount.h
        Src/User.cpp
        Headers/User.h
        Src/Student.cpp
        Headers/Student.h
        Src/Professor.cpp
        Headers/Professor.h
        ProfessorWindow.cpp
        ProfessorWindow.h)
target_link_libraries(ProfessorScheduler_Public_
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

