/*#######################################################
	Name of file	: main.cpp
	Author			: Stokic Stefan
	Version			: 1.0
	Description		: A dynamic link library that detects the System Information and creates a WinForm (with the WinAPI) with the
					   detected Information, displayed.
##########################################################
*/
#include <Windows.h>
#include <iostream>
#include "SystemInfo.h"

#define WIN32_LEAN_AND_MEAN
#define MAX_LENGTH 255

LPCTSTR ClsName = "SystemInformation";
LPCTSTR WndName = "SystemInformation";

HINSTANCE hInstText;
HINSTANCE hInstLabel;

char compName[MAX_LENGTH], osName[MAX_LENGTH], editionName[MAX_LENGTH], platfName[MAX_LENGTH], servicePackName[MAX_LENGTH], archiName[MAX_LENGTH];


LRESULT CALLBACK WndProcedure(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
void setWindowMiddle(HWND hWnd);
void setSysInfo();

/* Creating the WinForm with the WinAPI*/
#ifdef __cplusplus    
extern "C" {          
#endif
	__declspec(dllexport) int __cdecl crWindow(HINSTANCE hInstance)
	{
		
		MSG        Msg;
		HWND       hWnd;
		WNDCLASSEX WndClsEx;


		WndClsEx.cbSize        = sizeof(WNDCLASSEX);
		WndClsEx.style         = CS_HREDRAW | CS_VREDRAW;
		WndClsEx.lpfnWndProc   = WndProcedure;
		WndClsEx.cbClsExtra    = 0;
		WndClsEx.cbWndExtra    = 0;
		WndClsEx.hIcon         = LoadIcon(hInstance, IDI_APPLICATION);
		WndClsEx.hCursor       = LoadCursor(NULL, IDC_ARROW);
		WndClsEx.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH); //(HBRUSH)(COLOR_WINDOW + 18); //18,22,23,24,25
		WndClsEx.lpszMenuName  = NULL;
		WndClsEx.lpszClassName = ClsName;
		WndClsEx.hInstance     = hInstance;
		WndClsEx.hIconSm       = LoadIcon(hInstance, IDI_APPLICATION);


		if(!RegisterClassEx(&WndClsEx)){
			MessageBox(NULL, "Register Class failed!", "Error", MB_ICONERROR);
			return false;
		}


		hWnd = CreateWindowEx(WS_EX_STATICEDGE,
			ClsName,
			WndName,
			WS_OVERLAPPED | WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX ,
			500,
			200,
			400,
			240,
			NULL,
			NULL,
			hInstance,
			NULL);


		if( !hWnd ) 
			return 0; 


		setWindowMiddle(hWnd);

		ShowWindow(hWnd, SW_SHOWNORMAL);
		UpdateWindow(hWnd);

		ZeroMemory(&Msg, sizeof(MSG));

		while( GetMessage(&Msg, NULL, 0, 0) )
		{
			TranslateMessage(&Msg);
			DispatchMessage(&Msg);
		}

		return Msg.wParam;
	}
#ifdef __cplusplus
}
#endif

