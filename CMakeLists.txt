cmake_minimum_required(VERSION 2.8)
project(nao-emotional-framework)

find_package(qibuild)


# Source files
set(_srcs

# Create a executable named nao-emotional-framework
# with the source file: main.cpp
qi_create_bin(nao-emotional-framework "main.cpp")

# Add a simple test:
enable_testing()
qi_create_test(test_nao-emotional-framework "test.cpp")

# Tell CMake that myproject depends on ALCOMMON and ALPROXIES
# This will set the libraries to link myproject with,
# the include paths, and so on
qi_use_lib(nao-emotional-framework ALCOMMON ALPROXIES)
