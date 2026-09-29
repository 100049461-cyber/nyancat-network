# Add one line such as nyan_add_test(cli_test) when tests/cli_test.cpp exists.
function(nyan_add_test name)
    add_executable(${name} ${name}.cpp)
    target_link_libraries(${name} PRIVATE nyan_core)
    target_compile_options(${name} PRIVATE -Wall -Wextra -Wpedantic)
    add_test(NAME ${name} COMMAND ${name})
    set_tests_properties(${name} PROPERTIES TIMEOUT 10)
endfunction()

# No client tests exist in the initial scaffold. Add them with implementations.
