
add_executable(TestAOCDay12
        day12.cpp
        testday12.cpp
        ../utils/aocutils.cpp
        )
target_link_libraries(TestAOCDay12
        gtest_main
        )
add_test(TestAOCDay12 TestAOCDay12)

add_executable(AOCDay12
        day12.cpp
        main.cpp
        ../utils/aocutils.cpp
        )