/* Creating components in the/for the WinForm */
LRESULT CALLBACK WndProcedure(HWND hWnd, UINT Msg, WPARAM wParam, LPARAM lParam){

	HWND hEditComputer, hEditOS, hEditEdition, hEditPlatformType, hEditServicePack, hEditArchi, 
		hLabelCompName, hLabelOS, hLabelEdition, hLabelPlatformType, hLabelServicePack, hLabelArchi,
		hLabelCred;

	switch(Msg)
	{
	case WM_CREATE:

		setSysInfo();

		hLabelCompName = CreateWindowEx(
			NULL,
			"STATIC",
			"Computer:",
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			5, 25,
			90, 25,
			hWnd, (HMENU) 1,
			hInstLabel,
			NULL);

		hEditComputer = CreateWindowEx(
			WS_EX_STATICEDGE,
			"Edit",
			compName,
			WS_VISIBLE | WS_CHILD | ES_READONLY,
			80, 25,
			200, 20,
			hWnd, (HMENU) 2,
			hInstText,
			NULL);

		hLabelOS = CreateWindowEx(
			NULL,
			"STATIC",
			"OS:",
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			5, 55,
			90, 25,
			hWnd, (HMENU) 3,
			hInstLabel,
			NULL);

		hEditOS = CreateWindowEx(
			WS_EX_STATICEDGE,
			"Edit",
			osName,
			WS_VISIBLE | WS_CHILD | ES_READONLY ,
			80, 55,
			200, 20,
			hWnd, (HMENU) 4,
			hInstText,
			NULL);

		hLabelEdition = CreateWindowEx(
			NULL,
			"STATIC",
			"Edition:",
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			5, 85,
			90, 25,
			hWnd, (HMENU) 5,
			hInstLabel,
			NULL);

		hEditEdition = CreateWindowEx(
			WS_EX_STATICEDGE,
			"Edit",
			editionName,
			WS_VISIBLE | WS_CHILD | ES_READONLY ,
			80, 85,
			200, 20,
			hWnd, (HMENU) 6,
			hInstText,
			NULL);
		
		hLabelPlatformType = CreateWindowEx(
			NULL,
			"STATIC",
			"Platform type:",
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			5, 115,
			90, 25,
			hWnd, (HMENU) 7,
			hInstLabel,
			NULL);

		hEditPlatformType = CreateWindowEx(
			WS_EX_STATICEDGE,
			"Edit",
			platfName,
			WS_VISIBLE | WS_CHILD | ES_READONLY ,
			100, 115,
			200, 20,
			hWnd, (HMENU) 8,
			hInstText,
			NULL);
		
		hLabelServicePack = CreateWindowEx(
			NULL,
			"STATIC",
			"Service Pack:",
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			5, 145,
			90, 25,
			hWnd, (HMENU) 9,
			hInstLabel,
			NULL);

		hEditServicePack = CreateWindowEx(
			WS_EX_STATICEDGE,
			"Edit",
			servicePackName,
			WS_VISIBLE | WS_CHILD | ES_READONLY ,
			100, 145,
			200, 20,
			hWnd, (HMENU) 10,
			hInstText,
			NULL);

		hLabelArchi = CreateWindowEx(
			NULL,
			"STATIC",
			"Architecture:",
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			5, 175,
			90, 25,
			hWnd, (HMENU) 11,
			hInstLabel,
			NULL);

		hEditArchi = CreateWindowEx(
			WS_EX_STATICEDGE,
			"Edit",
			archiName,
			WS_VISIBLE | WS_CHILD | ES_READONLY ,
			90, 175,
			200, 20,
			hWnd, (HMENU) 12,
			hInstText,
			NULL);

		hLabelCred = CreateWindowEx(
			NULL,
			"STATIC",
			"© Stefan Stokic",
			WS_CHILD | WS_VISIBLE | SS_LEFT,
			290, 197,
			120, 25,
			hWnd, (HMENU) 13,
			hInstLabel,
			NULL);

		break;

	case WM_CTLCOLORSTATIC:


		if(((HWND) lParam == GetDlgItem(hWnd, 1)) || ((HWND) lParam == GetDlgItem(hWnd, 2))){

			SetTextColor((HDC) wParam,RGB(0,255,0));
			SetBkMode((HDC) wParam,TRANSPARENT);
			return (LRESULT) GetStockObject (NULL_BRUSH);

		}
		if((HWND) lParam == GetDlgItem(hWnd, 3) || ((HWND) lParam == GetDlgItem(hWnd, 4))){

			SetTextColor((HDC) wParam,RGB(0,255,0));
			SetBkMode((HDC) wParam,TRANSPARENT);
			return (LRESULT) GetStockObject (NULL_BRUSH);
		}
		if((HWND) lParam == GetDlgItem(hWnd, 5) || ((HWND) lParam == GetDlgItem(hWnd, 6))){

			SetTextColor((HDC) wParam,RGB(0,255,0));
			SetBkMode((HDC) wParam,TRANSPARENT);
			return (LRESULT) GetStockObject (NULL_BRUSH);
		}
		if((HWND) lParam == GetDlgItem(hWnd, 7) || ((HWND) lParam == GetDlgItem(hWnd, 8))){

			SetTextColor((HDC) wParam,RGB(0,255,0));
			SetBkMode((HDC) wParam,TRANSPARENT);
			return (LRESULT) GetStockObject (NULL_BRUSH);
		}
		if((HWND) lParam == GetDlgItem(hWnd, 9) || ((HWND) lParam == GetDlgItem(hWnd, 10))){

			SetTextColor((HDC) wParam,RGB(0,255,0));
			SetBkMode((HDC) wParam,TRANSPARENT);
			return (LRESULT) GetStockObject (NULL_BRUSH);
		}
		if((HWND) lParam == GetDlgItem(hWnd, 11) || ((HWND) lParam == GetDlgItem(hWnd, 12))){

			SetTextColor((HDC) wParam,RGB(0,255,0));
			SetBkMode((HDC) wParam,TRANSPARENT);
			return (LRESULT) GetStockObject (NULL_BRUSH);
		}
		if((HWND) lParam == GetDlgItem(hWnd, 13)){

			SetTextColor((HDC) wParam,RGB(0,255,0));
			SetBkMode((HDC) wParam,TRANSPARENT);
			return (LRESULT) GetStockObject (NULL_BRUSH);
		}

		break;

	case WM_CLOSE:
		
		DestroyWindow(hWnd);
		ExitProcess(1);
		break;

	case WM_DESTROY:
		
		PostQuitMessage(0);
		ExitProcess(1);
		break;

	default:
		return DefWindowProc(hWnd, Msg, wParam, lParam);
	}
	return 0;
}

