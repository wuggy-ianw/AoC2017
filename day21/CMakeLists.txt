
add_executable(TestAOCDay21
        day21.cpp
        testday21.cpp
        ../utils/aocutils.cpp
        )
target_link_libraries(TestAOCDay21
        gtest_main
        )
add_test(TestAOCDay21 TestAOCDay21)

add_executable(AOCDay21
        day21.cpp
        main.cpp
        ../utils/aocutils.cpp
        )
