
add_executable(TestAOCDay17
        day17.cpp
        testday17.cpp
        )
target_link_libraries(TestAOCDay17
        gtest_main
        )
add_test(TestAOCDay17 TestAOCDay17)

add_executable(AOCDay17
        day17.cpp
        main.cpp
        )
