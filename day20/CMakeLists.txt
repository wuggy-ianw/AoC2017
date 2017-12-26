
add_executable(TestAOCDay20
        day20.cpp
        testday20.cpp
        ../utils/aocutils.cpp
        )
target_link_libraries(TestAOCDay20
        gtest_main
        )
add_test(TestAOCDay20 TestAOCDay20)

add_executable(AOCDay20
        day20.cpp
        main.cpp
        ../utils/aocutils.cpp
        )
