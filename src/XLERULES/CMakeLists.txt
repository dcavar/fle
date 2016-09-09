# CMakeLists for FLE
#
# Copyright 2015-2016 by Damir Cavar
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

set(LIBRARY_NAME XLERULES)

# add all .cpp and .h files to source
file(GLOB ALL_MY_SRC
        "XLERuleParser.h"
        "XLERuleParser.cpp"
        "Absyn.C"
        "Absyn.H"
        "Lexer.C"
        "Parser.C"
        "Parser.H"
        )

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -w -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(${CMAKE_CURRENT_SOURCE_DIR})

# this would be to create an OBJECT only
add_library(${LIBRARY_NAME} OBJECT ${ALL_MY_SRC})
#add_library(${LIBRARY_NAME} STATIC ${ALL_MY_SRC})
#add_library(${LIBRARY_NAME} SHARED ${ALL_MY_SRC})
