//----------------------------------------------------------------------------
// Shaik Hussain Arshad Naushad
//----------------------------------------------------------------------------
//
// Thread Framework - for Keenan's C++ classes
//
//    One header to rule them all, 
//        one header to find them, 
//        one header to bring them all 
//        and in the Linker bind them.   <thank you Tolkien>
//
//    Don't try to understand it... its very complicated
//
//    Systems:
//        Dictionary - hold info {name,threadID,tabs} per thread
//        Banner - thread banner (begin/end) of thread
//        ThreadHelper - Front door
//    
// ---------------------------------------------------------------------------
//    v.1.00  Merge files / start
//    v.1.01 - Start Banner
//    v.1.02 - Fix banner printing
//    v.1.03 - Version control
//    v.1.04 - Remove entry from map when thread ended
//    v.1.05 - Deep copy of name in Banner
//    v.1.06 - new name -async defer- label
//    v.1.07 - problem with names on uninitialized thread names
//----------------------------------------------------------------------------- 

#ifndef THREAD_FRAMEWORK_VER_H
#define THREAD_FRAMEWORK_VER_H

#define THREAD_FRAMEWORK_VER "1.07"

#endif

#ifndef THREAD_FRAMEWORK_H
#define THREAD_FRAMEWORK_H

// Comment this out to turn off all thread-debugging i.e. prints
#define THREAD_FRAMEWORK_ENABLED

// -----------------------------------------------
//
// To Enable:
//      define THREAD_FRAMEWORK_ENABLED 
//
// In Compiler:
//      preprocessor define:
//           USE_THREAD_FRAMEWORK
//      forced include:
//           ThreadFramework.h
// 
// -----------------------------------------------
//  SUMMARY
// -----------------------------------------------
//
//  class Debug
//   {
//    public:
//        static void Reset()
//        static unsigned int GetCurrentID()
//        static void SetName(const std::thread &t0, const char *threadName, int numTabs = 1)
//        static void SetName(DWORD threadId, const char *threadName, int numTabs = 1)
//        static bool SetCurrentName(const char *threadName, int numTabs = 1)
//        static const char *GetThreadName()
//        static int GetNumTabs()
//        static void out(const char *const fmt, ...)
//   };
//
//   class BannerBase  <--- Functor Base for Thread Names
//   {
//        BannerBase(const char *const _pName)
//   };
//
//   class Banner  <--- RAII for ThreadBanner
//   {
//   public:
//       Banner(class BannerName *pBannerName)
//       Banner();
//       ~Banner();
//   }
//
// Useful Macros
//
//   #define START_BANNER_MAIN(name) 
//   #define START_BANNER_DERIVED
//   #define START_BANNER		
//


namespace ThreadFramework
{
#define THREAD_UNUSED_VAR(x) (void(x))

#ifdef THREAD_FRAMEWORK_ENABLED

	#define START_BANNER_MAIN(x)    Debug::Reset(); \
									Debug::SetCurrentName(x, 0); \
									Banner banner;
	#define START_BANNER_DERIVED	Banner banner(this);
	#define START_BANNER			Banner banner;

#else

	#define START_BANNER_MAIN(x)    THREAD_UNUSED_VAR(x);
	#define START_BANNER_DERIVED	
	#define START_BANNER			

#endif

}


#pragma warning( push )
#pragma warning( disable : 4625 )
#pragma warning( disable : 4626 )
#pragma warning( disable : 4774 )
#include <iostream>
#include <thread>
#include <sstream> 
#include <map>
#include <mutex>
#include <future>
#include <assert.h>
#pragma warning( pop ) 

// --------------------------------------------------------------
// DICTIONARY
// --------------------------------------------------------------

namespace ThreadFramework
{
	class Dictionary
	{
	public:
		static const unsigned int NUM_CHAR = 64;

		struct Data
		{
			char name[NUM_CHAR];  // maximum name length 63+null
			int  numTabs;         // number of tabs for printing
			bool async;           // does thread have an active active deferred
			char pad[3];          // alignment
		};
	public:
		Dictionary()
			: poThreadNames(),
			mtx()
		{
		}
		Dictionary(const Dictionary &) = delete;
		Dictionary &operator = (const Dictionary &) = delete;
		~Dictionary()
		{
			std::lock_guard<std::mutex> lock(this->mtx);

			// Since Map owns name... you need to release the memory
			for (auto it = poThreadNames.begin(); it != poThreadNames.end(); ++it)
			{
				//delete it->second;
			}
		}

