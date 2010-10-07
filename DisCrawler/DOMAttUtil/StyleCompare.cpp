#include "StyleCompare.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

float sim_score(const string & s1, const string & s2)
{
	if(s1.compare("") == 0 && s2.compare("") == 0) return -1.0;
	if(s1.compare(s2) == 0) return 1.0;
	bool b = s1.length() > s2.length(); 
	const char* list1;
	const char* list2;
	int len1,len2;
	if(b)
	{
		list1 = s1.data();
		len1 = s1.length();
		list2 = s2.data();
		len2 = s2.length();
	}
	else
	{
		list1 = s2.data();
		len1 = s2.length();
		list2 = s1.data();
		len2 = s1.length();
	}

	char * it1 = (char*)list1;
	char * it2 = (char*)list2;
	
	int same_count = 0;
	
	char lb1,lb2;
	int j = 0;
	int k = 0;
//	bool record = false;
	for( int i = 0 ; i < len1; i++ )
	{
		lb1 = *it1++;
		//record = false;
		it2 = (char*)list2 + k;
		for(j = k; j < len2; j++ )
		{
			lb2 = *it2++;
			if(lb1 == lb2)
			{
//				cout << "1 "<<lb1<<" 2 "<<lb2<<endl;
				i ++;
				lb1 = *it1++;
				same_count++;
				//record = false;
				//if(!record)
				{
					k = j+1;
					//record = true;
				}

			}
			//else
			{
			}
		}
	}
	
//	cout << "diff_score ok" << same_count << " " << s1.length()<< " "<<s2.length()<< endl;
	
	return 2 * same_count / (float)(s1.length() + s2.length());
}

void init_color_db()
{
	map_color.insert( pair<string,int>(COLOR_YELLOW,COLOR_YELLOW_VALUE) );
	map_color.insert( pair<string,int>(COLOR_GRAY,COLOR_GRAY_VALUE) );
}

//normalize CSS property:value pair
void normalize(map<string,string> & style)
{
//	string background
	map<string,string>::iterator background_it;
	background_it = style.find(BACKGROUND);
	if(background_it != style.end())
	{
//		cout << BACKGROUND << " " << background_it->second << endl;
		style.erase(background_it);
		style.insert( pair<string,string>(BACKGROUND_COLOR, string(background_it->second)) );
	}
}

int parse_color(string & color)
{
	DEFINE_RGB_MATRIX
	
	//cout << "color" << color << endl;
	
	int rgb = 0;
	size_t found = color.find("rgb");
	if(found != string::npos)
	{
		const char * s = color.data();
		int co[3];
		int n = 0;
		char* p = (char *)s;
		int x;
		while(1)
		{
			if(*p <= '9' && *p >= '0')
   			{
	   			co[n++] = strtol(p,NULL, 10); //这里就读出那个数字
      				while( *p <= '9' && *p >= '0' ) p++  ;
   			}
   			if((*p)=='\0') 
				break;
   			else 
				p++  ;
		}
		//cout << co[0] << co[1] << co[2] << endl;
		rgb = co[0] * 65536 + co[1] * 256 + co[2];
	}
	else
	{
		found = color.find("#");
		if(found != string::npos)
		{
			rgb = strtol(color.data()+((int)found+1),NULL, 16);
		}
		else
		{
			map<string,int>::iterator color_it;
			color_it = map_color.find(color);
			if(color_it != map_color.end())
			{
				rgb = color_it->second;
				r = rgb / 65536;
				g = (unsigned char)(rgb / 256);
				b = (unsigned char)rgb;
//				cout << color <<" r " << r << " g " << g << " b " << b << endl;
			}
			else
			{
				rgb = -1;
			}
		}
	}
	
	return rgb;
}

int parse_size(string & str)
{
	int size = -1;
	char * p = (char*)str.data();
	int len = str.length();
	while(--len > 0)
	{
		if(*p <= '9' && *p >= '0')
   		{
			size = strtol(p,NULL, 10); //这里就读出那个数字
			break;
   		}
		p++  ;
	}
	//cout << "transform " << str << " to " << size << endl;
	return size;
}

