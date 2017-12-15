
add_executable(TestAOCDay07
        day07.cpp
        testday07.cpp
        ../utils/aocutils.cpp
        )
target_link_libraries(TestAOCDay07
        gtest_main
        )
add_test(TestAOCDay06 TestAOCDay07)

add_executable(AOCDay07
        day07.cpp
        main.cpp
        ../utils/aocutils.cpp
        )
