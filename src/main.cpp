#include "menu.hpp"
#include "game.hpp"
#include "umap/umap.hpp"
#include <iostream>

//#include "menu.hpp"

//#include <gtkmm.h>
//#include <gtkmm/application.h>
//#include <gtkmm/button.h>
//#include <gtkmm/window.h>

/*class HelloWorld// : public Gtk::Window
{

public:
  HelloWorld();
  virtual ~HelloWorld();

protected:
  //Signal handlers:
  void on_button_clicked();

  //Member widgets:
  Gtk::Button m_button;
};

HelloWorld::HelloWorld()
: m_button("Hello Based")   // creates a new button with label "Hello World".
{
  // Sets the border width of the window.
  set_default_size(600, 400);

  // When the button receives the "clicked" signal, it will call the
  // on_button_clicked() method defined below.
  m_button.signal_clicked().connect(sigc::mem_fun(*this,
              &HelloWorld::on_button_clicked));

  // This packs the button into the Window (a container).
  add(m_button);

  // The final step is to display this newly created widget...
  m_button.show();
}

HelloWorld::~HelloWorld()
{
}

void HelloWorld::on_button_clicked()
{
  std::cout << "Hello World" << std::endl;
}
*/
int main(int argc, char *argv[])
{
  /*   auto app = Gtk::Application::create(argc, argv, "org.gtkmm.example");

    HelloWorld helloworld;
    //helloworld.add(Gtk::TextView());
    //helloworld.show_all();

    //Shows the window and returns when it is closed.
    return app->run(helloworld); */

  // build dictionary from file
  UMap dictionary;
  readMapFromFile("../config/dict.txt", dictionary);
  if (Menu::MainMenu(dictionary))
  {
    Game game(Menu::rounds, Menu::letters);
    std::cout << game.start(Menu::letters, Menu::rounds, dictionary);
  }
}
