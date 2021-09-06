set(atmcontroller_SRCS
    BankApiAccessManager.cc
    atmcontroller.cc
    cardreader.cc
    main.cc
)

set(atmcontroller_HDRS
    BankApiAccessManager.h
    BankApiAccessManagerInterface.h
    atmcontroller.h
    bankaccount.h
    cardreader.h
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
