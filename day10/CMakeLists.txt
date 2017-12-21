
add_executable(TestAOCDay10
        day10.cpp
        testday10.cpp
        ../utils/aocutils.cpp
        )
target_link_libraries(TestAOCDay10
        gtest_main
        )
add_test(TestAOCDay10 TestAOCDay10)

add_executable(AOCDay10
        day10.cpp
        main.cpp
        ../utils/aocutils.cpp
        )
