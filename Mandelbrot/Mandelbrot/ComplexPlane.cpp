#include "ComplexPlane.h"

ComplexPlane::ComplexPlane(int pixelWidth, int pixelHeight)
{
    m_pixel_size = { pixelWidth, pixelHeight };
    m_aspectRatio = { (float)pixelHeight / pixelWidth };
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
                Vector2f complexCoord = mapPixelToCoords({j, i});
                size_t numofIterations = countIterations(complexCoord);
                Uint8 r, g, b;
                iterationsToRGB(numofIterations, r, g, b);
                m_vArray[j + i * m_pixel_size.x].color = { r,g,b };
            }
        }
        m_state = Displaying;
    }
}

void ComplexPlane::zoomIn()
{
    m_zoomCount++;
    float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_plane_size = { x, y };
    m_state = Calculating;
}

void ComplexPlane::zoomOut()
{
    m_zoomCount--;
    float x = BASE_WIDTH * (pow(BASE_ZOOM, m_zoomCount));
    float y = BASE_HEIGHT * m_aspectRatio * (pow(BASE_ZOOM, m_zoomCount));
    m_plane_size = { x, y };
    m_state = Calculating;
}


void ComplexPlane::setCenter(Vector2i mousePixel)
{
	m_plane_center = mapPixelToCoords(mousePixel);
	m_state = Calculating;
}

void ComplexPlane::setMouseLocation(Vector2i mousePixel) {
    m_mouselocation = mapPixelToCoords(mousePixel);
}


void ComplexPlane::loadText(Text& text) {
    stringstream ss;

    ss << fixed;
    ss.precision(5); // Limit decimals for clean display

    ss << "Cursor: (" << m_mouselocation.x << ", " << m_mouselocation.y << ")\n";
    ss << "Center: (" << m_plane_center.x << ", " << m_plane_center.y << ")";

    text.setString(ss.str());
}


size_t ComplexPlane::countIterations(Vector2f coord) {
    float x = 0.0f;
    float y = 0.0f;

    size_t count = 0;

    while (x * x + y * y <= 4.0f && count < MAX_ITER) {
        float xTemp = x * x - y * y + coord.x;
        y = 2.0f * x * y + coord.y;
        x = xTemp;
        count++;
    }

    return count;
}

void ComplexPlane::iterationsToRGB(size_t count, Uint8& r, Uint8& g, Uint8& b) {
    if (count >= MAX_ITER) {
        r = g = b = 0;
        return;
    }

    float t = static_cast<float>(count) / MAX_ITER;

    if (t < 0.2f) {
        r = static_cast<Uint8>(128 - t * 640); // 128 → 0
        g = 0;
        b = static_cast<Uint8>(255);
    }
    else if (t < 0.4f) {

        r = 0;
        g = static_cast<Uint8>(255 * (t - 0.2f) / 0.2f); // 0 → 255
        b = 255;
    }
    else if (t < 0.6f) {
        r = 0;
        g = 255;
        b = static_cast<Uint8>(255 - 255 * (t - 0.4f) / 0.2f); // 255 → 0
    }
    else if (t < 0.8f) {
        r = static_cast<Uint8>(255 * (t - 0.6f) / 0.2f); // 0 → 255
        g = 255;
        b = 0;
    }
    else {
        r = 255;
        g = static_cast<Uint8>(255 - 255 * (t - 0.8f) / 0.2f); // 255 → 0
        b = 0;
    }
}


Vector2f ComplexPlane::mapPixelToCoords(Vector2i mousePixel)
{
	int pixelX = mousePixel.x;
	int pixelY = mousePixel.y;

	float left = m_plane_center.x - m_plane_size.x / 2.0f;
	float top = m_plane_center.y + m_plane_size.y / 2.0f;

	float real = ((pixelX - 0) / static_cast<float>(m_pixel_size.x)) * m_plane_size.x + left;
	float imag = ((pixelY - m_pixel_size.y) / static_cast<float>(-m_pixel_size.y)) * m_plane_size.y + top;

	return Vector2f(real, imag);

}
