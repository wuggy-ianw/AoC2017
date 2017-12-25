
add_executable(TestAOCDay18
        day18.cpp
        testday18.cpp
        )
target_link_libraries(TestAOCDay18
        gtest_main
        )
add_test(TestAOCDay18 TestAOCDay18)

add_executable(AOCDay18
        day18.cpp
        main.cpp
        )
