#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
	m_pixel_size = { pixelWidth, pixelHeight };
	m_aspectRatio = { (float)pixelHeight / pixelWidth};
	m_plane_center = { 0,0 };
	m_plane_size = { BASE_WIDTH, BASE_HEIGHT * m_aspectRatio };
	m_zoomCount = 0;
	m_state = State::Calculating;
	VertexArray m_vArray(Points, pixelHeight * pixelWidth);
}


void ComplexPlane::draw(RenderTarget& target, RenderStates states) const
{
	target.draw(m_vArray);
}

void ComplexPlane::updateRender()
{
	if (m_state == Calculating)
	{
		for (int j = 0; j < m_pixel_size.x; j++)
		{
			for (int i = 0; i < m_pixel_size.y; i++)
			{
				m_vArray[j + i * m_pixel_size.x].position = { (float)j, (float)i };
				mapPixelToCoords();
				size_t numofIterations = countIterations(m_mouselocation);
				Uint8 r, g, b;
				iterationsToRGB(numofIterations , r, g, b);
				m_vArray[j + i * m_pixel_size.x].color = { r,g,b };
			}
		}
		m_state = Displaying;
	}
}

void ComplexPlane::zoomIn()
{
	m_zoomCount++;
	size_t x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	size_t y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = { x, y };
	m_state = Calculating;

}

void ComplexPlane::zoomOut()
{
	m_zoomCount--;
	size_t x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
	size_t y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
	m_plane_size = { x, y };
	m_state = Calculating;
}

void ComplexPlane::setMouseLocation(Vector2i mousPixel)
{
	Vector2f pixelCoords = mapPixelToCoords();
	m_mouselocation = pixelCoords;
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
