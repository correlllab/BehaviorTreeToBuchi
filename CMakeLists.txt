cmake_minimum_required(VERSION 3.14)
project(MyBTProject LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Source files
set(SOURCES
    src/main.cpp
    src/BTtoBuchiConverter.cpp
    src/BuchiNode.cpp
)

# Include directory for headers
include_directories(include)

# Add executable
add_executable(main_bt ${SOURCES})

# Include BT.CPP headers
target_include_directories(main_bt PRIVATE /usr/local/include)

# Link BT.CPP library
target_link_libraries(main_bt PRIVATE behaviortree_cpp)

# Spot library
set(SPOT_PREFIX "/opt/homebrew/opt/spot")
target_include_directories(main_bt PRIVATE ${SPOT_PREFIX}/include)

target_link_libraries(main_bt PRIVATE
    ${SPOT_PREFIX}/lib/libspot.dylib
    ${SPOT_PREFIX}/lib/libspotltsmin.dylib
    ${SPOT_PREFIX}/lib/libspotgen.dylib
    ${SPOT_PREFIX}/lib/libbddx.dylib
)

if(APPLE)
    if(EXISTS "/opt/homebrew/lib/libspot.dylib")
        set(HOMEBREW_LIB_PATH "/opt/homebrew/lib")
    else()
        set(HOMEBREW_LIB_PATH "/usr/local/lib")
    endif()
    set_target_properties(main_bt PROPERTIES
        INSTALL_RPATH "${HOMEBREW_LIB_PATH}"
    )
endif()
