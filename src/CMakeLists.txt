# CMakeLists for NewParser
#
# Copyright 2016 by Damir Cavar
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#    http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

cmake_minimum_required(VERSION 3.5)
project(NewParser)
set(EXECUTABLE_NAME "newfle")
#set(LIBRARY_NAME "fle")
include_directories(AFTER SYSTEM /usr/local/include)
link_directories(/usr/local/lib)

set(CMAKE_BUILD_TYPE Release)

# add all .cpp and .h files to source
file(GLOB ALL_MY_SRC
        "*.h"
        "*.cpp")

set(CMAKE_CONFIGURATION_TYPES "Debug" CACHE STRING "" FORCE) # setting two custom configuration types

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})

# generate the CFG code with target: cfg
set(CFG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/CFG)
set(CFG_SOURCES
        ${CFG_DIR}/CFG.y
        ${CFG_DIR}/CFG.l )
add_custom_command(
        OUTPUT  ${CFG_SOURCES}
        DEPENDS ${CFG_DIR}/CFG.cf
        WORKING_DIRECTORY ${CFG_DIR}
        COMMAND sh ./build.sh
        COMMAND make
        COMMENT "Generating CFG parser"
        VERBATIM )
add_custom_target(cfg DEPENDS ${CFG_SOURCES} )

# generate the PCFG code with target: pcfg
set(PCFG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/PCFG)
set(PCFG_SOURCES
        ${PCFG_DIR}/PCFG.y
        ${PCFG_DIR}/PCFG.l )
add_custom_command(
        OUTPUT  ${PCFG_SOURCES}
        DEPENDS ${PCFG_DIR}/PCFG.cf
        WORKING_DIRECTORY ${PCFG_DIR}
        COMMAND sh ./build.sh
        COMMAND make
        COMMENT "Generating PCFG parser"
        VERBATIM )
add_custom_target(pcfg DEPENDS ${PCFG_SOURCES} )

# generate the PCFG code with target: pcfg
set(PCFGNLTK_DIR ${CMAKE_CURRENT_SOURCE_DIR}/PCFGNLTK)
set(PCFGNLTK_SOURCES
        ${PCFGNLTK_DIR}/PCFGNLTK.y
        ${PCFGNLTK_DIR}/PCFGNLTK.l )
add_custom_command(
        OUTPUT  ${PCFGNLTK_SOURCES}
        DEPENDS ${PCFGNLTK_DIR}/PCFGNLTK.cf
        WORKING_DIRECTORY ${PCFGNLTK_DIR}
        COMMAND sh ./build.sh
        COMMAND make
        COMMENT "Generating PCFGNLTK parser"
        VERBATIM )
add_custom_target(pcfgnltk DEPENDS ${PCFGNLTK_SOURCES} )

# generate the XLE_RULES code with target: xle_rules
set(XLE_RULES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/XLERULES)
set(XLE_RULES_SOURCES
        ${XLE_RULES_DIR}/XLE_RULES.y
        ${XLE_RULES_DIR}/XLE_RULES.l )
add_custom_command(
        OUTPUT  ${XLE_RULES_SOURCES}
        DEPENDS ${XLE_RULES_DIR}/XLE_RULES.cf
        WORKING_DIRECTORY ${XLE_RULES_DIR}
        COMMAND sh ./build.sh
        COMMAND make
        COMMENT "Generating XLE_RULES parser"
        VERBATIM )
add_custom_target(xle_rules DEPENDS ${XLE_RULES_SOURCES} )

# generate the XLE_CONFIG code with target: xle_config
#set(XLE_CONFIG_DIR ${CMAKE_CURRENT_SOURCE_DIR}/XLECONFIG)
#set(XLE_CONFIG_SOURCES
#        ${XLE_CONFIG_DIR}/XLE_CONFIG.y
#        ${XLE_CONFIG_DIR}/XLE_CONFIG.l )
#add_custom_command(
#        OUTPUT  ${XLE_CONFIG_SOURCES}
#        DEPENDS ${XLE_CONFIG_DIR}/XLE_CONFIG.cf
#        WORKING_DIRECTORY ${XLE_CONFIG_DIR}
#        COMMAND sh ./build.sh
#        COMMAND make
#        COMMENT "Generating XLE_CONFIG parser"
#        VERBATIM )
#add_custom_target(xle_config DEPENDS ${XLE_CONFIG_SOURCES} )

# generate the XLE_FEATURES code with target: xle_features
#set(XLE_FEATURES_DIR ${CMAKE_CURRENT_SOURCE_DIR}/XLEFEATURES)
#set(XLE_FEATURES_SOURCES
#        ${XLE_FEATURES_DIR}/XLE_FEATURES.y
#        ${XLE_FEATURES_DIR}/XLE_FEATURES.l )
#add_custom_command(
#        OUTPUT  ${XLE_FEATURES_SOURCES}
#        DEPENDS ${XLE_FEATURES_DIR}/XLE_FEATURES.cf
#        WORKING_DIRECTORY ${XLE_FEATURES_DIR}
#        COMMAND sh ./build.sh
#        COMMAND make
#        COMMENT "Generating XLE_FEATURES parser"
#        VERBATIM )
#add_custom_target(xle_features DEPENDS ${XLE_FEATURES_SOURCES} )

