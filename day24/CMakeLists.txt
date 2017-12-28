
add_executable(TestAOCDay24
        day24.cpp
        testday24.cpp
        ../utils/aocutils.cpp
        )
target_link_libraries(TestAOCDay24
        gtest_main
        )
add_test(TestAOCDay24 TestAOCDay24)

add_executable(AOCDay24
        day24.cpp
        main.cpp
        ../utils/aocutils.cpp
        )
