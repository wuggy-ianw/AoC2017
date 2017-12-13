
add_executable(TestAOCDay06
        day06.cpp
        testday06.cpp
        )
target_link_libraries(TestAOCDay06 gtest_main)
add_test(TestAOCDay06 TestAOCDay06)

add_executable(AOCDay06
        day06.cpp
        main.cpp
        )
