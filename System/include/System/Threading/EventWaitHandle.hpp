#pragma once

#include <wtypes.h>

#include <vector>
#include <memory>
#include <exception>

namespace System
{
	namespace Threading
	{
		enum EventResetMode {
			AutoReset,
			ManualReset
		};

		class EventWaitHandle;

		typedef std::shared_ptr<EventWaitHandle> EventWaitHandle_ptr;

		class EventWaitHandle
		{
		public:
			static const int WaitTimeout = WAIT_TIMEOUT;

		public:
			EventWaitHandle(bool signaled, EventResetMode mode);
			EventWaitHandle(bool signaled, EventResetMode mode, const std::wstring& name);

			virtual ~EventWaitHandle();

			explicit operator HANDLE() const;
			operator bool() const;

			void Set();
			void Reset();

			bool IsSet() const;

			int WaitOne() const;
			int WaitOne(DWORD dwMilliseconds) const;

			static int WaitAny(const std::vector<EventWaitHandle_ptr>& waitHandles);
			static int WaitAny(const std::vector<EventWaitHandle_ptr>& waitHandles, DWORD dwMilliseconds);
			static bool WaitAll(const std::vector<EventWaitHandle_ptr>& waitHandles);
			static bool WaitAll(const std::vector<EventWaitHandle_ptr>& waitHandles, DWORD dwMilliseconds);

		protected:
			HANDLE m_hEvent;
		};
	}
}
