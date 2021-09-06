set(atmcontroller_SRCS
    BankApiAccessManager.cc
    CardReader.cc
    atmcontroller.cc
    main.cc
)

set(atmcontroller_HDRS
    BankAccount.h
    BankApiAccessManager.h
    BankApiAccessManagerInterface.h
    CardReader.h
    CardReaderInterface.h
    atmcontroller.h
)

add_executable(atmcontroller
    ${atmcontroller_SRCS}
    ${atmcontroller_HDRS}
)

target_link_libraries(atmcontroller
    Qt::Core
    Qt::Network
)

add_subdirectory(tests)
