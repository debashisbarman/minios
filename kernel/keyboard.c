/*
 * keyboard.c
 *
 * These set of keyboard functions are actually required for
 * converting scan code to ascii. 'handle_shift()' is still 
 * incomplete.
 */
#include <minios/tty.h>

static char is_lshift_down = 0;
static char is_rshift_down = 0;
static char is_caps_lock_pressed = 0;

static void toggle_left_shift(void)
{
	is_lshift_down = is_lshift_down ? 0 : 1;
}

static void toggle_right_shift(void)
{
	is_rshift_down = is_rshift_down ? 0 : 1;
}

static void toggle_caps_lock(void)
{
	is_caps_lock_pressed = is_caps_lock_pressed ? 0 : 1;
}

static char handle_caps_lock(char ch)
{
	if (ch >= 'a' && ch <= 'z')
		return ch + 'A' - 'a';
	return ch;
}

/* FIXME: fix the shift down side effect */
static char handle_shift(char ch)
{
	switch(ch) {
		case '`' :	ch = '~';
				break;
		case '1' :	ch = '!';
				break;
		case '2' :	ch = '@';
				break;
		case '3' :	ch = '#';
				break;
		case '4' :	ch = '$';
				break;
		case '5' :	ch = '%';
				break;
		case '6' :	ch = '^';
				break;
		case '7' :	ch = '&';
				break;
		case '8' :	ch = '*';
				break;
		case '9' :	ch = '(';
				break;
		case '0' :	ch = ')';
				break;
		case '-' :	ch = '_';
				break;
		case '=' :	ch = '+';
				break;
		case '[' :	ch = '{';
				break;
		case ']' :	ch = '}';
				break;
		case '\\' :	ch = '|';
				break;
		case ';' :	ch = ':';
				break;
		case '\'' :	ch = '\"';
				break;
		case ',' :	ch = '<';
				break;
		case '.' :	ch = '>';
				break;
		case '/' :	ch = '?';
				break;
		default:	
				break;	
	}

	return ch;
}

char toascii(unsigned char sc)
{
	char ch = 0;

	switch(sc) {
		case 42:	toggle_left_shift();
				break;
		case 54:	toggle_right_shift();
				break;
		case 58:	toggle_caps_lock();
				break;
		default:
				break;
	}

	switch(sc) {
		case 16:	ch='q'; 
				break;
		case 17:	ch = 'w'; 
				break;
		case 18:	ch = 'e'; 
				break;
		case 19:	ch = 'r'; 
				break;
		case 20:	ch = 't'; 
				break;
		case 21:	ch = 'y'; 
				break;
		case 22:	ch = 'u'; 
				break;
		case 23:	ch = 'i'; 
				break;
		case 24:	ch = 'o'; 
				break;
		case 25:	ch = 'p'; 
				break;
		case 30:	ch = 'a'; 
				break;
		case 31:	ch = 's'; 
				break;
		case 32:	ch = 'd'; 
				break;
		case 33:	ch = 'f'; 
				break;
		case 34:	ch = 'g'; 
				break;
		case 35:	ch = 'h'; 
				break;
		case 36:	ch = 'j'; 
				break;
		case 37:	ch = 'k'; 
				break;
		case 38:	ch = 'l'; 
				break;	
		case 41:	ch = '`';
				break;
		case 44:	ch = 'z'; 
				break;
		case 45:	ch = 'x'; 
				break;
		case 46:	ch = 'c'; 
				break;
		case 47:	ch = 'v'; 
				break;
		case 48:	ch = 'b'; 
				break;
		case 49:	ch = 'n'; 
				break;
		case 50:	ch = 'm'; 
				break;
		case 2:		ch = '1'; 
				break;
		case 3:		ch = '2'; 
				break;
		case 4:		ch = '3'; 
				break; 
		case 5:		ch = '4'; 
				break;
		case 6:		ch = '5'; 
				break;
		case 7:		ch = '6'; 
				break;
		case 8:		ch = '7'; 
				break;
		case 9:		ch = '8'; 
				break;
		case 10:	ch = '9'; 
				break;
		case 11:	ch = '0'; 
				break;
		case 57:	ch = ' '; 
				break;
		case 14:	ch = '\b'; 
				break;
		case 28:	ch = '\n'; 
				break;
		case 185:	ch = ' '; 
				break;
		case 142:	ch = '\b'; 
				break;
		case 156:	ch = '\n'; 
				break;
		case 13:	ch = '='; 
				break;
		case 26:	ch = '['; 
				break;
		case 27:	ch = ']'; 
				break;
		case 15:	ch = '\t'; 
				break;
		case 122:	ch = '/'; 
				break;
		case 43:	ch = '\\'; 
				break;
		case 53:	ch = '/'; 
				break;
		default: 
				break;
	}

	if (is_caps_lock_pressed)
		ch = handle_caps_lock(ch);
	
	if (is_lshift_down || is_rshift_down)
		ch = handle_shift(ch);

	return ch;
}