# generate the XLE_LEXICON code with target: xle_lexicon
#set(XLE_LEXICON_DIR ${CMAKE_CURRENT_SOURCE_DIR}/XLELEXICON)
#set(XLE_LEXICON_SOURCES
#        ${XLE_LEXICON_DIR}/XLE_LEXICON.y
#        ${XLE_LEXICON_DIR}/XLE_LEXICON.l )
#add_custom_command(
#        OUTPUT  ${XLE_LEXICON_SOURCES}
#        DEPENDS ${XLE_LEXICON_DIR}/XLE_LEXICON.cf
#        WORKING_DIRECTORY ${XLE_LEXICON_DIR}
#        COMMAND sh ./build.sh
#        COMMAND make
#        COMMENT "Generating XLE_LEXICON parser"
#        VERBATIM )
#add_custom_target(xle_lexicon DEPENDS ${XLE_LEXICON_SOURCES} )

# generate the XLE_MORPHOLOGY code with target: xle_morphology
#set(XLE_MORPHOLOGY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/XLEMORPHOLOGY)
#set(XLE_MORPHOLOGY_SOURCES
#        ${XLE_MORPHOLOGY_DIR}/XLE_MORPHOLOGY.y
#        ${XLE_MORPHOLOGY_DIR}/XLE_MORPHOLOGY.l )
#add_custom_command(
#        OUTPUT  ${XLE_MORPHOLOGY_SOURCES}
#        DEPENDS ${XLE_MORPHOLOGY_DIR}/XLE_MORPHOLOGY.cf
#        WORKING_DIRECTORY ${XLE_MORPHOLOGY_DIR}
#        COMMAND sh ./build.sh
#        COMMAND make
#        COMMENT "Generating XLE_MORPHOLOGY parser"
#        VERBATIM )
#add_custom_target(xle_morphology DEPENDS ${XLE_MORPHOLOGY_SOURCES} )

# generate the XLE_MORPHTEXT code with target: xle_morphtext
#set(XLEMORPHTEXT_DIR ${CMAKE_CURRENT_SOURCE_DIR}/XLEMORPHTEXT)
#set(XLEMORPHTEXT_SOURCES
#        ${XLEMORPHTEXT_DIR}/XLE_MORPHOLOGYTEXT.y
#        ${XLEMORPHTEXT_DIR}/XLE_MORPHOLOGYTEXT.l )
#add_custom_command(
#        OUTPUT  ${XLEMORPHTEXT_SOURCES}
#        DEPENDS ${XLEMORPHTEXT_DIR}/XLE_MORPHOLOGYTEXT.cf
#        WORKING_DIRECTORY ${XLE_MORPHTEXT_DIR}
#        COMMAND sh ./build.sh
#        COMMAND make
#        COMMENT "Generating XLE_MORPHOLOGYTEXT parser"
#        VERBATIM )
#add_custom_target(xle_morphtext DEPENDS ${XLEMORPHTEXT_SOURCES} )

# generate the XLE_TEMPLATES code with target: xle_templates
#set(XLE_TEMPLATE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/XLETEMPLATES)
#set(XLE_TEMPLATE_SOURCES
#        ${XLE_TEMPLATE_DIR}/XLE_TEMPLATES.y
#        ${XLE_TEMPLATE_DIR}/XLE_TEMPLATES.l )
#add_custom_command(
#        OUTPUT  ${XLE_TEMPLATE_SOURCES}
#        DEPENDS ${XLE_TEMPLATE_DIR}/XLE_TEMPLATES.cf
#        WORKING_DIRECTORY ${XLE_TEMPLATE_DIR}
#        COMMAND sh ./build.sh
#        # COMMAND bnfc -m -cpp -p xletemp XLE_TEMPLATES.cf
#        COMMAND make
#        COMMENT "Generating XLE_TEMPLATES parser"
#        VERBATIM )
#add_custom_target(xle_templates DEPENDS ${XLE_TEMPLATE_SOURCES} )


# add Xerces C++ libs for XML parsing
# find_library(XercesLib NAMES xerces-c PATHS /usr/local/lib)

# add Foma libs for morphological analysis parsing
# find the dynamic library
# find_library(FomaLib NAMES foma PATHS /usr/local/lib)
# find the static library
find_library(FomaLib NAMES libfoma.a)
# Foma requires libz
find_library(ZLib NAMES z)

