#pragma once

#include <string>
#include <utility>

namespace BurningSky {
	// layers are unit of behavior that the Application updates/renders each frame
	// can be stacked (game layer, ui layer, debug layer)

	class Layer 
	{
	public:
		explicit Layer(std::string name = "Layer")
			: m_Name(std::move(name)) {}

		virtual ~Layer() = default;


		//called when layer is addewd to the app
		virtual void OnAttach() {}

		//called when layer removed from app
		virtual void OnDetach() {}

		//called every frame (dt in seconds)
		virtual void OnUpdate(float dt) { (void)dt; }

		//called every frame after updates to render
		virtual void OnRender() {}

		const std::string& GetName() const { return m_Name; }
		

	protected:
		std::string m_Name;

	};

}