		void Clear()
		{
			std::lock_guard<std::mutex> lock(this->mtx);
			this->poThreadNames.clear();
		}

		char *GetName(unsigned int threadId)
		{
			std::lock_guard<std::mutex> lock(this->mtx);

			auto it = poThreadNames.find(threadId);
			char *s = nullptr;

			if (it == poThreadNames.end())
			{
				s = nullptr;
			}
			else
			{
				s = it->second.name;
			}

			return s;
		}
		int GetNumTabs(unsigned int threadId)
		{
			std::lock_guard<std::mutex> lock(this->mtx);

			auto it = poThreadNames.find(threadId);
			int numTabs = 0;

			if (it == poThreadNames.end())
			{
				numTabs = 0;
			}
			else
			{
				numTabs = it->second.numTabs;
			}

			return numTabs;
		}
		void SetNumTabs(unsigned int threadId, int count)
		{
			std::lock_guard<std::mutex> lock(this->mtx);

			auto it = poThreadNames.find(threadId);

			if (it == poThreadNames.end())
			{
				assert(0);
			}
			else
			{
				it->second.numTabs = count;
			}
		}
		void ClearAsync(unsigned int threadId)
		{
			std::lock_guard<std::mutex> lock(this->mtx);

			auto it = poThreadNames.find(threadId);

			if (it == poThreadNames.end())
			{
				assert(0);
			}
			else
			{
				it->second.async = false;
			}
		}
		void SetAsync(unsigned int threadId)
		{
			std::lock_guard<std::mutex> lock(this->mtx);

			auto it = poThreadNames.find(threadId);
	
			if (it == poThreadNames.end())
			{
				assert(0);
			}
			else
			{
				it->second.async = true;
			}
		}
		bool GetAsync(unsigned int threadId)
		{
			std::lock_guard<std::mutex> lock(this->mtx);

			auto it = poThreadNames.find(threadId);
			bool flag = false;

			if (it == poThreadNames.end())
			{
				flag = false;
				//assert(0);
			}
			else
			{
				flag = it->second.async;
			}

			return flag;
		}

		bool AddToMap(const char *const threadName, unsigned int threadId, int _numTabs)
		{
			std::lock_guard<std::mutex> lock(this->mtx);
			
			bool status(true);

			// is the string name too big?
			const size_t N = strlen(threadName) + 1;
			assert(N <= NUM_CHAR);

			// Fill the data struct
			Dictionary::Data data;

			memset(data.name, 0x0, NUM_CHAR);
			strcpy_s(data.name, N, threadName);
			data.numTabs = _numTabs;
			data.async = false;

			// The name is now OWNED by the Map
			auto it = poThreadNames.emplace(threadId, data);

			// is that threadId already in the map?
			if (it.second == false)
			{				
				// duplicate entry... no transfer

				// auto it2 = poThreadNames.find(threadId);
				// Debug::privOut("--> warning AddToMap(%d) repeated threadID using %s  \n", threadId, it2->second.name);
				
				status = false;
			}
			return status;
		}


		bool RemoveFromMap(unsigned int threadId)
		{
			std::lock_guard<std::mutex> lock(this->mtx);

			bool status = false;
			auto it = poThreadNames.find(threadId);
	
			if (it == poThreadNames.end())
			{
				assert(false);
				status = false;
			}
			else
			{
				// it->second.name;
				// do something
				status = true;
				poThreadNames.erase(it);
			}

			return status;
		}


	private:
		std::map<unsigned int, Data> poThreadNames;
		std::mutex mtx;
	};
}

// ---------------------------------------------------------------
// Locally static section
//----------------------------------------------------------------

namespace ThreadFramework
{
	constexpr DWORD MS_VC_EXCEPTION = 0x406D1388;

#pragma pack(push,8)
	typedef struct tagTHREADNAME_INFO
	{
		DWORD dwType; // Must be 0x1000.
		LPCSTR szName; // Pointer to name (in user addr space).
		DWORD dwThreadID; // Thread ID (-1=caller thread).
		DWORD dwFlags; // Reserved for future use, must be zero.
	} THREADNAME_INFO;
#pragma pack(pop)

#ifdef THREAD_FRAMEWORK_ENABLED
	class Debug
	{
	public:
		static const unsigned int DebugBuffSize = 256;

