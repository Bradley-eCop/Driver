file(GLOB SOURCES "*.c")
include_directories(include)
add_library(instrumentDriver ${SOURCES})
target_link_libraries(instrumentDriver network)