float sim_size(string & s1, string & s2)
{
	if(s1.compare("") == 0 && s2.compare("") == 0) return -1.0;
	if(s1.compare(s2) == 0) return 1.0;

	int a = parse_size(s1);
	int b = parse_size(s2);

	if(a >= 0 && b >= 0)
	{
		int min = a > b ? b : a;
		int max = a > b ? a : b;
		return 2 * min / (float)( max + min );
	}
	else
	{
		return sim_score(s1,s2);
	}

	return 0.0;
}

float sim_color(string & c1, string & c2)
{
	if(c1.compare("") == 0 && c2.compare("") == 0) return -1.0;
	int rgb = parse_color(c1);
	int rgb1 = parse_color(c2);
	if(rgb == rgb1 && rgb >= 0.0) return 1;
	if(rgb == -1 || rgb1 == -1)
	{
		if(c1.compare(c2)==0) return 1;
		if(c1.compare("transparent")==0 || c2.compare("transparent")) return 1;
		return sim_score(c1,c2);
	}

	rgb = rgb == 0 ? 1:rgb;
	rgb1 = rgb1 == 0 ? 1:rgb1;

	int r = rgb / 65536;
	int g = (unsigned char)(rgb / 256);
	int b = (unsigned char)rgb;
	
	int r1 = rgb1 / 65536;
	int g1 = (unsigned char)(rgb1 / 256);
	int b1 = (unsigned char)rgb1;

/*
	long i = r*r1+g*g1+b*b1;
	long j = r*r+g*g+b*b;
	long k = r1*r1+g1*g1+b1*b1;
	float s = i / sqrt(j * k);
*/
//	int i = r < r1 ? r : r1;
//	int j = g < g1 ? g : g1;
//	int k = b < b1 ? b : b1;
//	int x = r + r1 > 0 ? r + r1 : 1;
//	int y = g + g1 > 0 ? g + g1 : 1;
//	int z = b + b1 > 0 ? b + b1 : 1;
//	float a  = (2*i)/(float)x + (2*j)/(float)y + (2*k)/(float)z ;

//	cout << a << endl;
//	float s = ((2*i)/(float)x + (2*j)/(float)y + (2*k)/(float)z) / 3;

	int i = r - r1;
	int j = g - g1;
	int k = b - b1;
	
	float d = sqrt( i*i + j*j + k*k );
	float s = 0.0;
	if(d < 17) 
		s = 1.0;

	//cout << "color cosine: " << i <<" "<<j<<" "<<k<<" "<<s <<endl;
	
	return s;
}

float sim_enum(string & s1, string s2)
{
	if(s1.compare("") == 0 && s2.compare("") == 0) return -1.0;
	if(s1.compare(s2)==0)
		return 1.0;
	return 0.0;
}

/*
   比较背景色的差异，使用background-color参数
 */
float diff_background( map<string,string> & style1,
		map<string,string> & style2 )
{
	map<string,string>::iterator background_it;
	background_it = style1.find(BACKGROUND_COLOR);
	string c1,c2;
	if(background_it != style1.end())
		c1 = background_it->second;

	background_it = style2.find(BACKGROUND_COLOR);
	if(background_it != style2.end())
		c2 = background_it->second;

	float d = sim_color(c1,c2);
	//cout << "background style d" << d << endl;
//	cout << BACKGROUND_COLOR << " : " << c1 << " ; " << c2 << " ; s="<< d << endl;
	return d;
}

/*
   比较文本字体的颜色
   */
float diff_text_color( map<string,string> & style1,
		map<string,string> & style2 )
{
	map<string,string>::iterator it;
        it = style1.find(TEXT_COLOR);
	string s1,s2;
	if(it != style1.end())
		s1 = it->second;

	it = style2.find(TEXT_COLOR);
	if(it != style2.end())
		s2 = it->second;
	float d = sim_color(s1,s2);
//	cout << TEXT_COLOR<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
	return d;
}
/*
   比较文本是否对齐
   */
float diff_text_align( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(TEXT_ALIGN);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(TEXT_ALIGN);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_enum(s1,s2);
//        cout << TEXT_ALIGN<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
        return d;
}

/*
   比较文本的装饰，是否有下划线等
   */
float diff_text_decoration( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(TEXT_DECORATION);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(TEXT_DECORATION);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_enum(s1,s2);
//        cout << TEXT_DECORATION<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
	return d;
}

