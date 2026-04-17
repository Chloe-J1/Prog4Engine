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
		virtual ~EventArg() = default;
	};

	//************

	struct Event
	{
		const std::string id;
		std::unique_ptr<EventArg> arg;

		explicit Event(const std::string& _id) :
			id{ _id }
		{
		}
	};
}
