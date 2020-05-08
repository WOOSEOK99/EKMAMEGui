// license:BSD-3-Clause
// copyright-holders:Chris Kirmse, Mike Haaland, Ren� Single, Mamesick

#ifndef SCREENSHOT_H
#define SCREENSHOT_H

bool LoadScreenShot(int nGame, int nType);
HANDLE GetScreenShotHandle(void);
int GetScreenShotWidth(void);
int GetScreenShotHeight(void);
void FreeScreenShot(void);
bool ScreenShotLoaded(void);

#endif
