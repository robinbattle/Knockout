#include "KnockOutListeners.h"


#include "DebugOverlay.h"


namespace KnockOut
{
	DebugOverlay::DebugOverlay()
	{
		olm=OverlayManager::getSingletonPtr();

		// First, create an overlay: 

		overlay=olm->create("MyTextDisplayOverlay");  // We can call this anything we like, 
										   //  If we have multiple overlays, the name
										   //  needs to be unique

		// Next, we create a panel within this overlay:
		panel=static_cast<OverlayContainer*>(olm->createOverlayElement("Panel","TextPanel"));
		panel->setMetricsMode(Ogre::GMM_RELATIVE); // Use relative dimensions for positions, size, etc
		panel->setPosition(.08f,.08f);                // Panel starts at 20$ to the right, and 20% down from the top
												  // left corner of the screen
		panel->setDimensions(0.5f,0.5f);           // Panel is half the width and half the height of the screen
		// panel->setMaterialName("Dirt");       // Give the panel a background material.
												 // Not required.  If you do use a background, need to 
												 //  create a material (More on this in a bit -- I did not
												 // include a "Dirt" material in your Content folder, so uncommenting
												 // this line will cause a runtime error in your projects
		overlay->add2D(panel);                   // Add our panel to the overlay




		// Next, we create a panel within this overlay:
		panel2=static_cast<OverlayContainer*>(olm->createOverlayElement("Panel","TextPanel2"));
		panel2->setMetricsMode(Ogre::GMM_RELATIVE); // Use relative dimensions for positions, size, etc
		panel2->setPosition(.28f,.08f);                // Panel starts at 20$ to the right, and 20% down from the top
												  // left corner of the screen
		panel2->setDimensions(0.5f,0.5f);           // Panel is half the width and half the height of the screen
		// panel->setMaterialName("Dirt");       // Give the panel a background material.
												 // Not required.  If you do use a background, need to 
												 //  create a material (More on this in a bit -- I did not
												 // include a "Dirt" material in your Content folder, so uncommenting
												 // this line will cause a runtime error in your projects
		overlay->add2D(panel2);                   // Add our panel to the overlay



		// Next, we create a panel within this overlay:
		panel3=static_cast<OverlayContainer*>(olm->createOverlayElement("Panel","TextPanel3"));
		panel3->setMetricsMode(Ogre::GMM_RELATIVE); // Use relative dimensions for positions, size, etc
		panel3->setPosition(.08f,.48f);                // Panel starts at 20$ to the right, and 20% down from the top
												  // left corner of the screen
		panel3->setDimensions(0.5f,0.5f);           // Panel is half the width and half the height of the screen
		// panel->setMaterialName("Dirt");       // Give the panel a background material.
												 // Not required.  If you do use a background, need to 
												 //  create a material (More on this in a bit -- I did not
												 // include a "Dirt" material in your Content folder, so uncommenting
												 // this line will cause a runtime error in your projects
		overlay->add2D(panel3);                   // Add our panel to the overlay



		// Next, we create a panel within this overlay:
		panel4=static_cast<OverlayContainer*>(olm->createOverlayElement("Panel","TextPanel4"));
		panel4->setMetricsMode(Ogre::GMM_RELATIVE); // Use relative dimensions for positions, size, etc
		panel4->setPosition(.08f,.68f);                // Panel starts at 20$ to the right, and 20% down from the top
												  // left corner of the screen
		panel4->setDimensions(0.5f,0.5f);           // Panel is half the width and half the height of the screen
		// panel->setMaterialName("Dirt");       // Give the panel a background material.
												 // Not required.  If you do use a background, need to 
												 //  create a material (More on this in a bit -- I did not
												 // include a "Dirt" material in your Content folder, so uncommenting
												 // this line will cause a runtime error in your projects
		overlay->add2D(panel4);                   // Add our panel to the overlay




		// Next, we create a panel within this overlay:
		panel5=static_cast<OverlayContainer*>(olm->createOverlayElement("Panel","TextPanel5"));
		panel5->setMetricsMode(Ogre::GMM_RELATIVE); // Use relative dimensions for positions, size, etc
		panel5->setPosition(.08f,.88f);                // Panel starts at 20$ to the right, and 20% down from the top
												  // left corner of the screen
		panel5->setDimensions(0.5f,0.5f);           // Panel is half the width and half the height of the screen
		// panel->setMaterialName("Dirt");       // Give the panel a background material.
												 // Not required.  If you do use a background, need to 
												 //  create a material (More on this in a bit -- I did not
												 // include a "Dirt" material in your Content folder, so uncommenting
												 // this line will cause a runtime error in your projects
		overlay->add2D(panel5);                   // Add our panel to the overlay




		// Create a TextArea element.  The 1st parameter "TextArea" tells the constructor to create
		//   a TextArea element.  The second paramater "text1" is just a name we give the element
		//   (needs to be unique!) so that we can retreive the element later
		textArea=static_cast<TextAreaOverlayElement*>(olm->createOverlayElement("TextArea","text1"));
	
		textArea->setFontName("StarWars");  	      // Set the font of the displayed text
		textArea->setMetricsMode(Ogre::GMM_PIXELS);   // We'll set the text area to be pixel relative instead of 
													  // screen relative (We don't need to do this, I'm only doing
													  // it to show the difference between screen relative and
		textArea->setCaption("");					  // Set what we want the text area to show
    
		textArea->setCharHeight(15);	              // Set the height of the text (in pixels)

		textArea2=static_cast<TextAreaOverlayElement*>(olm->createOverlayElement("TextArea","text2"));
	
		textArea2->setFontName("StarWars");  	      // Set the font of the displayed text
		textArea2->setMetricsMode(Ogre::GMM_PIXELS);   // We'll set the text area to be pixel relative instead of 
		textArea2->setCaption("2");					  // Set what we want the text area to show
		textArea2->setCharHeight(15);	              // Set the height of the text (in pixels)
		textArea2->setPosition(0.1f, 0.1f);

		textArea3=static_cast<TextAreaOverlayElement*>(olm->createOverlayElement("TextArea","text3"));
		textArea3->setFontName("StarWars");  	      // Set the font of the displayed text
		textArea3->setMetricsMode(Ogre::GMM_PIXELS);   // We'll set the text area to be pixel relative instead of 
		textArea3->setCaption("3");					  // Set what we want the text area to show
		textArea3->setCharHeight(15);	              // Set the height of the text (in pixels)
		textArea3->setPosition(0.3f, 0.3f);

		textArea4=static_cast<TextAreaOverlayElement*>(olm->createOverlayElement("TextArea","text4"));
		textArea4->setFontName("StarWars");  	      // Set the font of the displayed text
		textArea4->setMetricsMode(Ogre::GMM_PIXELS);   // We'll set the text area to be pixel relative instead of 
		textArea4->setCaption("4");					  // Set what we want the text area to show
		textArea4->setCharHeight(15);	              // Set the height of the text (in pixels)
		textArea4->setPosition(0.5f, 0.5f);

		textArea5=static_cast<TextAreaOverlayElement*>(olm->createOverlayElement("TextArea","text5"));
		textArea5->setFontName("StarWars");  	      // Set the font of the displayed text
		textArea5->setMetricsMode(Ogre::GMM_PIXELS);   // We'll set the text area to be pixel relative instead of 
		textArea5->setCaption("5");					  // Set what we want the text area to show
		textArea5->setCharHeight(15);	              // Set the height of the text (in pixels)
		textArea5->setPosition(0.7f, 0.7f);

		// Add the text area to the panel
		panel->addChild(textArea);
		panel2->addChild(textArea2);
		panel3->addChild(textArea3);
		panel4->addChild(textArea4);
		panel5->addChild(textArea5);

    
		// Show the overlay
		overlay->hide();
	
	}       

	void DebugOverlay::setText(std::string newText)
	{
		textArea->setCaption(newText);
	}
	
	void DebugOverlay::setText2(std::string newText)
	{
		textArea2->setCaption(newText);
	}

	void DebugOverlay::setText3(std::string newText)
	{
		textArea3->setCaption(newText);
	}

	void DebugOverlay::setText4(std::string newText)
	{
		textArea4->setCaption(newText);
	}

	void DebugOverlay::setText5(std::string newText)
	{
		textArea5->setCaption(newText);
	}
}
 