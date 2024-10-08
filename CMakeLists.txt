cmake_minimum_required(VERSION 3.18)
project(OneText)

add_definitions(-Wall)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_PREFIX_PATH "D:\\Installed\\Qt\\Core\\6.8.0\\mingw_64\\lib\\cmake\\Qt6")
set(QT_VERSION 6)

EXECUTE_PROCESS(
        COMMAND git rev-list --count HEAD
        OUTPUT_VARIABLE COMMIT_COUNT
        ERROR_VARIABLE GIT_ERROR
)

if(GIT_ERROR)
    message(FATAL_ERROR "Failed to get commit count: ${GIT_ERROR}")
endif ()

set(VERSION_BASIC 1)
set(VERSION_API ${QT_VERSION})
set(VERSION_UI 1)
set(VERSION_PATCH ${COMMIT_COUNT})

set(CURRENT_VERSION_CODE "${VERSION_BASIC}.${VERSION_API}.${VERSION_UI}.${VERSION_PATCH}")

string(REGEX REPLACE "\n$" "" CURRENT_VERSION_CODE ${CURRENT_VERSION_CODE})

message("CURRENT_VERSION_CODE is: " ${CURRENT_VERSION_CODE})

configure_file(
        version.h.in
        ${CMAKE_CURRENT_SOURCE_DIR}/version.h
        @ONLY
)


#set(CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++")
set(REQUIRED_LIBS Core Gui Widgets SerialPort Network)
set(REQUIRED_LIBS_QUALIFIED
        Qt${QT_VERSION}::Core
        Qt${QT_VERSION}::Gui
        Qt${QT_VERSION}::Widgets
        Qt${QT_VERSION}::SerialPort
        Qt::Network
)

add_executable(${PROJECT_NAME}
        main.cpp
        #ui类
        ui_designer.h
        version.h
        core.cpp
        core.h
        var_global.h
        main.h
        #log
        log.h
        log.cpp
)

find_package(Qt${QT_VERSION} COMPONENTS ${REQUIRED_LIBS} REQUIRED)
find_package(OpenSSL REQUIRED)
target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS_QUALIFIED} OpenSSL::Crypto)