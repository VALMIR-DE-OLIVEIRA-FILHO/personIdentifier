# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles\\FuncionarioApp_autogen.dir\\AutogenUsed.txt"
  "CMakeFiles\\FuncionarioApp_autogen.dir\\ParseCache.txt"
  "FuncionarioApp_autogen"
  )
endif()
