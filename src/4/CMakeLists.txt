add_executable(4 4.cpp)
file(GLOB MY_TESTS "in*.txt" )
# configure_file(${MY_TESTS} ${CMAKE_CURRENT_BINARY_DIR}/)
# file(COPY ${MY_TESTS} DESTINATION ${CMAKE_CURRENT_BINARY_DIR}/)