/*
   比较字体
   */
float diff_font_family( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(FONT_FAMILY);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(FONT_FAMILY);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_score(s1,s2);
//        cout << FONT_FAMILY<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
        return d;
}

/*
   比较字体大小
   */
float diff_font_size( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(FONT_SIZE);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(FONT_SIZE);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_size(s1,s2);
//        cout << FONT_SIZE<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
        return d;
}

/*
   比较字体风格
   */
float diff_font_style( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(FONT_STYLE);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(FONT_STYLE);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_enum(s1,s2);
//        cout << FONT_STYLE<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
        return d;
}

/*
   比较字体粗体
   */
float diff_font_weight( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(FONT_WEIGHT);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(FONT_WEIGHT);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_enum(s1,s2);
//        cout << FONT_WEIGHT<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
        return d;
}

/*
   比较列表标志图片
   */
float diff_list_image( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(LIST_STYLE_IMAGE);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(LIST_STYLE_IMAGE);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_score(s1,s2);
//        cout << LIST_STYLE_IMAGE<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
        return d;
}

/*
   比较列表标志类型
   */
float diff_list_type( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(LIST_STYLE_TYPE);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(LIST_STYLE_TYPE);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_score(s1,s2);
//        cout << LIST_STYLE_TYPE<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
        return d;
}

/*
   比较列表标志位置
   */
float diff_list_position( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(LIST_STYLE_POSITION);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(LIST_STYLE_POSITION);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_enum(s1,s2);
//        cout << LIST_STYLE_POSITION<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
        return d;
}

/*
   比较表格布局
   */
float diff_table_layout( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(TABLE_LAYOUT);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(TABLE_LAYOUT);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_enum(s1,s2);
//        cout << TABLE_LAYOUT<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
        return d;
}

/*
   比较表格合并
   */
float diff_table_collapse( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(TABLE_COLLAPSE);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(TABLE_COLLAPSE);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_enum(s1,s2);
//        cout << TABLE_COLLAPSE<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
        return d;
}

/*
   比较表格标题位置
   */
float diff_table_caption( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(TABLE_CAPTION);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(TABLE_CAPTION);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_enum(s1,s2);
//        cout << TABLE_CAPTION<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
        return d;
}

/*
   比较边框
   */
float diff_border( map<string,string> & style1,
		map<string,string> & style2 )
{
	map<string,string>::iterator it;
        it = style1.find(BORDER);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(BORDER);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_enum(s1,s2);
//	cout << BORDER<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
	return d;
}

/*
   比较内边距顶部
   */
float diff_padding_top( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(PADDING_TOP);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(PADDING_TOP);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_size(s1,s2);
//        cout << PADDING_TOP<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
        return d;
}

/*
   比较内边距右部
   */
float diff_padding_right( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(PADDING_RIGHT);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(PADDING_RIGHT);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_size(s1,s2);
//        cout << PADDING_RIGHT<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
        return d;
}

/*
   比较内边距左部
   */
float diff_padding_left( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(PADDING_LEFT);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(PADDING_LEFT);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_size(s1,s2);
//        cout << PADDING_LEFT<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
        return d;
}

/*
   比较内边距底部
   */
float diff_padding_bottom( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(PADDING_BOTTOM);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(PADDING_BOTTOM);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_size(s1,s2);
//        cout << PADDING_BOTTOM<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
        return d;
}

/*
   比较外边距
   */
float diff_margin( map<string,string> & style1,
		map<string,string> & style2 )
{
        map<string,string>::iterator it;
        it = style1.find(MARGIN);
        string s1,s2;
        if(it != style1.end())
                s1 = it->second;

        it = style2.find(MARGIN);
        if(it != style2.end())
                s2 = it->second;
        float d = sim_score(s1,s2);
//        cout << MARGIN<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
        return d;
}

float diff_position( map<string,string> & style1,
		map<string,string> & style2 )
{
	map<string,string>::iterator it;
	it = style1.find(POSITION);
	string s1,s2;
	if(it != style1.end())
		s1 = it->second;
	it = style2.find(POSITION);
	if(it != style2.end())
		s2 = it->second;

	float d = sim_enum(s1,s2);

//	cout << POSITION<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
	//cout << "position style d " << dp << endl;
	return d;
}

