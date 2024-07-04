struct Button_State {				// The state of the Button
	bool is_down;
	bool changed;
};

enum {
	BUTTON_UP,
	BUTTON_DOWN,					// Enumeratring the moves
	BUTTON_RIGHT,
	BUTTON_LEFT,					// Remember, these should be commas, not semicolons
	BUTTON_W,
	BUTTON_S,
	BUTTON_ENTER,
	BUTTON_ESC,

	BUTTON_COUNT,					// Count of number of moves, must be the last item
};

struct Input {						// Struct for Input
	Button_State buttons[BUTTON_COUNT];
};