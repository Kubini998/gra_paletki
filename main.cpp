#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include<iostream>
#include<ctime>
#include<cmath>
#include<vector>
#include<Windows.h>
using namespace std;
int licznik;
bool tryb1 = false, tryb2 = false, tryb3 = false;
bool animate1 = false;
bool animate2 = false;

void timer() {
    if (licznik == 310) {
        licznik = 0;
    }
    licznik++;
}
class menu :public sf::Drawable
{
public:
    menu(string direction)
    {
        set_texture(direction);

        if (direction == "grafiki/guzik4.png")
        {
            Bohater.setOrigin(23, 11);
        }
        else Bohater.setOrigin(119/ 2, 10);

        Bohater.setScale(3,3);
        Srodek_.x = 640;
        Srodek_.y = 200;
        Bohater.setPosition(Srodek_);
    }


    ~menu()
    {
    }
    void draw(sf::RenderTarget& target, sf::RenderStates state) const
    {
        target.draw(this->Bohater, state);
    }

    void set_position(float iks, float igrek)
    {
        Bohater.setPosition(iks, igrek);
        Srodek_.x = Bohater.getPosition().x;
        Srodek_.y = Bohater.getPosition().y;

    }
    void set_texture(std::string tex)
    {
        NazwaTekstury_ = tex;
        TexturaBohatera_.loadFromFile(NazwaTekstury_);
        Bohater.setTexture(TexturaBohatera_);

    }
    sf::Sprite Zwroc_bohatera()
    {
        return Bohater;
    }



private:
    sf::Sprite Bohater;
    std::string NazwaTekstury_;
    sf::Texture TexturaBohatera_;
    sf::Vector2f RozmiarBohatera_;
    int Szerokosc_;
    int Wysokosc_;
    sf::Vector2f Srodek_;
};

class Paletka// : public sf::RectangleShape
{
private:
    sf::Sprite paletka;
    sf::Texture tex;
public:
    Paletka(string direction) {
        tex.loadFromFile(direction);
        paletka.setTexture(tex);
        paletka.setScale(6,3);
        paletka.setOrigin(26, 6);
        paletka.setPosition(400, 585);
    }
    void rysowaniep(sf::RenderWindow &w) {
        w.draw(paletka);
    }
    void pozycja(float x, float y) {
        paletka.setPosition(x, y);
    }
    float nadajpozycjex() {
        float x = paletka.getPosition().x;
        return x;
    }
    float nadajpozycjey() {
        float y = paletka.getPosition().y;
        return y;
    }
    void ruch(float x, float y, float delta) {
        paletka.move(x*delta, y*delta);
    }
    sf::FloatRect bound() {
        sf::FloatRect bound = paletka.getGlobalBounds();
        return bound;
    }

};
class Pilka {
private:
    sf::Sprite pilka;
    sf::Texture tex,tex2;

