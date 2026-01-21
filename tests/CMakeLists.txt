#tests/CmakeLists.txt



include(FetchContent)


FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2  

)

set(gtest_build_tests OFF CACHE BOOL "" FORCE)
set(install_gtest OFF CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)






#  subdirectory for unit tests
add_subdirectory(unit)
#  subdirectory for integration tests
add_subdirectory(integration)
