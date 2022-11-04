#pragma once
#include <functional>
#include <chrono>
#include <iostream>

namespace helping_function
{
	using namespace std::chrono;
	template<typename  FUNC>
	class FuncWithDelay
	{
		milliseconds last_call;
		FUNC func;
	public:
		int min_delay;
		FuncWithDelay(FUNC func, int min_delay_bettwen_call = 60)
		{
			this->func = func;
			min_delay = min_delay_bettwen_call;
		}
		template<typename ... ARGS>
		void operator()(ARGS ... args)
		{

			auto new_call = duration_cast<milliseconds>(system_clock::now().time_since_epoch());
			if((new_call - last_call).count() < min_delay)
				return;
			last_call = new_call;
			func(args...);
		}
	};
}
