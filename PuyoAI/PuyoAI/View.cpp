#include "View.h"

using namespace std;
using namespace sf;

static char puyo_to_char(int puyo) {
	switch (puyo) {
	case BLUE: return 'B'; break;
	case GREEN: return 'G'; break;
	case YELLOW: return 'Y'; break;
	case RED: return 'R'; break;
	case OJAMA: return 'O'; break;
	}
	return ' ';
}

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

static Color puyo_to_color(int puyo) {
	switch (puyo) {
	case BLUE: return Color::Blue; break;
	case GREEN: return Color::Green; break;
	case YELLOW: return Color::Yellow; break;
	case RED: return Color::Red; break;
	case OJAMA: return Color::White; break;
	}
	return Graphical_View::BACKGROUND;
}

void Graphical_View::draw(const Game& g)
{
	Event event;
	window.pollEvent(event);
	window.clear(Color(20, 45, 7));
	const int WIDTH = 350;
	const int w = WIDTH / BOARD_WIDTH;
	const int DELTA_X = 75;
	const int DELTA_Y = 50;
	RectangleShape square(Vector2f(w, w));
	for (int x = 0; x < BOARD_HEIGHT; ++x)
	{
		for (int y = 0; y < BOARD_WIDTH; ++y)
		{
			square.setPosition(DELTA_X + x * w, DELTA_Y + y * w);
			square.setFillColor(puyo_to_color(g.get(x, y)));
			window.draw(square);
		}
	}
	RectangleShape next_couple_rectangle(Vector2f(w * 4, w * 4));
	next_couple_rectangle.setPosition(DELTA_X + w * BOARD_WIDTH + 10, DELTA_Y);
	next_couple_rectangle.setFillColor(BACKGROUND);
	window.draw(next_couple_rectangle);
	Couple& next_couple = g.get_next_couple();
	Color c0 = puyo_to_color(next_couple.get_puyos()[0]);
	Color c1 = puyo_to_color(next_couple.get_puyos()[1]);
	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			int v = next_couple.get_shape_value(y, x);
			if (v == 0) continue;
			if (v == 1) {
				square.setPosition(DELTA_X + w * BOARD_WIDTH + 10 + x * w, DELTA_Y + y * w);
				square.setFillColor(c1);
				window.draw(square);
			}
			if (v == 2) {
				square.setPosition(DELTA_X + w * BOARD_WIDTH + 10 + x * w, DELTA_Y + y * w);
				square.setFillColor(c0);
				window.draw(square);
			}
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
	txt.setString(to_string(g.get_score()));
	txt.setCharacterSize(24);
	window.draw(txt);

	txt.setPosition(DELTA_X + w * BOARD_WIDTH + 20, DELTA_Y + 10 * w);
	txt.setString("Hits");
	txt.setCharacterSize(32);
	window.draw(txt);

	txt.setPosition(DELTA_X + w * BOARD_WIDTH + 20, DELTA_Y + 11.5 * w);
	txt.setString(to_string(g.get_hits()));
	txt.setCharacterSize(24);
	window.draw(txt);

	txt.setPosition(DELTA_X + w * BOARD_WIDTH + 20, DELTA_Y + 14 * w);
	txt.setString("=^._.^=");
	txt.setCharacterSize(32);
	window.draw(txt);

	window.display();
}

const Color Graphical_View::BACKGROUND = Color::Black;

Graphical_View::Graphical_View() : window(VideoMode(600, 800), "Gropuyo")
{
	font.loadFromFile("Font/Monaco-Linux.ttf");
}
