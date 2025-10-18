cmake_minimum_required(VERSION 3.5)
project(FuncionarioApp)

set(CMAKE_CXX_STANDARD 17)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
qt_standard_project_setup()

add_executable(FuncionarioApp
    main.cpp
    mainwindow.cpp
    funcionario.cpp
    mainwindow.h
    funcionario.h
)

target_link_libraries(FuncionarioApp PRIVATE Qt6::Widgets)