/* Positioning the window in the middle screen of your desktop */
void setWindowMiddle(HWND hWnd)
{
	int cx = GetSystemMetrics(SM_CXSCREEN);
	int cy = GetSystemMetrics(SM_CYSCREEN);

	int px = (cx - 400) / 2;
	int py = (cy - 240) / 2;

	MoveWindow(hWnd, px, py, 400, 240, false);
}

/* Getting and setting the detected System Information in the components of the WinForm */
void setSysInfo()
{

	char dmnNameBuf[MAX_LENGTH];
	char usrNameBuf[MAX_LENGTH];
	DWORD pcNameBufSize = sizeof dmnNameBuf-1;
	DWORD usrNameBufSize = sizeof usrNameBuf-1;

	if(GetComputerNameA(dmnNameBuf, &pcNameBufSize) == TRUE) 
	{
		GetUserNameA(usrNameBuf, &usrNameBufSize);	  	
	}
	sprintf_s(compName, "%s\\%s", dmnNameBuf, usrNameBuf);

	SystemInfo sysInfo;
	TCHAR szServicePack[128] = {0};

	switch(sysInfo.GetWindowsVersion())
	{
	case Windows:                 sprintf_s(osName, "Windows" );  break;
	case Windows32s:              sprintf_s(osName, "Windows 32s" );  break;
	case Windows95:               sprintf_s(osName, "Windows 95" );  break;
	case Windows95OSR2:           sprintf_s(osName, "Windows 95 SR2" );  break;
	case Windows98:               sprintf_s(osName, "Windows 98" );  break;
	case Windows98SE:             sprintf_s(osName, "Windows 98 SE" );  break;
	case WindowsMillennium:       sprintf_s(osName, "Windows Me" );  break;
	case WindowsNT351:            sprintf_s(osName, "Windows NT 3.51" );  break;
	case WindowsNT40:             sprintf_s(osName, "Windows NT 4.0" ); break;
	case WindowsNT40Server:       sprintf_s(osName, "Windows NT 4.0 Server" );  break;
	case Windows2000:             sprintf_s(osName, "Windows 2000" ); break;
	case WindowsXP:               sprintf_s(osName, "Windows XP" ); break;
	case WindowsXPProfessionalx64:sprintf_s(osName, "Windows XP Professional x64" );  break;
	case WindowsHomeServer:       sprintf_s(osName, "Windows Home Server" );  break;
	case WindowsServer2003:       sprintf_s(osName, "Windows Server 2003" );  break;
	case WindowsServer2003R2:     sprintf_s(osName, "Windows Server 2003 R2" );  break;
	case WindowsVista:            sprintf_s(osName, "Windows Vista" );  break;
	case WindowsServer2008:       sprintf_s(osName, "Windows Server 2008" ); break;
	case WindowsServer2008R2:     sprintf_s(osName, "Windows Server 2008 R2" );  break;
	case Windows7:                sprintf_s(osName, "Windows 7" ); break;
	case Windows8:                sprintf_s(osName, "Windows 8" ); break;
	case WindowsServer2012:       sprintf_s(osName, "Windows Server 2012" );  break;
	}


	switch(sysInfo.GetWindowsEdition())
	{
	case EditionUnknown:    sprintf_s(editionName, "Edition unknown Edition" ); break;
	case Workstation:       sprintf_s(editionName, "Workstation Edition" ); break;
	case Server:            sprintf_s(editionName, "Server Edition" ); break;
	case AdvancedServer:    sprintf_s(editionName, "Advanced Server Edition" ); break;
	case Home:              sprintf_s(editionName, "Home Edition" ); break;
	case Ultimate:          sprintf_s(editionName, "Ultimate Edition" ); break;
	case HomeBasic:         sprintf_s(editionName, "Home Basic Edition" ); break;
	case HomePremium:       sprintf_s(editionName, "Home Premium Edition" ); break;
	case Enterprise:        sprintf_s(editionName, "Enterprise Edition" ); break;
	case HomeBasic_N:       sprintf_s(editionName, "Home Basic N Edition" ); break;
	case Business:          sprintf_s(editionName, "Business Edition" ); break;
	case StandardServer:    sprintf_s(editionName, "Standard Server Edition" ); break;
	case EnterpriseServerCore: sprintf_s(editionName, "Enterprise Server Core Edition" ); break;
	case EnterpriseServerIA64: sprintf_s(editionName, "Enterprise Server IA64 Edition" ); break;
	case Business_N:           sprintf_s(editionName, "Business N Edition" ); break;
	case WebServer:            sprintf_s(editionName, "Web Server Edition" ); break;
	case ClusterServer:        sprintf_s(editionName, "Cluster Server Edition" ); break;
	case HomeServer:           sprintf_s(editionName, "Home Server Edition" ); break;

	}

	if(sysInfo.IsNTPlatform()) sprintf_s(platfName, "NT" );
	else if(sysInfo.IsWindowsPlatform()) sprintf_s(platfName, "Windows" );
	else if(sysInfo.IsWin32sPlatform()) sprintf_s(platfName, "Win32s" );
	else sprintf_s(platfName, "Unknown" );


	sysInfo.GetServicePackInfo(szServicePack);
	sprintf_s(servicePackName, "%s" , szServicePack);

	if(sysInfo.Is32bitPlatform() == TRUE)
	{
		sprintf_s(archiName, "x32" );
	}
	if(sysInfo.Is64bitPlatform() == TRUE)
	{
		sprintf_s(archiName, "x64" );
	}


	ZeroMemory(&dmnNameBuf, sizeof(pcNameBufSize));
	ZeroMemory(&usrNameBuf, sizeof(usrNameBufSize));
}