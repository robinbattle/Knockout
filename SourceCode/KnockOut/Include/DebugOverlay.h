#pragma once

#include "OgreTextAreaOverlayElement.h"
#include "OgreFontManager.h"
#include "Ogre.h"
#include "Common.h"

namespace KnockOut
{

	using namespace Ogre;

	class DebugOverlay : public SingletonT<DebugOverlay>
	{
		SINGLETON_DEFINE(DebugOverlay)
		
	public:
		DebugOverlay() ;

		void setText(std::string newText);
		void setText2(std::string newText);
		void setText3(std::string newText);
		void setText4(std::string newText);
		void setText5(std::string newText);

	protected:
		TextAreaOverlayElement *textArea;
		TextAreaOverlayElement *textArea2;
		TextAreaOverlayElement *textArea3;
		TextAreaOverlayElement *textArea4;
		TextAreaOverlayElement *textArea5;
		TextAreaOverlayElement *textArea6;


		OverlayContainer *panel ;
		OverlayContainer *panel2 ;
		OverlayContainer *panel3 ;
		OverlayContainer *panel4 ;
		OverlayContainer *panel5 ;



		OverlayManager *olm;
		
		Overlay *overlay;
		

	};



}
