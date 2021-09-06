get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR})

add_executable(testcardreader testcardreader.cc)
target_link_libraries(testcardreader Qt::Test)
add_test(NAME testcardreader COMMAND testcardreader)

add_executable(TestBankApiAccessManager TestBankApiAccessManager.cc ${PARENT_DIR}/BankApiAccessManager.cc)
target_link_libraries(TestBankApiAccessManager Qt::Test Qt::Network)
add_test(NAME TestBankApiAccessManager COMMAND TestBankApiAccessManager)

