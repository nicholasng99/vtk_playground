cmake_minimum_required(VERSION 3.26)
cmake_policy(SET CMP0099 NEW)

set(APPLICATION_NAME "VtkPlayground")

project(${APPLICATION_NAME} VERSION 0.1 LANGUAGES CXX)

set(CMAKE_AUTOMOC ON)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_STANDARD 20)

find_package(Qt6 6.8 COMPONENTS Quick QuickControls2 LinguistTools REQUIRED)
qt_policy(SET QTP0001 NEW)
qt_policy(SET QTP0004 NEW)

set(PROJECT_TESTS TRUE)
include(config.cmake)

add_subdirectory(modules/utility)
add_subdirectory(modules/style)

if(${PROJECT_TESTS})
    add_subdirectory(tests/unit_test_cpp)
    add_subdirectory(tests/unit_test_qml)
endif()

file(GLOB_RECURSE PROJECT_SOURCES "src/*.cpp")
file(GLOB_RECURSE PROJECT_HEADERS "include/*.hpp" "include/*.h")
file(GLOB_RECURSE RESOURCES "resources/*.qrc")

qt_add_resources(PROJECT_RESOURCES ${RESOURCES})

qt_add_executable(${APPLICATION_NAME}
    ${PROJECT_SOURCES} ${PROJECT_HEADERS}
    ${PROJECT_RESOURCES}
)

set_target_properties(${APPLICATION_NAME} PROPERTIES
    MACOSX_BUNDLE FALSE
    WIN32_EXECUTABLE TRUE
    OUTPUT_NAME ${APPLICATION_NAME}App # prevent clash with module directory on some OS
)

# Subfolders must be grouped seperately
file(GLOB PROJECT_QMLS RELATIVE ${CMAKE_SOURCE_DIR} qml/*.qml)
source_group("Qml Files" FILES ${PROJECT_QMLS})

qt_add_qml_module(${APPLICATION_NAME}
    URI ${APPLICATION_NAME}
    VERSION 1.0
    QML_FILES ${PROJECT_QMLS}
)

target_include_directories(${APPLICATION_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${APPLICATION_NAME} PRIVATE
    Qt6::Quick
    Qt6::QuickControls2
    Styleplugin
    Utilityplugin
    Utility
    # add modules here append "plugin" to the name
)

file(GLOB_RECURSE ALL_QMLS RELATIVE ${CMAKE_SOURCE_DIR} *.qml)

qt_add_translations(${APPLICATION_NAME} TS_FILES
    translations/English.ts
    translations/Chinese.ts
    SOURCES ${ALL_QMLS} ${PROJECT_SOURCES} ${PROJECT_HEADERS}
    RESOURCE_PREFIX "/translations"
)

install(TARGETS ${APPLICATION_NAME}
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
)
