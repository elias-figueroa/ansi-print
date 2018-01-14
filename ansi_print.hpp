#ifndef COLOR_PRINT_HPP
#define COLOR_PRINT_HPP

#include <stdio.h>
#include <stdarg.h>
// #include <string.h>

#include "../string-utils/get-pointer.h"

#define COMP_BEGIN '<'
#define COMP_MID   ':'
#define COMP_END   '>'
#define COMP_ESCAPE '\\'
#define ANSI_FORMAT "\033[%dm"
#define ANSI_RESET  "\033[00m"

#define WORD_MAX   16
#define TEXT_MAX  512
#define BUFF_MAX 1024

#define XW_FAIL    -1
#define XW_SUCCESS  0





/* -------- START: get_pointer -------------------------------- */

// FINISHED
static void _copy_to_pointer (char * dst, char * src, char * end) {
	while (src < end)
		*dst++ = *src++;
}

// !! IN PROGRESS ...
static void _copy_to_character (char * dst, char * src, char c) {					// In progress ...

	char * end = _get_pointer_end (src);

	while (*src != '\0' && src < end)
		*dst++ = *src++;
}

/* -- Not sure what I'm doing here -- */
// static char * _get_token_attributes (char * src, int * len) {
// 	char * ptr = NULL;
// 	while (*src != '\0') {
// 		if ((*src >= 'A' && *src <= 'Z') || (*src >= 'a' && *src <= 'z')) {
// 			ptr = src;
// 			break;
// 		}
// 	}
// 	if (!ptr)
// 		return NULL;
// 	while ((*ptr >= 'A' && *ptr <= 'Z') || (*ptr >= 'a' && *ptr <= 'z'))
// 		++ptr;
// 	*len = (int) ptr - src;
// 	return src;
// }

// IN PROGRESS ...
static void _trim (char * buf) {													// In progress ...

	char * ptr = buf;

	while (*ptr <= ' ')
		++ptr;

	if (ptr != buf) {
		while (*ptr != '\0')
			*buf++ = *ptr++;
		while (*buf != '\0')
			*buf++ = '\0';
	} else {
		buf = _get_pointer_end (buf);
	}

	while (*buf <= ' ')
		*buf-- = '\0';
}

static char * _get_pointer_first_non_white_space (char * ptr) {
	while (*ptr != '\0' && *ptr <= ' ')
		++ptr;

	if (*ptr == 0)
		return NULL;

	return ptr;
}


static bool _pointer_range_has_character (char * p0, char * p1, char c) {
	while (p0 < p1) {
		if (*p0++ == c)
			return true;
	}

	return false;
}


/* ------------------ ALERT --------------------------------------------------------------------- */
/* -------- Code above will be moved into a separate string-utils file -------------------------- */
/* ---------------------------------------------------------------------------------------------- */

enum _ENUM_ANSI_VALUES {
	RESET = 0,
	BOLD,
	LIGHT,
	ITALIC,
	UNDERLINE,
	BLINK,

	INVERT = 6,
	HIDDEN,

	FG_BLACK = 30,
	FG_RED,
	FG_GREEN,
	FG_YELLOW,
	FG_BLUE,
	FG_MAGENTA,
	FG_CYAN,
	FG_GRAY,

	BG_BLACK = 40,
	BG_RED,
	BG_GREEN,
	BG_YELLOW,
	BG_BLUE,
	BG_MAGENTA,
	BG_CYAN,
	BG_GRAY,

	FG2_BLACK = 90,
	FG2_RED,
	FG2_GREEN,
	FG2_YELLOW,
	FG2_BLUE,
	FG2_MAGENTA,
	FG2_CYAN,
	FG2_GRAY,

	BG2_BLACK = 100,
	BG2_RED,
	BG2_GREEN,
	BG2_YELLOW,
	BG2_BLUE,
	BG2_MAGENTA,
	BG2_CYAN,
	BG2_GRAY
};


static const char * _ansi_names[] = {
	"bold",
	"underline",
	"italic",
	"light",

	"red",
	"green",
	"yellow",
	NULL
};

static int _ansi_values[] = {
	BOLD,
	UNDERLINE,
	ITALIC,
	LIGHT,

	FG_RED,
	FG_GREEN,
	FG_YELLOW,

	BG_RED,
	BG_GREEN,
	BG_YELLOW
};




