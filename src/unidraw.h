#include <iostream>
#include <cmath>

#ifndef _XOPEN_SOURCE_EXTENDED
#define _XOPEN_SOURCE_EXTENDED // pour utilisé les fonction wide character et cchar_t
#endif

extern "C"{
#include <ncursesw/curses.h>
}

#include <cwchar>
#include <cstring>
#include <string>
#include <cstdlib>
#include <list>

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS VECTOR2

template <typename T>
class Vector2 {

public:

	T x;
	T y;

	Vector2();
	
	Vector2(T x, T y);
	
	template <typename U>
	explicit Vector2(const Vector2<U>& vector);
	
	~Vector2();

	Vector2<int> rounded() const;

	Vector2<T> normal() const;

	float length() const;

	float length_squared() const;

	void normalize();

	static Vector2<T> zero;
	static Vector2<T> one;
	static Vector2<T> up;
	static Vector2<T> down;
	static Vector2<T> left;
	static Vector2<T> right;

	static float dot(const Vector2<T>& left, const Vector2<T>& right);
	static float distance(const Vector2<T>& left, const Vector2<T>& right);
	static float distance_squared(const Vector2<T>& left, const Vector2<T>& right);

	static Vector2<T> min(const Vector2<T>& left, const Vector2<T>& right);
	static Vector2<T> max(const Vector2<T>& left, const Vector2<T>& right);
	static Vector2<T> normalize(const Vector2<T>& vector);

	/* renvoie la reflexion du vecteur vector par rappor a la normal normal (normal doit etre normalisé) */
	static Vector2<T> reflect(const Vector2<T>& vector, const Vector2<T>& normal);
};

////////////////////////////////////////////////// TYPES COMMUNS

typedef Vector2<int> 			Vector2i;
typedef Vector2<unsigned int> 	Vector2u;
typedef Vector2<float> 			Vector2f;

////////////////////////////////////////////////// OPERATEURS DECLARATION

template <typename T>
Vector2<T> operator-(const Vector2<T>& right);

template <typename T>
Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right);

template <typename T>
Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right);

template <typename T>
Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right);

template <typename T>
Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right);

template <typename T>
Vector2<T> operator*(const Vector2<T>& left, T right);

template <typename T>
Vector2<T> operator*(T left, const Vector2<T>& right);

template <typename T>
Vector2<T>& operator*=(Vector2<T>& left, T right);

template <typename T>
Vector2<T> operator/(const Vector2<T>& left, T right);

template <typename T>
Vector2<T>& operator/=(Vector2<T>& left, T right);

template <typename T>
bool operator==(const Vector2<T>& left, const Vector2<T>& right);

template <typename T>
bool operator!=(const Vector2<T>& left, const Vector2<T>& right);

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& vector);

template <typename T>
std::istream& operator>>(std::istream& is, Vector2<T>& vector);

////////////////////////////////////////////////// CONSTRUCTEURS
 
template <typename T>
Vector2<T>::Vector2() : x(), y() {}

template <typename T>
Vector2<T>::Vector2(T x, T y) : x(x), y(y) {}

template <typename T>
template <typename U>
Vector2<T>::Vector2(const Vector2<U> &vector) : x(vector.x), y(vector.y) {}

template <typename T>
Vector2<T>::~Vector2() {}

////////////////////////////////////////////////// METHODES

template <typename T>
Vector2<T> Vector2<T>::normal() const{
	return Vector2<T>(-y, x);
}

template <typename T>
float Vector2<T>::length() const{
	return powf(length_squared(), 0.5);
}

template <typename T>
float Vector2<T>::length_squared() const{
	return (x * x) + (y * y);
}

template <typename T>
void Vector2<T>::normalize(){
	float length = this->length();
	x /= length;
	y /= length;
}

template <typename T>
Vector2<int> Vector2<T>::rounded() const{
	return Vector2<int>(round(x), round(y));
}

///////////////////////////////////////////////////// METHODES STATIQUES

template <typename T>
float Vector2<T>::dot(const Vector2<T>& left, const Vector2<T>& right){
	return (left.x * right.x) + (left.y * right.y); 
}

template <typename T>
float Vector2<T>::distance(const Vector2<T>& left, const Vector2<T>& right){
	return powf(Vector2<T>::distance_squared(left, right), 0.5);
}

template <typename T>
float Vector2<T>::distance_squared(const Vector2<T>& left, const Vector2<T>& right){
	Vector2<T> dv = left - right;
	return (dv.x * dv.x) + (dv.y * dv.y);
}

template <typename T>
Vector2<T> Vector2<T>::min(const Vector2<T>& left, const Vector2<T>& right){
	return left.length_squared() < right.length_squared() ? Vector2<T>(left) : Vector2<T>(right);
}

template <typename T>
Vector2<T> Vector2<T>::max(const Vector2<T>& left, const Vector2<T>& right){
	return left.length_squared() > right.length_squared() ? Vector2<T>(left) : Vector2<T>(right);
}

template <typename T>
Vector2<T> Vector2<T>::normalize(const Vector2<T>& vector){
	return vector / vector.length();
}

template <typename T>
Vector2<T> Vector2<T>::reflect(const Vector2<T>& vector, const Vector2<T>& normal){
	return vector - (2 * Vector2<T>::dot(vector, normal) * normal);
}

///////////////////////////////////////////////////// VARIABLE STATIQUES

template <typename T>
Vector2<T> Vector2<T>::zero(0, 0);

template <typename T>
Vector2<T> Vector2<T>::one(1, 1);

template <typename T>
Vector2<T> Vector2<T>::up(0, -1);

template <typename T>
Vector2<T> Vector2<T>::down(0, 1);

template <typename T>
Vector2<T> Vector2<T>::left(-1, 0);

template <typename T>
Vector2<T> Vector2<T>::right(1, 0);

////////////////////////////////////////////////// OPERATEURS DEFINITION

template <typename T>
Vector2<T> operator-(const Vector2<T>& right){
	return Vector2<T>(-right.x, -right.y);
}

template <typename T>
Vector2<T>& operator+=(Vector2<T>& left, const Vector2<T>& right){
	left.x += right.x;
	left.y += right.y;
	return left;
}

template <typename T>
Vector2<T>& operator-=(Vector2<T>& left, const Vector2<T>& right){
	left += -right;
	return left;
}

template <typename T>
Vector2<T> operator+(const Vector2<T>& left, const Vector2<T>& right){
	return Vector2<T>(left.x + right.x, left.y + right.y);
}

template <typename T>
Vector2<T> operator-(const Vector2<T>& left, const Vector2<T>& right){
	return (left + -right);
}

template <typename T>
Vector2<T> operator*(const Vector2<T>& left, T right){
	return Vector2<T>(left.x * right, left.y * right);
}

template <typename T>
Vector2<T> operator*(T left, const Vector2<T>& right){
	return (right * left);
}

template <typename T>
Vector2<T>& operator*=(Vector2<T>& left, T right){
	left.x *= right;
	left.y *= right;
	return left;
}

template <typename T>
Vector2<T> operator/(const Vector2<T>& left, T right){
	return Vector2<T>(left.x / right, left.y / right);
}

template <typename T>
Vector2<T>& operator/=(Vector2<T>& left, T right){
	left.x /= right;
	left.y /= right;
	return left;
}

template <typename T>
bool operator==(const Vector2<T>& left, const Vector2<T>& right){
	return left.x == right.x && left.y == right.y;
}

