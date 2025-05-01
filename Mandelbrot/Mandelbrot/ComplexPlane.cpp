#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size = ? ? ? ;
	m_plane_center{ 0,0 };
	m_plane_size{ BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::Calculating;
	VertexArray = ? ? ? ;
}


void ComplexPlane::draw(RenderTarget& target, RenderStates states)
{
	target.draw(m_vArray);
}

