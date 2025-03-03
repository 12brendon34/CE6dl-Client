#pragma once
#include <pch.h>

class CRTTIManager {
public:
	virtual ~CRTTIManager();
	virtual uint64_t FindEngineClass(uint param_2);
	virtual uint64_t FindScriptClass(uint param_2);
	virtual uint64_t FindScriptClass(void* param_2);

	virtual uint64_t FindClass(uint param_2);
	virtual byte* FindClass(void* param_2);
	virtual long FindClassNoCase(char* param_2);

	virtual uint64_t GetDerivedScriptClasses(CRTTI* param_2, long* param_3);
	virtual uint64_t GetNotDerivedScriptClasses(CRTTI* param_2, long* param_3);

	virtual uint64_t GetDerivedDirectlyScriptClasses(CRTTI* param_2, long* param_3);
	virtual void* GetDerivedEngineClasses(CRTTI* param_2, long* param_3);

	virtual class CRTTI* GetBaseClass(CRTTI* param_2, long* param_3);

	//virtual uint64_t GetBaseClass(CRTTI* param_2, long* param_3);
	//virtual void* GetBaseClass(uint64_t param_2);

	//virtual class CRTTI* GetBaseClass(CRTTI* param_2, uint64_t param_3, uint64_t param_4);

	//virtual void* FUN_18041bf90(CRTTI* param_2, char* param_3);
	//virtual vec2* GetUVMin();
	//virtual void* FUN_18041c6e0(CRTTI param_2, longlong param_3, longlong param_4);



	/*
	virtual ~CRTTIManager();
	virtual ~CRTTIManager_1();
	virtual long* FindEngineClass(int param_1);
	virtual long* FindScriptClass(void* param_1);
	virtual long* FindScriptClass(int param_1);
	virtual long* FindClass(void* param_1);
	virtual long* FindClass(int param_1);
	virtual long FindClassNoCase(char* param_1);
	virtual ulong GetDerivedScriptClasses(class CRTTI* param_1, long* param_2);
	virtual ulong GetNotDerivedScriptClasses(class CRTTI* param_1, long* param_2);
	virtual ulong GetDerivedDirectlyScriptClasses(class CRTTI* param_1, long* param_2);
	virtual ulong GetDerivedEngineClasses(class CRTTI* param_1, long* param_2);
	virtual class CRTTI* GetBaseClass(long* param_2);
	virtual void* GetBaseClass(long** param_1);
	virtual uint64_t GetBaseClass(long* param_1, long* param_2);
	virtual class CRTTI* GetBaseClass(class CRTTI* param_2, class CRTTI* param_3);
	virtual void* FindScriptClasses(long* param_1, char* param_2);
	virtual long GetScriptClasses();
	virtual void* ReplaceEngineClass(class CRTTI* param_1, long param_2, long param_3);
	*/

};