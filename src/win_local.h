#ifndef WIN_LOCAL_H
#define WIN_LOCAL_H

void	Win_Init(int width, int height, const char* title);

void	Win_Poll(void);

void	Win_Exit(void);

void	Win_In_Init(void);

void	Win_Cursor_Disable(void);

float	Win_Time(void);

int		Win_Loop(void);

#endif
