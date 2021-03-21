#pragma once
#include <blah/core/common.h>
#include <blah/containers/str.h>
#include <blah/containers/vector.h>
#include <blah/drawing/subtexture.h>
#include <blah/math/vec2.h>
#include <unordered_map>

namespace Blah
{
	class Font;

	class SpriteFont
	{
	public:
		struct Character
		{
			Subtexture subtexture;
			float advance = 0;
			Vec2 offset;
		};
	private:
		// charset & kerning maps
		std::unordered_map<u32, Character> m_characters;
		std::unordered_map<u64, float> m_kerning;

		// built texture
		Vector<TextureRef> m_atlas;

	public:
		static const u32* ASCII;

		String name;
		float size;
		float ascent;
		float descent;
		float line_gap;

		// Note:
		// charset is a list of range pairs, until a 0 terminator (ex. 32,128,0)

		SpriteFont();
		SpriteFont(const char* file, float size);
		SpriteFont(const char* file, float size, const u32* charset);
		SpriteFont(const Font& font, float size);
		SpriteFont(const Font& font, float size, const u32* charset);
		SpriteFont(const SpriteFont&) = delete;
		SpriteFont(SpriteFont&& src) noexcept;
		~SpriteFont();

		void dispose();

		SpriteFont& operator=(const SpriteFont&) = delete;
		SpriteFont& operator=(SpriteFont&& src) noexcept;

		float height() const { return ascent - descent; }
		float line_height() const { return ascent - descent + line_gap; }

		const Vector<TextureRef>& textures() { return m_atlas; }

		float width_of(const String& text) const;
		float width_of_line(const String& text, int start = 0) const;
		float height_of(const String& text) const;

		void build(const char* file, float size, const u32* charset);
		void build(const Font& font, float size, const u32* charset);

		float get_kerning(u32 codepoint0, u32 codepoint1) const;
		void set_kerning(u32 codepoint0, u32 codepoint1, float kerning);

		Character& get_character(u32 codepoint) { return m_characters[codepoint]; }
		const Character& get_character(u32 codepoint) const;
		Character& operator[](u32 codepoint) { return m_characters[codepoint]; }
		const Character& operator[](u32 codepoint) const;
	};
}