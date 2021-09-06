set(atmcontroller_SRCS
    main.cc
    atmcontroller.cc
    bankcommunicator.cc
    cardreader.cc
)

set(atmcontroller_HDRS
    BankApiAccessManagerInterface.h
    atmcontroller.h
    bankaccount.h
    bankcommunicator.h
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
