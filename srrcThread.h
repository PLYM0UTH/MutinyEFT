#pragma once
#include <vcruntime_string.h>
#include <basetsd.h>
#include <cstdint>

enum eThreadState
{
	ThreadStateIdle,
	ThreadStateRunning,
	ThreadStateKilled,
	ThreadState3,
	ThreadState4,
};

namespace rage
{

	struct scrVector
	{
		alignas(8) float x;
		alignas(8) float y;
		alignas(8) float z;
	};

	struct alignas(16) scrVec3N
	{
		float x;
		float y;
		float z;
	};

	struct scrVectorSpace
	{
		scrVector* outVectors[4];
		scrVec3N inVectors[4];
	};

	class scrNativeCallContext
	{
	protected:
		void* m_pReturn; // +0
		uint32_t m_nArgCount; // +8
		void* m_pArgs; // +16

		uint32_t m_nDataCount; // +24

		// scratch space for vector things
		scrVectorSpace m_vectorSpace;
		uint8_t pad[96];

	public:
		template<typename T>
		inline T GetArgument(int idx)
		{
			intptr_t* arguments = (intptr_t*)m_pArgs;

			return *(T*)&arguments[idx];
		}

		template<typename T>
		inline void SetResult(int idx, T value)
		{
			intptr_t* returnValues = (intptr_t*)m_pReturn;

			*(T*)&returnValues[idx] = value;
		}

		inline int GetArgumentCount()
		{
			return m_nArgCount;
		}

		template<typename T>
		inline T GetResult(int idx)
		{
			intptr_t* returnValues = (intptr_t*)m_pReturn;

			return *(T*)&returnValues[idx];
		}

		inline void* GetArgumentBuffer()
		{
			return m_pArgs;
		}

		// copy vector3 pointer results to the initial argument
		inline void SetVectorResults()
		{
			for (size_t i = 0; i < m_nDataCount; i++)
			{
				auto outVector = m_vectorSpace.outVectors[i];
				const auto& inVector = m_vectorSpace.inVectors[i];

				outVector->x = inVector.x;
				outVector->y = inVector.y;
				outVector->z = inVector.z;
			}
		}

		inline const scrVec3N* GetVector()
		{
			return &m_vectorSpace.inVectors[0];
		}
	};

	struct scrThreadContext
	{
		UINT32 ThreadId;
		UINT32 ScriptHash; // + 4 (program id)
		eThreadState State; // + 8
		UINT32 IP; // + 12
		UINT32 FrameSP; // 
		UINT32 SP; // + 20, aka + 28
		UINT32 TimerA; // + 24
		UINT32 TimerB; // + 28
		UINT32 TimerC; // + 32, aka + 40
		UINT32 _mUnk1;
		UINT32 _mUnk2;
		UINT32 _f2C;
		UINT32 _f30;
		UINT32 _f34;
		UINT32 _f38;
		UINT32 _f3C;
		UINT32 _f40;
		UINT32 _f44;
		UINT32 _f48;
		UINT32 _f4C;
		UINT32 _f50; // should be +88 aka +80; stack size?

		UINT32 pad1;
		UINT32 pad2;
		UINT32 pad3;

		UINT32 _set1;

		UINT32 pad[68 / 4];
	};

	static_assert(sizeof(scrThreadContext) == 0xA8, "scrThreadContext size mismatch");

	class scrThread
	{
	public:
		//virtual ~scrThread() = 0;
		virtual void deconstructor() = 0;
		virtual eThreadState Reset(UINT32 scriptHash, void* pArgs, UINT32 argCount) = 0;
		virtual eThreadState Run() = 0; // This might have opsToExecute param but i didn't see it in IDA
		virtual eThreadState Tick(UINT32 opsToExecute) = 0;
		virtual void Kill() = 0;

		// There's really no 
		eThreadState GetThreadState() {
			return *(eThreadState*)((DWORD64)this + 0x10);
		}

		scrThreadContext* GetContext() {
			return &m_ctx;
		}

		scrThreadContext m_ctx;					// 0008
		void* m_pStack;							// 00B0
		void* pad;								// 00B8
		void* pad2;								// 00C0
		const char* m_pszExitMessage;			// 00C8
	};
}


struct scrVector
{
	float x;

private:
	UINT32 pad;

public:
	float y;

private:
	UINT32 pad2;

public:
	float z;

private:
	UINT32 pad3;
};

class GtaThread : public rage::scrThread
{
public:
	//virtual ~GtaThread() = 0; // void vfn_0000() = 0;
	virtual void deconstructor() = 0;
	virtual eThreadState Reset(UINT32 scriptHash, void* pArgs, UINT32 argCount) = 0;
	virtual eThreadState Run() = 0;
	virtual eThreadState Tick(UINT32 opsToExecute) = 0;
	virtual void Kill() = 0;
};

//static_assert(sizeof(GtaThread) == 0x158, "GtaThread size mismatch");

typedef struct {
	void(*Deconstructor)(GtaThread* This);
	eThreadState(*Reset)(GtaThread* This, UINT32 scriptHash, void* pArgs, UINT32 argCount);
	eThreadState(*Run)(GtaThread* This);
	eThreadState(*Tick)(GtaThread* This, UINT32 opsToExecute);
	void(*Kill)(GtaThread* This);
	void(*unk001)(); // this shouldn't even exist, frankly
} GtaThread_VTable;