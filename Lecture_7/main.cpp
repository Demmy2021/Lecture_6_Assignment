#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

class CustomRectangleShape : public sf::RectangleShape {
public:
    CustomRectangleShape(const sf::Vector2f &size, const sf::Vector2f &position) : sf::RectangleShape(size)    {
        setPosition(position);
    }
    void setSpeed(const int& x_speed, const int& y_speed, const int & ro_speed) {
        x_speed_ = x_speed;
        y_speed_ = y_speed;
        ro_speed_ = ro_speed;
    }
    void animate(const sf::Time &elapsed){
        bounce();
        float dt = elapsed.asSeconds();
        move(x_speed_ * dt, y_speed_ * dt);
    }
    void setBounds(const float& l_bound, const float& r_bound,const float& u_bound,const float& d_bound){
        l_bound_  = l_bound  ;
        r_bound_  = r_bound  ;
        u_bound_  = u_bound  ;
        d_bound_  = d_bound  ;
    }
    void moveInDirection(const sf::Time &elapsed, const sf::Keyboard::Key &key, const std::vector<sf::Sprite> &hearts)      {
        float dt = elapsed.asSeconds();
        if(key == sf::Keyboard::Up) {
            y_speed_ = -1*abs(y_speed_);
            bounce();
            hearts.size();
            move(0, y_speed_ * dt);
        }
        else if(key == sf::Keyboard::Down) {
            y_speed_ = abs(y_speed_);
            bounce();
            move(0, y_speed_ * dt);
        }
        else if(key == sf::Keyboard::Left)  {
            x_speed_ = -1*abs(x_speed_);
            bounce();
            move(x_speed_ * dt, 0);
        }
        else if(key == sf::Keyboard::Right) {
            x_speed_ = abs(x_speed_);
            bounce();
            move(x_speed_ * dt, 0);
        }
    }
private:
    int x_speed_ = 0 ;
    int y_speed_ = 0 ;
    int ro_speed_ = 0 ;
    float l_bound_ = 0;
    float r_bound_ = 0;
    float u_bound_ = 0;
    float d_bound_ = 0;


