
add_executable(TestAOCDay15
        day15.cpp
        testday15.cpp
        )
target_link_libraries(TestAOCDay15
        gtest_main
        )
add_test(TestAOCDay15 TestAOCDay15)

add_executable(AOCDay15
        day15.cpp
        main.cpp
        )
