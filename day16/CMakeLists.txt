
add_executable(TestAOCDay16
        day16.cpp
        testday16.cpp
        ../utils/aocutils.cpp
        )
target_link_libraries(TestAOCDay16
        gtest_main
        )
add_test(TestAOCDay16 TestAOCDay16)

add_executable(AOCDay16
        day16.cpp
        main.cpp
        ../utils/aocutils.cpp
        )
