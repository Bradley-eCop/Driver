file(GLOB SOURCES "*.c")
include_directories(include)
add_library(logging STATIC ${SOURCES})