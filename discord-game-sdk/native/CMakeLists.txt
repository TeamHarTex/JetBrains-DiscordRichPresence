cmake_minimum_required(VERSION 3.24)

project(native)

file(GLOB SOURCE_FILES CONFIGURE_DEPENDS "src/*.cpp")

add_library(native SHARED ${SOURCE_FILES})

target_compile_features(native PUBLIC cxx_std_17)

if (MSVC)
    target_compile_definitions(native PUBLIC NOMINMAX)
endif ()

target_include_directories(native PUBLIC "../jvm/build/generated/include/" "include")

find_package(JNI REQUIRED)

target_include_directories(native PUBLIC ${JNI_INCLUDE_DIRS})

if (${CMAKE_SIZEOF_VOID_P} STREQUAL "8")
    set(ARCHITECTURE_TYPE x86-64) # 64 Bit
endif ()

find_library(
        GAMESDK_LIBRARY
        NAMES "${CMAKE_SHARED_LIBRARY_PREFIX}discord_game_sdk${CMAKE_SHARED_LIBRARY_SUFFIX}"
        NO_CMAKE_FIND_ROOT_PATH
        HINTS "lib/"
        PATH_SUFFIXES  "darwin/${ARCHITECTURE_TYPE}" "windows/${ARCHITECTURE_TYPE}" "linux/${ARCHITECTURE_TYPE}"
)

target_link_libraries(native PUBLIC ${DISCORD_LIBRARY})

if (MSVC)
    string(REPLACE ".lib" "" DISCORD_RUNTIME_LIBRARY ${DISCORD_LIBRARY})
else ()
    set(DISCORD_RUNTIME_LIBRARY ${DISCORD_LIBRARY})
endif ()

add_custom_target(DLLS COMMAND ${CMAKE_COMMAND} -E copy ${DISCORD_RUNTIME_LIBRARY} ${CMAKE_BINARY_DIR})

add_dependencies(native DLLS)
