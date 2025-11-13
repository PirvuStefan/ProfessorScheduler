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
        Schedule.cpp
        Schedule.h
        CreateAccount.cpp
        CreateAccount.h
        User.cpp
        User.h)
target_link_libraries(ProfessorScheduler_Public_
        Qt::Core
        Qt::Gui
        Qt::Widgets
)

