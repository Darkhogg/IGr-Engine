/**
 * @author Daniel Escoz Solana
 */
#ifndef __SCENE__H__
#define __SCENE__H__

#include "common.h"
#include "camera.hpp"

#include "dejavu.blob.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>

namespace igr {

  template <typename derived>
  class scene {
    protected:
      sf::RenderWindow window;
      sf::Font dejavu;
      camera cam;

    public:
      using event_t = sf::Event;

      scene (std::string title)
        : window{
            sf::VideoMode::getDesktopMode(),
            title,
            sf::Style::Default,
            sf::ContextSettings{24, 8, 8, 4, 4}
          }
        {
          std::cout << std::endl << "\x1B[1;34m[" << title << "]\x1B[m" << std::endl;
        }

      void run ();

      void on_begin () {}
      bool on_event (event_t event) { return false; }
      void on_update (float delta) {}
      void on_draw () {}
      void on_end () {}
  };

  template <typename derived>
  void scene<derived>::run () {
    derived& _this = * (derived*) this;

    window.setVerticalSyncEnabled(true);

    dejavu.loadFromMemory(_blob_dejavu.data(), _blob_dejavu.size());

    auto settings = window.getSettings();
    std::cout << "* \x1B[1;35mDepth Buffer Bits\x1B[m ..... \x1B[1m"
              << settings.depthBits << "\x1B[m" << std::endl
              << "* \x1B[1;35mStencil Buffer Bits\x1B[m ... \x1B[1m"
              << settings.stencilBits << "\x1B[m" << std::endl
              << "* \x1B[1;35mMultisample Level\x1B[m ..... \x1B[1m"
              << settings.antialiasingLevel << "\x1B[m" << std::endl
              << "* \x1B[1;35mOpenGL Version\x1B[m ........ \x1B[1m"
              << settings.majorVersion << "." << settings.minorVersion
              << "\x1B[m" << std::endl;

    sf::Clock clock;
    _this.on_begin();

    while (window.isOpen()) {
      window.clear();

      // Clock events
      sf::Time elapsed = clock.getElapsedTime();
      clock.restart();

      // Event polling
      sf::Event event;
      while (window.pollEvent(event)) {
        if (!_this.on_event(event)) {
          if (event.type == sf::Event::Closed) {
            window.close();

          } else if (event.type == sf::Event::Resized) {
            glViewport(0, 0, event.size.width, event.size.height);

          }
        }
      }

      // Update
      _this.on_update(elapsed.asSeconds());

      // Draw
      cam.gl_update();
      _this.on_draw();

      // Print it
      std::stringstream ss;
      ss << elapsed.asMilliseconds() << " ms\t"
         << std::fixed << std::setprecision(1) 
        << (1 / elapsed.asSeconds()) << "fps";

      sf::Text text;
      text.setFont(dejavu);
      text.setString(ss.str());
      text.setColor(sf::Color::White);
      text.setCharacterSize(12);

      window.resetGLStates();
      window.draw(text);

      // Swap buffers
      window.display();
    }

    _this.on_end();
  }
}

#endif