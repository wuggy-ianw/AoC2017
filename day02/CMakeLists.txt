
add_executable(TestAOCDay02
        day02.cpp
        testday02.cpp
)
target_link_libraries(TestAOCDay02 gtest_main)
add_test(TestAOCDay02 TestAOCDay02)

add_executable(AOCDay02
        day02.cpp
        main.cpp
        ../utils/aocutils.cpp
)


