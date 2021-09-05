set(atmcontroller_SRCS
    atmcontroller.cc
)

set(atmcontroller_HDRS
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
