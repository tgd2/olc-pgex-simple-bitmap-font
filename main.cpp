#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"

#define OLC_PGEX_SIMPLEFONT
#include "olcPGEX_SimpleBitmapFont.h"

class simpleBitmapFontTest : public olc::PixelGameEngine
{
public:
	simpleBitmapFontTest()
	{
		sAppName = "Simple Bitmap Font - Test";
	}

private:
	int SelectedFont{ 0 };
	float FontScaling{ 1.0f };
	olc::Pixel Tint{ olc::WHITE };

public:
	std::vector<std::shared_ptr<olc::sbfont::font>> TestFonts{};

	bool OnUserCreate() override
	{
		std::vector<std::string> FontAtlasFileNames
		{
			"example-font-atlas.png",
		};

		/*
		0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p q r s t u v w x y z A B C D E F G H I J K L M N O P Q R S T U V W X Y Z ! £ $ % ^ & * ( ) - _ + = { } [ ] : ; @ ' ~ # < , > . ? / | " \
		*/
		std::string FontCharacters{ "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ!£$%^&*()-_+={}[]:;@'~#<,>.?/|""\\" };

		for (auto& FontAtlasFileName : FontAtlasFileNames)
		{
			TestFonts.push_back
			(
				std::make_shared<olc::sbfont::font>(FontAtlasFileName, FontCharacters)
			);
		}

		Clear(olc::Pixel{ 32, 20, 64 });

		return true;
	}

	bool OnUserUpdate(float fElapsedTime) override
	{
		if (GetKey(olc::Key::LEFT).bPressed) --SelectedFont;
		if (GetKey(olc::Key::RIGHT).bPressed) ++SelectedFont;
		SelectedFont = (SelectedFont + TestFonts.size()) % TestFonts.size();

		if (GetKey(olc::Key::UP).bPressed) FontScaling += 0.25f;
		if (GetKey(olc::Key::DOWN).bPressed) FontScaling -= 0.25f;
		FontScaling = std::clamp(FontScaling, 0.25f, 25.0f);

		if (GetKey(olc::Key::SPACE).bPressed) Tint = olc::Pixel(rand() % 256, rand() % 256, rand() % 256);

		const std::string Text{ "The quick brown fox jumps over the lazy dog" };

		olc::vf2d TextSize{ TestFonts[SelectedFont]->GetTextSize(Text, FontScaling) };

		for (olc::vf2d TextPosition{ 0.0f, 0.0f }; TextPosition.y < (float)ScreenHeight(); TextPosition.y += TextSize.y)
		{
			TestFonts[SelectedFont]->DrawStringDecal(TextPosition, Text, Tint, FontScaling);
		}

		return true;
	}
};

int main()
{
	simpleBitmapFontTest SimpleBitmapFontTest;
	if (SimpleBitmapFontTest.Construct(640, 360, 2, 2))
		SimpleBitmapFontTest.Start();
	return 0;
}