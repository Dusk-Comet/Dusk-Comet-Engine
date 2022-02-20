#ifndef DUSKCOMET_SYSTEM_EVENT__HPP
#define DUSKCOMET_SYSTEM_EVENT__HPP

#include <vector>
#include <memory>

#include <functional>


namespace dc
{

	class EventArgs
	{

	};

	template<typename t>
	class Event;

	template<typename t>
	class EventDispatcher
	{
	protected:
		void invokeEvent(Event<t>& event, const t& args)
		{
			event.invoke(args);
		}
	};

	template<typename t>
	class Event
	{
		static_assert(std::is_base_of<EventArgs, t>::value, "T must inherit from EventArgs");
	private:

		std::vector<std::function<void(t)>> _funcList;


		void invoke(const t& args)
		{
			for (std::function<void(t)> func : this->_funcList)
			{
				func(args);
			}
		}

	public:
		void addFunction(const std::function<void(t)>& function)
		{
			this->_funcList.push_back(function);
		}

		void removeFunction(const std::function<void(t)>& function)
		{
			this->_funcList.erase(function);
		}

		void operator+=(const std::function<void(t)>& function)
		{
			this->_funcList.push_back(function);
		}
		void operator-=(const std::function<void(t)>& function)
		{
			this->_funcList.erase(function);
		}
		

		friend class EventDispatcher<t>;
	};

}

#endif // !DUSKCOMET_SYSTEM_EVENT__HPP
