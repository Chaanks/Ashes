#pragma once

#include <Prerequisites.hpp>

namespace vkapp
{
	/**
	*\~french
	*\brief
	*	Les donn�es d'un sommet textur�.
	*\~english
	*\brief
	*	The data for one textured vertex.
	*/
	struct TexturedVertexData
	{
		renderer::Vec4 position;
		renderer::Vec2 uv;
	};

	static wxString const AppName = wxT( "03-NormalMapping" );
	static wxString const AppDesc = wxT( "Normal Mapping" );

	class RenderPanel;
	class MainFrame;
	class Application;
}
