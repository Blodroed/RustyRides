cmake_minimum_required(VERSION 3.5)

project(HellHub VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Widgets)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Widgets)

set(PROJECT_SOURCES
        main.cpp
        src/ui-handlers/mainwindow.cpp
        include/ui-windows/mainwindow.h
        src/ui-design-files/mainwindow.ui
        include/Car.h
        src/Car.cpp
        include/CarManager.h
        src/CarManager.cpp
        include/JsonParser.h
        src/JsonParser.cpp
        #test/testForStuff.h
        #test/testForStuff.cpp
        include/Customer.h
        src/Customer.cpp
        src/CustomerManager.cpp
        include/CustomerManager.h
        include/ui-windows/CustomerDialog.h
        src/ui-handlers/CustomerDialog.cpp
        src/ui-design-files/customerdialog.ui
        src/ui-handlers/areyousuredialog.cpp
        include/ui-windows/areyousuredialog.h
        src/ui-design-files/areyousuredialog.ui
        include/Lease.h
        src/Lease.cpp
        include/LeaseManager.h
        src/LeaseManager.cpp
        include/ui-windows/CarDialog.h
        src/ui-handlers/CarDialog.cpp
        src/ui-design-files/cardialog.ui
        include/ui-windows/LeaseDialog.h
        src/ui-handlers/LeaseDialog.cpp
        include/ui-windows/editleasedialog.h
        src/ui-handlers/editleasedialog.cpp
        src/ui-design-files/editleasedialog.ui
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(HellHub
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET HellHub APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(HellHub SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(HellHub
            ${PROJECT_SOURCES}
        )
    endif()
endif()

# Add RapidJSON headers directory to the include path
include_directories(libs/rapidjson)

target_link_libraries(HellHub PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

# Qt for iOS sets MACOSX_BUNDLE_GUI_IDENTIFIER automatically since Qt 6.1.
# If you are developing for iOS or macOS you should consider setting an
# explicit, fixed bundle identifier manually though.
if(${QT_VERSION} VERSION_LESS 6.1.0)
  set(BUNDLE_ID_OPTION MACOSX_BUNDLE_GUI_IDENTIFIER com.example.HellHub)
endif()
set_target_properties(HellHub PROPERTIES
    ${BUNDLE_ID_OPTION}
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

include(GNUInstallDirs)
install(TARGETS HellHub
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(HellHub)
endif()
