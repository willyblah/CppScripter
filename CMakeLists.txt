cmake_minimum_required(VERSION 3.10)
project(CppScripter)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(wxWidgets REQUIRED COMPONENTS core base)
include(${wxWidgets_USE_FILE})

add_executable(${PROJECT_NAME} WIN32
        src/App.cpp
        src/App.h
        src/MainFrame.cpp
        src/MainFrame.h
)

target_link_libraries(${PROJECT_NAME} ${wxWidgets_LIBRARIES})
