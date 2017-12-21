
add_executable(TestAOCDay09
        day09.cpp
        testday09.cpp
        ../utils/aocutils.cpp
        )
target_link_libraries(TestAOCDay09
        gtest_main
        )
add_test(TestAOCDay09 TestAOCDay09)

add_executable(AOCDay09
        day09.cpp
        main.cpp
        ../utils/aocutils.cpp
        )
