set(AtmController_SRCS
    main.cc
)

set(AtmController_HDRS)

set(AtmControllerBase_SRCS
    AtmController.cc
    BankApiAccessManager.cc
    CardReader.cc
)

set(AtmControllerBase_HDRS
    AtmController.h
    BankAccount.h
    BankApiAccessManager.h
    BankApiAccessManagerBase.h
    CardReader.h
    CardReaderBase.h
)

add_library(AtmControllerBase SHARED
    ${AtmControllerBase_HDRS}
    ${AtmControllerBase_SRCS}
)

target_link_libraries(AtmControllerBase
    Qt::Core
    Qt::Network
)

add_executable(AtmController
    ${AtmController_HDRS}
    ${AtmController_SRCS}
)

target_link_libraries(AtmController AtmControllerBase)

add_subdirectory(tests)
