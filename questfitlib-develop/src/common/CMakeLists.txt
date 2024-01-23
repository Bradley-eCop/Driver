file(GLOB SOURCES "*.c")
include_directories(include)
add_library(common STATIC ${SOURCES})

file(GLOB TEST_SOURCES "test/*.c")
add_executable(Test_common ${TEST_SOURCES})
target_link_libraries(Test_common common)
target_link_libraries(Test_common logging)