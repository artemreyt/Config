cmake_minimum_required(VERSION 3.10)

project(Config LANGUAGES CXX)

add_subdirectory(third_party/json EXCLUDE_FROM_ALL)
add_subdirectory(Logger EXCLUDE_FROM_ALL)

set(CONFIG_SRC src/Config.cxx)
set(CONFIG_HEADERS includes/Config.hpp)

add_library(${PROJECT_NAME} SHARED ${CONFIG_SRC} ${CONFIG_HEADERS})
target_include_directories(${PROJECT_NAME} PUBLIC includes/)
target_link_libraries(${PROJECT_NAME} PUBLIC nlohmann_json::nlohmann_json Logger)
target_compile_features(${PROJECT_NAME} PUBLIC cxx_std_17)
link_libraries(stdc++fs)

add_subdirectory(examples)
