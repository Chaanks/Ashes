/*
This file belongs to Ashes.
See LICENSE file in root folder
*/
#pragma once

#include <Ashes/Pipeline/ColourBlendState.hpp>

namespace ashes::d3d11
{
	D3D11_BLEND_DESC convert( ashes::ColourBlendState const & state );
}
