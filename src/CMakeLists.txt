set(atmcontroller_SRCS
    atmcontroller.cc
)

add_executable(atmcontroller
    ${atmcontroller_SRCS}
)

target_link_libraries(atmcontroller
    Qt::Core
)
