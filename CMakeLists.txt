cmake_minimum_required(VERSION 3.10)
project(LEANG_EXECUTABLE)

find_package(wxWidgets REQUIRED COMPONENTS core base)
find_package(SQLite3 REQUIRED)

include(${wxWidgets_USE_FILE})

set(DIZIN_SRC       ${CMAKE_SOURCE_DIR}/src)
set(DIZIN_INCLUDE   ${CMAKE_SOURCE_DIR}/include)

set(PROGRAM_SRCS
    ${DIZIN_SRC}/main.cpp    
    ${DIZIN_SRC}/wx_gui.cpp
    ${DIZIN_SRC}/leang.cpp
    ${DIZIN_SRC}/database.cpp
    ${DIZIN_SRC}/konsol.cpp
)

set(PROGRAM_INCLUDES
    ${DIZIN_INCLUDE}/wx_gui.hpp
    ${DIZIN_INCLUDE}/leang.hpp
    ${DIZIN_INCLUDE}/database.hpp
    ${DIZIN_INCLUDE}/konsol.hpp
)

include_directories(
    ${PROGRAM_INCLUDES}
    ${wxWidgets_INCLUDE_DIRS}    
    ${SQLite3_INCLUDE_DIRS}
)

add_executable(${PROJECT_NAME} ${PROGRAM_SRCS}) 

target_link_libraries(
    ${PROJECT_NAME} 
    ${wxWidgets_LIBRARIES}
    ${SQLite3_LIBRARIES}
)