	public:
		Debug(const Debug &) = delete;
		Debug &operator = (const Debug &) = delete;
		~Debug() = default;

		static void Reset()
		{
			Debug *pDebug = privInstance();
			assert(pDebug);

			std::lock_guard<std::mutex> lock(pDebug->debugMtx);

			pDebug->privReset();
		}

		static unsigned int GetCurrentID()
		{
			// Get the string ID in an Integer form
			std::stringstream ss;

			// extracts the id
			ss << std::this_thread::get_id();

			// convert from string to number
			unsigned int id = std::stoul(ss.str());

			return id;
		}
		static void SetName(const std::thread &t0, const char *threadName, int numTabs = 1)
		{
			Debug *pDebug = privInstance();
			assert(pDebug);

			// Get the id

			// OMG - a const cast?
			// reason... if you have a thread reference... I want no way of modifying the data
			// but to get the name for the debugger, I need to call native_handle which is mutable

			const DWORD threadId = ::GetThreadId(
				static_cast<HANDLE>(
					(const_cast<std::thread &>(t0)).native_handle()
					)
			);

			// register the name
			bool status = pDebug->tDictionary.AddToMap(threadName, threadId, numTabs);

			if (status)
			{
				// Fill in the thread info for the debug
				THREADNAME_INFO info;
				info.dwType = 0x1000;
				info.szName = threadName;
				info.dwThreadID = threadId;
				info.dwFlags = 0;

				// Throw an exception on purpose to jam the thread info into debugger
				__try
				{
					RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR *)&info);
				}
				__except (EXCEPTION_EXECUTE_HANDLER)
				{
				}
			}
		}
		static void SetName(DWORD threadId, const char *threadName, int numTabs = 1)
		{
			Debug *pDebug = privInstance();
			assert(pDebug);

			// register the name
			pDebug->tDictionary.AddToMap(threadName, threadId, numTabs);

			// Fill in the thread info for the debug
			THREADNAME_INFO info;
			info.dwType = 0x1000;
			info.szName = threadName;
			info.dwThreadID = threadId;
			info.dwFlags = 0;

			// Throw an exception on purpose to jam the thread info into debugger
			__try
			{
				RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR *)&info);
			}
			__except (EXCEPTION_EXECUTE_HANDLER)
			{
			}
		}
		static bool SetCurrentName(const char *threadName, int numTabs = 1)
		{
			Debug *pDebug = privInstance();
			assert(pDebug);

			// Get id of the current thread
			const unsigned int threadId = ::GetThreadId(GetCurrentThread());

			// register the name
			bool status = pDebug->tDictionary.AddToMap(threadName, threadId, numTabs);

			if (status)
			{
				// Fill in the thread info for the debug
				THREADNAME_INFO info;
				info.dwType = 0x1000;
				info.szName = threadName;
				info.dwThreadID = threadId;
				info.dwFlags = 0;

				// Throw an exception on purpose to jam the thread info into debugger
				__try
				{
					RaiseException(MS_VC_EXCEPTION, 0, sizeof(info) / sizeof(ULONG_PTR), (ULONG_PTR *)&info);
				}
				__except (EXCEPTION_EXECUTE_HANDLER)
				{
				}
			}

			return status;
		}

		static const char *GetThreadName()
		{
			Debug *pDebug = privInstance();
			assert(pDebug);

			// Get id of the current thread
			const unsigned int threadId = ::GetThreadId(GetCurrentThread());

			return pDebug->tDictionary.GetName(threadId);
		}
		static int GetNumTabs()
		{
			Debug *pDebug = privInstance();
			assert(pDebug);

			// Get id of the current thread
			const unsigned int threadId = ::GetThreadId(GetCurrentThread());

			return pDebug->tDictionary.GetNumTabs(threadId);
		}

		// Same as Debug::privOut() but honor's tabs for specific threads
		static void out(const char *const fmt, ...)
		{
			Debug *pDebug = privInstance();
			assert(pDebug);

			std::lock_guard<std::mutex> lock(pDebug->debugMtx);

			// indent + 1 more 
			size_t numTabs = (size_t)Debug::GetNumTabs() + 1;

			va_list args;

#pragma warning( push )
#pragma warning( disable : 26492 )
#pragma warning( disable : 26481 )
			va_start(args, fmt);
#pragma warning( pop )

			char f[DebugBuffSize] = { 0 };
			char s[DebugBuffSize] = { 0 };
			char *p = &f[0];
			size_t count = numTabs;
			while (count--)
			{
				*p++ = 0x9; // "\t"
			}

			if (pDebug->tDictionary.GetAsync(Debug::GetCurrentID()))
			{
				sprintf_s(p, DebugBuffSize - numTabs, "(%s): -async defer-: ", Debug::GetThreadName());
			}
			else
			{
				const char *pThreadName = Debug::GetThreadName();
				if (pThreadName)
				{
					sprintf_s(p, DebugBuffSize - numTabs, "(%s): ", Debug::GetThreadName());
				}
				else
				{
					sprintf_s(p, DebugBuffSize - numTabs, "(%d): ", Debug::GetCurrentID());

				}
			}
			strcat_s(f, 256, fmt);

			vsprintf_s(s, 256, f, args);

			pDebug->privOut(s);

			//va_end(args);
			args = static_cast<va_list> (nullptr);

		}
