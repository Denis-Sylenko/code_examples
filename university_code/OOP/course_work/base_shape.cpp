#include "pch.h"
#include <SFML/Graphics/Shape.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/System/Err.hpp>
#include <cmath>
#include "Base_Shape.h"
#include <assert.h>

namespace
{
	sf::Vector2f computeNormal(const sf::Vector2f& p1, const sf::Vector2f& p2)
	{
		sf::Vector2f normal(p1.y - p2.y, p2.x - p1.x);
		float length = std::sqrt(normal.x * normal.x + normal.y * normal.y);
		if (length != 0.f)
			normal /= length;
		return normal;
	}

	float dotProduct(const sf::Vector2f& p1, const sf::Vector2f& p2)
	{
		return p1.x * p2.x + p1.y * p2.y;
	}
}


using namespace sf;

	base_shape::~base_shape()
	{
	}

	void base_shape::setFillColor(const Color& color)
	{
		m_fillColor = color;
		updateFillColors();
	}

	const Color& base_shape::getFillColor() const
	{
		return m_fillColor;
	}

	void base_shape::setOutlineColor(const Color& color)
	{
		m_outlineColor = color;
		updateOutlineColors();
	}

	const Color& base_shape::getOutlineColor() const
	{
		return m_outlineColor;
	}

	void base_shape::setOutlineThickness(float thickness)
	{
		m_outlineThickness = thickness;
		update(); 
	}

	float base_shape::getOutlineThickness() const
	{
		return m_outlineThickness;
	}

	FloatRect base_shape::getLocalBounds() const
	{
		return m_bounds;
	}

	FloatRect base_shape::getGlobalBounds() const
	{
		return getTransform().transformRect(getLocalBounds());
	}

	base_shape * base_shape::create_shape(Shape_ID id)
	{
		shape_registry& registry = getRegistry();
		if (registry.find(id) != registry.end()) {
			return registry[id]->clone();
		}
		return 0;
	}

	void base_shape::clear()
	{
		return;
	}


	base_shape::base_shape() :
		m_fillColor(255, 255, 255),
		m_outlineColor(255, 255, 255),
		m_outlineThickness(0),
		m_vertices(TriangleFan),
		m_outlineVertices(TriangleStrip),
		m_insideBounds(),
		m_bounds()
	{
	}

	void base_shape::update()
	{
		std::size_t count = getPointCount();
		if (count < 3)
		{
			m_vertices.resize(0);
			m_outlineVertices.resize(0);
			return;
		}

		m_vertices.resize(count + 2); 

		for (std::size_t i = 0; i < count; ++i)
			m_vertices[i + 1].position = getPoint(i);
		m_vertices[count + 1].position = m_vertices[1].position;


		m_vertices[0] = m_vertices[1];
		m_insideBounds = m_vertices.getBounds();

	
		m_vertices[0].position.x = m_insideBounds.left + m_insideBounds.width / 2;
		m_vertices[0].position.y = m_insideBounds.top + m_insideBounds.height / 2;


		updateFillColors();

		
		updateTexCoords();

		updateOutline();
	}

	void base_shape::addPrototype(Shape_ID id, base_shape * prototype)
	{
		shape_registry& registry = getRegistry();
			registry[id] = prototype;
	}

	void base_shape::removePrototype(Shape_ID id)
	{
		shape_registry& registry = getRegistry();
		registry.erase(registry.find(id));
	}

	void base_shape::draw(RenderTarget& target, RenderStates states) const
	{
		states.transform *= getTransform();

		states.texture = m_texture;
		target.draw(m_vertices, states);

		if (m_outlineThickness != 0)
		{
			states.texture = NULL;
			target.draw(m_outlineVertices, states);
		}
	}

	void base_shape::updateFillColors()
	{
		for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i)
			m_vertices[i].color = m_fillColor;
	}

	void base_shape::updateTexCoords()
	{
		for (std::size_t i = 0; i < m_vertices.getVertexCount(); ++i)
		{
			float xratio = m_insideBounds.width > 0 ? (m_vertices[i].position.x - m_insideBounds.left) / m_insideBounds.width : 0;
			float yratio = m_insideBounds.height > 0 ? (m_vertices[i].position.y - m_insideBounds.top) / m_insideBounds.height : 0;
			m_vertices[i].texCoords.x = m_textureRect.left + m_textureRect.width * xratio;
			m_vertices[i].texCoords.y = m_textureRect.top + m_textureRect.height * yratio;
		}
	}

	void base_shape::updateOutline()
	{
		if (m_outlineThickness == 0.f)
		{
			m_outlineVertices.clear();
			m_bounds = m_insideBounds;
			return;
		}

		std::size_t count = m_vertices.getVertexCount() - 2;
		m_outlineVertices.resize((count + 1) * 2);

		for (std::size_t i = 0; i < count; ++i)
		{
			std::size_t index = i + 1;

			Vector2f p0 = (i == 0) ? m_vertices[count].position : m_vertices[index - 1].position;
			Vector2f p1 = m_vertices[index].position;
			Vector2f p2 = m_vertices[index + 1].position;

			Vector2f n1 = computeNormal(p0, p1);
			Vector2f n2 = computeNormal(p1, p2);

			if (dotProduct(n1, m_vertices[0].position - p1) > 0)
				n1 = -n1;
			if (dotProduct(n2, m_vertices[0].position - p1) > 0)
				n2 = -n2;

			float factor = 1.f + (n1.x * n2.x + n1.y * n2.y);
			Vector2f normal = (n1 + n2) / factor;

			m_outlineVertices[i * 2 + 0].position = p1;
			m_outlineVertices[i * 2 + 1].position = p1 + normal * m_outlineThickness;
		}

		m_outlineVertices[count * 2 + 0].position = m_outlineVertices[0].position;
		m_outlineVertices[count * 2 + 1].position = m_outlineVertices[1].position;

		updateOutlineColors();

		m_bounds = m_outlineVertices.getBounds();
	}


	void base_shape::updateOutlineColors()
	{
		for (std::size_t i = 0; i < m_outlineVertices.getVertexCount(); ++i)
			m_outlineVertices[i].color = m_outlineColor;
	}

	bool base_shape::contains(const Vector2f & point) const
	{
		return getGlobalBounds().contains(point);
	}

	shape_registry & getRegistry()
	{
		static shape_registry instance;
		return instance;
	}
