
#include <scriptlua.h>
#include <enum.h>

#include <iostream>

using namespace CppLua;

enum TestEnum {
	TestEnum_1,
	TestEnum_2,
	TestEnum_3
};

int main()
{
	ScriptLua lua;

	lua_getglobal(lua.GetState(), "_G");

	Enum<TestEnum>(&lua, "TestEnum")
		.Value("val1", TestEnum::TestEnum_1)
		.Value("val2", TestEnum::TestEnum_2)
		.Value("val3", TestEnum::TestEnum_3);

	lua_pop(lua.GetState(), 1);

	lua.ExecuteBuffer(
		"print(TestEnum.val1)"
		"print(TestEnum.val2)"
		"print(TestEnum.val3)"
		);
}