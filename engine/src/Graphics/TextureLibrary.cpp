#include "BurningSky/Graphics/TextureLibrary.h"
#include "BurningSky/Graphics/Texture2D.h"

#include <stdexcept>

namespace BurningSky {

	std::shared_ptr<Texture2D> TextureLibrary::Load(const std::string& name, const std::string& path) 
	{
		//if loaded already, return it
		if (Exists(name)) 
		{
			return m_Textures.at(name);
		}

		//otherwise load and store
		auto texture = std::make_shared<Texture2D>(path);
		m_Textures[name] = texture;
		return texture;
	}

	std::shared_ptr<Texture2D> TextureLibrary::Get(const std::string& name) const 
	{
		auto it = m_Textures.find(name);
		if (it == m_Textures.end())
			throw std::runtime_error("Texture Library::Get - texture not found : " + name);

		return it->second;
	}

	bool TextureLibrary::Exists(const std::string& name) const
	{
		return m_Textures.find(name) != m_Textures.end();
	}

	void TextureLibrary::Clear() 
	{
		m_Textures.clear();
	}
}