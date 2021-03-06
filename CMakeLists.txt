cmake_minimum_required ( VERSION 2.8 )

# ---------- CppLua ----------
project ( CppLua )

IF ( NOT MSVC )
SET ( CMAKE_CXX_FLAGS "-std=c++11 -stdlib=libc++" )
ENDIF()

# ---------- Setup the executable output directory ----------
SET ( CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Bin CACHE PATH "Single directory for all executables." )
SET ( CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib CACHE PATH "Single directory for all executables." )
SET ( CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/Lib CACHE PATH "Single directory for all executables." )

# ---------- Useful variables ----------
SET ( INCLUDES_PATH ${PROJECT_SOURCE_DIR}/include )
SET ( SRCS_PATH ${PROJECT_SOURCE_DIR}/src )
SET ( DEPENDENCIES_PATH ${PROJECT_SOURCE_DIR}/Dependencies )
SET ( LUALIB_PATH ${DEPENDENCIES_PATH}/lua )

add_definitions(-DCPPLUA_EXPORTS)

SET ( INCLUDES
	"${INCLUDES_PATH}/interfaces/iscriptsystem.h"

	"${INCLUDES_PATH}/helpers/luahelper.h"
	
	"${INCLUDES_PATH}/utilities/arglist.h"
	"${INCLUDES_PATH}/utilities/callmember.h"
	"${INCLUDES_PATH}/utilities/fulluserdata.h"
	"${INCLUDES_PATH}/utilities/luastack.h"
	"${INCLUDES_PATH}/utilities/constructorinvoker.h"
	"${INCLUDES_PATH}/utilities/methodinvoker.h"

	"${INCLUDES_PATH}/scriptlua.h"
	"${INCLUDES_PATH}/cpplualib.h"
	"${INCLUDES_PATH}/class.h"
	"${INCLUDES_PATH}/enum.h"
)

SET ( SRCS
	"${SRCS_PATH}/scriptlua.cpp"
)

source_group ( Interfaces FILES
	"${INCLUDES_PATH}/interfaces/iscriptsystem.h"
)

source_group ( Helpers FILES
	"${INCLUDES_PATH}/helpers/luahelper.h"
)

source_group ( Utilities FILES
	"${INCLUDES_PATH}/utilities/arglist.h"
	"${INCLUDES_PATH}/utilities/callmember.h"
	"${INCLUDES_PATH}/utilities/fulluserdata.h"
	"${INCLUDES_PATH}/utilities/luastack.h"
	"${INCLUDES_PATH}/utilities/constructorinvoker.h"
	"${INCLUDES_PATH}/utilities/methodinvoker.h"
)

include_directories(
	"${INCLUDES_PATH}"
	"${LUALIB_PATH}/src"
)

link_directories(
	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}"
)

add_subdirectory( "Dependencies/lua" )

add_library(
	CppLua SHARED
	${INCLUDES}
	${SRCS}
)

add_dependencies( CppLua lua )
target_link_libraries( CppLua lua ) 

set(${PROJECT_NAME}_INCLUDE_DIRS ${INCLUDES_PATH}
							     ${LUALIB_PATH}/src
    CACHE INTERNAL "${PROJECT_NAME}: Include Directories" FORCE)

# ------------ Options -----------
OPTION( _TESTS "Compile test solutions." OFF )

IF (_TESTS)
	add_subdirectory( "Test" )
ENDIF()