float diff_display( map<string,string> & style1,
		map<string,string> & style2 )
{
	map<string,string>::iterator it;
	it = style1.find(DISPLAY);
	string s1,s2;
	if(it != style1.end())
		s1 = it->second;
	it = style2.find(DISPLAY);
	if(it != style2.end())
		s2 = it->second;

	float d = sim_enum(s1,s2);

//	cout << DISPLAY<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
	return d;
}

float diff_height( map<string,string> & style1,
		map<string,string> & style2 )
{
	map<string,string>::iterator it;
	it = style1.find(HEIGHT);
	string s1,s2;
	if(it != style1.end())
		s1 = it->second;
	it = style2.find(HEIGHT);
	if(it != style2.end())
		s2 = it->second;

	float d = sim_enum(s1,s2);

//	cout << HEIGHT<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
	return d;
}

float diff_width( map<string,string> & style1,
		map<string,string> & style2 )
{
	map<string,string>::iterator it;
	it = style1.find(WIDTH);
	string s1,s2;
	if(it != style1.end())
		s1 = it->second;
	it = style2.find(WIDTH);
	if(it != style2.end())
		s2 = it->second;

	float d = sim_enum(s1,s2);

//	cout << WIDTH<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
	return d;
}

float diff_float( map<string,string> & style1,
		map<string,string> & style2 )
{
	map<string,string>::iterator it;
	it = style1.find(FLOAT);
	string s1,s2;
	if(it != style1.end())
		s1 = it->second;
	it = style2.find(FLOAT);
	if(it != style2.end())
		s2 = it->second;

	float d = sim_enum(s1,s2);

//	cout << FLOAT<< " : " << s1 << " ; " << s2 << " ; s="<< d << endl;
	return d;
}

static bool init = false;
float compare_styles(map<string,string> style1, map<string,string> style2)
{
	VECTOR_WEIGHT
	float S[VECTOR_NUMBER];
	return compare_styles(style1,style2,S,W);
}

float compare_styles(map<string,string> style1, map<string,string> style2, float * S, float * W)
{
	if(!init) init_color_db();
	
	normalize(style1);
	normalize(style2);
	int i = 0;
	//background
	S[i++] = diff_background(style1,style2);
	//text
	//float S[i++] = diff_text(style1,style2);
	S[i++] = diff_text_color(style1,style2);
	S[i++] = diff_text_align(style1,style2);
	S[i++] = diff_text_decoration(style1,style2);
	//font
	//float S[i++] = diff_font(style1,style2);
	S[i++] = diff_font_family(style1,style2);
	S[i++] = diff_font_size(style1,style2);
	S[i++] = diff_font_style(style1,style2);
	S[i++] = diff_font_weight(style1,style2);
	//list_style
	//float S[i++] = diff_list_style(style1,style2);
	S[i++] = diff_list_image(style1,style2);
	S[i++] = diff_list_type(style1,style2);
	S[i++] = diff_list_position(style1,style2);
	//table_style
	//float S[i++] = diff_table_style(style1,style2);
	S[i++] = diff_table_layout(style1,style2);
	S[i++] = diff_table_collapse(style1,style2);
	S[i++] = diff_table_caption(style1,style2);
	//border,padding,margin
	//float S[i++] = diff_border(style1,style2);
	S[i++] = diff_border(style1,style2);
	S[i++] = diff_padding_top(style1,style2);
	S[i++] = diff_padding_right(style1,style2);
	S[i++] = diff_padding_left(style1,style2);
	S[i++] = diff_padding_bottom(style1,style2);
	S[i++] = diff_margin(style1,style2);
	//position
	S[i++] = diff_position(style1,style2);
	S[i++] = diff_display(style1,style2);
//	S[i++] = diff_height(style1,style2);
//	S[i++] = diff_width(style1,style2);
	S[i++] = diff_float(style1,style2);

	float sim = 0.0;
	float a = 0.0;
	float b = 0.0;
	for(int j = 0; j < i; j++)
	{
		if(S[j] >= 0.0)
		{
			b += W[j];
			a += W[j] * S[j];
		}
	}
	if(b > 0.0)
		sim = a / b;
	else
		sim = 1.0;

//	cout << "sim:" << sim << endl; 
	return sim;
}


