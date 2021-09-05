get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR})

add_executable(testhelloworld testhelloworld.cc)
target_link_libraries(testhelloworld Qt::Test)
add_test(NAME testhelloworld COMMAND testhelloworld)

add_executable(testcardreader testcardreader.cc)
target_link_libraries(testcardreader Qt::Test)
add_test(NAME testcardreader COMMAND testcardreader)
