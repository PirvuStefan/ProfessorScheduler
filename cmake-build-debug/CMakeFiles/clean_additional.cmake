# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/ProfessorScheduler_Public__autogen.dir/AutogenUsed.txt"
  "CMakeFiles/ProfessorScheduler_Public__autogen.dir/ParseCache.txt"
  "ProfessorScheduler_Public__autogen"
  )
endif()
