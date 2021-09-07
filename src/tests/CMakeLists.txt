get_filename_component(PARENT_DIR ../ ABSOLUTE)
include_directories(${PARENT_DIR})

add_executable(TestCardReader TestCardReader.cc)
target_link_libraries(TestCardReader AtmControllerBase Qt::Test)
add_test(NAME TestCardReader COMMAND TestCardReader)

add_executable(TestBankApiAccessManager TestBankApiAccessManager.cc)
target_link_libraries(TestBankApiAccessManager AtmControllerBase Qt::Test)
add_test(NAME TestBankApiAccessManager COMMAND TestBankApiAccessManager)

add_executable(TestAtmController TestAtmController.cc)
target_link_libraries(TestAtmController AtmControllerBase Qt::Test)
add_test(NAME TestAtmController COMMAND TestAtmController)

