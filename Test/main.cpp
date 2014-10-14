
#include <scriptlua.h>
#include <class.h>

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

int main()
{
	ScriptLua lua;

	lua_getglobal(lua.GetState(), "_G");

	Class<TestLua>(&lua, "TestLua")
		.Constructor<void (*)()>()
		.Method("MyMethod", &TestLua::MyMethod)
		.Property("a", &TestLua::GetA, &TestLua::SetA);

	lua_pop(lua.GetState(), 1);

	lua.ExecuteBuffer(
		"print(\"message\")"
		"local num = 3 + 4"
		"print(num)"
		);
	lua.ExecuteBuffer(
		"local t = TestLua()"
		"t:MyMethod(1, 2, 3)"
		/*"t:a = 3"
		"local a = t:a"*/
		);
	return 0;
}
