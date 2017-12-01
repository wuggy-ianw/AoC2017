
add_executable(TestAOCDay01
    day01.cpp
    testday01.cpp
)
target_link_libraries(TestAOCDay01 gtest_main)
add_test(TestAOCDay01 TestAOCDay01)

add_executable(AOCDay01
    day01.cpp
    main.cpp
)


