
add_executable(TestAOCDay11
        day11.cpp
        testday11.cpp
        ../utils/aocutils.cpp
        )
target_link_libraries(TestAOCDay11
        gtest_main
        )
add_test(TestAOCDay11 TestAOCDay11)

add_executable(AOCDay11
        day11.cpp
        main.cpp
        ../utils/aocutils.cpp
        )
