file(GLOB SOURCES "*.c")
include_directories(include)
add_library(network STATIC ${SOURCES})
target_link_libraries(network paho-mqtt3a-static logging common)

file(GLOB TEST_SOURCES "test/*.c")
add_executable(Test ${TEST_SOURCES})
target_link_libraries(Test network logging)