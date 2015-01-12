
#include <scriptlua.h>
#include <enum.h>
#include <class.h>

#include <iostream>

using namespace CppLua;

enum TestEnum {
	TestEnum_1,
	TestEnum_2,
	TestEnum_3
};

class TestLua
{
public:
	TestLua() : m_A(TestEnum::TestEnum_1)
	{
		std::cout << "TestLua::Constructor()" << std::endl;
	}

	void SetA(TestEnum a)
	{
		m_A = a;
		std::cout << "TestLua::SetA" << std::endl;
	}

	TestEnum GetA() const
	{
		std::cout << "TestLua::GetA -> " << m_A << std::endl;
		return m_A;
	}

	void PrintEnum(TestEnum e)
	{
		std::cout << "PrintEnum -> " << e << std::endl;
	}

private:
	TestEnum m_A;
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

	Class<TestLua>(&lua, "TestLua")
		.Constructor<void (*)()>()
		.Property("a", &TestLua::GetA, &TestLua::SetA)
		.Method("printEnum", &TestLua::PrintEnum);

	lua_pop(lua.GetState(), 1);

	lua.ExecuteBuffer(
		"print(TestEnum.val1)"
		"print(TestEnum.val2)"
		"print(TestEnum.val3)"
		"local t = TestLua()"
		"print(t.a);"
		"t.a = TestEnum.val2;"
		"print(t.a);"
		);
}