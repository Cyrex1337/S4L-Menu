#pragma once

#include "stdafx.h"

namespace CHook
{
	std::vector<uintptr_t> pCodeCaves;
	std::vector<std::pair<uintptr_t, std::size_t>> pHooks;

	void Unhook( )
	{
		// loop through all hooked objects
		for ( std::size_t i = 0; i < pHooks.size( ); ++i )
		{
			uintptr_t pCodeCave = pCodeCaves[ i ];
			std::pair<uintptr_t, std::size_t> pHook = pHooks[ i ];

			// restore original bytes
			unsigned long pOld;
			VirtualProtect( reinterpret_cast< LPVOID >( pHook.first ), pHook.second, PAGE_EXECUTE_READWRITE, &pOld );
			memcpy( reinterpret_cast< void* >( pHook.first ), reinterpret_cast< const void* >( pCodeCave ), pHook.second );
			VirtualProtect( reinterpret_cast< LPVOID >( pHook.first ), pHook.second, pOld, &pOld );

			// free the allocated memory
			VirtualFree( reinterpret_cast< LPVOID >( pCodeCave ), 0, MEM_RELEASE );
		}
	}

	uintptr_t Detour( uintptr_t pAddress, uintptr_t pRedirect, std::size_t nLength )
	{
		// create codecave and save bytes
		uintptr_t pCodeCave = reinterpret_cast< uintptr_t >( VirtualAlloc( nullptr, nLength + 5, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE ) );
		memcpy( reinterpret_cast< void* >( pCodeCave ), reinterpret_cast< const void* >( pAddress ), nLength );

		// allow ourselves to write in .code section
		unsigned long pOld;
		VirtualProtect( reinterpret_cast< LPVOID >( pAddress ), nLength, PAGE_EXECUTE_READWRITE, &pOld );

		// jmp-hook
		*reinterpret_cast< byte* >( pAddress ) = 0xE9;
		*reinterpret_cast< uintptr_t* >( pAddress + 1 ) = pCodeCave - ( pAddress + 5 );

		// overwrite invalid opcodes
		for ( std::size_t i = 5; i < nLength; ++i )
			*reinterpret_cast< byte* >( pAddress + i ) = 0x90;

		// restore
		VirtualProtect( reinterpret_cast< LPVOID >( pAddress ), nLength, pOld, &pOld );

		// jump-back in code cave
		*reinterpret_cast< byte* >( pCodeCave + nLength ) = 0xE9;
		*reinterpret_cast< uintptr_t* >( pCodeCave + nLength + 1 ) = ( pAddress + nLength ) - ( pCodeCave + nLength + 5 );

		// save things for unhooking purposes
		pCodeCaves.push_back( pCodeCave );
		pHooks.push_back( std::make_pair( pAddress, nLength ) );

		// return a pointer to our code cave
		return pCodeCave;
	}

}