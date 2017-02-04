#pragma once
#include <memory>
#include <string>
#include <vector>

namespace MonoLib
{


	/*
	
	Model Classes
	
	
	*/
	class IModel
	{
	};
	using ModelPtr = std::shared_ptr<IModel>;

	using ByteArray = std::vector<char>;
	class ISerializationTarget
	{
	public:
		virtual void GetBytes(ByteArray& data) const = 0;
	};
	using SerializationTargetPtr = std::shared_ptr<ISerializationTarget>;

	class ITextSerializationTarget : ISerializationTarget
	{
	public:
		virtual void GetText(std::string& data) const = 0;
	};
	
	class ISerializerBase
	{
	public:
		virtual SerializationTargetPtr Serialize(const ModelPtr& modelInstance) const = 0;
	};


	template<typename ModelTypeName>
	class ISerializer : ISerializerBase
	{
	public:
		virtual SerializationTargetPtr Serialize(const ModelPtr& modelInstance) const override sealed
		{
			return Serialize(std::dynamic_pointer_cast<ModelTypePtr, ModelPtr>(modelInstance));
		}

		using ModelTypePtr = std::shared_ptr<ModelTypeName>;
		virtual SerializationTargetPtr Serialize(const ModelTypePtr& modelInstance) const = 0;
	};


	/*

	View Model Classes


	*/

	class IViewModel
	{
	public:
		virtual void Update() = 0;//TODO: what parameters?
	};
	using ViewModelPtr = std::shared_ptr<IViewModel>;



	/*

	Controller Classes


	*/

	class IEventData
	{
	};
	using EventDataPtr = std::shared_ptr<IEventData>;




	class IEventHandler
	{
	public:
		virtual bool HandleEvent(const EventDataPtr& dataPtr) const = 0;
		virtual std::string GetEventName() const = 0;
	};
	using EventHandlerPtr = std::shared_ptr<IEventHandler>;



	
	class IController
	{
	public:
		virtual void QueueEvent(const EventDataPtr& data) = 0;
		virtual void ProcessQueue(double timeTarget) = 0;

		virtual void RegisterEventHandler(const std::string& eventName, const EventHandlerPtr& eventHandler) = 0;
	};
	using ControllerPtr = std::shared_ptr<IController>;



}