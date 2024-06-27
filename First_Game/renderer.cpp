internal void
render_background() {												// The Good Looking Pattern
	u32* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = 0xff00ff * x + 0x00ff00 * y;
		}
	}
}

internal void
clear_screen(u32 color) {
	u32* pixel = (u32*)render_state.memory;
	for (int y = 0; y < render_state.height; y++) {
		for (int x = 0; x < render_state.width; x++) {
			*pixel++ = color;
		}
	}
}

internal void
draw_rect_in_pixels(int x0, int y0, int x1, int y1, u32 color) {
	
	x0 = clamp(0, x0, render_state.width);
	x1 = clamp(0, x1, render_state.width);
	y0 = clamp(0, y0, render_state.height);
	y1 = clamp(0, y1, render_state.height);

	for (int y = y0; y < y1; y++) {
		u32* pixel = (u32*)render_state.memory + x0 + y * render_state.width;
		for (int x = x0; x < x1; x++) {
			*pixel++ = color;
		}
	}
}

global_variable float render_scale = 0.01f;

internal void
draw_rect(float x, float y, float half_size_x, float half_size_y, u32 color) {

	int scaling_quant = render_state.height;
	if ((float)render_state.width / (float)render_state.height < 1.0) scaling_quant = render_state.width;

	x *= scaling_quant * render_scale;
	y *= scaling_quant * render_scale;							// Scaling wrt height, can also be done with width
	half_size_x *= scaling_quant * render_scale;
	half_size_y *= scaling_quant * render_scale;

	x += render_state.width / 2.f;						// Adding half the width and height
	y += render_state.height / 2.f;

	// Change to pixels
	int x0 = x - half_size_x;
	int x1 = x + half_size_x;
	int y0 = y - half_size_y;
	int y1 = y + half_size_y;

	draw_rect_in_pixels(x0, y0, x1, y1, color);
}

internal void 
draw_number(int number, float x, float y, float size, u32 color) {

	bool displayed_number = false;
	while (number || !displayed_number) {
		displayed_number = true;
		int digit = number % 10;
		number /= 10;
		switch (digit) {
		case 0: {
			draw_rect(x - size, y, size * 0.5f, size * 2.5f, color);
			draw_rect(x + size, y, size * 0.5f, size * 2.5f, color);
			draw_rect(x, y + 2.0f * size, size * 0.5f, size * 0.5f, color);
			draw_rect(x, y - 2.0f * size, size * 0.5f, size * 0.5f, color);
			x -= 4.0f;
		} break;
		case 1: {
			draw_rect(x + size, y, size * 0.5f, size * 2.5f, color);
			x -= 2.0f;
		} break;
		case 2: {
			draw_rect(x, y + 2.0f * size, size * 1.5f, size * 0.5f, color);
			draw_rect(x, y - 2.0f * size, size * 1.5f, size * 0.5f, color);
			draw_rect(x, y, size * 1.5f, size * 0.5f, color);
			draw_rect(x + size, y + size, size * 0.5f, size * 1.5f, color);
			draw_rect(x - size, y - size, size * 0.5f, size * 1.5f, color);
			x -= 4.0f;
		} break;
		case 3: {
			draw_rect(x + size, y, size * 0.5f, size * 2.5f, color);
			draw_rect(x, y + 2.0f * size, size * 1.5f, size * 0.5f, color);
			draw_rect(x, y - 2.0f * size, size * 1.5f, size * 0.5f, color);
			draw_rect(x, y, size * 1.5f, size * 0.5f, color);
			x -= 4.0f;
		} break;
		case 4: {
			draw_rect(x + size, y, size * 0.5f, size * 2.5f, color);
			draw_rect(x - size, y + size, size * 0.5f, size * 1.5f, color);
			draw_rect(x, y, size * 1.5f, size * 0.5f, color);
			x -= 4.0f;
		} break;
		case 5: {
			draw_rect(x, y + 2.0f * size, size * 1.5f, size * 0.5f, color);
			draw_rect(x, y - 2.0f * size, size * 1.5f, size * 0.5f, color);
			draw_rect(x, y, size * 1.5f, size * 0.5f, color);
			draw_rect(x - size, y + size, size * 0.5f, size * 1.5f, color);
			draw_rect(x + size, y - size, size * 0.5f, size * 1.5f, color);
			x -= 4.0f;
		} break;
		case 6: {
			draw_rect(x - size, y, size * 0.5f, size * 2.5f, color);
			draw_rect(x, y + 2.0f * size, size * 1.5f, size * 0.5f, color);
			draw_rect(x, y - 2.0f * size, size * 1.5f, size * 0.5f, color);
			draw_rect(x, y, size * 1.5f, size * 0.5f, color);
			draw_rect(x + size, y - size, size * 0.5f, size * 1.5f, color);
			x -= 4.0f;
		} break;
		case 7: {
			draw_rect(x + size, y, size * 0.5f, size * 2.5f, color);
			draw_rect(x, y + 2.0f * size, size * 1.5f, size * 0.5f, color);
			x -= 4.0f;
		} break;
		case 8: {
			draw_rect(x - size, y, size * 0.5f, size * 2.5f, color);
			draw_rect(x + size, y, size * 0.5f, size * 2.5f, color);
			draw_rect(x, y + 2.0f * size, size * 0.5f, size * 0.5f, color);
			draw_rect(x, y - 2.0f * size, size * 0.5f, size * 0.5f, color);
			draw_rect(x, y, size * 1.5f, size * 0.5f, color);
			x -= 4.0f;
		} break;
		case 9: {
			draw_rect(x + size, y, size * 0.5f, size * 2.5f, color);
			draw_rect(x, y + 2.0f * size, size * 1.5f, size * 0.5f, color);
			draw_rect(x, y - 2.0f * size, size * 1.5f, size * 0.5f, color);
			draw_rect(x, y, size * 1.5f, size * 0.5f, color);
			draw_rect(x - size, y + size, size * 0.5f, size * 1.5f, color);
			x -= 4.0f;
		} break;
		}
	}
}