private:
		// displays a printf to the output window
		static void privOut(const char *const fmt, ...)
		{
			// Assumes its locked before this is called.
			Debug *pDebug = Debug::privInstance();
			assert(pDebug);
			//	std::lock_guard<std::mutex> lock(pDebug->helperMtx);

			std::lock_guard<std::mutex> lock(pDebug->printMtx);

			va_list args;

#pragma warning( push )
#pragma warning( disable : 26492 )
#pragma warning( disable : 26481 )
			va_start(args, fmt);
#pragma warning( pop )

			vsprintf_s(&pDebug->privBuff[0], DebugBuffSize, fmt, args);
			OutputDebugString(&pDebug->privBuff[0]);

			//va_end(args);
			args = static_cast<va_list> (nullptr);
		}
	private:
		friend class Banner;
		static Dictionary &GetDictionary()
		{
			Debug *pDebug = privInstance();
			assert(pDebug);

			return pDebug->tDictionary;
		}
		Debug()
			: tDictionary(),
			debugMtx()
		{

		}
		static Debug *privInstance()
		{
			static Debug debug;
			return &debug;
		}
		void privReset()
		{
			// already locked by Reset
			this->tDictionary.Clear();
		}

		Dictionary   tDictionary;
		std::mutex   debugMtx;
		std::mutex   printMtx;

		char privBuff[DebugBuffSize];
	};

#else
	class Debug
	{
	public:
		static const unsigned int DebugBuffSize = 256;

	public:
		Debug(const Debug &) = delete;
		Debug &operator = (const Debug &) = delete;
		~Debug() = default;

		static void Reset()
		{}

		static unsigned int GetCurrentID()
		{
			std::stringstream ss;

			// extracts the id
			ss << std::this_thread::get_id();

			// convert from string to number
			unsigned int id = std::stoul(ss.str());

			return id;
		}
		static void SetName(const std::thread &, const char *, int numTabs = 1)
		{	
			THREAD_UNUSED_VAR(numTabs);
		}
		static void SetName(DWORD , const char *, int numTabs = 1)
		{	
			THREAD_UNUSED_VAR(numTabs);	
		}
		static bool SetCurrentName(const char *, int numTabs = 1)
		{	
			THREAD_UNUSED_VAR(numTabs);
		}
		static const char *GetThreadName()
		{
			return nullptr;
		}
		static int GetNumTabs()
		{
			return 0;
		}

		// Same as Debug::privOut() but honor's tabs for specific threads
		static void out(const char *const , ...)
		{
		}
	private:
		// displays a printf to the output window
		static void privOut(const char *const , ...)
		{
		}
	private:
		friend class Banner;
		static Dictionary &GetDictionary()
		{
			Debug *pDebug = privInstance();
			assert(pDebug);

			return pDebug->tDictionary;
		}

		Debug()
			: tDictionary(),
			helperMtx()
		{

		}
		static Debug *privInstance()
		{
			static Debug debug;
			return &debug;
		}
		void privReset()
		{
			// already locked by Reset
			this->tDictionary.Clear();
		}

		Dictionary tDictionary;
		std::mutex		 helperMtx;
		char privBuff[DebugBuffSize];
	};

#endif

}

// --------------------------------------------------------------
// Banner
// --------------------------------------------------------------

