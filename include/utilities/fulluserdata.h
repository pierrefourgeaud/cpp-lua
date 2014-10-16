#ifndef CPPLUA_UTILITIES_FULLUSERDATA_H_
#define CPPLUA_UTILITIES_FULLUSERDATA_H_

extern "C"
{
	#include <lualib.h>
}

namespace CppLua
{

template <class T>
class FullUserData
{
public:
	static void* Construct(lua_State* iL)
	{
		const FullUserData<T>* userData =
			new (lua_newuserdata(iL, sizeof(FullUserData<T>))) FullUserData<T>();
		lua_rawgetp(iL, LUA_REGISTRYINDEX, Class<T>::GetIdentityKey());
		lua_setmetatable(iL, -2);
		return userData->GetMemoryPtr();
	}

	void* GetMemoryPtr() const
	{
		return m_Ptr;
	}

	static FullUserData* Get(lua_State* iL, int iIndex)
	{
		FullUserData* data = 0;
		// Make sure we have a userdata.
		if (lua_isuserdata(iL, iIndex))
		{
			// Recursive with parent ?
			// Add some security
			data = static_cast<FullUserData*>(lua_touserdata(iL, iIndex));
		}

		return data;
	}

private:
	FullUserData(const FullUserData<T>&);
	FullUserData<T> operator=(const FullUserData<T>&);

	FullUserData()
	{
		m_Ptr = &m_Memory[0];
	}

	~FullUserData()
	{
		reinterpret_cast<T*>(m_Ptr)->~T();
	}

	char  m_Memory[sizeof(T)];
	void* m_Ptr;
};

} // namespace CppLua

#endif // !CPPLUA_UTILITIES_FULLUSERDATA_H_