    void bounce(){
        sf::FloatRect rectangle_bounds = getGlobalBounds();
        if(rectangle_bounds.top <= u_bound_){
            y_speed_ = abs(y_speed_);
        }
        if(rectangle_bounds.top + rectangle_bounds.height >= d_bound_){
            y_speed_ = abs(y_speed_) * -1;
        }
        if(rectangle_bounds.left <= l_bound_ ){
            x_speed_ = abs(x_speed_);
        }
        if(rectangle_bounds.left + rectangle_bounds.width >= r_bound_){
            x_speed_ = abs(x_speed_) * -1;
        }
    }
};
int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");
    std::vector<std::unique_ptr<sf::Drawable>> shapes;
    const float gridSize = 50.f;
    sf::Vector2f velocity;
    sf::Vector2i mosPos;
    sf::Vector2f size(40.0, 60.0);
    sf::Vector2f position(520.0, 360.0);
    CustomRectangleShape rectangle(size, position);
    rectangle.setSpeed(20, 20, 5);
    std::srand(std::time(nullptr));
    //grass
    sf::Texture texture_grass;
    if (!texture_grass.loadFromFile("grass.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }
    sf::Sprite grass;
    grass.setTexture(texture_grass);
    grass.setTextureRect(sf::IntRect(0, 0, 800, 600));
    texture_grass.setRepeated(true);

    //won
    sf::Texture texture_won;
    if (!texture_won.loadFromFile("won.png")) {
        return 1;
    }
    sf::Sprite won;
    won.setTexture(texture_won);
    won.scale(2.0, 2.0);


    //gameover
    sf::Texture texture_gameover;
    if (!texture_gameover.loadFromFile("game_over.png")) {
        return 1;
    }
    sf::Sprite game_over;
    game_over.setTexture(texture_gameover);
    game_over.scale(2.0, 2.0);

    //guy
    sf::Texture texture_guy;
    if(!texture_guy.loadFromFile("guy.png")) {
        return 1; }
    sf::Sprite guy;
    guy.setTexture(texture_guy);
    guy.setTextureRect(sf::IntRect(20, 20, 20, 20)); //left, top, width, height
    texture_guy.setRepeated(true);

    //house
    sf::Texture texture_house;
    if (!texture_house.loadFromFile("house.png")) {
        return 1;
    }
    sf::Sprite house;
    house.setTexture(texture_house);
    house.scale(0.1, 0.1);
    house.setPosition(sf::Vector2f(700, 525));

    //heart
    sf::Texture texture_heart;
    if(!texture_heart.loadFromFile("heart.png")) {
        return 1; }
    std::vector<sf::Sprite> hearts;
    sf::Sprite heart;
    heart.scale(0.04, 0.04);
    heart.setTexture(texture_heart);
    //heart_1
    heart.setPosition(sf::Vector2f(680, 10));
    hearts.push_back(heart);
    //heart_2;
    heart.setPosition(sf::Vector2f(710, 10));
    hearts.push_back(heart);
    //heart_3;
    heart.setPosition(sf::Vector2f(740, 10));
    hearts.push_back(heart);
    //heart_4;
    heart.setPosition(sf::Vector2f(770, 10));
    hearts.push_back(heart);

    //wall
    sf::Texture texture_wall;
    if(!texture_wall.loadFromFile("wall.png")) {
        return 1; }
    rectangle.setTexture(&texture_guy);
    rectangle.setBounds(0, window.getSize().x, 0, window.getSize().y);

    std::vector<sf::Sprite> walls;
    sf::Sprite wall;
    wall.setTexture(texture_wall);
    wall.setTextureRect(sf::IntRect(0, 0, 40, 300));
    texture_wall.setRepeated(true);
    //wall_1
    wall.setPosition(sf::Vector2f(50, 80));
    walls.push_back(wall);
    //wall_2;
    wall.setPosition(sf::Vector2f(150, 220));
    walls.push_back(wall);
    //wall_3;
    wall.setPosition(sf::Vector2f(250, 80));
    walls.push_back(wall);
    //wall_4;
    wall.setPosition(sf::Vector2f(300, 300));
    walls.push_back(wall);
    //wall_5;
    wall.setPosition(sf::Vector2f(700, 100));
    walls.push_back(wall);
    //wall_6;
    wall.setPosition(sf::Vector2f(250, 235));
    wall.setRotation(-90);
    walls.push_back(wall);
    //wall_7;
    wall.setPosition(sf::Vector2f(50, 520));
    wall.setRotation(-90);
    walls.push_back(wall);
    //wall_8;
    wall.setPosition(sf::Vector2f(450, 520));
    wall.setRotation(-90);
    walls.push_back(wall);
    //wall_9;
    wall.setPosition(sf::Vector2f(440, 120));
    wall.setRotation(-90);
    walls.push_back(wall);

    sf::Clock clock;
   // bool flag = false;
    sf::FloatRect newPos;

    while (window.isOpen()) {
        sf::Time elapsed = clock.restart();
        mosPos.x = sf::Mouse::getPosition(window).x / (int)gridSize;
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }
        //guy Movement
        sf::Keyboard::Key pressed;
        if(event.type == sf::Event::KeyPressed){
            pressed = event.key.code;

            //collision
            for(auto &wall : walls) {
                sf::FloatRect guyBounds = rectangle.getGlobalBounds();
                sf::FloatRect wallBounds = wall.getGlobalBounds();
               sf::FloatRect houseBounds = house.getGlobalBounds();

                newPos = guyBounds;
                newPos.left += velocity.x;
                newPos.top += velocity.y;


                if(guyBounds.left > houseBounds.left
                    && guyBounds.left + guyBounds.width > houseBounds.left + wallBounds.width){

                              while(true) {
                    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                                             window.close();
                                 }
                    window.clear(sf::Color::White);
                    window.draw(won);
                    window.display();
                        }

                if (hearts.size() == 0) {

                    while (true) {
                        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter)){
                            window.close();
                        }
                        window.clear(sf::Color::White);
                        window.draw(game_over);
                        window.display();
                    }
                }
                }
                for (size_t i = 0; i < hearts.size(); --i){
                if(wallBounds.intersects(newPos)){
                    velocity.y = 0.f;
                    velocity.x = 0.f;
                    //Bottom Collision
                    if(guyBounds.top < wallBounds.top
                            && guyBounds.top  + guyBounds.height < wallBounds.top  + wallBounds.height
                            && guyBounds.left < wallBounds.left + wallBounds.width
                            && guyBounds.left + guyBounds.width > wallBounds.left){
                        hearts.pop_back();
                        rectangle.setPosition(10,10);
                    }
                    //Top Collision
                    else if(guyBounds.top > wallBounds.top
                            && guyBounds.top  + guyBounds.height > wallBounds.top  + wallBounds.height
                            && guyBounds.left < wallBounds.left + wallBounds.width
                            && guyBounds.left + guyBounds.width > wallBounds.left){
                        hearts.pop_back();
                        rectangle.setPosition(10,10);
                    }
                    //Right Collision
                    if(guyBounds.left < wallBounds.left
                            && guyBounds.left + guyBounds.width < wallBounds.left + wallBounds.width
                            && guyBounds.top < wallBounds.top + wallBounds.height
                            && guyBounds.top + guyBounds.height > wallBounds.top){
                        hearts.pop_back();
                        rectangle.setPosition(10,10);
                    }
                    //Left Collision
                    else if(guyBounds.left > wallBounds.left
                            && guyBounds.left + guyBounds.width > wallBounds.left + wallBounds.width
                            && guyBounds.top < wallBounds.top + wallBounds.height
                            && guyBounds.top + guyBounds.height > wallBounds.top){
                        hearts.pop_back();
                        rectangle.setPosition(10,10);

                    }
                }
                rectangle.moveInDirection(elapsed,pressed,hearts);
            }
            }
        }
        window.clear(sf::Color::Black);
        window.draw(grass);

         for(auto &wall_ : walls) {
            window.draw(wall_);
        }
        for(auto &heart_ : hearts) {
            window.draw(heart_);
        }
        window.draw(rectangle);
         window.draw(house);
        //        window.draw(gameover);
        window.display();
    }
    return 0;
}
