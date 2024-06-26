#define is_down(b) input->buttons[b].is_down
#define pressed(b) (input->buttons[b].is_down && input->buttons[b].changed)
#define released(b) (!input->buttons[b].is_down && input->buttons[b].changed)

float player1_p, player1_dp, player2_p, player2_dp;
float player_p_x = 80;
float arena_half_size_x = 85, arena_half_size_y = 45;
float player_half_size_x = 2.5, player_half_size_y = 12;
float ball_p_x = 0, ball_p_y = 0, ball_dp_x = 100, ball_dp_y = 0;
float ball_half_size_x = 1, ball_half_size_y = 1;

// p is position, dp is speed, ddp is acceleration

internal void
simulate_player(float* p, float* dp, float ddp, float dt) {
	ddp -= *dp * 10.f;

	*p += *dp * dt + ddp * dt * dt * 0.5f;
	*dp += ddp * dt;

	if (*p + player_half_size_y > arena_half_size_y) {
		*p = arena_half_size_y - player_half_size_y;
		*dp = 0;
	}
	else if (player_half_size_y - *p > arena_half_size_y) {
		*p = player_half_size_y - arena_half_size_y;
		*dp = 0;
	}
}

internal bool						// Axis Aligned Bounding Box Collision test function
aabb_vs_aabb(float bpx, float bpy, float ppx, float ppy) {
	return (bpx + ball_half_size_x > ppx - player_half_size_x &&
		bpx - ball_half_size_x < ppx + player_half_size_x &&
		bpy + ball_half_size_y > ppy - player_half_size_y &&
		bpy - ball_half_size_y < ppy + player_half_size_y);
}

internal void
simulate_game(Input* input, float dt) {
	//render_background();
	clear_screen(0x00ffff);
	draw_rect(0, 0, 85, 45, 0xffaa33);

	float player1_ddp = 0.f;
	float player2_ddp = 0.f;

	if (is_down(BUTTON_UP)) player1_ddp += 2000;
	if (is_down(BUTTON_DOWN)) player1_ddp -= 2000;

	if (is_down(BUTTON_W)) player2_ddp += 2000;
	if (is_down(BUTTON_S)) player2_ddp -= 2000;

	simulate_player(&player1_p, &player1_dp, player1_ddp, dt);
	simulate_player(&player2_p, &player2_dp, player2_ddp, dt);


	// Simulate Ball
	{
		ball_p_x += ball_dp_x * dt;
		ball_p_y += ball_dp_y * dt;

		if (aabb_vs_aabb(ball_p_x, ball_p_y, player_p_x, player1_p)) {
			ball_p_x = player_p_x - player_half_size_x - ball_half_size_x;
			ball_dp_x *= -1;
			ball_dp_y = (ball_p_y - player1_p) * 2 + player1_dp * 0.6;
		}
		else if (aabb_vs_aabb(ball_p_x, ball_p_y, -player_p_x, player2_p)) {
			ball_p_x = -player_p_x + player_half_size_x + ball_half_size_x;
			ball_dp_x *= -1;
			ball_dp_y = (ball_p_y - player2_p) * 2 + player2_dp * 0.6;
		}

		if (ball_p_y + ball_half_size_y > arena_half_size_y) {
			ball_p_y = arena_half_size_y - ball_half_size_y;
			ball_dp_y *= -1;
		}
		else if (ball_p_y - ball_half_size_y < -arena_half_size_y) {
			ball_p_y = -arena_half_size_y + ball_half_size_y;
			ball_dp_y *= -1;
		}

		if (ball_p_x + ball_half_size_x > arena_half_size_x) {
			ball_p_x = 0;
			ball_p_y = 0;
			ball_dp_y = 0;
			ball_dp_x *= -1;
		}
		else if (ball_p_x - ball_half_size_x < -arena_half_size_x) {
			ball_p_x = 0;
			ball_p_y = 0;
			ball_dp_y = 0;
			ball_dp_x *= -1;
		}
	}

	// Rendering
	draw_rect(ball_p_x, ball_p_y, ball_half_size_x, ball_half_size_y, 0xffffff);				// Ball

	draw_rect(player_p_x, player1_p, player_half_size_x, player_half_size_y, 0xff0000);			// Players
	draw_rect(-player_p_x, player2_p, player_half_size_x, player_half_size_y, 0xff0000);
}