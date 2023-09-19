#include <stdio.h>
#include <time.h>
#include <stdint.h>

void HashSeeds(uint32_t& seed1, uint32_t& seed2)
{
	seed1 ^= seed2;
	seed1 *= 0xBAC57D37;
	seed2 ^= seed1;
	seed2 *= 0x24F66AC9;
}

void HashIdx(uint32_t idx, uint32_t seed1, uint32_t seed2, float& hash)
{
	uint32_t HashSeeds = idx;

	HashSeeds ^= seed1;
	HashSeeds *= 0xBAC57D37;
	HashSeeds ^= seed2;
	HashSeeds *= 0x24F66AC9;

	hash = int32_t(HashSeeds) * 0.0000000004656612875245796f;
	//hash = uint32_t(HashSeeds) * 0.0000000002328306437622898f;
}

int main()
{
	uint32_t seed1 = time(NULL) ^ 0xE621B963;
	uint32_t seed2 = 0x6053653F ^ (time(NULL) >> 32);

	printf("Seed1: %u\n", seed1);
	printf("Seed2: %u\n\n", seed2);

	/*while(true)
	{*/
		HashSeeds(seed1, seed2);
		float hash;
		for (uint32_t x = 0; x < 16; x++)
		{
			HashIdx(x, seed1, seed2, hash);
			printf("%f\n", hash);
		}
	//}

	return 0;
}