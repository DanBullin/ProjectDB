#include "Physics/SFMLDebugDraw.h"

/*! \file SFMLDebugDraw.cpp
* \brief CPP file for SFMLDebugDraw
*
* Implementation for a SFMLDebugDraw
*
*/

/*!
\param world a b2World* - A pointer to the physics world
*/
void SFMLDebugDraw::setWorld(b2World * world) {
	m_pWorld = world;
	m_pWorld->SetDebugDraw(&m_debugDraw);
	m_debugDraw.SetFlags(b2Draw::e_shapeBit);
}

/*!
\param target a sf::RenderTarget& - A reference to the RenderTarget
\param states a sf::RenderStates - A render state
*/
void SFMLDebugDraw::draw(sf::RenderTarget &target, sf::RenderStates states) const {
	m_pWorld->DrawDebugData();
	std::vector<sf::VertexArray> shapes = m_debugDraw.getShapes();
	for (auto shape : shapes)
	{
		target.draw(shape);
	}
};

//! clear()
void SFMLDebugDraw::clear() 
{ 
	m_debugDraw.clearShapes(); 
}

/*!
\return a std::vector<sf::VertexArray> - Returns a vector of vertex arrays
*/
std::vector<sf::VertexArray> DebugDraw::getShapes() const 
{ 
	return m_shapes; 
}

//! clearShapes()
void DebugDraw::clearShapes() 
{
	m_shapes.clear(); 
}

/*!
\param p a const b2Vec2& - The vector of the point to draw
\param size a float32 - The size of the point
\param color a const b2Color& - The colour of the point
*/
void DebugDraw::DrawPoint(const b2Vec2& p, float32 size, const b2Color& color) {
	sf::VertexArray va(sf::Points, 1);
	va[0] = sf::Vertex(sf::Vector2f(p.x, p.y), sf::Color((int)color.r, (int)color.g, (int)color.b));
	m_shapes.push_back(va);
};

/*!
\param vertices a const b2Vec2* - A pointer to the vertices
\param vertexCount an int32 - The number of vertices
\param color a const b2Color& - The colour of the point
*/
void DebugDraw::DrawSolidPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
	sf::VertexArray va(sf::Quads, vertexCount);

	for (int i = 0; i < vertexCount; i++)
	{
		va[i] = sf::Vertex(sf::Vector2f(vertices[i].x, vertices[i].y), sf::Color((int)color.r, (int)color.g, (int)color.b));
	}
	m_shapes.push_back(va);
};

/*!
\param vertices a const b2Vec2* - A pointer to the vertices
\param vertexCount an int32 - The number of vertices
\param color a const b2Color& - The colour of the point
*/
void DebugDraw::DrawPolygon(const b2Vec2* vertices, int32 vertexCount, const b2Color& color) {
	sf::VertexArray va(sf::LineStrip, vertexCount + 1);

	for (int i = 0; i < vertexCount; i++)
	{
		va[i] = sf::Vertex(sf::Vector2f(vertices[i].x, vertices[i].y), sf::Color((int)color.r, (int)color.g, (int)color.b));
	}
	va[vertexCount] = va[0];
	m_shapes.push_back(va);
};

/*!
\param center a const b2Vec2& - The center point of the circle
\param radius a float32 - The radius of the circle
\param color a const b2Color& - The colour of the point
*/
void DebugDraw::DrawCircle(const b2Vec2& center, float32 radius, const b2Color& color) {
	float vertexCount = 30.f;
	sf::VertexArray va(sf::LinesStrip, (int)vertexCount);
	float thetaStep = (2.f * 3.15f) / (vertexCount - 1.f);
	float theta = 0;
	sf::Vector2f point;

	for (int i = 0; i < vertexCount; i++)
	{
		point.x = center.x + cos(theta) * radius;
		point.y = center.y + sin(theta) * radius;
		va[i] = sf::Vertex(point, sf::Color((int)color.r, (int)color.g, (int)color.b));
		theta += thetaStep;
	}
	m_shapes.push_back(va);
};

/*!
\param center a const b2Vec2& - The center point of the circle
\param radius a float32 - The radius of the circle
\param axis a const b2Vec2& - The axis the circle is on
\param color a const b2Color& - The colour of the point
*/
void DebugDraw::DrawSolidCircle(const b2Vec2& center, float32 radius, const b2Vec2& axis, const b2Color& color) {
	float vertexCount = 31.f;
	sf::VertexArray va(sf::TriangleFan, (int)vertexCount);
	float thetaStep = (2.f * 3.15f) / (vertexCount - 2.f);
	float theta = 0;
	sf::Vector2f point;

	va[0] = sf::Vertex(sf::Vector2f(center.x, center.y), sf::Color((int)color.r, (int)color.g, (int)color.b));
	for (int i = 1; i < vertexCount; i++)
	{
		point.x = center.x + cos(theta) * radius;
		point.y = center.y + sin(theta) * radius;
		va[i] = sf::Vertex(point, sf::Color((int)color.r, (int)color.g, (int)color.b));
		theta += thetaStep;
	}
	m_shapes.push_back(va);

	sf::VertexArray va2(sf::Lines, 2);
	va2[0] = sf::Vertex(sf::Vector2f(center.x, center.y), sf::Color(255, 0, 0));
	point.x = center.x + axis.x * radius;
	point.y = center.y + axis.y * radius;
	va2[1] = sf::Vertex(point, sf::Color(255, 0, 0));
	m_shapes.push_back(va2);
};

/*!
\param p1 a const b2Vec2& - The vector of the first point of the line
\param p2 a const b2Vec2& - The vector of the second point of the line
\param color a const b2Color& - The colour of the point
*/
void DebugDraw::DrawSegment(const b2Vec2& p1, const b2Vec2& p2, const b2Color& color) {
	sf::VertexArray va(sf::Lines, 2);
	va[0] = sf::Vertex(sf::Vector2f(p1.x, p1.y), sf::Color((int)color.r, (int)color.g, (int)color.b));
	va[1] = sf::Vertex(sf::Vector2f(p2.x, p2.y), sf::Color((int)color.r, (int)color.g, (int)color.b));
	m_shapes.push_back(va);
};

/*!
\param xf a const b2Transform& - A reference of the transform
*/
void DebugDraw::DrawTransform(const b2Transform& xf) {
	// Sorry, not sure how to do this?
};