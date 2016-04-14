#pragma once

#include "stdafx.h"

namespace Menu
{
	class CVector
	{
	public:
		int iX, iY;

	public:
		CVector( );
		CVector( int X, int Y );
	};


	class CButton
	{
	private:
		int iX, iY, iW, iH;
		std::size_t nIndex;
		bool* rFunction;
		std::string szName;

	public:
		CButton( const std::string& Name, bool* Function, std::size_t Index = 0 );

	public:
		CVector Position( ) const;
		CVector Size( ) const;
		std::size_t Index( ) const;
		bool* Reference( ) const;
		std::string Name( ) const;

		void Draw( );
		bool Clicked( );
	};

	class CMenu
	{
	private:
		std::string szTitle;
		std::size_t nItems;

		int iX, iY, iW, iH;

		std::vector<CButton> vButtons;

	private:
		void Handle( );

	public:
		CMenu( );
		CMenu( const std::string& Title = "test", int iW = 600, int iH = 400 );

	public:
		std::string Title( ) const;
		std::size_t Number( ) const;
		std::vector<CButton>& Items( );
		CVector Position( ) const;
		CVector Size( ) const;

		void AddButton( const std::string& Name, bool* Function );
		void Build( );
	};
}