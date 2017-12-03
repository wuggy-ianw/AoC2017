
add_executable(TestAOCDay03
        day03.cpp
        testday03.cpp
        )
target_link_libraries(TestAOCDay03 gtest_main)
add_test(TestAOCDay03 TestAOCDay03)

add_executable(AOCDay03
        day03.cpp
        main.cpp
        )


