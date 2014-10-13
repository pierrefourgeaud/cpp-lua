
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

	void MyMethod(int, int, int)
	{
		std::cout << "TestLua::MyMethod()" << std::endl;
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

	Class<TestLua>(&lua, "TestLua")
		.Constructor<void (*)()>()
		.Method("MyMethod", &TestLua::MyMethod)
		.Property("a", &TestLua::GetA, &TestLua::SetA);

	lua.ExecuteBuffer("print(\"message\")");
	lua.ExecuteBuffer(
		"local t = TestLua()"
		"t:MyMethod(1, 2, 3)"
		"t:a = 3"
		"local a = t:a"
		);
	return 0;
}
