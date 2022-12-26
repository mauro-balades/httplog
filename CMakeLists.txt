cmake_minimum_required (VERSION 3.11)

# --- Fetch FTXUI --------------------------------------------------------------
include(FetchContent)

set(FETCHCONTENT_UPDATES_DISCONNECTED TRUE)
FetchContent_Declare(ftxui
  GIT_REPOSITORY https://github.com/ArthurSonzogni/ftxui
  GIT_TAG v3.0.0
)

FetchContent_GetProperties(ftxui)
if(NOT ftxui_POPULATED)
  FetchContent_Populate(ftxui)
  add_subdirectory(${ftxui_SOURCE_DIR} ${ftxui_BINARY_DIR} EXCLUDE_FROM_ALL)
endif()

# ------------------------------------------------------------------------------

file(GLOB_RECURSE PROJECT_HEADERS include/frontend/*.hpp include/backend/*.hpp)
file(GLOB_RECURSE PROJECT_SOURCES src/*.cpp src/frontend/*.cpp src/backend/*.cpp)
file(GLOB_RECURSE PROJECT_CMAKE_UTILS cmake/*.cmake)
file(GLOB_RECURSE PROJECT_MISC *.md *.txt)
set (PROJECT_FILES
  ${PROJECT_HEADERS}
  ${PROJECT_SOURCES}
  ${PROJECT_CMAKE_UTILS}
  ${PROJECT_MISC})

project(httplog
  LANGUAGES CXX
  VERSION 1.0.0
)

add_executable(httplog ${PROJECT_FILES})
target_include_directories(${PROJECT_NAME} PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
    $<INSTALL_INTERFACE:include> PRIVATE source)
    target_include_directories(${PROJECT_NAME} PUBLIC ${PROJECT_INCLUDE_DIRS})

# message(LOG "${PROJECT_FILES}")

target_link_libraries(httplog
  PRIVATE ftxui::screen
  PRIVATE ftxui::dom
  PRIVATE ftxui::component
)