# Include OpenFST libs
# Sets the following variables:
# OPENFST_FOUND OPENFST_DIR
#find_path(OPENFST_INCLUDE_DIR fst/fst.h /usr/local/include /usr/include)
#find_library(OPENFST_LIB NAMES fst PATHS /usr/local/lib/ /usr/lib)
#find_library(OPENFSTSCRIPT_LIB NAMES fstscript PATHS /usr/local/lib/ /usr/lib)
#if(OPENFST_INCLUDE_DIR)
#    set(OPENFST_FOUND 1)
#    string(REGEX REPLACE "src/include/fst$" "" OPENFST_DIR ${OPENFST_INCLUDE_DIR})
#    set(OPENFST_INCLUDE_DIR "${OPENFST_INCLUDE_DIR}/..")
#    message(STATUS "OpenFst include: ${OPENFST_INCLUDE_DIR}")
#    message(STATUS "OpenFst lib:     ${OPENFST_LIB}")
#    message(STATUS "OpenFstScript lib: ${OPENFSTSCRIPT_LIB}")
#else()
#    message(FATAL_ERROR "No OpenFst found. Please specify OPENFST_ROOT.")
#ENDIF()

# add a target to generate API documentation with Doxygen
# if you use CMake to generate the Makefile, it will create a 'make doc' target
# manually just call: doxygen Doxyfile
find_package(Doxygen)
if(DOXYGEN_FOUND)
    set(DOC_DIR     ${CMAKE_CURRENT_SOURCE_DIR})
    set(DOC_SOURCES ${DOC_DIR}/Doxygen.stamp )
    configure_file(${DOC_DIR}/Doxyfile.in ${DOC_DIR}/Doxyfile @ONLY)
    add_custom_command(
            OUTPUT  ${DOC_SOURCES}
            DEPENDS ${DOC_DIR}/Doxyfile
            WORKING_DIRECTORY ${DOC_DIR}
            COMMAND ${DOXYGEN_EXECUTABLE} ${DOC_DIR}/Doxyfile
            COMMAND ${CMAKE_COMMAND} -E touch ${DOC_DIR}/Doxygen.stamp
            COMMENT "Generating documentation with Doxygen"
            VERBATIM )
    add_custom_target(doc DEPENDS ${DOC_SOURCES} )
endif(DOXYGEN_FOUND)

# add Boost libs
# set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(Boost_USE_STATIC_LIBS    OFF)
set(Boost_USE_MULTITHREADED  ON)
set(Boost_USE_STATIC_RUNTIME OFF)
set(BOOST_ALL_DYN_LINK       ON)
SET(BOOST_MIN_VERSION        "1.47.0")
find_package(Boost ${BOOST_MIN_VERSION} REQUIRED COMPONENTS program_options filesystem system regex) # date_time system regex)
if (NOT Boost_FOUND)
    message(FATAL_ERROR "Fatal error: Boost (version >= ${BOOST_MIN_VERSION}) required.\n")
endif (NOT Boost_FOUND)

include_directories(".")
include_directories(${Boost_INCLUDE_DIRS})
add_subdirectory(CFG)
add_subdirectory(PCFG)
add_subdirectory(PCFGNLTK)
#add_subdirectory(XLECONFIG)
#add_subdirectory(XLEFEATURES)
#add_subdirectory(XLELEXICON)
#add_subdirectory(XLEMORPHOLOGY)
#add_subdirectory(XLEMORPHTEXT)
add_subdirectory(XLERULES)
#add_subdirectory(XLETEMPLATES)
add_executable(${EXECUTABLE_NAME} ${ALL_MY_SRC}  $<TARGET_OBJECTS:CFG> $<TARGET_OBJECTS:PCFG>
        $<TARGET_OBJECTS:PCFGNLTK> $<TARGET_OBJECTS:XLERULES>
        #$<TARGET_OBJECTS:XLEMORPHTEXT>
        #$<TARGET_OBJECTS:XLECONFIG> $<TARGET_OBJECTS:XLEFEATURES> $<TARGET_OBJECTS:XLELEXICON>
        #$<TARGET_OBJECTS:XLEMORPHOLOGY> $<TARGET_OBJECTS:XLETEMPLATES>
        )
# target_link_libraries(${EXECUTABLE_NAME} ${Boost_LIBRARIES} ${XercesLib})
target_link_libraries(${EXECUTABLE_NAME} ${Boost_LIBRARIES} ${FomaLib} ${ZLib})
#add_library(${LIBRARY_NAME} SHARED  ${ALL_MY_SRC}  $<TARGET_OBJECTS:CFG> $<TARGET_OBJECTS:PCFG>
#        $<TARGET_OBJECTS:PCFGNLTK>
#        #$<TARGET_OBJECTS:XLEMORPHTEXT>
#        #$<TARGET_OBJECTS:XLECONFIG> $<TARGET_OBJECTS:XLEFEATURES> $<TARGET_OBJECTS:XLELEXICON>
#        #$<TARGET_OBJECTS:XLEMORPHOLOGY> $<TARGET_OBJECTS:XLERULES> $<TARGET_OBJECTS:XLETEMPLATES>
#        )
