
add_executable(TestAOCDay05
        day05.cpp
        testday05.cpp
        )
target_link_libraries(TestAOCDay05 gtest_main)
add_test(TestAOCDay05 TestAOCDay05)

add_executable(AOCDay05
        day05.cpp
        main.cpp
        )
