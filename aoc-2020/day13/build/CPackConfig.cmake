# This file will be configured to contain variables for CPack. These variables
# should be set in the CMake list file of the project before CPack module is
# included. The list of available CPACK_xxx variables and their associated
# documentation may be obtained using
#  cpack --help-variable-list
#
# Some variables are common to all generators (e.g. CPACK_PACKAGE_NAME)
# and some are specific to a generator
# (e.g. CPACK_NSIS_EXTRA_INSTALL_COMMANDS). The generator specific variables
# usually begin with CPACK_<GENNAME>_xxxx.


set(CPACK_BINARY_IFW "OFF")
set(CPACK_BINARY_MSYS "ON")
set(CPACK_BUILD_SOURCE_DIRS "c:/msys64/home/Nico/repos/aoc/aoc-2020/day01;c:/msys64/home/Nico/repos/aoc/aoc-2020/day01/build")
set(CPACK_CMAKE_GENERATOR "Ninja")
set(CPACK_COMPONENTS_ALL "")
set(CPACK_COMPONENT_UNSPECIFIED_HIDDEN "TRUE")
set(CPACK_COMPONENT_UNSPECIFIED_REQUIRED "TRUE")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.18.4/Templates/CPack.GenericDescription.txt")
set(CPACK_DEFAULT_PACKAGE_DESCRIPTION_SUMMARY "day01 built using CMake")
set(CPACK_GENERATOR "MsysBinary")
set(CPACK_INSTALL_CMAKE_PROJECTS "c:/msys64/home/Nico/repos/aoc/aoc-2020/day01/build;day01;ALL;/")
set(CPACK_INSTALL_PREFIX "/usr/local")
set(CPACK_MODULE_PATH "")
set(CPACK_NSIS_DISPLAY_NAME "day01 0.1.0")
set(CPACK_NSIS_INSTALLER_ICON_CODE "")
set(CPACK_NSIS_INSTALLER_MUI_ICON_CODE "")
set(CPACK_NSIS_INSTALL_ROOT "$PROGRAMFILES")
set(CPACK_NSIS_PACKAGE_NAME "day01 0.1.0")
set(CPACK_NSIS_UNINSTALL_NAME "Uninstall")
set(CPACK_OUTPUT_CONFIG_FILE "c:/msys64/home/Nico/repos/aoc/aoc-2020/day01/build/CPackConfig.cmake")
set(CPACK_PACKAGE_DEFAULT_LOCATION "/")
set(CPACK_PACKAGE_DESCRIPTION_FILE "/usr/share/cmake-3.18.4/Templates/CPack.GenericDescription.txt")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "day01 built using CMake")
set(CPACK_PACKAGE_FILE_NAME "day01-0.1.0-MINGW64_NT-10.0-18363")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "day01 0.1.0")
set(CPACK_PACKAGE_INSTALL_REGISTRY_KEY "day01 0.1.0")
set(CPACK_PACKAGE_NAME "day01")
set(CPACK_PACKAGE_RELOCATABLE "true")
set(CPACK_PACKAGE_VENDOR "Humanity")
set(CPACK_PACKAGE_VERSION "0.1.0")
set(CPACK_PACKAGE_VERSION_MAJOR "0")
set(CPACK_PACKAGE_VERSION_MINOR "1")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PROJECT_NAME "day01")
set(CPACK_PROJECT_VERSION "0.1.0")
set(CPACK_RESOURCE_FILE_LICENSE "/usr/share/cmake-3.18.4/Templates/CPack.GenericLicense.txt")
set(CPACK_RESOURCE_FILE_README "/usr/share/cmake-3.18.4/Templates/CPack.GenericDescription.txt")
set(CPACK_RESOURCE_FILE_WELCOME "/usr/share/cmake-3.18.4/Templates/CPack.GenericWelcome.txt")
set(CPACK_SET_DESTDIR "OFF")
set(CPACK_SOURCE_GENERATOR "MsysSource")
set(CPACK_SOURCE_MSYS "ON")
set(CPACK_SOURCE_OUTPUT_CONFIG_FILE "c:/msys64/home/Nico/repos/aoc/aoc-2020/day01/build/CPackSourceConfig.cmake")
set(CPACK_SYSTEM_NAME "MINGW64_NT-10.0-18363")
set(CPACK_TOPLEVEL_TAG "MINGW64_NT-10.0-18363")
set(CPACK_WIX_SIZEOF_VOID_P "8")

if(NOT CPACK_PROPERTIES_FILE)
  set(CPACK_PROPERTIES_FILE "c:/msys64/home/Nico/repos/aoc/aoc-2020/day01/build/CPackProperties.cmake")
endif()

if(EXISTS ${CPACK_PROPERTIES_FILE})
  include(${CPACK_PROPERTIES_FILE})
endif()
