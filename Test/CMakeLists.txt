
include_directories( "${INCLUDES_PATH}" )

link_directories( "${CMAKE_ARCHIVE_OUTPUT_DIRECTORY}" )

# SimpleTestExec
add_executable( SimpleTestExec "SimpleTestExec.cpp" )

add_dependencies( SimpleTestExec CppLua )
target_link_libraries( SimpleTestExec CppLua )

# SimpleTestClass
add_executable( SimpleTestClass "SimpleTestClass.cpp" )

add_dependencies( SimpleTestClass CppLua )
target_link_libraries( SimpleTestClass CppLua )

# SimpleTestEnum
add_executable( SimpleTestEnum "SimpleTestEnum.cpp" )

add_dependencies( SimpleTestEnum CppLua )
target_link_libraries( SimpleTestEnum CppLua )

# TestEncapsulation
add_executable( TestEncapsulation "TestEncapsulation.cpp" )

add_dependencies( TestEncapsulation CppLua )
target_link_libraries( TestEncapsulation CppLua )

# TestEnumArgument
add_executable( TestEnumArgument "TestEnumArgument.cpp" )

add_dependencies( TestEnumArgument CppLua )
target_link_libraries( TestEnumArgument CppLua )
