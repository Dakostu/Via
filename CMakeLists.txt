cmake_minimum_required(VERSION 3.5)

project(Wegweiser LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 COMPONENTS Widgets LinguistTools REQUIRED)

set(TS_FILES test/test_translate.ts)

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


  add_executable(Wegweiser
    main.cpp
    ${controller_src}
    ${interface_src}
    ${model_src}
    ${shapes_src}
    ${ui_src}
    ${TS_FILES}
  )

target_link_libraries(Wegweiser PRIVATE Qt5::Widgets)

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
