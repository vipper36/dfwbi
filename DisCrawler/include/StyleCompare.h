#include <string>
#include <map>
#include <list>
#include <set>

#ifndef __STYLECOMPARE_H__
#define __STYLECOMPARE_H__

using namespace std;

#define BACKGROUND		"background"
#define BACKGROUND_COLOR	"background-color"

#define TEXT_COLOR		"color"
#define TEXT_ALIGN		"text-align"
#define TEXT_DECORATION		"text-decoration"

#define FONT			"font"
#define FONT_FAMILY		"font-family"
#define FONT_SIZE		"font-size"
#define FONT_STYLE		"font-style"
#define FONT_WEIGHT		"font-weight"

#define LIST_STYLE		"list_style"
#define LIST_STYLE_IMAGE	"list-style-image"
#define LIST_STYLE_TYPE		"list-style-type"
#define LIST_STYLE_POSITION	"list-style-position"

#define TABLE_LAYOUT		"table-layout"
#define TABLE_COLLAPSE		"border-collapse"
//#define TABLE_SPACING		"border-spacing"
#define TABLE_CAPTION		"caption-side"

#define PADDING			"padding"
#define PADDING_TOP		"padding-top"
#define PADDING_RIGHT		"padding-right"
#define PADDING_LEFT		"padding-left"
#define PADDING_BOTTOM		"padding-bottom"

#define BORDER			"border-style"
#define MARGIN			"margin"
#define POSITION		"position"
#define DISPLAY			"display"
#define HEIGHT			"height"
#define WIDTH			"width"
#define FLOAT			"float"

#define VECTOR_NUMBER		25
#define VECTOR_WEIGHT		float W[VECTOR_NUMBER]; \
				for(int f = 0; f<VECTOR_NUMBER; f++) W[f] = 1;

#define DEFINE_RGB_MATRIX	int r,g,b;
#define COLOR_YELLOW		"yellow"
#define COLOR_YELLOW_VALUE	255*65536 + 255*256 + 0
#define COLOR_GRAY		"gray"
#define COLOR_GRAY_VALUE	190*65536 + 190*256 + 190



float compare_styles(map<string,string> style1, map<string,string>style2);

float compare_styles(map<string,string> style1, map<string,string> style2, float * S, float * W);

void normalize(map<string,string> & style);

static map<string,int> map_color;

#endif
