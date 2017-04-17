#include "View.h"

using namespace std;
using namespace sf;

ostream& operator<<(ostream& os, const Game& g)
{
	for (int i = 0; i <= BOARD_HEIGHT; ++i)
	{
		os << '+';
		for (int j = 0; j < BOARD_WIDTH; ++j)
		{
			os << "-+";
		}
		os << endl;
		if (i == BOARD_HEIGHT) break;
		os << "|";
		for (int j = 0; j < BOARD_WIDTH; ++j)
		{
			os << puyo_to_char(g.get(i, j)) << '|';
		}
		os << endl;
	}
	return os;
}

void ASCII_View::draw(const Game& g)
{
	cout << g;
}


static char puyo_to_char(Puyo puyo) {
	switch (puyo) {
		case BLUE: return 'B';
		case GREEN: return 'G';
		case YELLOW: return 'Y';
		case RED: return 'R';
		case OJAMA: return 'O';
	}
	return ' ';
}

static Color puyo_to_color(Puyo puyo) {
	switch (puyo) {
		case BLUE: return Color::Blue;
		case GREEN: return Color::Green;
		case YELLOW: return Color::Yellow;
		case RED: return Color::Red;
		case OJAMA: return Color::White;
	}
	return Graphical_View::BACKGROUND;
}
/*
void graphical_view::draw(const tetris& t)
{
	Event event;
	window.pollEvent(event);
	window.clear(Color(20, 45, 7));
	const int WIDTH = 350;
	const int w = WIDTH / BOARD_WIDTH;
	const int DELTA_X = 75;
	const int DELTA_Y = 50;
	RectangleShape square(Vector2f(w, w));
	for (int y = 0; y < BOARD_HEIGHT; ++y)
	{
		for (int x = 0; x < BOARD_WIDTH; ++x)
		{
			square.setPosition(DELTA_X + x * w, DELTA_Y + y * w);
			square.setFillColor(kind_to_color(t.get(y, x)));
			window.draw(square);
		}
	}
	RectangleShape next_piece_rectangle(Vector2f(w * 4, w * 4));
	next_piece_rectangle.setPosition(DELTA_X + w * BOARD_WIDTH + 10, DELTA_Y);
	next_piece_rectangle.setFillColor(BACKGROUND);
	window.draw(next_piece_rectangle);
	const piece& next_piece = t.get_next_piece();
	Color c = kind_to_color(next_piece.get_kind());
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			int v = next_piece.get_shape_value(y, x);
			if (v == 0) continue;
			square.setPosition(DELTA_X + w * BOARD_WIDTH + 10 + x * w, DELTA_Y + y * w);
			square.setFillColor(c);
			window.draw(square);
		}
	}
	Text txt;
	txt.setFont(font);
	txt.setColor(Color::White);
	txt.setStyle(Text::Bold);

	txt.setPosition(DELTA_X + w * BOARD_WIDTH + 20, DELTA_Y + 6 * w);
	txt.setString("Score");
	txt.setCharacterSize(32);
	window.draw(txt);

	txt.setPosition(DELTA_X + w * BOARD_WIDTH + 20, DELTA_Y + 7.5 * w);
	txt.setString(to_string(t.get_score()));
	txt.setCharacterSize(24);
	window.draw(txt);

	txt.setPosition(DELTA_X + w * BOARD_WIDTH + 20, DELTA_Y + 10 * w);
	txt.setString("Level");
	txt.setCharacterSize(32);
	window.draw(txt);

	txt.setPosition(DELTA_X + w * BOARD_WIDTH + 20, DELTA_Y + 11.5 * w);
	txt.setString(to_string(t.get_level()));
	txt.setCharacterSize(24);
	window.draw(txt);

	txt.setPosition(DELTA_X + w * BOARD_WIDTH + 20, DELTA_Y + 14 * w);
	txt.setString("Lines");
	txt.setCharacterSize(32);
	window.draw(txt);

	txt.setPosition(DELTA_X + w * BOARD_WIDTH + 20, DELTA_Y + 15.5 * w);
	txt.setString(to_string(t.get_lines()));
	txt.setCharacterSize(24);
	window.draw(txt);

	window.display();
}
*/
const Color Graphical_View::BACKGROUND = Color::Black;

Graphical_View::Graphical_View() : window(VideoMode(600, 800), "Gropuyo")
{
	font.loadFromFile("Font/Monaco-Linux.ttf");
}
