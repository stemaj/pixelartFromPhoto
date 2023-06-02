#define OLC_PGE_APPLICATION
#include "olcPixelGameEngine.h"
#include <string_view>

static constexpr std::string_view png = "./assets/landschaft.png";

static constexpr int TargetWidth 	= 640;
static constexpr int TargetHeight	= 480;
static constexpr int PixelSize		= 8;

// choose none or one of them
#define PALETTE_AVATAR
//#define PALETTE_OPTIMISM
//#define PALETTE_IOWASUMMER
//#define PALETTE_SWEETHOPE


#if defined(PALETTE_AVATAR)
std::array<olc::Pixel, 24> palette()
{
  //https://lospec.com/palette-list/avatar-palette
  return {
  olc::Pixel(0xa7,0x81,0x25),
  olc::Pixel(0xd3,0xaa,0x49),
  olc::Pixel(0x6a,0x4f,0x0e),
  olc::Pixel(0x49,0xa5,0xc1),
  olc::Pixel(0x8f,0x53,0x17),
  olc::Pixel(0x00,0x00,0x00),
  olc::Pixel(0xff,0xff,0xff),
  olc::Pixel(0x1a,0x52,0x02),
  olc::Pixel(0x55,0x3e,0x29),
  olc::Pixel(0xff,0xca,0x99),
  olc::Pixel(0x93,0xc3,0xd2),
  olc::Pixel(0x95,0x71,0x4f),
  olc::Pixel(0xfc,0xa0,0x44),
  olc::Pixel(0xed,0xb5,0x82),
  olc::Pixel(0x94,0xb3,0x52),
  olc::Pixel(0x4c,0x79,0x13),
  olc::Pixel(0xd2,0x7e,0x2a),
  olc::Pixel(0xd2,0x52,0x2a),
  olc::Pixel(0x8f,0x17,0x34),
  olc::Pixel(0xc9,0xc9,0xc9),
  olc::Pixel(0xa7,0x64,0x58),
  olc::Pixel(0xfc,0xc6,0x44),
  olc::Pixel(0x51,0x63,0x88),
  olc::Pixel(0xfe,0xff,0x99) };
}
#elif defined(PALETTE_OPTIMISM)
std::array<olc::Pixel, 32> palette()
{
  // https://lospec.com/palette-list/optimism
	return {
	olc::Pixel(0xff,0xf9,0xc9),
	olc::Pixel(0xff,0xe4,0x82),
	olc::Pixel(0xf5,0xaa,0x21),
	olc::Pixel(0xf2,0xbf,0x85),
	olc::Pixel(0xe6,0x8d,0x4f),
	olc::Pixel(0xf5,0x60,0x37),
	olc::Pixel(0xed,0x39,0x15),
	olc::Pixel(0x7b,0x35,0x26),
	olc::Pixel(0x58,0x0f,0x0b),
	olc::Pixel(0xab,0x6c,0x5c),
	olc::Pixel(0x68,0x4c,0x3c),
	olc::Pixel(0x46,0x32,0x20),
	olc::Pixel(0x25,0x17,0x0b),
	olc::Pixel(0xd9,0x8b,0x90),
	olc::Pixel(0xb8,0x48,0x69),
	olc::Pixel(0x63,0x33,0x5f),
	olc::Pixel(0x42,0x2f,0x4a),
	olc::Pixel(0x22,0x20,0x38),
	olc::Pixel(0xc1,0xd6,0xd6),
	olc::Pixel(0x5b,0xca,0xd9),
	olc::Pixel(0x03,0x83,0xbf),
	olc::Pixel(0x15,0x3f,0x94),
	olc::Pixel(0x00,0xa1,0x93),
	olc::Pixel(0x2d,0x70,0x74),
	olc::Pixel(0x3c,0x54,0x57),
	olc::Pixel(0x18,0x3f,0x39),
	olc::Pixel(0x44,0x69,0x27),
	olc::Pixel(0x92,0x9e,0x0a),
	olc::Pixel(0xc4,0xbe,0x12),
	olc::Pixel(0xa5,0x8c,0x27),
	olc::Pixel(0x70,0x5d,0x1f),
	olc::Pixel(0x8f,0x77,0x59) } ;
}
#elif defined(PALETTE_IOWASUMMER)
std::array<olc::Pixel, 5> palette()
{
  // https://lospec.com/palette-list/iowa-summer
	return {
	olc::Pixel(0xab,0xf2,0xf2),
  olc::Pixel(0x3e,0x7d,0x13),
  olc::Pixel(0xec,0xe2,0x95),
  olc::Pixel(0xf5,0x5e,0x54),
  olc::Pixel(0x65,0x33,0x2f) };
}
#elif defined(PALETTE_SWEETHOPE)
std::array<olc::Pixel, 8> palette()
{
  // https://lospec.com/palette-list/sweethope
	return {
	olc::Pixel(0x61,0x5e,0x85),
  olc::Pixel(0x9c,0x8d,0xc2),
  olc::Pixel(0xd9,0xa3,0xcd),
  olc::Pixel(0xeb,0xc3,0xa7),
  olc::Pixel(0xe0,0xe0,0xdc),
  olc::Pixel(0xa3,0xd1,0xaf),
  olc::Pixel(0x90,0xb4,0xde),
  olc::Pixel(0x71,0x7f,0xb0) };
}
#else
std::array<olc::Pixel, 0> palette()
{
  return {};
}
#endif

olc::Pixel Quantise_RGB_CustomPalette(const olc::Pixel in)
{
  float fClosest = INFINITY;
  olc::Pixel pClosest;
  auto nShades = palette();
  if (nShades.size() == 0) return in;
  for (const auto& c : nShades)
  {
    float fDistance = float(
      std::sqrt(
        std::pow(float(c.r) - float(in.r), 2) +
        std::pow(float(c.g) - float(in.g), 2) +
        std::pow(float(c.b) - float(in.b), 2)));

    if (fDistance < fClosest)
    {
      fClosest = fDistance;
      pClosest = c;
    }
  }
        
  return pClosest;
};

class PixelartFromPhoto : public olc::PixelGameEngine
{
public:
	PixelartFromPhoto()
	{
		sAppName = "PixelartFromPhoto";
	}

private:	
  olc::Sprite* sOrginal = nullptr;
  olc::Sprite* sTarget = nullptr;

public:
	bool OnUserCreate() override
	{
    sOrginal = new olc::Sprite(std::string(png));
    sTarget = new olc::Sprite(ScreenWidth(), ScreenHeight());

    // Sampling
    for (int x = 0; x < ScreenWidth(); x++)
    {
      for (int y = 0; y < ScreenHeight(); y++)
      {
        float a = float(x)/float(ScreenWidth());
        float b = float(y)/float(ScreenHeight());
        sTarget->SetPixel(x,y,Quantise_RGB_CustomPalette(sOrginal->Sample(a,b)));
      }
    }

    DrawSprite(0,0,sTarget);

    return true;
  }

  bool OnUserUpdate(float fElapsedTime) override
	{
    if (GetKey(olc::Key::ESCAPE).bPressed)
		{
			exit(0);
		}

    return true;
  }
};

int main()
{
	PixelartFromPhoto demo;
  if (demo.Construct(TargetWidth/PixelSize, TargetHeight/PixelSize, PixelSize, PixelSize))
		demo.Start();

	return 0;
}
