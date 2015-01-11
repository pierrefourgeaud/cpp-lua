
#include <scriptlua.h>
#include <class.h>

#include <iostream>

using namespace CppLua;

class InternalObject
{
public:
	InternalObject(const char* iStr)
		: m_pStr(iStr) {}

	const char* GetStr() const { return m_pStr; }

private:
	const char* m_pStr;
};

class TestLua
{
public:
	TestLua()
	{
		std::cout << "TestLua::Constructor()" << std::endl;
	}

	void SetObj(InternalObject* iObj)
	{
		m_pObj = iObj;
		std::cout << "TestLua::SetObj" << std::endl;
	}

	InternalObject* GetObj() const
	{
		std::cout << "TestLua::GetObj -> " << m_pObj->GetStr() << std::endl;
		return m_pObj;
	}

private:
	InternalObject* m_pObj = nullptr;
};

void Operations(TestLua* test)
{
	ScriptLua lua;

	lua_getglobal(lua.GetState(), "_G");

	Class<TestLua>(&lua, "TestLua")
		.Constructor<void (*)()>()
		.Property("obj", &TestLua::GetObj, &TestLua::SetObj);

	lua_pop(lua.GetState(), 1);

	Class<InternalObject>(&lua, "InternalObject")
		.Constructor<void (*)(const char*)>()
		.Property("str", &InternalObject::GetStr);

	lua_pop(lua.GetState(), 1);

	lua.SetGlobal("Test", test);

	lua.ExecuteBuffer(
		"Test.obj = InternalObject(\"My message in internal object.\")"
		"local obj = Test.obj;"
		"print(obj.str)"
		);
}

int main()
{
	TestLua test;
	Operations(&test);

	std::cout << "C++ -> " << test.GetObj()->GetStr() << std::endl;
	return 0;
}