namespace ThreadFramework
{
	class BannerBase
	{
	public:
	public:
		BannerBase(const char *const _pName)
			: BannerName{ 0 }
		{
			strncpy_s(this->BannerName, Dictionary::NUM_CHAR, _pName, strlen(_pName) + 1);
		}
		BannerBase() = delete;
		BannerBase(const BannerBase &) = default;
		BannerBase &operator=(const BannerBase &) = default;
		~BannerBase() = default;

		const char *const GetBannerName()
		{
			return this->BannerName;
		}

	private:
	//	const char *const pBannerName;
		char BannerName[Dictionary::NUM_CHAR];
	};
}

namespace ThreadFramework
{
	class Banner
	{
	public:
		Banner(class BannerBase *pBannerBase)
			: bannerMtx(),
			isThread(true),
			dict(Debug::GetDictionary())
		{
			std::lock_guard<std::mutex> lock(this->bannerMtx);

			bool status = Debug::SetCurrentName(pBannerBase->GetBannerName());
			this->isThread = status;

			unsigned int _ThreadID = Debug::GetCurrentID();

			size_t numTabs = (size_t)this->dict.GetNumTabs(_ThreadID);
				
			// Add the number of tabs into the banner
			//    A real PAIN we cannot tear Debug::privOut()
			//    Create a buffer... print into that, submit buff to Debug::privOut()
			char s[Debug::DebugBuffSize] = { 0 };
			char *p = &s[0];
			size_t count = numTabs;
			while (count--)
			{
				*p++ = 0x9; // "\t"
			}

			if (this->isThread)
			{
				sprintf_s(p, Debug::DebugBuffSize - numTabs, "thread(%5d) %s: begin()\n",
					_ThreadID,
					this->dict.GetName(_ThreadID));

				Debug::privOut(s);
			}
			else
			{
				this->dict.SetAsync(_ThreadID);
			
				int _tabCount = this->dict.GetNumTabs(_ThreadID) + 1;
				this->dict.SetNumTabs(_ThreadID, _tabCount);

				Debug::out("start()\n");

			}
		}
		Banner()
			: bannerMtx(),
			isThread(true),
			dict(Debug::GetDictionary())
		{
			std::lock_guard<std::mutex> lock(this->bannerMtx);

			unsigned int _ThreadID = Debug::GetCurrentID();

			size_t numTabs = (size_t)this->dict.GetNumTabs(_ThreadID);

			// Add the number of tabs into the banner
			//    A real PAIN we cannot tear Debug::privOut()
			//    Create a buffer... print into that, submit buff to Debug::privOut()
			char s[Debug::DebugBuffSize] = { 0 };
			char *p = &s[0];
			size_t count = numTabs;
			while (count--)
			{
				*p++ = 0x9; // "\t"
			}
			sprintf_s(p, Debug::DebugBuffSize - numTabs, "thread(%5d) %s: begin()\n",
				_ThreadID,
				this->dict.GetName(_ThreadID));

			Debug::privOut(s);

		}

		Banner(const Banner &) = default;
		Banner &operator = (const Banner &) = default;
		~Banner()
		{
			std::lock_guard<std::mutex> lock(this->bannerMtx);

			unsigned int _ThreadID = Debug::GetCurrentID();

			size_t numTabs = (size_t)this->dict.GetNumTabs(_ThreadID);

			// Add the number of tabs into the banner
			//    A real PAIN we cannot tear Debug::privOut()
			//    Create a buffer... print into that, submit buff to Debug::privOut()

			//Debug::privOut("%d: tab:%d\n", numTabs, _ThreadID);

			char s[Debug::DebugBuffSize] = { 0 };
			char *p = &s[0];
			size_t count = numTabs;
			while (count--)
			{
				*p++ = 0x9; // "\t"
			}

			if (this->isThread)
			{
				sprintf_s(p, Debug::DebugBuffSize - numTabs, "thread(%5d) %s: end()\n",
					_ThreadID,
					this->dict.GetName(_ThreadID));
				Debug::privOut(s);

				bool status = this->dict.RemoveFromMap(_ThreadID);
				assert(status);
				AZUL_UNUSED_VAR(status);
			}
			else
			{
				Debug::out("end()\n"); 

				this->dict.ClearAsync(_ThreadID);
				int _tabCount = this->dict.GetNumTabs(_ThreadID) - 1;
				this->dict.SetNumTabs(_ThreadID, _tabCount);
			}

		};

		// Data ------------------
		std::mutex		 bannerMtx;
		bool             isThread;
		Dictionary       &dict;
	};
}

#endif

// --- End of File ---
