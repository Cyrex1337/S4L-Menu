#include "CHook.h"
#include "CMenu.h"

// shitty example of using this
bool bDope = false, bShit = false, bCrazy = true;

void Functions( )
{
	if ( bDope )
	{
		/* do shit */
	}

	if ( bShit )
	{
		/* do shit */
	}

	if ( bCrazy )
	{
		/* do shit */
	}
}

void hkDrawFunction( /* ... */ )
{
	Menu::CMenu MyMenu( "Yooo." );

	MyMenu.AddButton( "dope", &bDope );
	MyMenu.AddButton( "shit", &bShit );
	MyMenu.AddButton( "crazy", &bCrazy );

	MyMenu.Build( );

	Functions( );

	// call original or w/e
}

void Hook( LPVOID lpReserved )
{
	// use my hook lib or something else to hook a function to draw smoothly
}

BOOL APIENTRY DllMain( HMODULE hModule, DWORD dwReason, LPVOID lpReserved )
{
	if ( dwReason == DLL_PROCESS_ATTACH )
		_beginthread( Hook, 0, nullptr );
	else if ( dwReason == DLL_PROCESS_DETACH )
		CHook::Unhook( );

	return TRUE;
}