#pragma once
#include <memory>
#include <string>
#include <unordered_map>

namespace BurningSky {
	class Texture2D;

	//simple texture cache
	class TextureLibrary 
	{
	public:
		//load texture and store under a name
		//if name already exists, returns the existing texture
		std::shared_ptr<Texture2D> Load(const std::string& name, const std::string& path);


		//get a previously loaded texture
		std::shared_ptr<Texture2D> Get(const std::string& name) const;

		//returns true if library has a texture with this name
		bool Exists(const std::string& name) const;

		//optional helpers
		void Clear();
		std::size_t Size() const { return m_Textures.size(); }

	private:
		std::unordered_map<std::string, std::shared_ptr<Texture2D>> m_Textures;	
	};


}