
cmake_minimum_required(VERSION 2.8.12)
project(testcpp)

# Parameter Setting
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_BINARY_DIR})
set(LIBRARY_OUTPUT_PATH ${PROJECT_BINARY_DIR})

set(PROJECT_THIRD_PARTY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/thirdparty)

# Get all source file
aux_source_directory(src SRC_DIR)

# Separate testing file from program source file.
set(SRC_LIST ${SRC_DIR} ${UTIL_DIR})
set(TEST_REGEX_ST "^.+_testing\\.(h|H|hcc|HCC|c|C|cc|CC|cpp|CPP)$")
foreach(srcFile ${SRC_LIST})
  if("${srcFile}" MATCHES "${TEST_REGEX_ST}")
    set(TESTING_FILE ${TESTING_FILE} ${srcFile})
    message(STATUS "ADD TESTING FILE : " ${srcFile})
  else("${srcFile}" MATCHES "${TEST_REGEX_ST}")
    set(SRC_FILE ${SRC_FILE} ${srcFile})
    message(STATUS "ADD SRC FILE : " ${srcFile})
  endif("${srcFile}" MATCHES "${TEST_REGEX_ST}")
endforeach(srcFile)

# Compiling arguments
add_definitions("-Wno-unused-result -std=c++14 -Wsign-compare -g -fwrapv -Wall")
#add_definitions("-Wall -Xlinker -export-dynamic -fstack-protector-all")

# Make libtestcpp.so or libtestcpp.a

if (BUILD_SHARED_LIBS)
  set(TestCpp_BUILD_SHARED_LIBS_DEFAULT ON)
else (BUILD_SHARED_LIBS)
  set(TestCpp_BUILD_SHARED_LIBS_DEFAULT OFF)
endif (BUILD_SHARED_LIBS)

option(TestCpp_BUILD_SHARED_LIBS "Build Shared Libraries" ${Testcpp_BUILD_SHARED_LIBS_DEFAULT})

if (TestCpp_BUILD_SHARED_LIBS)
  set(TestCpp_SHARED_OR_STATIC "SHARED")
else (TestCpp_BUILD_SHARED_LIBS)
  set(TestCpp_SHARED_OR_STATIC "STATIC")
endif (TestCpp_BUILD_SHARED_LIBS)


# Make testing program.
add_executable(testcpp ${SRC_FILE})
set(PUB_LIBRARIES pthread dl util m)
target_link_libraries(testcpp ${PUB_LIBRARIES})
