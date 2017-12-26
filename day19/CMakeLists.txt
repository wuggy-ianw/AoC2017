
add_executable(TestAOCDay19
        day19.cpp
        testday19.cpp
        )
target_link_libraries(TestAOCDay19
        gtest_main
        )
add_test(TestAOCDay19 TestAOCDay19)

add_executable(AOCDay19
        day19.cpp
        main.cpp
        ../utils/aocutils.cpp
        )
