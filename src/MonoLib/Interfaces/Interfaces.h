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
	
	class IDeserializationSource
	{
	public:
		virtual void SetBytes(const ByteArray& data) const = 0;
	};
	using DeserializationSourcePtr = std::shared_ptr<IDeserializationSource>;
	
	//TODO: is this helpful? - maybe
	class ISerializerBase
	{
	public:
		virtual bool SerializeBase(const ModelPtr& modelInstance, SerializationTargetPtr& target) const = 0;
		virtual bool DeserializeBase(ModelPtr& modelInstance, const DeserializationSourcePtr& source) const = 0;
	};


	template<typename ModelTypeName>
	class ISerializer : ISerializerBase
	{
		//disable the class if the ModelTypeName is not a child of Model
		template<typename U = ModelTypeName>
		typename std::enable_if_t<!std::is_base_of_v<IModel, U>>
		ISerializer() {}
	public:
		virtual bool SerializeBase(const ModelPtr& modelInstance, SerializationTargetPtr& target) const override sealed
		{
			return Serialize(std::dynamic_pointer_cast<ModelTypePtr, ModelPtr>(modelInstance), target);
		}
		virtual bool DeserializeBase(ModelPtr& modelInstance, const DeserializationSourcePtr& source) const override sealed
		{
			return Deserialize(std::dynamic_pointer_cast<ModelTypePtr, ModelPtr>(modelInstance), source);
		}


		using ModelTypePtr = std::shared_ptr<ModelTypeName>;
		virtual bool Serialize(const ModelTypePtr& modelInstance, SerializationTargetPtr& target) const = 0;
		virtual bool Deserialize(ModelTypePtr& modelInstance, const DeserializationSourcePtr& source) const = 0;
	};


	/*

	View Model Classes


	*/

	//This would hold stuff like the scene graph
	class IViewModel
	{
	public:
		virtual void ReloadModel(const ModelPtr& modelInstance) = 0;//TODO: what parameters?
	};
	using ViewModelPtr = std::shared_ptr<IViewModel>;



	/*
	
	View Classes
	
	
	*/

	//this would interact with OpenGL/DirectX to buffer the ViewModel data and render it
	class IView
	{
	public:
		virtual void Init(const ViewModelPtr& vm) = 0;
		virtual void ShowOutput(double timeNow) = 0;
		virtual void ProcessMessages() = 0;
	};

	class IResourceData
	{
	};
	using ResourceDataPtr = std::shared_ptr<IResourceData>;

	class IResourceLoader
	{
	public:
		virtual std::string GetPattern() const = 0;
		virtual bool UseRawData() const = 0;
		virtual bool LoadResource(ResourceDataPtr& targetData, const ByteArray& rawData) const = 0;

		//how big the resource be once in memory
		virtual int GetLoadedSize(const ByteArray& rawData) const = 0;
	};

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