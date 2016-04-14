#include "CMenu.h"

namespace Renderer
{
	enum Colors
	{
		Red,
		Green,
		Blue,
		Purple,
		Yellow,
		Brown,
		Violet,
		Magenta,
		LightBlue,
		LightRed,
		Black,
		White,
		Grey,
		Dark
	};

	void DrawRect( int iX, int iY, int iW, int iH, Colors cColor ) { }
	void DrawOutlinedRect(int iX, int iY, int iW, int iH, Colors cColor) { }
	void DrawText(int iX, int iY, Colors cColor) { }
}

namespace Menu
{
	CVector::CVector( )
	{
		iX = 0;
		iY = 0;
	}

	CVector::CVector( int X, int Y )
	{
		iX = X;
		iY = Y;
	}

	// ########################################################################
	// ########################################################################
	// ########################################################################

	CButton::CButton( const std::string& Name, bool* Function, std::size_t Index )
	{
		rFunction = Function;
		iX = iY = 100;
		iW = iH = 40;
		szName = Name;
		nIndex = Index;
	}

	CVector CButton::Position( ) const
	{
		return CVector( iX, iY );
	}

	CVector CButton::Size( ) const
	{
		return CVector ( iW, iH );
	}

	std::size_t CButton::Index( ) const
	{
		return nIndex;
	}

	bool* CButton::Reference( ) const
	{
		return rFunction;
	}

	std::string CButton::Name( ) const
	{
		return szName;
	}

	void CButton::Draw( )
	{
		Renderer::DrawOutlinedRect( iX, iY + ( nIndex * 15 ), iW, iH, Renderer::Colors::Black );
		if ( rFunction )
			Renderer::DrawRect( iX + 4, iY + ( nIndex * 15 ) + 4, iW - 4, iH - 4, Renderer::Colors::Green );
		else
			Renderer::DrawRect( iX + 4, iY + ( nIndex * 15 ) + 4, iW - 4, iH - 4, Renderer::Colors::Grey );
	}

	// adjust to windowed frames via screentoclient
	bool CButton::Clicked( )
	{
		POINT pMousePos;
		GetCursorPos( &pMousePos );

		if ( ( GetAsyncKeyState( VK_LBUTTON ) & 1 ) && pMousePos.x >= iX && pMousePos.x <= iX + iW
			&& pMousePos.y >= iY && pMousePos.y <= pMousePos.y + iH )
		{
			*rFunction = !*rFunction;
			return true;
		}

		return false;
	}

	// ########################################################################
	// ########################################################################
	// ########################################################################

	// call once per frame
	void CMenu::Handle( )
	{

	}

	CMenu::CMenu( )
	{
		iX = iY = 0;
		iW = iH = 500;
		szTitle = "Test";
	}

	CMenu::CMenu( const std::string& Title, int iW, int iH )
	{
		iX = iY = 0;
		this->iW = iW;
		this->iH = iH;
		szTitle = Title;
	}

	std::string CMenu::Title( ) const
	{
		return szTitle;
	}

	std::size_t CMenu::Number( ) const
	{
		return nItems;
	}

	std::vector<CButton>& CMenu::Items( )
	{
		return vButtons;
	}

	CVector CMenu::Position( ) const
	{
		return CVector( iX, iY );
	}

	CVector CMenu::Size( ) const
	{
		return CVector( iW, iH );
	}

	// call once per frame
	void CMenu::AddButton( const std::string& Name, bool* Function )
	{
		static std::size_t nCounter = 0;
		CButton button( Name, Function, nCounter++ );
		vButtons.push_back( button );
		++nItems;
	}

	// call once per frame
	void CMenu::Build( )
	{
		Renderer::DrawOutlinedRect( iX, iY, iW, iH, Renderer::Colors::White );
		Renderer::DrawRect( iX + 1, iY + 1, iW - 1, iH - 1, Renderer::Colors::Grey );
		Renderer::DrawText( iX + iW / 2, iY + 20, Renderer::Colors::Green );

		for ( auto& button : vButtons )
		{
			button.Draw( );
		}
	}
}