project(nslookup)

include_directories(include)
file(GLOB SRC src/*.cpp src/*.cxx)
add_executable(${PROJECT_NAME} ${SRC} src/nslookup_app.cpp)

target_link_libraries(${PROJECT_NAME} ${COMMON_DEPENDENCIES})
