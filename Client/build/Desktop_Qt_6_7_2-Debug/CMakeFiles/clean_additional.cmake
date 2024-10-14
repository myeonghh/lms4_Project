# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "00_ChatClient_autogen"
  "CMakeFiles/00_ChatClient_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/00_ChatClient_autogen.dir/ParseCache.txt"
  )
endif()
