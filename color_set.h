#include <windows.h>
#include <string.h>
using namespace std;
char color_reference[9][20] = { "black", "blue", "green", "light blue", "red", "purple", "yellow", "white", "grey" };
void set_color(const char *color)
{
	int color_no;
	for(int i = 0; i < 9 ; ++i )
	{
		if(strcmpi(color,color_reference[i])==0)
		{
			color_no=i;
			break;
		}
	}
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };
    SetConsoleTextAttribute(output, color_no);
}
void set_font_size(int x, int y)
{
	HANDLE output = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_FONT_INFOEX font = { sizeof(CONSOLE_FONT_INFOEX) };
    GetCurrentConsoleFontEx(output, false, &font);
    font.dwFontSize.X = x;
    font.dwFontSize.Y = y;
    SetCurrentConsoleFontEx(output, false, &font);
}
void fullscreen()
{
	keybd_event(VK_MENU,0x38,0,0);
	keybd_event(VK_RETURN,0x1c,0,0);
	keybd_event(VK_RETURN,0x1c,KEYEVENTF_KEYUP,0);
	keybd_event(VK_MENU,0x38,KEYEVENTF_KEYUP,0);
}
