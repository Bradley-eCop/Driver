file(GLOB SOURCES "*.c")
include_directories(include)
add_library(QuestFitApplicationInterface SHARED ${SOURCES})
target_link_libraries(QuestFitApplicationInterface instrumentDriver)

file(GLOB TEST_SOURCES "test/*.c")
add_executable(Test_appIfc ${TEST_SOURCES})
target_link_libraries(Test_appIfc QuestFitApplicationInterface logging)
