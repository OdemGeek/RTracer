#include "Renderer.h"

#include "Walnut/Random.h"

void Renderer::OnResize(uint32_t width, uint32_t height)
{
	if (m_FinalImage)
	{
		if (width == m_FinalImage->GetWidth() && height == m_FinalImage->GetHeight())
			return;

		m_FinalImage->Resize(width, height);
	}
	else
	{
		m_FinalImage = std::make_shared<Walnut::Image>(width, height, Walnut::ImageFormat::RGBA);
	}

	delete[] m_ImageData;
	m_ImageData = new uint32_t[width * height];
}

void Renderer::Render()
{
	for (size_t y = 0; y < m_FinalImage->GetHeight(); y++)
	{
		for (size_t x = 0; x < m_FinalImage->GetWidth(); x++)
		{
			glm::vec2 coord = { x / (float)m_FinalImage->GetWidth(), y / (float)m_FinalImage->GetHeight() };
			coord = coord * 2.0f - 1.0f; // remap from 0->1 to -1->1
			m_ImageData[x + y * m_FinalImage->GetWidth()] = PerPixel(coord);
		}
	}

	m_FinalImage->SetData(m_ImageData);

}

uint32_t Renderer::PerPixel(glm::vec2 coord)
{
	//return Walnut::Random::UInt();
	uint8_t red = (uint8_t)(0.0f);
	uint8_t green = (uint8_t)(0.0f);
	uint8_t blue = (uint8_t)(0.0f);

	glm::vec3 rayOringin(0.0f, 0.0f, 2.0f);
	glm::vec3 rayDirection(coord.x, coord.y, -1.0f);
	float radius = 0.5f;
	rayDirection = glm::normalize(rayDirection);

	// (bx^2 + by^2)t^2 + (2(axbx + ayby))t + (ax^2 + ay^2 - r^2) = 0
	// where
	// a = ray origin
	// b = ray direction
	// r = radius
	// t = hit distance

	float a = glm::dot(rayDirection, rayDirection);
	float b = 2.0f * glm::dot(rayOringin, rayDirection);
	float c = glm::dot(rayOringin, rayOringin) - radius * radius;

	// b^2 - 4ac

	float discriminant = b * b - 4 * a * c;

	if (discriminant >= 0)
	{
		red = (uint8_t)(120.0f);
		blue = (uint8_t)(255.0f);
	}
	
	return 0xff000000 | (blue << 16) | (green << 8) | red;
}