template <typename T>
bool operator!=(const Vector2<T>& left, const Vector2<T>& right){
	return !(left == right);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Vector2<T>& vector){
	os << "{" << vector.x << ", " << vector.y << "}";
	return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Vector2<T>& vector){
  is >> vector.x >> vector.y;
  return is;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS RECT

template <typename T>
class Rect {

public:

	T x;
	T y;
	T width;
	T height;

	Rect();
	
	Rect(T x, T y, T width, T height);
	
	Rect(const Vector2<T>& position, const Vector2<T>& size);

   	template <typename U>
	explicit Rect(const Rect<U>& rectangle);

	Vector2<T> center();

	Vector2<T> get_size();
	Vector2<T> get_position();
	
	void set_size(const Vector2<T>& size);
	void set_position(const Vector2<T>& position);

	bool contains(T x, T y)  const;

	bool contains(const Vector2<T>& point) const;

	bool intersects(const Rect<T>& rect) const;

	bool intersects(const Rect<T>& rect, Rect<T>& intersection) const;
};

////////////////////////////////////////////////// TYPES COMMUNS

typedef Rect<int> IntRect;
typedef Rect<float> FloatRect;

////////////////////////////////////////////////// OPERATEURS DECLARATION

template <typename T>
bool operator==(const Rect<T>& left, const Rect<T>& right);

template <typename T>
bool operator!=(const Rect<T>& left, const Rect<T>& right);

template <typename T>
std::ostream& operator<<(std::ostream& os, const Rect<T>& rect);

template <typename T>
std::istream& operator>>(std::istream& is, Rect<T>& rect);

////////////////////////////////////////////////// CONSTRUCTEURS
 
template <typename T>
Rect<T>::Rect() : x(), y(), width(), height() {}

template <typename T>
Rect<T>::Rect(T x, T y, T width, T height) : x(x), y(y), width(width), height(height) {}

template <typename T>
Rect<T>::Rect(const Vector2<T>& position, const Vector2<T>& size) : x(position.x), y(position.y), width(size.x), height(size.y) {}

template <typename T>
template <typename U>
Rect<T>::Rect(const Rect<U>& rectangle) : x(rectangle.x), y(rectangle.y), width(rectangle.width), height(rectangle.height) {}

////////////////////////////////////////////////// METHODES

template <typename T>
Vector2<T> Rect<T>::center(){
	return Vector2<T>(x + (width / 2), y + (height / 2));
}

template <typename T>
Vector2<T> Rect<T>::get_size(){
	return Vector2<T>(width, height);
}

template <typename T>
Vector2<T> Rect<T>::get_position(){
	return Vector2<T>(x, y);
}

template <typename T>
void Rect<T>::set_size(const Vector2<T>& size){
	width = size.x;
	height = size.y;
}

template <typename T>
void Rect<T>::set_position(const Vector2<T>& position){
	x = position.x;
	y = position.y;
}

template <typename T>
bool Rect<T>::contains(T x, T y)  const {
	return x >= this->x && x <= width && y >= this->y && y <= height;
}

template <typename T>
bool Rect<T>::contains(const Vector2<T>& point) const {
	return contains(point.x, point.y);
}

template <typename T>
bool Rect<T>::intersects(const Rect<T>& rect) const {
	return !(rect.x >= x + width || rect.x + rect.width <= x ||
		rect.y >= y + height || rect.y + rect.height <= y);
}

template <typename T>
bool Rect<T>::intersects(const Rect<T>& rect, Rect<T>& intersection) const {
	if (intersects(rect)) {

		int xmin = x > rect.x ? x : rect.x; //std::max(x, rect.x);
		int ymin = y > rect.y ? y : rect.y; //std::max(y, rect.y);
		int xmax = x + width < rect.x + rect.width ? x + width : rect.x + rect.width; //std::min(x + width, rect.x + rect.width);
		int ymax = y + height < rect.y + rect.height ? y + height : rect.y + rect.height; //std::min(y + height, rect.y + rect.height);

		intersection = Rect(xmin, ymin, xmax - xmin, ymax - ymin);
		return true;
	}
	return false;
}

////////////////////////////////////////////////// OPERATEURS DEFINITION

template <typename T>
bool operator==(const Rect<T>& left, const Rect<T>& right){
	return left.x == right.x && left.y == right.y && left.width == right.width && left.height == right.height;
}

template <typename T>
bool operator!=(const Rect<T>& left, const Rect<T>& right){
	return !(left == right);
}

template <typename T>
std::ostream& operator<<(std::ostream& os, const Rect<T>& rect){
	os << "{" << rect.x << ", " << rect.y << ", " << rect.width << ", " << rect.height << "}";
	return os;
}

template <typename T>
std::istream& operator>>(std::istream& is, Rect<T>& rect){
  is >> rect.x >> rect.y >> rect.width >> rect.height;
  return is;
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS ATTR

class Attr
{
private:
	chtype m_attribute;

public:

	Attr();
	Attr(chtype);
	operator chtype() const;

	static const Attr Normal;
	static const Attr Standout;
	static const Attr Underline;
	static const Attr Reverse;
	static const Attr Blink;
	static const Attr HalfBright;
	static const Attr Bright;
	static const Attr Protected;
	static const Attr Invisible;
	static const Attr AltCharset;
	static const Attr Italic;
};
 
////////////////////////////////////////////////// CONSTRUCTEURS

Attr::Attr() : m_attribute(A_NORMAL) {}

Attr::Attr(chtype c) : m_attribute(c & A_ATTRIBUTES) {}

////////////////////////////////////////////////// METHODES

Attr::operator chtype() const {
	return m_attribute;
}

////////////////////////////////////////////////// VARIABLE STATIQUES

const Attr Attr::Normal(A_NORMAL);
const Attr Attr::Standout(A_STANDOUT);
const Attr Attr::Underline(A_UNDERLINE);
const Attr Attr::Reverse(A_REVERSE);
const Attr Attr::Blink(A_BLINK);
const Attr Attr::HalfBright(A_DIM);
const Attr Attr::Bright(A_BOLD);
const Attr Attr::Protected(A_PROTECT);
const Attr Attr::Invisible(A_INVIS);
const Attr Attr::AltCharset(A_ALTCHARSET);
const Attr Attr::Italic(A_ITALIC);
  
//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS COLORPAIR

enum ColorUnit{
	DEFAULT = -1, //La couleur par default du terminal a l'initialisation de ncurses
	
	BLACK = COLOR_BLACK,
	WHITE = COLOR_WHITE,

	RED = COLOR_RED,
	GREEN = COLOR_GREEN,
	BLUE = COLOR_BLUE,
		
	CYAN = COLOR_CYAN,
	MAGENTA = COLOR_MAGENTA,
	YELLOW = COLOR_YELLOW
};

class ColorPair
{
public:
	ColorUnit front;
	ColorUnit back;

	ColorPair();
	ColorPair(chtype);
	ColorPair(ColorUnit front_back);
	ColorPair(ColorUnit front, ColorUnit back);

/* Renvoie le numéro correspondant à la paire de couleur composée de front et back */
	int pair_num() const;

/* Convertie en chtype la paire de couleur composée de front et back */
	operator chtype() const;

	static const ColorPair Default;
	static const ColorPair WhiteBlack;
	static const ColorPair WhiteRed;
	static const ColorPair WhiteGreen;
	static const ColorPair WhiteBlue;
	static const ColorPair WhiteMagenta;
	static const ColorPair WhiteYellow;
	static const ColorPair WhiteCyan;

	static const ColorPair White;
	static const ColorPair Black;
	static const ColorPair Red;
	static const ColorPair Green;
	static const ColorPair Blue;
	static const ColorPair Magenta;
	static const ColorPair Yellow;
	static const ColorPair Cyan;
};

////////////////////////////////////////////////// FONCTIONS DECLARATION

/* Initialise toutes les pairs de couleurs possible en fonction du terminal */
void init_color_pairs();

/* Change les valeurs de rouge vert et bleu associée à une couleur */
void color_rgb(ColorUnit color, short r, short g, short b);

////////////////////////////////////////////////// CONSTRUCTEURS
 
ColorPair::ColorPair() : front(DEFAULT), back(DEFAULT) {}

ColorPair::ColorPair(chtype c){

	chtype color = c & A_COLOR;
	short f = 0, b = 0;

	pair_content(PAIR_NUMBER(color), &f, &b);

	front = (ColorUnit)f;
	back = (ColorUnit)b;
}

ColorPair::ColorPair(ColorUnit front_back){
	front = front_back;
	back = front_back;
}

ColorPair::ColorPair(ColorUnit front, ColorUnit back) {
	this->front = front;
	this->back = back;
}

////////////////////////////////////////////////// METHODES

int ColorPair::pair_num() const{
	return (front + 1) * COLORS + (back + 1) + 1;
}

ColorPair::operator chtype() const{
	
	return COLOR_PAIR(pair_num());
}

////////////////////////////////////////////////// VARIABLE STATIQUES

const ColorPair ColorPair::Default(DEFAULT, DEFAULT);
const ColorPair ColorPair::WhiteBlack(WHITE, BLACK);
const ColorPair ColorPair::WhiteRed(WHITE, RED);
const ColorPair ColorPair::WhiteGreen(WHITE, GREEN);
const ColorPair ColorPair::WhiteBlue(WHITE, BLUE);
const ColorPair ColorPair::WhiteMagenta(WHITE, MAGENTA);
const ColorPair ColorPair::WhiteYellow(WHITE, YELLOW);
const ColorPair ColorPair::WhiteCyan(WHITE, CYAN);

const ColorPair ColorPair::White(WHITE, DEFAULT);
const ColorPair ColorPair::Black(BLACK, DEFAULT);
const ColorPair ColorPair::Red(RED, DEFAULT);
const ColorPair ColorPair::Green(GREEN, DEFAULT);
const ColorPair ColorPair::Blue(BLUE, DEFAULT);
const ColorPair ColorPair::Magenta(MAGENTA, DEFAULT);
const ColorPair ColorPair::Yellow(YELLOW, DEFAULT);
const ColorPair ColorPair::Cyan(CYAN, DEFAULT);

////////////////////////////////////////////////// FONCTIONS DEFINITION

void init_color_pairs(){

	if (has_colors()) {

		start_color();

		use_default_colors(); // -> COLOR_PAIR(0) = DefaultColor (est un extensino de ncurses)

		for (int j = 0; j < COLORS; ++j)
		{
			for (int i = 0; i < COLORS; ++i)
			{
				//init_pair(numero, front, back) (-1 correspond à la couleur par default du terminal)
				init_pair(j * COLORS + i + 1, j - 1, i - 1);
			}
		}
	}
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS CELL

class Cell
{
public:
	wint_t character;
	ColorPair color;
	Attr attr;

	Cell();
	Cell(cchar_t);
	Cell(wint_t, ColorPair color = ColorPair::Default, Attr attr = Attr::Normal);
	operator cchar_t() const; //verifier avec valgrind pas de problème d'initialisation de variable local
};

///////////////////////////////////////////////// CONSTRUCTEURS
 
Cell::Cell() : character(L' '), color(), attr() {}

Cell::Cell(cchar_t c) : character(c.chars[0]), color(c.attr), attr(c.attr) {}

Cell::Cell(wint_t character, ColorPair color, Attr attr) : character(character), color(color), attr(attr) {} 

///////////////////////////////////////////////// METHODES

//la conversion en cchar_t pourrais etre meilleur je pense qu'il y a des characters unicode qui ne sont pas supporté
//mais pour l'instant ca marche et c'est plus simple comme ça, un modification sera facile si besoin. 
Cell::operator cchar_t() const{

	cchar_t c;// = { 0, {0, 0, 0, 0, 0}};
	memset(&c, 0, sizeof(c));

	c.attr = attr | color;

	c.chars[0] = character;
	c.chars[1] = L'\0';

	return c;
}

/* definition de quelques characters unicodes interresants */

#define U_LIGHT_V  			L'\u2502'
#define U_LIGHT_H  			L'\u2500'
#define U_LIGHT_UL 			L'\u250C'
#define U_LIGHT_UR 			L'\u2510'
#define U_LIGHT_DL 			L'\u2514'
#define U_LIGHT_DR 			L'\u2518'

#define U_LIGHT_ARC_UL 		L'\u256D'
#define U_LIGHT_ARC_UR 		L'\u256E'
#define U_LIGHT_ARC_DL 		L'\u2570'
#define U_LIGHT_ARC_DR 		L'\u256F'

#define U_HEAVY_V  			L'\u2503'
#define U_HEAVY_H  			L'\u2501'
#define U_HEAVY_UL 			L'\u250F'
#define U_HEAVY_UR 			L'\u2513'
#define U_HEAVY_DL 			L'\u2517'
#define U_HEAVY_DR 			L'\u251B'

#define U_DOUBLE_V  		L'\u2551'
#define U_DOUBLE_H  		L'\u2550'
#define U_DOUBLE_UL 		L'\u2554'
#define U_DOUBLE_UR 		L'\u2557'
#define U_DOUBLE_DL 		L'\u255A'
#define U_DOUBLE_DR 		L'\u255D'

#define U_BLOCK_FULL 		L'\u2588'
#define U_BLOCK_U 			L'\u2580'
#define U_BLOCK_D 			L'\u2584'

#define U_BLOCK_LIGHT 		L'\u2591'
#define U_BLOCK_MEDIUM 		L'\u2592'
#define U_BLOCK_DARK 		L'\u2593'

#define U_DIAMOND 			L'\u25C6'

#define U_POINT 			L'\u25CF'

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS WINDOW

/* Cette class permet d'englober la structure WINDOW* definie dans ncurses. */ 

class Window {

protected:

	WINDOW* m_win;
	Window(WINDOW* win);

public:

	enum BorderType {
		Empty,
		Light,
		LightArc,
		Heavy,
		Double,
		BlockFull,
		BlockLight,
		BlockMedium,
		BlockDark,
		Dash,
		Diamond,
		Point
	};

	Window();
	virtual ~Window();

	operator WINDOW*();

/* return the dimensions of the Window (col, row) (stdscr ne peut pas  être resize et rien ne peut etre plus grand que stdscr a par les pads) */
	Vector2i get_dimension() const;
	//void set_dimension(const Vector2i& dim);

/* return/set the cursor position relative to up-left corner of the Window (col, row) */
	Vector2i get_curs_pos() const;
	void set_curs_pos(const Vector2i& coord);

/* return/set a Window's cell relative to up-left corner of the window (col, row) */
	Cell get_cell(const Vector2i& coord) const;
	void set_cell(const Vector2i& coord, const Cell& cell);
	void set_cell(const Vector2i& coord, wint_t wchar, ColorPair color = ColorPair::Default, Attr attr = Attr::Normal);

/* return/set the Window's attribute when writing */
	Attr get_attr() const; //wattr_set
	void set_attr(Attr); //wattr_get

/* return/set the Window's color pair when writing */
	ColorPair get_color() const;
	void set_color(ColorPair);

/* set on/off a Window's attribute and/or Color can be or'd with | */
	void set_on(chtype attr_color);
	void set_off(chtype attr_color);

/* return the data of the Window in one wide string */
	std::wstring to_wstring() const;

/* draw a border around the window */
	void set_border(BorderType type, ColorPair c = ColorPair::Default, Attr  a = Attr::Normal); //verifier pas de problème avec assignation par default
	void set_border(Cell left, Cell right, Cell up, Cell down, Cell upLeft, Cell upRight, Cell downLeft, Cell downRight);

/* fill the windows background whith a specific Cell, ColorPair and/or Attribute */
	void fill(const Cell&);
	void fill(ColorPair color, Attr attr = Attr::Normal); 

/* return/set the windows background whith a specific Cell, ColorPair and/or Attribute */
	Cell get_background() const;
	void set_background(const Cell&);
	void set_background(ColorPair color, Attr attr = Attr::Normal); 

/* copy the content of another Window */
	//void copy(const Window&, const IntRect&, const Vector2i&, bool convert_attr = true);// copywin;

/* clear the Window */
	void clear();
	void clear(const IntRect& zone);

/* display the window to the virtual screen (use Term::update to display the virtual screen) */
	virtual void display(); //pnoutrefresh;

/* display the window directly to the realscreen without optimisation */
	void refresh();
};

///////////////////////////////////////////////// CONSTRUCTEURS
 
Window::Window() : m_win() {}

Window::Window(WINDOW* win) : m_win(win) {}

Window::~Window() {
	delwin(m_win);
}

///////////////////////////////////////////////// METHODES

Window::operator WINDOW*(){
	return m_win;
}

Vector2i Window::get_dimension() const{
	int x = 0, y = 0;
	getmaxyx(m_win, y, x);
	return Vector2i(x, y);
}

Vector2i Window::get_curs_pos() const{
	int x = 0, y = 0;
	getyx(m_win, y, x);
	return Vector2i(x, y);
}

void Window::set_curs_pos(const Vector2i& pos){
	wmove(m_win, pos.y, pos.x);
}

Cell Window::get_cell(const Vector2i& coord) const{
	cchar_t c;
	mvwin_wch(m_win, coord.y, coord.x, &c);
	return Cell(c);
}

void Window::set_cell(const Vector2i& coord, const Cell& cell){

	cchar_t c = cell;

	if(cell.color == ColorPair::Default)
		c.attr |= get_color(); //affiche dans la couleur courante du terminal

	mvwadd_wchnstr(m_win, coord.y, coord.x, &c, 1);
}

void Window::set_cell(const Vector2i& coord, wint_t wchar, ColorPair color, Attr attr){
	set_cell(coord, Cell(wchar, color, attr));
}

Attr Window::get_attr() const{
	attr_t at;
	short pair; 
	
	wattr_get(m_win, &at, &pair, NULL);

	return Attr(at);
}

void Window::set_attr(Attr attr){ 
	attr_t at = attr;
	short pair = get_color().pair_num();
	
	wattr_set(m_win, at, pair, NULL);
}

ColorPair Window::get_color() const{
	attr_t at;
	short pair; 
	
	wattr_get(m_win, &at, &pair, NULL);

	return COLOR_PAIR(pair);
}

void Window::set_color(ColorPair color){

	wcolor_set(m_win, color.pair_num(), NULL);
}

void Window::set_on(chtype attr_color){
	wattron(m_win, attr_color);
}

void Window::set_off(chtype attr_color){
	wattroff(m_win, attr_color);
}

std::wstring Window::to_wstring() const{
	std::wstring data;
	wchar_t* wstr = new wchar_t[get_dimension().x];

	for(int i = 0 ; i < get_dimension().y ; i++){

		mvwinwstr(m_win, 0, 0, wstr);
		data += std::wstring(wstr); 
	}
	return data;
}

void Window::set_border(Cell left, Cell right, Cell up, Cell down, Cell upLeft, Cell upRight, Cell downLeft, Cell downRight){
	cchar_t l = left;
	cchar_t r = right;
	cchar_t u = up;
	cchar_t d = down;
	cchar_t ul = upLeft;
	cchar_t ur = upRight;
	cchar_t dl = downLeft;
	cchar_t dr = downRight;

	wborder_set(m_win, &l, &r, &u, &d, &ul, &ur, &dl, &dr);
}

void Window::set_border(BorderType type, ColorPair color, Attr a){

	ColorPair c = color == ColorPair::Default ? get_color() : color;
 
	switch (type)
	{
		case Empty:
		set_border(Cell(' ', c, a), Cell(' ', c, a), Cell(' ', c, a), Cell(' ', c, a), Cell(' ', c, a), Cell(' ', c, a), Cell(' ', c, a), Cell(' ', c, a));
		break;
		case Light:
		set_border(Cell(U_LIGHT_V, c, a), Cell(U_LIGHT_V, c, a), Cell(U_LIGHT_H, c, a), Cell(U_LIGHT_H, c, a), Cell(U_LIGHT_UL, c, a), Cell(U_LIGHT_UR, c, a), Cell(U_LIGHT_DL, c, a), Cell(U_LIGHT_DR, c, a));
		break;
		case LightArc:
		set_border(Cell(U_LIGHT_V, c, a), Cell(U_LIGHT_V, c, a), Cell(U_LIGHT_H, c, a), Cell(U_LIGHT_H, c, a), Cell(U_LIGHT_ARC_UL, c, a), Cell(U_LIGHT_ARC_UR, c, a), Cell(U_LIGHT_ARC_DL, c, a), Cell(U_LIGHT_ARC_DR, c, a));
		break;
		case Heavy:
		set_border(Cell(U_HEAVY_V, c, a), Cell(U_HEAVY_V, c, a), Cell(U_HEAVY_H, c, a), Cell(U_HEAVY_H, c, a), Cell(U_HEAVY_UL, c, a), Cell(U_HEAVY_UR, c, a), Cell(U_HEAVY_DL, c, a), Cell(U_HEAVY_DR, c, a));
		break;
		case Double:
		set_border(Cell(U_DOUBLE_V, c, a), Cell(U_DOUBLE_V, c, a), Cell(U_DOUBLE_H, c, a), Cell(U_DOUBLE_H, c, a), Cell(U_DOUBLE_UL, c, a), Cell(U_DOUBLE_UR, c, a), Cell(U_DOUBLE_DL, c, a), Cell(U_DOUBLE_DR, c, a));
		break;
		case BlockFull:
		set_border(Cell(U_BLOCK_FULL, c, a), Cell(U_BLOCK_FULL, c, a), Cell(U_BLOCK_U, c, a), Cell(U_BLOCK_D, c, a), Cell(U_BLOCK_FULL, c, a), Cell(U_BLOCK_FULL, c, a), Cell(U_BLOCK_FULL, c, a), Cell(U_BLOCK_FULL, c, a));
		break;
		case BlockLight:
		set_border(Cell(U_BLOCK_LIGHT, c, a), Cell(U_BLOCK_LIGHT, c, a), Cell(U_BLOCK_LIGHT, c, a), Cell(U_BLOCK_LIGHT, c, a), Cell(U_BLOCK_LIGHT, c, a), Cell(U_BLOCK_LIGHT, c, a), Cell(U_BLOCK_LIGHT, c, a), Cell(U_BLOCK_LIGHT, c, a));
		break;
		case BlockMedium:
		set_border(Cell(U_BLOCK_MEDIUM, c, a), Cell(U_BLOCK_MEDIUM, c, a), Cell(U_BLOCK_MEDIUM, c, a), Cell(U_BLOCK_MEDIUM, c, a), Cell(U_BLOCK_MEDIUM, c, a), Cell(U_BLOCK_MEDIUM, c, a), Cell(U_BLOCK_MEDIUM, c, a), Cell(U_BLOCK_MEDIUM, c, a));
		break;
		case BlockDark:
		set_border(Cell(U_BLOCK_DARK, c, a), Cell(U_BLOCK_DARK, c, a), Cell(U_BLOCK_DARK, c, a), Cell(U_BLOCK_DARK, c, a), Cell(U_BLOCK_DARK, c, a), Cell(U_BLOCK_DARK, c, a), Cell(U_BLOCK_DARK, c, a), Cell(U_BLOCK_DARK, c, a));
		break;
		case Dash: 
		set_border(Cell('|', c, a), Cell('|', c, a), Cell('-', c, a), Cell('-', c, a), Cell('+', c, a), Cell('+', c, a), Cell('+', c, a), Cell('+', c, a));
		break;
		case Diamond:
		set_border(Cell(U_DIAMOND, c, a), Cell(U_DIAMOND, c, a), Cell(U_DIAMOND, c, a), Cell(U_DIAMOND, c, a), Cell(U_DIAMOND, c, a), Cell(U_DIAMOND, c, a), Cell(U_DIAMOND, c, a), Cell(U_DIAMOND, c, a));
		break;
		case Point:
		set_border(Cell(U_POINT, c, a), Cell(U_POINT, c, a), Cell(U_POINT, c, a), Cell(U_POINT, c, a), Cell(U_POINT, c, a), Cell(U_POINT, c, a), Cell(U_POINT, c, a), Cell(U_POINT, c, a));
		break;
		default:
		set_border(Cell(U_LIGHT_V, c, a), Cell(U_LIGHT_V, c, a), Cell(U_LIGHT_H, c, a), Cell(U_LIGHT_H, c, a), Cell(U_LIGHT_UL, c, a), Cell(U_LIGHT_UR, c, a), Cell(U_LIGHT_DL, c, a), Cell(U_LIGHT_DR, c, a));
		break;
	}
}

void Window::fill(const Cell& cell){
	cchar_t c = cell;

	if(cell.color == ColorPair::Default)
		c.attr |= get_color(); //affiche dans la couleur courante du terminal

	wbkgrnd(m_win, &c);
}

void Window::fill(ColorPair color, Attr attr){
	Cell cell;
	cell.color = color;
	cell.attr = attr;

	fill(cell);
}

Cell Window::get_background() const{
	cchar_t c;

	wgetbkgrnd(m_win, &c);

	return c;
}

void Window::set_background(const Cell& cell){
	cchar_t c = cell;

	wbkgrndset(m_win, &c);
}

void Window::set_background(ColorPair color, Attr attr){
	Cell cell;
	cell.color = color == ColorPair::Default ? get_color() : color;
	cell.attr = attr;

	set_background(cell);
} 

void Window::clear(){
	/* faster than wclear */
	werase(m_win);
} 

void Window::clear(const IntRect& zone){
	
	Cell back = get_background();

	for(int j = zone.y ; j < zone.height ; j++){

		for (int i = zone.x; i < zone.width; i++){
			set_cell(Vector2i(i, j), back);
		}
	}
}

void Window::display(){
	if(is_pad(m_win)){
		int h, w;
		getmaxyx(stdscr, h, w);
		pnoutrefresh(m_win, 0, 0, 0, 0, h - 1, w -1);
	}
	else
		wnoutrefresh(m_win);
} 

void Window::refresh(){
	if(is_pad(m_win)){
		int h, w;
		getmaxyx(stdscr, h, w);
		prefresh(m_win, 0, 0, 0, 0, h - 1, w -1);
	}
	else
		wrefresh(m_win);
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS KEYBOARD
 
class Keyboard {

public:
	static int input;
	
	enum Key {
		A, B, C,
		D, E, F, G,
		H, I, J, K,
		L, M, N, O,
		P, Q, R, S,
		T, U, V, W,
		X, Y, Z, Num0,
		Num1, Num2, Num3, Num4,
		Num5, Num6, Num7, Num8,
		Num9, Escape, SemiColon, 
		Comma, Period, Equal, Space, Return,
		BackSpace, Tab, Left, Right, Up, Down,
		Numpad0, Numpad1, Numpad2, Numpad3,
		Numpad4, Numpad5, Numpad6, Numpad7,
		Numpad8, Numpad9, F1, F2,
		F3, F4, F5, F6,
		F7, F8, F9, F10,
		F11, F12,
	};

	static bool is_pressed(Key key);
};

///////////////////////////////////////////////// VARIABLES STATIQUES
 
int Keyboard::input = -1;

///////////////////////////////////////////////// METHODES

bool Keyboard::is_pressed(Key key) {

	switch (key)
	{
	case Keyboard::A:
		return input == 'a' || input == 'A';
		break;
	case Keyboard::B:
		return input == 'b' || input == 'B';
		break;
	case Keyboard::C:
		return input == 'c' || input == 'C';
		break;
	case Keyboard::D:
		return input == 'd' || input == 'D';
		break;
	case Keyboard::E:
		return input == 'e' || input == 'E';
		break;
	case Keyboard::F:
		return input == 'f' || input == 'F';
		break;
	case Keyboard::G:
		return input == 'g' || input == 'G';
		break;
	case Keyboard::H:
		return input == 'h' || input == 'H';
		break;
	case Keyboard::I:
		return input == 'i' || input == 'I';
		break;
	case Keyboard::J:
		return input == 'j' || input == 'J';
		break;
	case Keyboard::K:
		return input == 'k' || input == 'K';
		break;
	case Keyboard::L:
		return input == 'l' || input == 'L';
		break;
	case Keyboard::M:
		return input == 'm' || input == 'M';
		break;
	case Keyboard::N:
		return input == 'n' || input == 'N';
		break;
	case Keyboard::O:
		return input == 'o' || input == 'O';
		break;
	case Keyboard::P:
		return input == 'p' || input == 'P';
		break;
	case Keyboard::Q:
		return input == 'q' || input == 'Q';
		break;
	case Keyboard::R:
		return input == 'r' || input == 'R';
		break;
	case Keyboard::S:
		return input == 's' || input == 'S';
		break;
	case Keyboard::T:
		return input == 't' || input == 'T';
		break;
	case Keyboard::U:
		return input == 'u' || input == 'U';
		break;
	case Keyboard::V:
		return input == 'v' || input == 'V';
		break;
	case Keyboard::W:
		return input == 'w' || input == 'W';
		break;
	case Keyboard::X:
		return input == 'x' || input == 'X';
		break;
	case Keyboard::Y:
		return input == 'y' || input == 'Y';
		break;
	case Keyboard::Z:
		return input == 'z' || input == 'Z';
		break;
	case Keyboard::Num0:
		return input == 224 || input == '0'; //probl�me avec la reconnaissance de '�' (meme avec toupper et tolowwer)
		break;
	case Keyboard::Num1:
		return input == '&' || input == '1';
		break;
	case Keyboard::Num2:
		return input == 233 || input == '2';  //probl�me avec la reconnaissance de '�' (meme avec toupper et tolowwer)
		break;
	case Keyboard::Num3:
		return input == '\"' || input == '3';
		break;
	case Keyboard::Num4:
		return input == '\'' || input == '4';
		break;
	case Keyboard::Num5:
		return input == '(' || input == '5';
		break;
	case Keyboard::Num6:
		return input == '-' || input == '6';
		break;
	case Keyboard::Num7:
		return input == 232 || input == '7';  //probl�me avec la reconnaissance de '�' (meme avec toupper et tolowwer)
		break;
	case Keyboard::Num8:
		return input == '_' || input == '8';
		break;
	case Keyboard::Num9:
		return input == 231 || input == '9';  //probl�me avec la reconnaissance de '�' (meme avec toupper et tolowwer)
		break;
	case Keyboard::Escape:
		return input == 27; //Surement probleme de compatibilit�
		break;
	case Keyboard::SemiColon:
		return input == ';' || input == '.';
		break;
	case Keyboard::Comma:
		return input == ',' || input == '?';
		break;
	case Keyboard::Period:
		return input == '<' || input == '>';
		break;
	case Keyboard::Equal:
		return input == '=' || input == '+';
		break;
	case Keyboard::Space:
		return input == ' ';
		break;
	case Keyboard::Return:
		return input == KEY_ENTER || input == 13 || input == 10; //Surement probleme de compatibilit�
		break;
	case Keyboard::BackSpace:
		return input == KEY_BACKSPACE || input == 8; //Surement probleme de compatibilit�
		break;
	case Keyboard::Tab:
		return input == KEY_BTAB || input == 9; //Surement probleme de compatibilit�
		break;
	case Keyboard::Left:
		return input == KEY_LEFT;
		break;
	case Keyboard::Right:
		return input == KEY_RIGHT;
		break;
	case Keyboard::Up:
		return input == KEY_UP;
		break;
	case Keyboard::Down:
		return input == KEY_DOWN;
		break;
	case Keyboard::Numpad0:
		return input == '0';
		break;
	case Keyboard::Numpad1:
		return input == '1';
		break;
	case Keyboard::Numpad2:
		return input == '2';
		break;
	case Keyboard::Numpad3:
		return input == '3';
		break;
	case Keyboard::Numpad4:
		return input == '4';
		break;
	case Keyboard::Numpad5:
		return input == '5';
		break;
	case Keyboard::Numpad6:
		return input == '6';
		break;
	case Keyboard::Numpad7:
		return input == '7';
		break;
	case Keyboard::Numpad8:
		return input == '8';
		break;
	case Keyboard::Numpad9:
		return input == '9';
		break;
	case Keyboard::F1:
		return input == KEY_F(1);
		break;
	case Keyboard::F2:
		return input == KEY_F(2);
		break;
	case Keyboard::F3:
		return input == KEY_F(3);
		break;
	case Keyboard::F4:
		return input == KEY_F(4);
		break;
	case Keyboard::F5:
		return input == KEY_F(5);
		break;
	case Keyboard::F6:
		return input == KEY_F(6);
		break;
	case Keyboard::F7:
		return input == KEY_F(7);
		break;
	case Keyboard::F8:
		return input == KEY_F(8);
		break;
	case Keyboard::F9:
		return input == KEY_F(9);
		break;
	case Keyboard::F10:
		return input == KEY_F(10);
		break;
	case Keyboard::F11:
		return input == KEY_F(11);
		break;
	case Keyboard::F12:
		return input == KEY_F(12);
		break;
	default:
		return false;
		break;
	}
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS MOUSE

class Mouse {

public:

	static MEVENT event;

	enum Button { Left, Right, Middle };
	enum Wheel { ScrollUp, ScrollDown };

	static Vector2i get_position();

	static bool is_pressed(Button button);
	static bool is_released(Button button);
	static bool is_scrolling(Wheel wheel);
};

///////////////////////////////////////////////// VARIABLES STATIQUES
 
MEVENT Mouse::event;

///////////////////////////////////////////////// METHODES

Vector2i Mouse::get_position() {
	return Vector2i(event.x, event.y);
}

bool Mouse::is_pressed(Button button) {

	switch(button)
	{
		case Mouse::Left:
		return event.bstate & BUTTON1_PRESSED;
		break;
		case Mouse::Right:
		return event.bstate & BUTTON3_PRESSED;
		break;
		case Mouse::Middle:
		return event.bstate & BUTTON2_PRESSED;
		break;
		default:
		return false;
		break;
	}
}

bool Mouse::is_released(Button button) {

	mmask_t input_released = 0;

	switch (button)
	{
		case Mouse::Left:
		input_released = event.bstate & BUTTON1_RELEASED;
		break;
		case Mouse::Right:
		input_released = event.bstate & BUTTON3_RELEASED;
		break;
		case Mouse::Middle:
		input_released = event.bstate & BUTTON2_RELEASED;
		break;
		default:
		return false;
		break;
	}

	if(input_released)
		event.bstate = 0;

	return input_released;
}

bool Mouse::is_scrolling(Wheel wheel) {

	switch (wheel)
	{
		case Mouse::ScrollUp:
		return event.bstate & BUTTON4_PRESSED;
		break;
		case Mouse::ScrollDown:
		return false;//return event.bstate & BUTTON5_PRESSED;
		break;
		default:
		return false;
		break;
	}
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS TERMSCREEN

class TermScreen : public Window {

private:
	static TermScreen* m_screen;

	TermScreen();
	TermScreen(const TermScreen&);
	TermScreen& operator=(const TermScreen&);

public:
	~TermScreen();

	static TermScreen* getInstance();
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS TERM

class Term {

public:
	static Window scr;

	static void init_curs();
	static void end_curs();

	static void save_state();
	static void load_state();

/* all the terminal options to activate/set */
	static void set_cooked_mode_enabled(bool enable);
	static void set_echo_key_enabled(bool enable);
	static void set_keypad_enabled(bool enable);
	static void set_mouse_enabled(bool enable);

	static void set_timeout(int ms);
	static void set_curs_vis(int vis);

/* pop/push an input for the next call to the input queue */
	static int pop_input();
	static void push_input(int input);

/* Read inputs from mouse and keyboard */
	static int read_input();

/* Renvoie un chaine de character taper par l'untilisateur dans la chaine "str" */
	static void get_line(std::string& str);

/* Pointeur vers la fonction scanw */
	//static int (*scan)(const char*, ...);

/* clear the screen */ 
	static void clear();

/* attend jusqu'à ce que "ms" microseconds soit passées */ 
	static void wait(int ms);

/* Display the virtual screen to the real screen */
	static void update();
};

////////////////////////////////////////////////// VARIABLES STATIQUES

TermScreen* TermScreen::m_screen = NULL;

////////////////////////////////////////////////// CONSTRUCTEURS

TermScreen::TermScreen() : Window(stdscr) {}

TermScreen::~TermScreen() {
	//delete m_screen;
}

////////////////////////////////////////////////// METHODES

TermScreen* TermScreen::getInstance(){
	if(!m_screen){
		m_screen = new TermScreen();
	}
	return m_screen;
}

////////////////////////////////////////////////// VARIABLES STATIQUES

Window Term::scr; 

//int (*Term::scan)(const char*, ...) = scanw; 

////////////////////////////////////////////////// METHODES

void Term::init_curs() {

	setlocale(LC_ALL, "");

	//active les deplacements de la souris si un touche est pressé (-1003 tout le temps)
	setenv("TERM", "xterm-1002", 1); 	

	initscr();    // initialize curses

	init_color_pairs(); // initialize colors for the Term if compatible

	Term::scr = *TermScreen::getInstance();

	set_keypad_enabled(true);
	set_mouse_enabled(true);
	set_curs_vis(0); // 0 -> cursor is invisible.

	set_cooked_mode_enabled(false);
	set_echo_key_enabled(false);
	set_timeout(-1); //-1 -> wait indefinitly for input.
	
	mouseinterval(0); // 0 -> no click resolution.

	refresh();
}

void Term::end_curs(){
	endwin();
}

void Term::save_state(){
	def_prog_mode();// Save the ncurses win (!= savetty)
}

void Term::load_state(){
	reset_prog_mode(); // reset the ncurses win (!= resetty)
}

void Term::set_cooked_mode_enabled(bool enable){
	enable ? nocbreak() : cbreak();
}

void Term::set_echo_key_enabled(bool enable){
	enable ? echo() : noecho();
}

void Term::set_keypad_enabled(bool enable){
	enable ? keypad(stdscr, TRUE) : keypad(stdscr, FALSE);
}

void Term::set_mouse_enabled(bool enable){
	enable ? mousemask(ALL_MOUSE_EVENTS | REPORT_MOUSE_POSITION, NULL) : mousemask((mmask_t)NULL, NULL);
}

void Term::set_timeout(int ms){
	timeout(ms);
}

void Term::set_curs_vis(int vis){
	curs_set(vis);
}

int Term::pop_input(){
	return getch();
}

void Term::push_input(int ch){
	ungetch(ch); 
}

int Term::read_input(){

	int ch = getch();

	if(ch == KEY_MOUSE){

		MEVENT temp = Mouse::event;
		
		getmouse(&(Mouse::event));

		//Si l'evenement correspond a un deplacement du curseur
		if(Mouse::event.bstate & REPORT_MOUSE_POSITION)
			Mouse::event.bstate = temp.bstate;
	}
	else{
		Keyboard::input = ch;
	}

	return ch;
}

void Term::get_line(std::string& str){
	char cstr[1024] = "";
	getstr(cstr);
	str = cstr;
}

void Term::clear(){
	erase();
}

void Term::wait(int ms){
	napms(ms);
}

void Term::update(){
	doupdate();
}


//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS CANVAS
 
class Canvas : public Window {

protected:
	Vector2i m_pixel_size;

public:

/* initialise un canvas qui fait la taille de l'ecran */
	Canvas();
	Canvas(int w, int h);
	virtual ~Canvas();

/* place un pixel a la position "point" */
	void set(int x, int y);
	void set(const Vector2i& point);
	
/* enleve le pixel qui ce trouve a la position "point" */
	void unset(int x, int y);
	void unset(const Vector2i& point);

/* place un pixel a la position "point" du canvas si il n'y est pas deja, sinon l'enleve */
	void toggle(int x, int y);
	void toggle(const Vector2i& point);

/* Renvoie les dimension du canvas en nombre de pixel (width, height) */
	Vector2i get_size() const;

/* affiche entièrement le canvas à la position (0, 0) */
	virtual void display();

/* affiche entièrement le canvas à la position "position" */
	void display(const Vector2i& position);

/* affiche à la position "position", le rectangle "view" représentant une vue/camera sur le canvas  */
	void display(const Vector2i& position, const IntRect& view);

/* verifie un pixel existe à la position (x, y) */
	bool is_set(int x, int y);
	bool is_set(const Vector2i& point);

/* verifie si la position (x, y) est à l'interieur du canvas */
	bool is_in(int x, int y);
	bool is_in(const Vector2i& point);
};

///////////////////////////////////////////////// FONCTIONS DECLARATION

/* Converti la position du pixel (x, y) en coordonnée de cellule (row, col) */
Vector2i pixel_to_cell_coord(int x, int y);
Vector2i pixel_to_cell_coord(const Vector2i& point);

/* Converti les coordonnées de la cellule (row, col) en position de pixel (x, y) */
Vector2i cell_to_pixel_pos(int col, int row);
Vector2i cell_to_pixel_pos(const Vector2i& cell_coord);

/* verifie si le wide character "wch" est du braille */
bool is_braille(wint_t wch);

/* dessine une ligne sur le canvas allant du point p1 au point p2 */
void draw_line(Canvas& canvas, int x1, int y1, int x2, int y2);
void draw_line(Canvas& canvas, const Vector2i& p1, const Vector2i p2);

////////////////////////////////////////////////// VARIABLES STATIQUES
 
const wint_t braille_char_offset = 0x2800;

const int pixel_map[4][2] = { 	{0x01, 0x08}, 
{0x02, 0x10},
{0x04, 0x20},
{0x40, 0x80} };

////////////////////////////////////////////////// CONSTRUCTEURS

Canvas::Canvas(){
	int h = 0, w = 0;

	getmaxyx(stdscr, h, w);

	m_win = newpad(h, w);

	/* converti le nombre de cellules en nombre de pixel */
	m_pixel_size = Vector2i(w * 2, h * 4);
}

Canvas::Canvas(int w, int h) : m_pixel_size(w, h) {		
	/* verification pour ne pas qu'il nous manque de cellules */
	w = w % 2 != 0 ? w + 2 : w;	 
	h = h % 4 != 0 ? h + 4 : h;

	/* converti le nombre de pixels en nombre de colonnes/lignes */
	m_win = newpad(h / 4, w / 2);
} 

Canvas::~Canvas(){}

////////////////////////////////////////////////// METHODES

void Canvas::set(int x, int y){
	set(Vector2i(x, y));
}

void Canvas::set(const Vector2i& point){

	if(is_in(point)){

		Vector2i cell_coord = pixel_to_cell_coord(point);

		wint_t cell = get_cell(cell_coord).character;

		if(!is_braille(cell))
			cell = braille_char_offset;

		cell |= pixel_map[point.y % 4][point.x % 2];

		set_cell(cell_coord, cell);
	}
}

void Canvas::unset(int x, int y){
	unset(Vector2i(x, y));
}

void Canvas::unset(const Vector2i& point){

	if(is_in(point)){

		Vector2i cell_coord = pixel_to_cell_coord(point);

		wint_t cell = get_cell(cell_coord).character;

		if(!is_braille(cell))
			return;

		cell &= ~pixel_map[point.y % 4][point.x % 2];

		set_cell(cell_coord, cell);
	}
}

void Canvas::toggle(int x, int y){

	toggle(Vector2i(x, y));
}

void Canvas::toggle(const Vector2i& point){
	if(is_set(point))
		unset(point);
	else
		set(point);
}

Vector2i Canvas::get_size() const {
	return m_pixel_size;
}

void Canvas::display(){
	Window::display();
}

void Canvas::display(const Vector2i& position){
	display(position, IntRect(Vector2i::zero, get_dimension()));
} 

void Canvas::display(const Vector2i& position, const IntRect& view){
	int h, w;
	getmaxyx(stdscr, h, w);

	int maxY = position.y + view.height - 1;
	int maxX = position.x + view.width - 1;
	int maxTermY = h - 1;
	int maxTermX = w - 1;

	int pminrow = position.y >= 0 ? view.y : view.y - position.y;
	int pmincol = position.x >= 0 ? view.x : view.x - position.x;
	int sminrow = view.y >= 0 ? position.y : position.y - view.y;
	int smincol = view.x >= 0 ? position.x : position.x - view.x;
	int smaxrow = maxTermY >= maxY ? maxY : maxY - (maxY - maxTermY);
	int smaxcol = maxTermX >= maxX ? maxX : maxX - (maxX - maxTermX);

	pnoutrefresh(m_win, pminrow, pmincol, sminrow, smincol, smaxrow, smaxcol);
}

bool Canvas::is_set(int x, int y){
	return is_set(Vector2i(x, y));
}

bool Canvas::is_set(const Vector2i& point){
	wint_t cell = get_cell(pixel_to_cell_coord(point)).character;
	return is_braille(cell) && cell & pixel_map[point.y % 4][point.x % 2];
}

bool Canvas::is_in(int x, int y){
	return is_in(Vector2i(x, y));
}

bool Canvas::is_in(const Vector2i& point){
	return point.x >= 0 && point.y >= 0 && point.x < get_size().x && point.y < get_size().y;
}

////////////////////////////////////////////////// FONCTIONS DEFINITION

Vector2i pixel_to_cell_coord(int x, int y){
	return Vector2i(x / 2, y / 4);
}

Vector2i pixel_to_cell_coord(const Vector2i& point){
	return pixel_to_cell_coord(point.x, point.y);
}

Vector2i cell_to_pixel_pos(int col, int row){
	return Vector2i(col * 2, row * 4);
}

Vector2i cell_to_pixel_pos(const Vector2i& cell_coord){
	return cell_to_pixel_pos(cell_coord.x, cell_coord.y);
}

bool is_braille(wint_t cell){
	return cell >= 0x2800 && cell <= 0x28FF;
}

/* version plus simple de draw_line mais un peu moins precise */
void draw_line1(Canvas& canvas, int x1, int y1, int x2, int y2){

	int xdiff = std::max(x1, x2) - std::min(x1, x2);
	int ydiff = std::max(y1, y2) - std::min(y1, y2);
	int xdir = x1 <= x2 ? 1 : -1;
	int ydir = y1 <= y2 ? 1 : -1;

	int r = std::max(xdiff, ydiff);

	for (int i = 0; i < r + 1; ++i){
		int x = x1;
		int y = y1;

		if (ydiff)
			y += (float(i) * ydiff) / r * ydir;
		if (xdiff)
			x += (float(i) * xdiff) / r * xdir;

		canvas.set(x, y);
	}
}

void draw_line(Canvas& canvas, const Vector2i& p1, const Vector2i p2){
	draw_line(canvas, p1.x, p1.y, p2.x, p2.y);
}

void draw_line(Canvas& canvas, int x1, int y1, int x2, int y2){

	int dx = x2 - x1;
	int dy = y2 - y1;

	if(dx != 0){
		if(dx > 0){
			if(dy != 0){
				if(dy > 0){
					// vecteur oblique dans le 1er quadran
					
					if(dx >= dy){
						// vecteur diagonal ou oblique proche de l’horizontale dans le 1er octant

						float e = dx ;
						dx = e * 2;
						dy *= 2;

						while(1){
							canvas.set(x1, y1);

							if((x1++) == x2)
								break;

							if((e -= dy) < 0){
								y1++;
								e += dx;
							}
						}
					}
					else{
						// vecteur oblique proche de la verticale, dans le 2d octant
						
						float e = dy;
						dy = e * 2;
						dx *= 2;

						while(1){
							canvas.set(x1, y1);

							if((y1++) == y2)
								break;

							if((e -= dx) < 0){
								x1++;
								e += dy;
							}
						}
					}
				}
				else{
					// vecteur oblique dans le 4e cadran
					
					if(dx >= -dy){
						// vecteur diagonal ou oblique proche de l’horizontale, dans le 8e octant
						float e = dx;
						dx = e * 2;
						dy *= 2;

						while(1){
							canvas.set(x1, y1);

							if((x1++) == x2)
								break;

							if((e += dy) < 0){
								y1--;
								e += dx;
							}
						}
					}
					else{
						// vecteur oblique proche de la verticale, dans le 7e octant
						
						float e = dy;
						dy = e * 2;
						dx *= 2;

						while(1){
							canvas.set(x1, y1);

							if((y1--) == y2)
								break;

							if((e += dx) > 0){
								x1++;
								e += dy;
							}
						}
					}
				}
			}
			else{
				// vecteur horizontal vers la droite
				
				do{
					canvas.set(x1, y1);
				}while(!((x1++) == x2));
			}
		}
		else{
			if(dy != 0){
				if(dy > 0){
					// vecteur oblique dans le 2d quadran
					
					if(-dx >= dy){
						// vecteur diagonal ou oblique proche de l’horizontale, dans le 4e octant
						
						float e = dx;
						dx = e * 2;
						dy *= 2;

						while(1){
							canvas.set(x1, y1);

							if((x1--) == x2)
								break;

							if((e += dy) >= 0){
								y1++;
								e += dx;
							}
						}
					}
					else{
						// vecteur oblique proche de la verticale, dans le 3e octant
						
						float e = dy;
						dy = e * 2;
						dx *= 2;

						while(1){
							canvas.set(x1, y1);

							if((y1++) == y2)
								break;

							if((e += dx) <= 0){
								x1--;
								e += dy;
							}
						}
					}
				}
				else{
					// vecteur oblique dans le 3e cadran
					
					if(dx <= dy){
						// vecteur diagonal ou oblique proche de l’horizontale, dans le 5e octant
						
						float e = dx;
						dx = e * 2;
						dy *= 2;

						while(1){
							canvas.set(x1, y1);

							if((x1--) == x2)
								break;

							if((e -= dy) >= 0){
								y1--;
								e += dx;
							}
						}
					}
					else{
						// vecteur oblique proche de la verticale, dans le 6e octant
						
						float e = dy;
						dy = e * 2;
						dx *= 2;

						while(1){
							canvas.set(x1, y1);

							if((y1--) == y2)
								break;

							if((e -= dx) >= 0){
								x1--;
								e += dy;
							}
						}
					}
				}
			}
			else{
				// vecteur horizontal vers la gauche
				
				do{
					canvas.set(x1, y1);
				}while(!((x1--) == x2));
			}
		}
	}
	else{
		if(dy != 0){
			if(dy > 0){
				// vecteur vertical croissant
				
				do{
					canvas.set(x1, y1);
				}while(!((y1++) == y2));
			}
			else{
				// vecteur vertical décroissant
				
				do{
					canvas.set(x1, y1);
				}while(!((y1--) == y2));
			}
		}
	}
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS TURTLE
 
class Turtle
{
private:
	Canvas* m_canvas;
	float rotation;
	bool allocated;

public:
	Vector2f position;

	Turtle();
	Turtle(Canvas* canvas);
	~Turtle();

/* draw a line of "distance" pixels */
	void draw(float distance);

/* move the turtle of "distance" pixels */
	void move(float distance);

/* turn the turtle by "angle" degrees to the right if the angle is positive, or to the left if not. */
	void turn(float angle);
};

////////////////////////////////////////////////// FONCTIONS DECLARATION

/* Convert the angle "degree" in radians */
float to_radians(float degree);

/* Draw a polygon on the canvas */
void draw_polygon(Canvas& canvas, Vector2f center, int sides, float radius, float rotation);

////////////////////////////////////////////////// CONSTRUCTEURS
 
Turtle::Turtle() : m_canvas(new Canvas()), rotation(), allocated(true), position() {}

Turtle::Turtle(Canvas* canvas) : m_canvas(canvas), rotation(), allocated(false), position() {}

Turtle::~Turtle(){
	if(allocated)
		delete m_canvas;
}

////////////////////////////////////////////////// METHODES

void Turtle::draw(float distance){

	Vector2f origin(position);

	move(distance);

	draw_line(*m_canvas, round(origin.x), round(origin.y), round(position.x), round(position.y));
}

void Turtle::move(float distance){

	float angle = to_radians(rotation);

	position += Vector2f(distance * cos(angle), distance * sin(angle));
}

void Turtle::turn(float angle){
	rotation += angle;
}

////////////////////////////////////////////////// FONCTIONS DEFINITION

float to_radians(float degree){
	return degree * M_PI / float(180);
}

void draw_polygon(Canvas& canvas, Vector2f center, int sides, float radius, float rotation){
	
	Turtle T(&canvas);

	float angle = float(360) / sides;
	float length = 2 * radius * sin(M_PI / float(sides));
	float inradius = radius * cos(M_PI / float(sides));
	Vector2f offset(length / 2.0, inradius);

	//canvas->set(round(center.x), round(center.y));

	T.position = center;
	T.turn(rotation);
 
	T.move(-length / 2.0);
	T.turn(90);
	T.move(-inradius);
	T.turn(-90);

	for(int i = 0 ; i < sides ; i++){
		T.draw(length);
		T.turn(angle);
	}
}

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS PARTICLE

class Particle {

public:
	Vector2f position;
	Vector2f velocity;
	Vector2f acceleration;
	float lifetime;
	float mass;

	Particle();
	Particle(const Vector2f& position, float lifetime = 100);
	Particle(const Vector2f& pos, const Vector2f& v, float lifetime = 100);

	void apply_force(const Vector2f& force);

	void update();

	void display(Canvas& c);

	void run(Canvas& c);

	bool is_alive();

};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS ATTRACTOR

class Attractor {

public:

	Vector2f position;
	float strength; //Force du champ d'attraction
	float mass;

	Attractor();
	Attractor(const Vector2f& position);

	Vector2f attract(const Particle& p) const;
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS REPELLER

class Repeller {

public:

	Vector2f position;
	float strength; //Force du champ de repulsion
	float mass;
	Repeller();
	Repeller(const Vector2f& position);

	Vector2f repel(const Particle& p) const;
};

//@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@ CLASS PARTICLESYSTEM

class ParticleSystem {

public:
	std::list<Particle> particles;

	float duration;

	IntRect velocity_range;
	float velocity_over_time;
	//int max_particles;

	ParticleSystem();
	ParticleSystem(float duration, IntRect velocity_range = IntRect(0, 0, 0, 0), float velocity_over_time = 1);

	void apply_force(const Vector2f& force);
	
	void apply_repeller(const Repeller& rep);
	void apply_attractor(const Attractor& att);

	void add_particles(int n, Vector2f origin);
	void add_particles(int n, IntRect zone);
	
	void run(Canvas& c);
};

////////////////////////////////////////////////// FONCTIONS DECLARATION

/* genere un nombre flotant aléatoire entre "start" et "end", precision permet de stypulé le nombre max de zero aprés la virgule */
float random(int start, int end, int precision = 100000);

/* Oblige le nombre floatant f à être entre "start" et "end" */
float constrain(float f, float start, float end);

////////////////////////////////////////////////// CONSTRUCTEURS
 
Particle::Particle() : position(), velocity(random(-1, 1), random(-1, -1)), acceleration(), lifetime(), mass(1) {}

Particle::Particle(const Vector2f& position, float lifetime) : position(position), velocity(random(-1, 1), random(-1, -1)), acceleration(), lifetime(lifetime), mass(1){}

Particle::Particle(const Vector2f& pos, const Vector2f& v, float lifetime) : position(pos), velocity(v), acceleration(), lifetime(lifetime), mass(1) {} 

////////////////////////////////////////////////// METHODES

void Particle::apply_force(const Vector2f& force){
	acceleration += (force / mass);
}

void Particle::update() { 
	velocity += acceleration;
	position += velocity;
	acceleration = Vector2f::zero;
	lifetime -= 1.0;
}

void Particle::display(Canvas& c) {
		
	c.set(position.rounded());
	//c.toggle(position.rounded());
}

void Particle::run(Canvas& c) {
	update();
	display(c);
}

bool Particle::is_alive() {
	return lifetime > 0;
}

////////////////////////////////////////////////// CONSTRUCTEURS

Attractor::Attractor() : position(), strength(100), mass(1) {}

Attractor::Attractor(const Vector2f& position) : position(position), strength(100), mass(1) {}

////////////////////////////////////////////////// METHODES

Vector2f Attractor::attract(const Particle& p) const {

	Vector2f dir = position - p.position;
	
	float dist_squared = dir.length_squared();

	//constrain dist pour ne pas perdre le controle des particules trop rapides
	dist_squared = constrain(dist_squared, 100, 1000000000000);

	dir.normalize();

	float force = (strength * mass * p.mass) / dist_squared;
	
	return dir * force;
}

////////////////////////////////////////////////// CONSTRUCTEURS

Repeller::Repeller() : position(), strength(1), mass(1) {}

Repeller::Repeller(const Vector2f& position) : position(position), strength(100), mass(1) {}

////////////////////////////////////////////////// METHODES

Vector2f Repeller::repel(const Particle& p) const {

	Vector2f dir = position - p.position;
	
	float dist_squared = dir.length_squared();

	//constrain dist pour ne pas perdre le controle des particules trop rapides
	dist_squared = constrain(dist_squared, 100, 10000000000000);

	dir.normalize();

	float force = (strength * mass * p.mass) / dist_squared; 

	return -dir * force;
}

////////////////////////////////////////////////// CONSTRUCTEURS

ParticleSystem::ParticleSystem() : particles(), duration(1000), velocity_range(), velocity_over_time() {}

ParticleSystem::ParticleSystem(float duration, IntRect velocity_range, float velocity_over_time) : particles(),  duration(duration), velocity_range(velocity_range), velocity_over_time(velocity_over_time) {}
 
////////////////////////////////////////////////// METHODES

void ParticleSystem::apply_force(const Vector2f& force){
	for(std::list<Particle>::iterator it = particles.begin() ; it != particles.end() ; ++it){
		it->apply_force(force);
	}
}

void ParticleSystem::apply_repeller(const Repeller& rep){
	for(std::list<Particle>::iterator it = particles.begin() ; it != particles.end() ; ++it){
		Vector2f force = rep.repel(*it);
		it->apply_force(force);
	}
}

void ParticleSystem::apply_attractor(const Attractor& att){
	for(std::list<Particle>::iterator it = particles.begin() ; it != particles.end() ; ++it){
		Vector2f force = att.attract(*it);
		it->apply_force(force);
	}
}

void ParticleSystem::add_particles(int n, Vector2f origin){
	for(int i = 0 ; i < n ; i++){
		particles.push_back(Particle(origin, 
									 Vector2f(random(velocity_range.x, velocity_range.y), random(velocity_range.width, velocity_range.height)), 
									 duration));
	}
}

void ParticleSystem::add_particles(int n, IntRect zone){
	for(int i = 0 ; i < n ; i++){
		particles.push_back(Particle(Vector2f(random(zone.x, zone.width), random(zone.y, zone.height)), 
									 Vector2f(random(velocity_range.x, velocity_range.y), random(velocity_range.width, velocity_range.height)), 
									 duration));
	}
}

void ParticleSystem::run(Canvas& c){
	for(std::list<Particle>::iterator it = particles.begin() ; it != particles.end() ; ++it){
		
		if(it->is_alive()){
			it->run(c);
			it->velocity *= velocity_over_time;
		}
		else
			it = particles.erase(it); //met a jour l'iterateur pour pointer vers l'iterateur suivant
	}
}

////////////////////////////////////////////////// FONCTIONS DEFINITION

float random(int start, int end, int precision){

	int longueur = abs(abs(end) - start);

	int randlong = (rand() % ((longueur * precision) + 1));

	return (float) start + ((float) randlong / (float) precision);
}

float constrain(float f, float start, float end){
	return f < start ? start : f > end ? end : f;  
}

