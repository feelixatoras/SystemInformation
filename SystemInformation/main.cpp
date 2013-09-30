/*#######################################################
	Name of file	: Main.cpp
	Author			: Stokic Stefan
	Version			: 1.0
	Description		: An "Injector". Is animating a progressbar and loads our gLib.dll
##########################################################
*/

#include <Windows.h>
#include <iostream>
#include <iomanip>

#define WIN32_LEAN_AND_MEAN


using namespace std;

void SetDebugPrivilege();
BOOL IsAdministrator(VOID);
void progressBar();
typedef int (__cdecl *FUNCI)(HINSTANCE);


/* main - starting the progressbar animation and loads the gLib.dll */
int main(int argc, char* argv[])
{

	SetConsoleTitleA("System Information");

	if(IsAdministrator()==FALSE)
	{
		MessageBoxA(0, "Please start it as admin !", "Error", MB_ICONERROR);
		//ExitProcess(1);
		return 1;
	}

	char title[19] = "System Information";
	HWND hwndConsole = FindWindowA( NULL, title );
	progressBar();
	ShowWindow(hwndConsole, SW_HIDE);
	HINSTANCE hInstance = (HINSTANCE)GetWindowLong(hwndConsole, GWL_HINSTANCE);

	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);
	//###################################################################
	SetDebugPrivilege();

	
	BOOL fFreeResult, fRunTimeLinkSuccess = FALSE; 
	HINSTANCE gLib;
	FUNCI funci;

	gLib = LoadLibrary("./glib.dll");
	if (gLib != 0){
		
		printf("gLib successfully loaded!\n\n");

		funci = (FUNCI)GetProcAddress(gLib, "crWindow");
		if (NULL != funci) 
		{
			fRunTimeLinkSuccess = TRUE;
			(funci) (hInstance); 
		}


		fFreeResult = FreeLibrary(gLib);

	}else{
		printf("gLib failed to load!\n");
	}

	if (!fRunTimeLinkSuccess) 
		printf("Function not located!\n");
	
	if(!fFreeResult)
		printf("FreeLibrary failed!\n");

	

	cin.get();
	return 0;
}

/* Setting/Giving debug privileges */
void SetDebugPrivilege() 
{
	HANDLE hProcess=GetCurrentProcess(), hToken;
	TOKEN_PRIVILEGES priv;
	LUID luid;

	OpenProcessToken(hProcess, TOKEN_ADJUST_PRIVILEGES, &hToken);
	GetLastError();

	priv.PrivilegeCount = 1;
	priv.Privileges[0].Luid = luid;
	priv.Privileges[0].Attributes = SE_PRIVILEGE_ENABLED;
	AdjustTokenPrivileges(hToken, false, &priv, 0, 0, 0);
	GetLastError();
	CloseHandle(hToken); 
}

/* Cheking if the program was executed with admin rights */
BOOL IsAdministrator(VOID)
{
	SID_IDENTIFIER_AUTHORITY NtAuthority = SECURITY_NT_AUTHORITY;
	PSID AdministratorsGroup;

	if( !AllocateAndInitializeSid(&NtAuthority,2,SECURITY_BUILTIN_DOMAIN_RID,
		DOMAIN_ALIAS_RID_ADMINS,0, 0, 0, 0, 0, 0,&AdministratorsGroup))
	{
		return FALSE;
	}

	BOOL IsInAdminGroup = FALSE;

	if(!CheckTokenMembership(NULL,AdministratorsGroup,&IsInAdminGroup))
	{
		IsInAdminGroup = FALSE;
	}

	FreeSid(AdministratorsGroup);
	return IsInAdminGroup;
}

/* Animating the progressbar */
void progressBar()
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 10);

	char buffer[256] = {0};
	char percent[7] = "0.0%%";
	int i,j,k;

	printf("Detecting computer information...\n");
	buffer[0] = '[';
	for(i = 0; i < 30; i++){
		buffer[i + 1] = '=';
		j = i % 4;
		if(j == 0)
			buffer[i + 2] = '\\';
		else if(j == 1)
			buffer[i + 2] = '|';
		else if(j == 2)
			buffer[i + 2] = '/';
		else
			buffer[i + 2] = '-';
		for(k = i+3; k < 31; k++)
			buffer[k] = ' ';

		buffer[31] = ']';

		sprintf(percent, "%3.2f%%", (i / 30.0) * 100.0);
		printf("%s %s\r", buffer, percent);
		Sleep(200);
	}
	sprintf(percent, "%3.2f%%", (i / 30.0) * 100.0);
	printf("%s %s\r\n", buffer, percent);

}