#unit/CMakeLists.txt



include(GoogleTest)


add_executable(SanityCheckTests sanity_check.cpp)



target_link_libraries(SanityCheckTests PRIVATE
    GTest::gtest_main
)














add_executable(ecs-system-test

  ecs/archetype_manager_test.cpp
  ecs/entity_manager_test.cpp

)

target_link_libraries(
    ecs-system-test PRIVATE
    GTest::gtest_main
    GTest::gmock_main
    TheEngine_ECS

)








gtest_discover_tests(ecs-system-test)

#gtest_discover_tests(SanityCheckTests)
