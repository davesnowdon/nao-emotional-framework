cmake_minimum_required(VERSION 2.8)
project(nao-emotional-framework)

find_package(qibuild)

option(IS_REMOTE
       "module is compiled as a remote module (ON or OFF)"
       ON)

# Source files
set(_srcs
    emotion.h
    emotion.cpp
    motion.h
    motion.cpp
    leds.h
    leds.cpp
    tts.h
    tts.cpp
    main.cpp)

if (IS_REMOTE)
  qi_info("Building remote executable")
  add_definitions(" -DFRAMEWORK_IS_REMOTE ")
  qi_create_bin(nao-emotional-framework ${_srcs})
else()
  qi_info("Build on-robot shared library")
  qi_create_lib(nao-emotional-framework SHARED ${_srcs} SUBFOLDER naoqi)
endif()

# Add a simple test:
enable_testing()
qi_create_test(test_nao-emotional-framework "test.cpp")

# Tell CMake that myproject depends on ALCOMMON and ALPROXIES
# This will set the libraries to link myproject with,
# the include paths, and so on
qi_use_lib(nao-emotional-framework ALCOMMON ALPROXIES)
