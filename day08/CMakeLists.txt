
add_executable(TestAOCDay08
        day08.cpp
        testday08.cpp
        ../utils/aocutils.cpp
        )
target_link_libraries(TestAOCDay08
        gtest_main
        )
add_test(TestAOCDay08 TestAOCDay08)

add_executable(AOCDay08
        day08.cpp
        main.cpp
        ../utils/aocutils.cpp
        )
