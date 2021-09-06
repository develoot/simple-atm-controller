set(atmcontroller_SRCS
    AtmController.cc
    BankApiAccessManager.cc
    CardReader.cc
    main.cc
)

set(atmcontroller_HDRS
    AtmController.h
    BankAccount.h
    BankApiAccessManager.h
    BankApiAccessManagerBase.h
    CardReader.h
    CardReaderBase.h
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
