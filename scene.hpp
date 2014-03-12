#ifndef __SCENE__H__
#define __SCENE__H__

#include "common.h"
#include "camera.hpp"

#include <iostream>

namespace igr {

  template <typename derived>
  class scene {
    protected:
      sf::RenderWindow window;
      camera cam;

    public:
      using event_t = sf::Event;

      scene () :
        window{sf::VideoMode::getDesktopMode(), "SFML Window - OpenGL Render"}
      {}

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

    sf::Clock clock;
    _this.on_begin();

    while (window.isOpen()) {
      // Clock events
      sf::Time elapsed = clock.getElapsedTime();
      clock.restart();

      // Print it
      std::cout << " \033[K"
        << elapsed.asMilliseconds() << " ms\t"
        << (1 / elapsed.asSeconds()) << "fps\r"
        << std::flush;

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

      // Swap buffers
      window.display();
    }

    _this.on_end();
  }
}

#endif