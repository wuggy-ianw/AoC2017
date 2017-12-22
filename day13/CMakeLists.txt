
add_executable(TestAOCDay13
        day13.cpp
        testday13.cpp
        ../utils/aocutils.cpp
        )
target_link_libraries(TestAOCDay13
        gtest_main
        )
add_test(TestAOCDay13 TestAOCDay13)

add_executable(AOCDay13
        day13.cpp
        main.cpp
        ../utils/aocutils.cpp
        )
