#pragma once
#include <memory>
#include <string>
namespace dae
{
	class GameObject;
	// EVENT ARGS
	//************
	struct EventArg
	{
		EventArg() = default;
		virtual ~EventArg() = default;
		EventArg(const EventArg& other) = delete;
		EventArg(EventArg&& other) = delete;
		EventArg& operator=(const EventArg& other) = delete;
		EventArg& operator=(EventArg&& other) = delete;
	};

	//************

	struct Event
	{
		const std::string id;
		std::unique_ptr<EventArg> arg;

		explicit Event(const std::string& _id) :
			id{ _id },
			arg{}
		{
		}
	};
}
