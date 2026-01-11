# Additional clean files
cmake_minimum_required(VERSION 3.16)

if("${CONFIG}" STREQUAL "" OR "${CONFIG}" STREQUAL "Debug")
  file(REMOVE_RECURSE
  "CMakeFiles/EnsteinStockManager_autogen.dir/AutogenUsed.txt"
  "CMakeFiles/EnsteinStockManager_autogen.dir/ParseCache.txt"
  "EnsteinStockManager_autogen"
  "QXlsx/QXlsx/CMakeFiles/QXlsx_autogen.dir/AutogenUsed.txt"
  "QXlsx/QXlsx/CMakeFiles/QXlsx_autogen.dir/ParseCache.txt"
  "QXlsx/QXlsx/QXlsx_autogen"
  )
endif()
