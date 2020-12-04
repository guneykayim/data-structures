set(BINARY ${CMAKE_PROJECT_NAME})

file(GLOB SOURCES *.cpp)

add_library(${BINARY}_lib STATIC ${SOURCES})
