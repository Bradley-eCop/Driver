file(GLOB SOURCES "*.c")
include_directories(include)
add_library(calibrationRig SHARED ${SOURCES})
target_link_libraries(calibrationRig network)
add_library(calibrationRig-static STATIC ${SOURCES})
target_link_libraries(calibrationRig-static network)

file(GLOB TEST_SOURCES "test/*.c")
add_executable(Test_calibration ${TEST_SOURCES})
target_link_libraries(Test_calibration calibrationRig-static logging)

file(GLOB DRIFT_TEST_SOURCES "driftTest/*.c")
add_executable(Test_drift ${DRIFT_TEST_SOURCES})
target_link_libraries(Test_drift calibrationRig-static logging)
