get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR})

add_executable(TestCardReader
    TestCardReader.cc
    ${PARENT_DIR}/CardReaderBase.h
    ${PARENT_DIR}/CardReader.h
    ${PARENT_DIR}/CardReader.cc
)
target_link_libraries(TestCardReader Qt::Test)
add_test(NAME TestCardReader COMMAND TestCardReader)

add_executable(TestBankApiAccessManager
    TestBankApiAccessManager.cc
    ${PARENT_DIR}/BankApiAccessManagerBase.h
    ${PARENT_DIR}/BankApiAccessManager.h
    ${PARENT_DIR}/BankApiAccessManager.cc
)
target_link_libraries(TestBankApiAccessManager Qt::Test Qt::Network)
add_test(NAME TestBankApiAccessManager COMMAND TestBankApiAccessManager)

