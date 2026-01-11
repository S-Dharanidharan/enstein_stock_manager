# Install script for directory: /home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/tmp")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "Debug")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

# Is this installation the result of a crosscompile?
if(NOT DEFINED CMAKE_CROSSCOMPILING)
  set(CMAKE_CROSSCOMPILING "FALSE")
endif()

# Set path to fallback-tool for dependency-resolution.
if(NOT DEFINED CMAKE_OBJDUMP)
  set(CMAKE_OBJDUMP "/bin/objdump")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE STATIC_LIBRARY FILES "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/build/Desktop_Qt_6_10_1-Debug/QXlsx/QXlsx/libQXlsxQt6.a")
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/include/QXlsxQt6" TYPE FILE FILES
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxabstractooxmlfile.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxabstractsheet.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxabstractsheet_p.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxcellformula.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxcell.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxcelllocation.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxcellrange.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxcellreference.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxchart.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxchartsheet.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxconditionalformatting.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxdatavalidation.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxdatetype.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxdocument.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxformat.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxglobal.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxrichstring.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxworkbook.h"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/QXlsx/QXlsx/header/xlsxworksheet.h"
    )
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  include("/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/build/Desktop_Qt_6_10_1-Debug/QXlsx/QXlsx/CMakeFiles/QXlsx.dir/install-cxx-module-bmi-Debug.cmake" OPTIONAL)
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "devel" OR NOT CMAKE_INSTALL_COMPONENT)
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets.cmake")
    file(DIFFERENT _cmake_export_file_changed FILES
         "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets.cmake"
         "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/build/Desktop_Qt_6_10_1-Debug/QXlsx/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets.cmake")
    if(_cmake_export_file_changed)
      file(GLOB _cmake_old_config_files "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets-*.cmake")
      if(_cmake_old_config_files)
        string(REPLACE ";" ", " _cmake_old_config_files_text "${_cmake_old_config_files}")
        message(STATUS "Old export file \"$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6/QXlsxQt6Targets.cmake\" will be replaced.  Removing files [${_cmake_old_config_files_text}].")
        unset(_cmake_old_config_files_text)
        file(REMOVE ${_cmake_old_config_files})
      endif()
      unset(_cmake_old_config_files)
    endif()
    unset(_cmake_export_file_changed)
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/build/Desktop_Qt_6_10_1-Debug/QXlsx/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets.cmake")
  if(CMAKE_INSTALL_CONFIG_NAME MATCHES "^([Dd][Ee][Bb][Uu][Gg])$")
    file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/build/Desktop_Qt_6_10_1-Debug/QXlsx/QXlsx/CMakeFiles/Export/5e1a71f991ec0867fe453527b0963803/QXlsxQt6Targets-debug.cmake")
  endif()
endif()

if(CMAKE_INSTALL_COMPONENT STREQUAL "Unspecified" OR NOT CMAKE_INSTALL_COMPONENT)
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/cmake/QXlsxQt6" TYPE FILE FILES
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/build/Desktop_Qt_6_10_1-Debug/QXlsx/QXlsx/QXlsxQt6Config.cmake"
    "/home/ensteinrobotsystem/DEV_ENVIRONMENT/CODES/NIGHTLY_BUILDS/Enstein_Stock_Manager/build/Desktop_Qt_6_10_1-Debug/QXlsx/QXlsx/QXlsxQt6ConfigVersion.cmake"
    )
endif()

