#include <stdio.h>
#include <string.h>
#include <math.h>
#include <unistd.h>

int main(void)
{
	float a = 0, b = 0;
	float i, j;
	int k;
	float z[1760];
	char buf[1760];

	printf("\x1b[2J");

	for (;;) {
		memset(buf, 32, 1760);
		memset(z, 0, 7040);

		for (j = 0; j < 6.28; j += 0.07) {
			for (i = 0; i < 6.28; i += 0.02) {
				float c = sin(i);
				float d = cos(j);
				float e = sin(a);
				float f = sin(j);
				float g = cos(a);
				float h = d + 2;
				float d_inv = 1 / (c * h * e + f * g + 5);
				float l = cos(i);
				float m = cos(b);
				float n = sin(b);
				float t = c * h * g - f * e;

				int x = 40 + 30 * d_inv * (l * h * m - t * n);
				int y = 12 + 15 * d_inv * (l * h * n + t * m);
				int o = x + 80 * y;
				int lum = 8 * ((f * e - c * d * g) * m - 
					      c * d * e - f * g - l * d * n);

				if (y < 22 && y > 0 && x > 0 && x < 80 && d_inv > z[o]) {
					z[o] = d_inv;
					buf[o] = ".,-~:;=!*#$@"[lum > 0 ? lum : 0];
				}
			}
		}

		printf("\x1b[H");

		for (k = 0; k < 1761; k++)
			putchar(k % 80 ? buf[k] : 10);

		a += 0.04;
		b += 0.02;
		usleep(30000);
	}

	return 0;
}
