
#include <scriptlua.h>
#include <class.h>
#include <enum.h>

#include <iostream>

using namespace CppLua;

class TestLua
{
public:
	TestLua() : m_A(0)
	{
		std::cout << "TestLua::Constructor()" << std::endl;
	}

	void MyMethod(int a, int b, int c)
	{
		std::cout << "TestLua::MyMethod(" << 
			a << ", " << b << ", " << c << ")" << std::endl;
	}

	void SetA(int a)
	{
		m_A = a;
		std::cout << "TestLua::SetA" << std::endl;
	}

	int GetA() const
	{
		std::cout << "TestLua::GetA -> " << m_A << std::endl;
		return m_A;
	}

private:
	int m_A;

};

enum TestEnum {
	TestEnum_1,
	TestEnum_2,
	TestEnum_3
};

int main()
{
	ScriptLua lua;

	lua_getglobal(lua.GetState(), "_G");

	Class<TestLua>(&lua, "TestLua")
		.Constructor<void (*)()>()
		.Method("MyMethod", &TestLua::MyMethod)
		.Property("a", &TestLua::GetA, &TestLua::SetA);

	lua_pop(lua.GetState(), 1);

	Enum<TestEnum>(&lua, "TestEnum")
		.Value("val1", TestEnum::TestEnum_1)
		.Value("val2", TestEnum::TestEnum_2)
		.Value("val3", TestEnum::TestEnum_3);

	lua_pop(lua.GetState(), 1);

	lua.ExecuteBuffer(
		"print(\"message\")"
		"local num = 3 + 4"
		"print(num)"
		);
	lua.ExecuteBuffer(
		"local t = TestLua()"
		"t:MyMethod(1, 2, 3)"
		"t.a = 3"
		"local toto = t.a;"
		"print(toto)"
		"print(TestEnum.val1)"
		"print(TestEnum.val2)"
		);
	return 0;
}
