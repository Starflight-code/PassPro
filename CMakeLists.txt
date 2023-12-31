cmake_minimum_required(VERSION 3.5)

project(PassPro VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)
find_package(OpenSSL REQUIRED)

set(PROJECT_SOURCES
    main.cpp
    mainwindow.h
    mainwindow.cpp
    mainwindow.ui
    entryviewer.h
    entryviewer.cpp
    entryviewer.ui
    loginwindow.h
    loginwindow.cpp
    loginwindow.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(PassPro
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        Data_Structures/PasswordEntry.cpp
        loginwindow.h loginwindow.cpp loginwindow.ui
        entryviewer.h entryviewer.cpp entryviewer.ui
        Data_Storage/DatabaseManager.h
        Data_Storage/DatabaseObject.h
        Data_Storage/DatabaseManager.cpp
        Data_Storage/DatabaseObject.cpp
        Cryptography/CryptographyStorage.h
        Cryptography/Cryptography.cpp
        Cryptography/CryptographyStorage.cpp
        Logo.qrc
    )
else()
    if(ANDROID)
        add_library(PassPro SHARED
            ${PROJECT_SOURCES}
        )
    else()
        add_executable(PassPro
            ${PROJECT_SOURCES}
            Cryptography/Cryptography.cpp
            Cryptography/CryptographyStorage.h
            Cryptography/CryptographyStorage.cpp
            Data_Storage/DatabaseManager.h
            Data_Storage/DatabaseManager.cpp
            Data_Storage/DatabaseObject.h
            Data_Storage/DatabaseObject.cpp
            Data_Structures/PasswordEntry.h
            Data_Structures/PasswordEntry.cpp
            Data_Structures/SecureString.cpp
            Logo.qrc



        )
    endif()
endif()

target_link_libraries(PassPro PRIVATE
    Qt${QT_VERSION_MAJOR}::Widgets
    OpenSSL::SSL
    OpenSSL::Crypto
    ClipboardXX
)

if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.PassPro)
endif()

set_target_properties(PassPro PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS PassPro
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(PassPro)
endif()

#set(CLIP_EXAMPLES OFF CACHE BOOL "Compile clip examples")
#set(CLIP_TESTS OFF CACHE BOOL "Compile clip tests")
add_subdirectory(include/ClipboardXX    EXCLUDE_FROM_ALL)

set (CMAKE_STATIC_LINKER_FLAGS "-lcrypto -lssl -fstack-protector")
