#include <iostream>
#include <memory>
#include <vector>
#include <cmath>
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>


class AnimatedSprite : public sf::Sprite {
public:
    AnimatedSprite(const int fps, const std::string& path):fps_(fps) //make an initializer list for fps_
    {


        if (!texture_.loadFromFile(path)) {
            std::cerr << "Could not load texture" << std::endl;

        }

        setTexture(texture_);
        setTextureRect(sf::IntRect(50, 0, 50, 37));
    }


    void setSpeed(const int& x_speed, const int& y_speed, const int & ro_speed) {
        x_speed_ = x_speed;
        y_speed_ = y_speed;
        ro_speed_ = ro_speed;
    }

    void animate(const sf::Time &elapsed){
        bounce();
        float dt = elapsed.asSeconds();
        t_ = t_ + dt;
        if (t_> 1.0/fps_){
            fragments_index++;
            t_ = 0.0;
           }

        if (fragments_index == running_frames.size()){
            fragments_index = 0.0;
        }

        // based on dt and fps_ fins fragments_index here

        setTextureRect(running_frames[fragments_index]);

        move(x_speed_*dt,y_speed_*dt);
    }

        void updateMovement() {
            bounce();
            if(y < 500)                  //If you are above ground
                velocityY += gravity;    //Add gravity
            else if(y > 500)             //If you are below ground
                y = 500;                 //That's not supposed to happen, put him back up

            velocityX += accelerationX;
            velocityY += accelerationY;

            x += velocityX;
            y += velocityY;
        }
    void setBounds(const float& l_bound, const float& r_bound,const float& u_bound,const float& d_bound){
        l_bound_  = l_bound  ;
        r_bound_  = r_bound  ;
        u_bound_  = u_bound  ;
        d_bound_  = d_bound  ;
    }
    void add_animation_frame(const sf::IntRect& frame){
        //add animation frames to vector
        running_frames.emplace_back(frame);

    }
       void moveInDirection(const sf::Time &elapsed, const sf::Keyboard::Key &key)
      {
          float dt = elapsed.asSeconds();
            if(key == sf::Keyboard::Up)
          {
              y_speed_ = -1*abs(y_speed_);
                          bounce();

         move(0, y_speed_ * dt);
          }
          else if(key == sf::Keyboard::Down)
          {
              y_speed_ = abs(y_speed_);
                          bounce();
                  move(0, y_speed_ * dt);
                   }
          else if(key == sf::Keyboard::Left)
          {
              x_speed_ = -1*abs(x_speed_);
                          bounce();

              move(x_speed_ * dt, 0);
              }
          else if(key == sf::Keyboard::Right)
          {
              x_speed_ = abs(x_speed_);
                         bounce();

                   move(x_speed_ * dt, 0);
          }
      }


private:

       sf::Texture texture_;
       float gravity = 2;
       int fps_;
       int x_speed_ = 0 ;
       int y_speed_ = 0 ;
       int ro_speed_ = 0 ;
       float l_bound_ = 0;
       float r_bound_ = 0;
       float u_bound_ = 0;
       float d_bound_ = 0;
       float t_ = 0.0;
       float x = 0;
       float y = 0;
       float velocityX = 0;
       float velocityY = 0;
       float accelerationX = 0;
       float accelerationY = 0;

       //float gravity = 2;
       unsigned int fragments_index = 0;
       std::vector<sf::IntRect> running_frames;


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


    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

     std::vector<std::unique_ptr<sf::Drawable>> shapes;

     AnimatedSprite hero(10, "Character\\character.png");
     hero.setBounds(0, window.getSize().x, 0, window.getSize().y);
     hero.setSpeed(30,30,10);


     hero.add_animation_frame(sf::IntRect(0, 0, 50, 37)); // hero standing frame 1
     hero.add_animation_frame(sf::IntRect(50, 0, 50, 37)); // hero standing frame 2
     hero.add_animation_frame(sf::IntRect(100, 0, 50, 37)); // hero standing frame 3
     hero.add_animation_frame(sf::IntRect(150, 0, 50, 37)); // hero running frame 1
     hero.add_animation_frame(sf::IntRect(200, 0, 50, 37)); // hero running frame 1
     hero.add_animation_frame(sf::IntRect(250, 0, 50, 37)); // hero running frame 1
     hero.add_animation_frame(sf::IntRect(300, 0, 50, 37)); // hero running frame 1
     hero.add_animation_frame(sf::IntRect(350, 0, 50, 37)); // hero running frame 1
     hero.add_animation_frame(sf::IntRect(400, 0, 50, 37)); // hero running frame 1


      sf::Vector2f velocity;

   std::srand(std::time(nullptr));

    sf::Texture texture;
    if (!texture.loadFromFile("background.png")) {
        std::cerr << "Could not load texture" << std::endl;
        return 1;
    }

    sf::Sprite sprite;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0, 0, 800, 600));
    texture.setRepeated(true);


    //sf::Transformable::setScale;
    sf::Texture texture_wall;
    if(!texture_wall.loadFromFile("floor.png")) {
        return 1; }

std::vector<sf::Sprite> walls;

