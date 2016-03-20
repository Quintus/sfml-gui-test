#include <iostream>
#include <CEGUI/CEGUI.h>
#include <CEGUI/RendererModules/OpenGL/GLRenderer.h>
#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include <SFML/Graphics.hpp>

int main()
{
  // Create SFML window
  sf::RenderWindow window(sf::VideoMode(1024, 780), "CEGUI Test");
  window.setMouseCursorVisible(false); // Drawn with CEGUI

  // Some example scene drawn with SFML
  sf::CircleShape circle(50);
  circle.setFillColor(sf::Color::Green);

  // Instruct CEGUI to use the OpenGL renderer and the default (filesystem) resource provider
  CEGUI::OpenGLRenderer& cegui_renderer = CEGUI::OpenGLRenderer::bootstrapSystem();
  CEGUI::DefaultResourceProvider* p_rp = static_cast<CEGUI::DefaultResourceProvider*>(CEGUI::System::getSingleton().getResourceProvider());

  // Setup base pathes
  p_rp->setResourceGroupDirectory("schemes", "../data/schemes");
  p_rp->setResourceGroupDirectory("imagesets", "../data/imagesets");
  p_rp->setResourceGroupDirectory("fonts", "../data/fonts");
  p_rp->setResourceGroupDirectory("layouts", "../data/layouts");
  p_rp->setResourceGroupDirectory("looknfeels", "../data/looknfeels");

  // map path groups to the CEGUI system
  CEGUI::Scheme::setDefaultResourceGroup("schemes");
  CEGUI::ImageManager::setImagesetDefaultResourceGroup("imagesets");
  CEGUI::Font::setDefaultResourceGroup("fonts");
  CEGUI::WindowManager::setDefaultResourceGroup("layouts");
  CEGUI::WidgetLookManager::setDefaultResourceGroup("looknfeels");

  // Select TaharezLook as our GUI theme
  CEGUI::SchemeManager::getSingleton().createFromFile("TaharezLook.scheme");

  // Have CEGUI draw a mouse cursor
  CEGUI::GUIContext& gui_context = CEGUI::System::getSingleton().getDefaultGUIContext();
  gui_context.getMouseCursor().setDefaultImage("TaharezLook/MouseArrow");

  // Add the invisible root window
  CEGUI::Window* p_rootwindow = CEGUI::WindowManager::getSingleton().createWindow("DefaultWindow", "root");
  gui_context.setRootWindow(p_rootwindow);

  // Add a real framed window
  CEGUI::FrameWindow* p_frame = static_cast<CEGUI::FrameWindow*>(CEGUI::WindowManager::getSingleton().createWindow("TaharezLook/FrameWindow", "TestWindow"));
  p_rootwindow->addChild(p_frame);
  p_frame->setPosition(CEGUI::UVector2(CEGUI::UDim(0.25f, 0.0f), CEGUI::UDim(0.25f, 0.0f)));
  p_frame->setSize(CEGUI::USize(CEGUI::UDim(0.5f, 0.0f), CEGUI::UDim(0.5f, 0.0f)));
  p_frame->setText("Hello CEGUI World!");

  // Main loop
  bool terminate = false;
  while (!terminate) {
    sf::Event evt;

    // Dispatch events
    while (window.pollEvent(evt)) {
      switch(evt.type) {
      case sf::Event::Closed:
	terminate = true;
	break;
      case sf::Event::MouseMoved:
	// Tell CEGUI about mouse position changes
	gui_context.injectMousePosition(evt.mouseMove.x, evt.mouseMove.y);
	break;
      case sf::Event::MouseButtonPressed:
	// Tell CEGUI about left mouse button pressed
	if (evt.mouseButton.button == sf::Mouse::Left) {
	  gui_context.injectMouseButtonDown(CEGUI::LeftButton);
	}
	break;
      case sf::Event::MouseButtonReleased:
	// Tell CEGUI about left mouse button released
	if (evt.mouseButton.button == sf::Mouse::Left) {
	  gui_context.injectMouseButtonUp(CEGUI::LeftButton);
	}
	break;
      default:
	// ignore
	break;
      }
    }

    // Draw the SFML scecne
    window.clear(sf::Color::Black);
    window.draw(circle);

    // Draw CEGUI after the rest (with SFML OpenGL reset applied)
    window.pushGLStates();
    CEGUI::System::getSingleton().renderAllGUIContexts();
    window.popGLStates();

    window.display();
  }

  // Finish
  cegui_renderer.destroySystem();
  window.close();
  return 0;
}
