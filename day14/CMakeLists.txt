
add_executable(TestAOCDay14
        day14.cpp
        testday14.cpp
        ../day10/day10.cpp
        )
target_link_libraries(TestAOCDay14
        gtest_main
        )
add_test(TestAOCDay14 TestAOCDay14)

add_executable(AOCDay14
        day14.cpp
        main.cpp
        ../day10/day10.cpp
        )
