
add_executable(TestAOCDay04
        day04.cpp
        testday04.cpp
        )
target_link_libraries(TestAOCDay04 gtest_main)
add_test(TestAOCDay04 TestAOCDay04)

add_executable(AOCDay04
        day04.cpp
        main.cpp
        )
