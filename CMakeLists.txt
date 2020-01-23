cmake_minimum_required(VERSION 3.5)

file(GLOB controller_src
        "controller/*.h"
        "controller/*.cpp"
        )

file(GLOB interface_src
        "interfaces/*.h"
        "interfaces/*.cpp"
        )

file(GLOB model_src
        "model/*.h"
        "model/*.cpp"
        )

file(GLOB shapes_src
        "shapes/*.h"
        "shapes/*.cpp"
        )

file(GLOB ui_src
        "ui/*.h"
        "ui/*.cpp"
        "ui/*.ui"
        )

    file(GLOB unit_test_src
        "unit-tests/*.h"
        "unit-tests/*.cpp")


set (ALL_FILES ${controller_src} ${interface_src} ${model_src} ${shapes_src} ${ui_src} ${TS_FILES})
set (LINK_LIBS PRIVATE Qt5::Widgets)
set (PACKAGES COMPONENTS Widgets LinguistTools REQUIRED)


project (UnitTests LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 ${PACKAGES})
find_package(Qt5Test REQUIRED)

set(TS_FILES test/test_translate.ts)

add_executable(UnitTests
    ${unit_test_src}
    ${ALL_FILES}
)

target_link_libraries(UnitTests ${LINK_LIBS} Qt5::Test)


project(Wegweiser LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 ${PACKAGES})

set(TS_FILES test/test_translate.ts)

  add_executable(Wegweiser
    main.cpp
    ${ALL_FILES}
  )

target_link_libraries(Wegweiser ${LINK_LIBS})

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
