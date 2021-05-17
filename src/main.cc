#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fstream>

#include "../include/led-matrix-c.h"

using namespace std;

int main(int argc, char** argv) {
	struct RGBLedMatrixOptions options;
	struct RGBLedMatrix* matrix;
	struct LedCanvas* offscreen_canvas;
	int width, height;
	int x, y;

	memset(&options, 0, sizeof(options));
	
	matrix = led_matrix_create_from_options(&options, &argc, &argv);
	if (matrix == NULL)
		return 1;

	offscreen_canvas = led_matrix_create_offscreen_canvas(matrix);

	led_canvas_get_size(offscreen_canvas, &width, &height);

	fprintf(stderr, "Size: %dx%d. Hardware gpio mapping: %s\n",
		width, height, options.hardware_mapping);

	ifstream fin("array_data", ios_base::in);
	int r, g, b, mode;
	fin >> mode;
	while (1) {
		for (y = 0; y < height; ++y) {
			for (x = 0; x < width; ++x) {
				r=g=b=-1;
				fin >> r;
				fin >> g;
				fin >> b;
				if(r==-1) break;
				led_canvas_set_pixel(offscreen_canvas, x, y, r, g, b);
			}
			if(r==-1) break;
		}
		if(r==-1)
		{
			fin.clear();
			fin.seekg(0, std::ios::beg);
			fin >> mode;
		}
		offscreen_canvas = led_matrix_swap_on_vsync(matrix, offscreen_canvas);
		if(mode) usleep(100000);
	}
	led_matrix_delete(matrix);
	fin.close();
	return 0;
}
