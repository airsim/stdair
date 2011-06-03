# Library sources. All listed here for simplicity, but tailored
# compilations can be done in a given subdir if a CMakeList is
# provided there and add_subdirectory is used here (and the
# corresponding sources removed from here, of course).
file (GLOB_RECURSE stdair_SOURCES *.cpp)

# Compilation
#set (CMAKE_CXX_FLAGS "-g -Wall -Wextra -pedantic -Werror")
set (CMAKE_CXX_FLAGS "-g -Wall -Werror")
include_directories (BEFORE ${CMAKE_SOURCE_DIR} ${CMAKE_BINARY_DIR}) 

# Assembling
add_executable (${PROJECT_NAME} ${PROJECT_NAME}.cpp)
target_link_libraries (${PROJECT_NAME} ${STDAIR_LIBRARIES} ${CMAKE_REQUIRED_LIBRARIES})
add_dependencies (${PROJECT_NAME} ${STDAIR_LIBRARIES})

# Install binaries
install (TARGETS ${PROJECT_NAME} RUNTIME DESTINATION bin)
