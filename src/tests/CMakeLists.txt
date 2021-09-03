add_executable(testhelloworld testhelloworld.cc)
target_link_libraries(testhelloworld Qt::Test)
add_test(NAME testhelloworld COMMAND testhelloworld)
