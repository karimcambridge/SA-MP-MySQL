#pragma once

#include "CSingleton.h"

#include <string>
#include <unordered_map>

using std::string;
using std::unordered_map;

class CQuery;
class CCallback;


class CHandle
{
	friend class CHandleManager;
public: //type definitions
	using Id_t = unsigned int;

	enum class ExecutionType
	{
		INVALID,
		THREADED,
		PARALLEL,
		UNTHREADED
	};


private: //constructor / deconstructor
	CHandle(Id_t id) :
		m_Id(id)
	{ }
	~CHandle() = default;


private: //variables
	const Id_t m_Id;


public: //functions
	bool Execute(ExecutionType type, CQuery *query, CCallback *callback = nullptr);


	inline Id_t GetId() const
	{
		return m_Id;
	}

};

class CHandleManager : public CSingleton<CHandleManager>
{
	friend class CSingleton<CHandleManager>;
private: //constructor / deconstructor
	CHandleManager() = default;
	~CHandleManager() = default;


private: //variables
	unordered_map<CHandle::Id_t, CHandle *> m_Handles;


public: //functions
	CHandle *Create(string host, string user, string pass, string db, 
		size_t port, size_t pool_size);
	bool Destroy(CHandle * handle);

	inline bool IsValidHandle(const CHandle::Id_t id)
	{
		return m_Handles.find(id) != m_Handles.end();
	}
	inline CHandle *GetHandle(const CHandle::Id_t id)
	{
		return IsValidHandle(id) ? m_Handles.at(id) : nullptr;
	}
};
