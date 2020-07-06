#pragma once
#include <map>
#include <SFML/Graphics/Export.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/System/Vector2.hpp>
#include "SFML/Graphics.hpp"
#include "Memento.h"

using namespace sf;

enum Shape_ID { Simple_Shape_ID, Rectangle_Shape_ID };
class base_shape;

typedef std::map<Shape_ID, base_shape*> shape_registry;

shape_registry& getRegistry();

class Help_Class { };

	class base_shape : public Drawable, public Transformable
	{
	public:
		virtual ~base_shape();
		virtual void setFillColor(const Color& color);
		virtual void setOutlineColor(const Color& color);
		virtual void setOutlineThickness(float thickness);
		const Color& getFillColor() const;
		const Color& getOutlineColor() const;
		float getOutlineThickness() const;
		virtual std::size_t getPointCount() const = 0;
		virtual Vector2f getPoint(std::size_t index) const = 0;
		virtual FloatRect getLocalBounds() const;
		virtual FloatRect getGlobalBounds() const;
		

		virtual std::string get_data_to_save () = 0;
		virtual void paint_it_red() = 0;
		virtual base_shape* clone() = 0;
		static base_shape* create_shape(Shape_ID id);
		virtual void clear();
		virtual void add_shape(base_shape* shape) = 0;
		virtual bool select_shape(sf::RenderWindow& window) = 0;
		virtual void draw_shape(sf::RenderWindow& window) const = 0;
		virtual void collision_color_change() = 0;
		virtual void resize() = 0;
		virtual void movement(sf::RenderWindow& window) = 0;
		virtual void auto_movement(sf::RenderWindow& window) = 0;
		virtual bool contains(const Vector2f& point) const;
		virtual	void make_speed_bigger() = 0;
		virtual	void change_automove() = 0;
		virtual	void make_speed_smaller() =0;
		virtual void set_speed(double speed) = 0;
		virtual void set_automove(bool _automove)= 0;
		virtual void set_scale(float _scale) = 0;
	protected:
		base_shape();
		void update();
		static void addPrototype(Shape_ID id, base_shape * prototype);
		static void removePrototype(Shape_ID id);

	private:

		virtual void draw(RenderTarget& target, RenderStates states) const;
		void updateFillColors();
		void updateTexCoords();
		void updateOutline();
		void updateOutlineColors();

	private:

		const Texture* m_texture;          
		IntRect        m_textureRect;      
		Color          m_fillColor;        
		Color          m_outlineColor;     
		float          m_outlineThickness; 
		VertexArray    m_vertices;         
		VertexArray    m_outlineVertices;  
		FloatRect      m_insideBounds;     
		FloatRect      m_bounds;           

	};
