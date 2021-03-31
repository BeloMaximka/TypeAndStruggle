#include "main.h"

void BoxBlurHorizontal(Uint32* Source, Uint32* Target, int Width, int Height, int Radius) {
	double Accumlator = 1.0 / (Radius + Radius + 1);
	for (int i = 0; i < Height; i++) {
		int TotalIter = i * Width;
		int LeftIter = TotalIter;
		int RightIter = TotalIter + Radius;
		Uint8 FirstValue = *(Uint8*)(Source + TotalIter);
		Uint8 LastValue = *(Uint8*)(Source + TotalIter + Width - 1);
		int Value = (Radius + 1) * FirstValue;
		for (int j = 0; j < Radius; j++)
		{
			Value += *(Uint8*)(Source + TotalIter + j);
		}
		for (int j = 0; j <= Radius; j++)
		{
			Value += *(Uint8*)(Source + RightIter++) - FirstValue;
			*(Uint8*)(Target + TotalIter++) = round(Value * Accumlator);
		}
		for (int j = Radius + 1; j < Width - Radius; j++)
		{
			Value += *(Uint8*)(Source + RightIter++) - *(Uint8*)(Source + LeftIter++);
			*(Uint8*)(Target + TotalIter++) = round(Value * Accumlator);
		}
		for (int j = Width - Radius; j < Width; j++)
		{
			Value += LastValue - *(Uint8*)(Source + LeftIter++);
			*(Uint8*)(Target + TotalIter++) = round(Value * Accumlator);
		}
	}
}
void BoxBlurTotal(Uint32* Source, Uint32* Destination, int Width, int Height, int Radius) {
	double Accumlator = 1.0 / (Radius + Radius + 1);
	for (auto i = 0; i < Width; i++) {
		int TotalIter = i;
		int LeftIter = TotalIter;
		int RightIter = TotalIter + Radius * Width;
		Uint8 FirstValue = *(Uint8*)(Source + TotalIter);
		Uint8 LastValue = *(Uint8*)(Source + TotalIter + Width * (Height - 1));
		int Value = (Radius + 1) * FirstValue;
		for (int j = 0; j < Radius; j++)
		{
			Value += *(Uint8*)(Source + TotalIter + j * Width);
		}
		for (int j = 0; j <= Radius; j++)
		{
			Value += *(Uint8*)(Source + RightIter) - FirstValue;
			*(Uint8*)(Destination + TotalIter) = round(Value * Accumlator);
			RightIter += Width;
			TotalIter += Width;
		}
		for (int j = Radius + 1; j < Height - Radius; j++)
		{
			Value += *(Uint8*)(Source + RightIter) - *(Uint8*)(Source + LeftIter);
			*(Uint8*)(Destination + TotalIter) = round(Value * Accumlator);
			LeftIter += Width;
			RightIter += Width;
			TotalIter += Width;
		}
		for (int j = Height - Radius; j < Height; j++)
		{
			Value += LastValue - *(Uint8*)(Source + LeftIter);
			*(Uint8*)(Destination + TotalIter) = round(Value * Accumlator);
			LeftIter += Width;
			TotalIter += Width;
		}
	}
}
void BoxBlur(Uint32* Source, Uint32* Destination, int Width, int Height, int Radius) {
	BoxBlurHorizontal(Destination, Source, Width, Height, Radius);
	BoxBlurTotal(Source, Destination, Width, Height, Radius);
}
void Blur(Uint32* PixelData, int Width, int Height, int Radius)
{
	Uint32* Source = new Uint32[Width * Height];
	memcpy(Source, PixelData, Width * Height);
	BoxBlur(Source, PixelData, Width, Height, Radius); // первый цветовой канал 0xff0000
	BoxBlur(Source, (Uint32*)((Uint8*)PixelData + 1), Width, Height, Radius); // второй цветовой канал 0x00ff00
	BoxBlur(Source, (Uint32*)((Uint8*)PixelData + 2), Width, Height, Radius); // третий цветовой канал  0x0000ff
	delete[] Source;
}