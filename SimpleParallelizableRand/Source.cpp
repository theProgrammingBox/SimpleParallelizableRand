#include <stdio.h>
#include <time.h>
#include <stdint.h>

typedef uint32_t u32;
typedef int8_t i8;
typedef float f32;

void Lehmer32(u32& x)
{
	x *= 0xBAC57D37;
	x ^= x >> 16;
	x *= 0x24F66AC9;
	x ^= x >> 16;
}

void FourF32Rands(u32 idx, u32 seed1, u32 seed2, f32* fourF32s)
{
	idx ^= seed1;
	Lehmer32(idx);
	idx ^= seed2;

	fourF32s[0] = i8(idx & 0xFF) * 0.0078125f;
	fourF32s[1] = i8(idx >> 8 & 0xFF) * 0.0078125f;
	fourF32s[2] = i8(idx >> 16 & 0xFF) * 0.0078125f;
	fourF32s[3] = i8(idx >> 24) * 0.0078125f;
}

int main()
{
	const u32 WIDTH = 1440;
	const u32 HEIGHT = 810;

	f32 fourF32s[4];

	u32 seed1 = time(NULL) ^ 0xE621B963;
	Lehmer32(seed1);
	u32 seed2 = seed1 ^ 0x6053653F;
	Lehmer32(seed2);

	printf("Seed1: %u\n", seed1);
	printf("Seed2: %u\n\n", seed2);

	while(true)
	{
		Lehmer32(seed1);
		Lehmer32(seed2);
		for (u32 x = 0; x < WIDTH; x++)
		{
			for (u32 y = 0; y < HEIGHT; y++)
			{
				FourF32Rands(y * WIDTH + x, seed1, seed2, fourF32s);
				printf("%f %f %f %f\n", fourF32s[0], fourF32s[1], fourF32s[2], fourF32s[3]);
			}
		}
	}

	return 0;
}