static const int _ansi_lookup (const char * name) {
	int i = 0;

	while (_ansi_names[i] != NULL) {

		printf ("_ansi_lookup: Looping through \"%s\", value: %d\n", _ansi_names[i], _ansi_values[i]);

		if (strcmp (name, _ansi_names[i]) == 0)
			return _ansi_values[i];

		++i;
	}

	return -1;
}

/*

"This is sample text to the rescue"
"This is <red: sample text> to the rescue"
"<green: This is> sample text to the rescue"
"<yellow: This is sample text to the rescue>"
"This is sample text <blue: to the rescue>"


// Advanced stuff below:
"This <red: is sample <blue: text> to the> rescue"

*/


struct _ansi_components_t {
	char * begin;
	char * middle;
	char * end;
};


static char * _ansi_get_begin_component_pointer (char * src) {
	if (*src == COMP_BEGIN)
		return src;

	char * p = _get_pointer_character (src);
	return (*(p-1) != COMP_ESCAPE) ? p : _ansi_get_begin_pointer (p+1);
}


// Make it so that $COMP_MID is found only after a valid $COMP_BEGIN and before a $COMP_END
static char * _ansi_get_middle_component_pointer (char * comp_begin) {

}

// Make it so that $COMP_END is found only after a valid $COMP_BEGIN and $COMP_MID
static char * _ansi_get_end_component_pointer () {

}



static int _ansi_get_components (struct * _ansi_components_t, char * src) {

}



static int _ansi_buffered_compartmentalize (char * buf, int len) {

	char * comp_begin = _get_pointer_character (src, COMP_BEGIN);
	char * comp_mid = _get_pointer_character (src, COMP_MID);
	char * comp_end = _get_pointer_character (src, COMP_END);

	if (_pointer_range_has_character (comp_begin, comp_end, COMP_BEGIN)) {
		// inner ansi section found

		comp_begin = _get_pointer_character (comp_begin+1, COMP_BEGIN);

	}

	if (!comp_begin || !comp_mid || !comp_end)
		return XW_FAIL;
	if (comp_mid < comp_begin || comp_end < comp_mid)
		return XW_FAIL;

	if ((comp_mid - comp_begin) > WORD_MAX)
		return XW_FAIL;
	if ((comp_end - comp_mid) > TEXT_MAX)
		return XW_FAIL;



}


// WARNING: This function will only handle ONE ansi section
static int _ansi_compartmentalize (char * src) {

	char * comp_begin = _get_pointer_character (src, COMP_BEGIN);
	char * comp_mid = _get_pointer_character (src, COMP_MID);
	char * comp_end = _get_pointer_character (src, COMP_END);

	if (!comp_begin || !comp_mid || !comp_end)
		return XW_FAIL;
	if (comp_mid < comp_begin || comp_end < comp_mid)
		return XW_FAIL;

	if ((comp_mid - comp_begin) > WORD_MAX)
		return XW_FAIL;
	if ((comp_end - comp_mid) > TEXT_MAX)
		return XW_FAIL;

	char nameBuf[WORD_MAX+1];
	char textBuf[TEXT_MAX+1];

	_copy_to_pointer (nameBuf, comp_begin+1, comp_mid);
	_trim (nameBuf);

	_copy_to_pointer (textBuf, comp_mid+1, comp_end);
	_trim (textBuf);

	char prefixBuf[BUFF_MAX+1];
	_copy_to_pointer (prefixBuf, src, comp_begin);

	char resultBuf[BUFF_MAX+1];
	sprintf (resultBuf, ANSI_FORMAT, _ansi_lookup (nameBuf));
	strcat (resultBuf, textBuf);
	strcat (resultBuf, ANSI_RESET);
	strcat (resultBuf, comp_end+1);


	// @debug
	printf ("  Attribute: [%s]\n", nameBuf);
	printf ("       Text: [%s]\n", textBuf);
	printf ("Ansi-Lookup: [%d]\n", _ansi_lookup (nameBuf));
	printf ("     Result: [%s]\n", resultBuf);

	return XW_SUCCESS;
}

void aprintf (const char * format, ... ) {

	char tmpBuf[BUFF_MAX+1];

	va_list args;
	va_start (args, format);
	vsprintf (tmpBuf, format, args);
	va_end (args);

	int retval;

	do {
		retval = _ansi_compartmentalize (tmpBuf);
	} while (retval != XW_FAIL);

	// you we last here, friend (_pointer_range_has_character)
}







#endif