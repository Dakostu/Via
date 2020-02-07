cmake_minimum_required(VERSION 3.5)

set(EXEC_NAME Via)

file(GLOB_RECURSE ALL_SRC_HEADER_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.h" "${CMAKE_CURRENT_SOURCE_DIR}/*/*.h")
file(GLOB_RECURSE ALL_SRC_CODE_FILES "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp" "${CMAKE_CURRENT_SOURCE_DIR}/*/*.cpp")

set (ALL_FILES ${controller_src} ${interface_src} ${structures_src} ${model_src} ${shapes_src} ${ui_src} ${TS_FILES})
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
    ${ALL_SRC_HEADER_FILES}
    ${ALL_SRC_CODE_FILES}
)

target_link_libraries(UnitTests ${LINK_LIBS} Qt5::Test)


project(${EXEC_NAME} LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(Qt5 ${PACKAGES})

set(TS_FILES test/test_translate.ts)

  add_executable(${EXEC_NAME}
    main.cpp
    ${ALL_SRC_HEADER_FILES}
    ${ALL_SRC_CODE_FILES}
  )

target_link_libraries(${EXEC_NAME} ${LINK_LIBS})

qt5_create_translation(QM_FILES ${CMAKE_SOURCE_DIR} ${TS_FILES})