sf::Sprite wall;

    //wall_1
    wall.setTexture(texture_wall);
    wall.setScale(0.6, 0.6);
    wall.setPosition(sf::Vector2f(150, 200)); // absolute position
    wall.move(sf::Vector2f(20, 20));
    wall.setTextureRect(sf::IntRect(0, 0, 60, 500));
    texture_wall.setRepeated(true);
    walls.push_back(wall);

    //wall_2;
    wall.setTexture(texture_wall);
    wall.setScale(0.6, 0.6);
    wall.setPosition(sf::Vector2f(10, 50)); // absolute position
    wall.move(sf::Vector2f(20, 20));
    wall.setTextureRect(sf::IntRect(0, 0, 60, 400));
    texture_wall.setRepeated(true);
    walls.push_back(wall);

    //wall_3;
    wall.setTexture(texture_wall);
    wall.setScale(0.6, 0.6);
    wall.setPosition(sf::Vector2f(550, 170)); // absolute position
    wall.move(sf::Vector2f(20, 20));
    wall.setTextureRect(sf::IntRect(0, 0, 60, 500));
    texture_wall.setRepeated(true);
    walls.push_back(wall);

    //wall_4;
    wall.setTexture(texture_wall);
    wall.setScale(0.6, 0.6);
    wall.setPosition(sf::Vector2f(250, 250)); // absolute position
    wall.move(sf::Vector2f(20, 20));
    wall.setRotation(-90); // absolute angle
    wall.setTextureRect(sf::IntRect(0, 0, 60, 250));
    texture_wall.setRepeated(true);
    walls.push_back(wall);

    //wall_5;
    wall.setTexture(texture_wall);
    wall.setScale(0.6, 0.6);
    wall.setPosition(sf::Vector2f(550, 350)); // absolute position
    wall.move(sf::Vector2f(20, 20));
    wall.setRotation(-90); // absolute angle
    wall.setTextureRect(sf::IntRect(0, 0, 60, 250));
    texture_wall.setRepeated(true);
    walls.push_back(wall);

    //wall_6;
    wall.setTexture(texture_wall);
    wall.setScale(0.6, 0.6);
    wall.setPosition(sf::Vector2f(300, 450)); // absolute position
    wall.move(sf::Vector2f(20, 20));
    wall.setRotation(-90); // absolute angle
    wall.setTextureRect(sf::IntRect(0, 0, 60, 250));
    texture_wall.setRepeated(true);
    walls.push_back(wall);

    //wall_7;
    wall.setTexture(texture_wall);
    wall.setScale(0.6, 0.6);
    wall.setPosition(sf::Vector2f(220, 100)); // absolute position
    wall.move(sf::Vector2f(20, 20));
    wall.setRotation(-90); // absolute angle
    wall.setTextureRect(sf::IntRect(0, 0, 60, 500));
    texture_wall.setRepeated(true);
    walls.push_back(wall);

    sf::Clock clock;

  sf::FloatRect nextPos;


    // run the program as long as the window is open
    while (window.isOpen()) {

        sf::Time elapsed = clock.restart();

        hero.setTextureRect(sf::IntRect(50, 0, 50, 37));
        hero.setScale(1.5,1.5);

                sf::Event event;
        while (window.pollEvent(event)) {

            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }


              //hero Movement
        sf::Keyboard::Key pressed;
          if(event.type == sf::Event::KeyPressed){
                   pressed = event.key.code;
                   velocity.y = -10;
                   if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
                              velocity.x = -5;
                          else if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
                              velocity.x = 5;

          //collision
          for(auto &wall : walls) {
             sf::FloatRect heroBounds = hero.getGlobalBounds();
             sf::FloatRect wallBounds = wall.getGlobalBounds();
             nextPos = heroBounds;
             nextPos.left += velocity.x;
             nextPos.top += velocity.y;

             if(wallBounds.intersects(nextPos)){

                 //Bottom Collision
                 if(heroBounds.top < wallBounds.top
                   && heroBounds.top  + heroBounds.height < wallBounds.top  + wallBounds.height
                   && heroBounds.left < wallBounds.left + wallBounds.width
                   && heroBounds.left + heroBounds.width > wallBounds.left){

                     velocity.y = 0.f;
                     hero.setPosition(heroBounds.left, wallBounds.top - heroBounds.height);

                         }

                 //Top Collision
                   else if(heroBounds.top > wallBounds.top
                           && heroBounds.top  + heroBounds.height > wallBounds.top  + wallBounds.height
                           && heroBounds.left < wallBounds.left + wallBounds.width
                           && heroBounds.left + heroBounds.width > wallBounds.left){

                     velocity.y = 0.f;
                    hero.setPosition(heroBounds.left, wallBounds.top + wallBounds.height);

                        }

                 //Right Collision
                  if(heroBounds.left < wallBounds.left
                   && heroBounds.left + heroBounds.width < wallBounds.left + wallBounds.width
                   && heroBounds.top < wallBounds.top + wallBounds.height
                   && heroBounds.top + heroBounds.height > wallBounds.top){

                     velocity.x = 0.f;
                    hero.setPosition(wallBounds.left - heroBounds.width, heroBounds.top);

                    }

                 //Left Collision
                   else if(heroBounds.left > wallBounds.left
                   && heroBounds.left + heroBounds.width > wallBounds.left + wallBounds.width
                   && heroBounds.top < wallBounds.top + wallBounds.height
                   && heroBounds.top + heroBounds.height > wallBounds.top){

                     velocity.x = 0.f;
                    hero.setPosition(wallBounds.left + wallBounds.width, heroBounds.top);

                        }

                 }
              hero.animate(elapsed);
              hero.moveInDirection(elapsed,pressed);
              hero.updateMovement();
            }
            }
       // clear the window with black color
         window.clear(sf::Color::Black);

         window.draw(sprite);
           for(auto &s : walls) {
             window.draw(s);
         }
         window.draw( hero);
        // end the current frame
        window.display();
    }

    return 0;
}