    float velocity_x_;
    float velocity_y_;
public:
    Pilka() {
        tex.loadFromFile("grafiki/pilka.png");
        tex2.loadFromFile("grafiki/pilka2.png");
        pilka.setTexture(tex);
        pilka.setScale(80/23, 80/23);
        pilka.setOrigin(13, 13);
        pilka.setPosition(400, 515);

    }
    void animate() {
        if (animate1)
        {
            pilka.rotate(2);
        }
        else if (animate2)
        {
            pilka.rotate(-2);
        }
    }
    float set_velocity_x(float v_x) {
        velocity_x_ = v_x;
        return v_x;
    }
    float set_velocity_y(float v_y) {
        velocity_y_ = v_y;
        return v_y;
    }
    void rysowanie(sf::RenderWindow &w) {
        w.draw(pilka);
    }
    void pozycjakulki(float x, float y, bool czy) {
        if (czy == false) {
            pilka.setPosition(x, y);
        }
    }
    void ustawteksturke(string direction) {


    }
    void ruch(float delta, bool czy, sf::FloatRect obiekt, sf::FloatRect obiekt1) {
        sf::FloatRect bounds = pilka.getGlobalBounds();
        if (czy == true) {

            if (bounds.left <= 0)
            {
                //  velocity_y_ = fabs(velocity_y_);
                velocity_x_ = fabs(velocity_x_);
            }
            if (bounds.top <= 0)
            {
                velocity_y_ = fabs(velocity_y_);
                //   velocity_x_ = fabs(velocity_x_);

            }
            if (bounds.left + bounds.width >= 800)
            {
                //   velocity_y_ = -fabs(velocity_y_);
                velocity_x_ = -fabs(velocity_x_);
            }
            if (bounds.intersects(obiekt))
            {
                //  velocity_x_ = -fabs(velocity_x_);
                pilka.setTexture(tex);
                animate1 = true;
                animate2 = false;
                velocity_y_ = -fabs(velocity_y_);
            }
            if (bounds.intersects(obiekt1))
            {
                pilka.setTexture(tex2);
                animate1 = false;
                    animate2 = true;
                velocity_x_ = fabs(velocity_x_);
                velocity_y_ = fabs(velocity_y_);
            }

            pilka.move(velocity_x_*delta, velocity_y_*delta);
        }

    }
    void ruchdo1v1(float delta, bool czy, sf::FloatRect obiekt, sf::FloatRect obiekt1) {
        sf::FloatRect bounds = pilka.getGlobalBounds();
        if (czy == true) {

            if (bounds.left <= 0)
            {
                //  velocity_y_ = fabs(velocity_y_);
                velocity_x_ = fabs(velocity_x_);
            }

            if (bounds.left + bounds.width >= 800)
            {
                //   velocity_y_ = -fabs(velocity_y_);
                velocity_x_ = -fabs(velocity_x_);
            }
            if (bounds.intersects(obiekt))
            {
                //  velocity_x_ = -fabs(velocity_x_);
                pilka.setTexture(tex);
                animate1 = true;
                animate2 = false;
                velocity_y_ = -fabs(velocity_y_);
            }
            if (bounds.intersects(obiekt1))
            {
                pilka.setTexture(tex2);
                animate1 = false;
                    animate2 = true;
                velocity_x_ = fabs(velocity_x_);
                velocity_y_ = fabs(velocity_y_);
            }

            pilka.move(velocity_x_*delta, velocity_y_*delta);
        }

    }

    void kolizja(bool czy, sf::FloatRect obiekt) {
        sf::FloatRect bounds = pilka.getGlobalBounds();
        if (czy == true) {
            if (bounds.intersects(obiekt)) {
                velocity_x_ = -velocity_x_;
                velocity_y_ = -velocity_y_;
            }
            //pilka.move(velocity_x_*delta,velocity_y_*delta);
        }
    }
    sf::FloatRect boundpilki() {

        sf::FloatRect bound = pilka.getGlobalBounds();
        return bound;
    }


    float nadajpozycjex() {
        float x = pilka.getPosition().x;
        return x;
    }
};

