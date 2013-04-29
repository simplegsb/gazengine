#include "Keyboard.h"

using namespace std;

map<unsigned char, Keyboard::Button> createAsciiKeyboardButtonMap()
{
	map<unsigned char, Keyboard::Button> asciiButtonMap;

	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('0', Keyboard::ZERO));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('1', Keyboard::ONE));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('2', Keyboard::TWO));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('3', Keyboard::THREE));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('4', Keyboard::FOUR));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('5', Keyboard::FIVE));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('6', Keyboard::SIX));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('7', Keyboard::SEVEN));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('8', Keyboard::EIGHT));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('9', Keyboard::NINE));

	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('a', Keyboard::A));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('A', Keyboard::A));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('b', Keyboard::B));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('B', Keyboard::B));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('c', Keyboard::C));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('C', Keyboard::C));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('d', Keyboard::D));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('D', Keyboard::D));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('e', Keyboard::E));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('E', Keyboard::E));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('f', Keyboard::F));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('F', Keyboard::F));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('g', Keyboard::G));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('G', Keyboard::G));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('h', Keyboard::H));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('H', Keyboard::H));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('i', Keyboard::I));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('I', Keyboard::I));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('j', Keyboard::J));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('J', Keyboard::J));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('k', Keyboard::K));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('K', Keyboard::K));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('l', Keyboard::L));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('L', Keyboard::L));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('m', Keyboard::M));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('M', Keyboard::M));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('n', Keyboard::N));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('N', Keyboard::N));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('o', Keyboard::O));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('O', Keyboard::O));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('p', Keyboard::P));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('P', Keyboard::P));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('q', Keyboard::Q));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('Q', Keyboard::Q));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('r', Keyboard::R));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('R', Keyboard::R));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('s', Keyboard::S));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('S', Keyboard::S));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('t', Keyboard::T));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('T', Keyboard::T));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('u', Keyboard::U));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('U', Keyboard::U));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('v', Keyboard::V));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('V', Keyboard::V));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('w', Keyboard::W));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('W', Keyboard::W));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('x', Keyboard::X));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('X', Keyboard::X));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('y', Keyboard::Y));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('Y', Keyboard::Y));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('z', Keyboard::Z));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('Z', Keyboard::Z));

	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('\'', Keyboard::APOSTROPHE));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('*', Keyboard::ASTERISK));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('@', Keyboard::AT));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('\\', Keyboard::BACKSLASH));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('\b', Keyboard::BACKSPACE));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>(':', Keyboard::COLON));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>(',', Keyboard::COMMA));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>(127, Keyboard::DEL));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>(27, Keyboard::ESCAPE));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('=', Keyboard::EQUALS));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('`', Keyboard::GRAVE));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('(', Keyboard::LEFT_BRACKET));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('-', Keyboard::MINUS));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('.', Keyboard::PERIOD));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('\r', Keyboard::RETURN));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>(')', Keyboard::RIGHT_BRACKET));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>(';', Keyboard::SEMICOLON));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('/', Keyboard::SLASH));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>(' ', Keyboard::SPACE));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('\t', Keyboard::TAB));
	asciiButtonMap.insert(pair<unsigned char, Keyboard::Button>('_', Keyboard::UNDERLINE));

	return asciiButtonMap;
}
