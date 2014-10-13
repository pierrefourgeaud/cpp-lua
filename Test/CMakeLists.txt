
SET ( INCLUDES_TEST
)

SET ( SRCS_TEST
	"main.cpp"
)

include_directories(
	"${INCLUDES_PATH}"
)

link_directories(
	"${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}"
)

add_executable(
	SimpleTest
	${INCLUDES_TEST}
	${SRCS_TEST}
)

add_dependencies( SimpleTest CppLua )
target_link_libraries( SimpleTest CppLua )
