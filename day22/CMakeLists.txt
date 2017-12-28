
add_executable(TestAOCDay22
        day22.cpp
        testday22.cpp
        ../utils/aocutils.cpp
        )
target_link_libraries(TestAOCDay22
        gtest_main
        )
add_test(TestAOCDay22 TestAOCDay22)

add_executable(AOCDay22
        day22.cpp
        main.cpp
        ../utils/aocutils.cpp
        )
