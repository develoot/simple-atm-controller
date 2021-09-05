get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR})

add_executable(testcardreader testcardreader.cc)
target_link_libraries(testcardreader Qt::Test)
add_test(NAME testcardreader COMMAND testcardreader)

add_executable(testbankcommunicator testbankcommunicator.cc)
target_link_libraries(testbankcommunicator Qt::Test)
add_test(NAME testbankcommunicator COMMAND testbankcommunicator)
