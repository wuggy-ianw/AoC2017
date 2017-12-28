
add_executable(TestAOCDay25
        day25.cpp
        testday25.cpp
        )
target_link_libraries(TestAOCDay25
        gtest_main
        )
add_test(TestAOCDay25 TestAOCDay25)

add_executable(AOCDay25
        day25.cpp
        main.cpp
        )
