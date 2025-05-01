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

void ComplexPlane::updateRender()
{

}

void ComplexPlane::zoomIn()
{

}

void ComplexPlane::zoomOut()
{

}

void ComplexPlane::setMouseLocation(Vector 2i mousPixel)
{

}

void ComplexPlane::loadText(Text& text)
{

}

size_t ComplexPlane::countIterations(Vector2f coord)
{

}

void ComplexPlane::iterationsToRGB(size_t count, Uint& r, Uint& g, Uint& b)
{

}

Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{

}
