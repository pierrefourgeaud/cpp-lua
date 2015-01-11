
#include <scriptlua.h>
#include <class.h>

#include <string>
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

	void SetB(const std::string& iStr)
	{
		m_B = iStr;
		std::cout << "TestLua::SetB" << std::endl;
	}

	std::string GetB() const
	{
		std::cout << "TestLua::GetB -> " << m_B << std::endl;
		return m_B;
	}

private:
	int m_A;
	std::string m_B;

};

int main()
{
	ScriptLua lua;

	lua_getglobal(lua.GetState(), "_G");

	Class<TestLua>(&lua, "TestLua")
		.Constructor<void (*)()>()
		.Method("MyMethod", &TestLua::MyMethod)
		.Property("a", &TestLua::GetA, &TestLua::SetA)
		.Property("b", &TestLua::GetB, &TestLua::SetB);

	lua_pop(lua.GetState(), 1);

	TestLua toto;
	toto.SetA(42);
	lua.SetGlobal("Toto", &toto);

	lua.ExecuteBuffer(
		"local t = TestLua()"
		"t:MyMethod(1, 2, 3)"
		"t.a = 3"
		"local toto = t.a;"
		"print(toto)"
		"print(Toto.a)"
		"local str = \"My string\""
		"t.b = str;"
		"print(t.b)"
		"t.b = \"My temporary string\""
		"print(t.b)"
		);
	return 0;
}