class przeszkody {
private:
    sf::RectangleShape przeszkoda;
public:
    przeszkody() {
        przeszkoda.setSize(sf::Vector2f(20, 20));
        przeszkoda.setOrigin(10, 10);
        przeszkoda.setPosition(rand() % 801, rand() % 500);
        przeszkoda.setFillColor(sf::Color(rand() % 256, rand() % 256, rand() % 256));

    }
    void rysowaniep(sf::RenderWindow &w) {
        w.draw(przeszkoda);
    }
    void obrot(float g, float delta) {
        przeszkoda.rotate(g*delta);
    }
    sf::FloatRect boundprzeszkody() {
        sf::FloatRect bound = przeszkoda.getGlobalBounds();
        return bound;
    }
    bool znikanieprzeszkody(sf::FloatRect obiekt) {
        if (przeszkoda.getGlobalBounds().intersects(obiekt)) {
            przeszkoda.setSize(sf::Vector2f(0, 0));
            return true;
        }
        else return false;
    }
};
int ile_guzikow = 4;
bool men = true;
sf::Vector2f pozycja_myszy;
std::vector<menu> guziki;
bool kolizja_myszki(menu x)
{


    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
    {

        if (x.Zwroc_bohatera().getGlobalBounds().contains(pozycja_myszy))
        {
            return true;
        }
        else
        {
            return false;
        }

    }
    else
        return false;



}
void dodaj_guziki()
{

    for (int i = 0; i < ile_guzikow; i++)
    {



        string direction = "grafiki/guzik" + to_string(i + 1);
        direction += ".png";
        menu *temp = new menu(direction);
        temp->set_position(400, 240 + 100 * i);
        guziki.push_back(*temp);
    }
}
vector<przeszkody>wektor;
int main() {
    sf::Texture tex_tlo_menu,tex_tlo_gry_1;
    tex_tlo_menu.loadFromFile("grafiki/tlo_menu.png");
    tex_tlo_gry_1.loadFromFile("grafiki/tlo_gry1.png");
    sf::Sprite tlo_menu(tex_tlo_menu);
    sf::Sprite tlo_gry_1(tex_tlo_gry_1);
    tlo_menu.setScale(2.53, 2.53);
    tlo_gry_1.setScale(2.53,2.53);
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window"); //(szerokosc,dlugosc)
    Paletka p("grafiki/paletka1.png"); //gracz
    Pilka pi;
    Paletka p1("grafiki/paletka2.png"); //stworzenie bota
    p1.pozycja(400,15);
    bool czy1 = false;   // jesli falsz to pilka sledzi paletke, jesli true to zaczyna sie poruszac i sa kolizje , jesli spadnie , znow falsz
    pi.set_velocity_x(-200); //predkosc x
    pi.set_velocity_y(-300);
    sf::Clock clock;
    window.setFramerateLimit(60); // ustawione stałe fps
    dodaj_guziki();
    while (window.isOpen()) {
        window.clear(sf::Color::White);
        sf::Event event;
        while (window.pollEvent(event)) {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }
        pozycja_myszy.x = sf::Mouse::getPosition(window).x;
        pozycja_myszy.y = sf::Mouse::getPosition(window).y;
        if (men) {
            window.draw(tlo_menu);
            for (int i = 0; i < ile_guzikow; i++) // wyswietlanie guzikow
            {

                window.draw(guziki[i]);
                //sprawdzamy czy guzik zostal wcisniety
                if (kolizja_myszki(guziki[i]))
                {

                    if (i == 0)
                    {
                        men = false;
                        tryb1 = true;
                        Sleep(100);
                    }
                    else if (i == 1)
                    {
                        men = false;
                        tryb2 = true;
                        Sleep(100);
                    }
                    else if (i == 2)
                    {
                        men = false;
                        tryb3 = true;
                        Sleep(100);
                    }
                    else if (i == 3)
                    {
                        window.close();
                    }
                }


            }
        }
        else if ((men == false) && (tryb1 == true)) {
            window.draw(tlo_gry_1);
            float delta = float(clock.getElapsedTime().asSeconds());
            std::cout << delta << std::endl;
            clock.restart();
            timer();


            pi.animate();


            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                p.ruch(-500, 0, delta);
                if (p.bound().left <= 0) {
                    p.pozycja(150, 585);
                }
                pi.pozycjakulki(p.nadajpozycjex(), p.nadajpozycjey() - 70, czy1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                p.ruch(500, 0, delta);
                if (p.bound().left + p.bound().width >= 800) {
                    p.pozycja(650, 585);
                }
                pi.pozycjakulki(p.nadajpozycjex(), p.nadajpozycjey() - 70, czy1);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                czy1 = true; // uruchamianie ruchu pilki
            }
            //tworzenie przeszkod
            if (licznik == 300) {
                przeszkody temp;
                wektor.push_back(temp);
            }

            for (auto itr = wektor.begin(); itr != wektor.end();) {
                (*itr).rysowaniep(window);
                (*itr).obrot(100, delta);
                pi.kolizja(czy1, (*itr).boundprzeszkody()); //kolizja miedzy pilka a przeszkodami, jesli dotknie to znikaja
                if ((*itr).znikanieprzeszkody(pi.boundpilki()) == true) {
                    itr = wektor.erase(itr);
                }
                else itr++;

            }
            pi.ruch(delta, czy1, p.bound(), p1.bound()); // ruch pilki

            p1.pozycja(pi.nadajpozycjex(), 15); //nadanie pozycji botowi

            if (pi.boundpilki().top + pi.boundpilki().height >= 600) { // falsz jesli spadnie , wracanie do punktu wyjscia
                czy1 = false;
                if (czy1 == false) {
                    pi.pozycjakulki(p.nadajpozycjex(), p.nadajpozycjey() - 70, czy1);

                }
            }

            p.rysowaniep(window);
            p1.rysowaniep(window);
            pi.rysowanie(window);


        }
        else if ((men == false) && (tryb2 == true)) {
                   float delta = float(clock.getElapsedTime().asSeconds());
                   std::cout << delta << std::endl;
                   clock.restart();
                   timer();


                   window.draw(tlo_gry_1);

                   pi.animate();

                   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                       p.ruch(-500, 0, delta);
                       if (p.bound().left <= 0) {
                           p.pozycja(150, 585);
                       }
                       pi.pozycjakulki(p.nadajpozycjex(), p.nadajpozycjey() - 70, czy1);
                   }
                   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                       p.ruch(500, 0, delta);
                       if (p.bound().left + p.bound().width >= 800) {
                           p.pozycja(650, 585);
                       }
                       pi.pozycjakulki(p.nadajpozycjex(), p.nadajpozycjey() - 70, czy1);
                   }
                   if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                       p1.ruch(-500, 0, delta);
                       if (p1.bound().left <= 0) {
                           p1.pozycja(150, 15);
                       }
                     //  pi.pozycjakulki(p.nadajpozycjex(), p.nadajpozycjey() - 70, czy1);
                   }
                   if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
                       p1.ruch(500, 0, delta);
                       if (p1.bound().left + p.bound().width >= 800) {
                           p1.pozycja(650, 15);
                       }
                      // pi.pozycjakulki(p.nadajpozycjex(), p.nadajpozycjey() - 70, czy1);
                   }
                   if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                       czy1 = true; // uruchamianie ruchu pilki
                   }
                   //tworzenie przeszkod
                   if (licznik == 300) {
                       przeszkody temp;
                       wektor.push_back(temp);
                   }

                   for (auto itr = wektor.begin(); itr != wektor.end();) {
                       (*itr).rysowaniep(window);
                       (*itr).obrot(100, delta);
                       pi.kolizja(czy1, (*itr).boundprzeszkody()); //kolizja miedzy pilka a przeszkodami, jesli dotknie to znikaja
                       if ((*itr).znikanieprzeszkody(pi.boundpilki()) == true) {
                           itr = wektor.erase(itr);
                       }
                       else itr++;

                   }
                   pi.ruchdo1v1(delta, czy1, p.bound(), p1.bound()); // ruch pilki



                   if (pi.boundpilki().top + pi.boundpilki().height >= 600) { // falsz jesli spadnie , wracanie do punktu wyjscia
                       czy1 = false;
                       if (czy1 == false) {
                           pi.pozycjakulki(p.nadajpozycjex(), p.nadajpozycjey() - 70, czy1);

                       }
                   }
                   if (pi.boundpilki().top <= 0) { // falsz jesli spadnie , wracanie do punktu wyjscia
                       czy1 = false;
                       if (czy1 == false) {
                           pi.pozycjakulki(p1.nadajpozycjex(), p1.nadajpozycjey()+30 , czy1);

                       }
                   }
                   p.rysowaniep(window);
                   p1.rysowaniep(window);
                   pi.rysowanie(window);
               }
        else if ((men == false) && (tryb3 == true)) {

        }

        window.display();
    }

    return 0;
}
