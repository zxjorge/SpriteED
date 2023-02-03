#include <iostream>
class Cat
{
private:
    int lives{9};

public:
    Cat(int startLives) : lives(startLives) { }

    void reportLives(){
        std::cout << "The cat has "<< lives << " lives.\n";
    }

    void loseLife(){
        lives--;
    }

    Cat& operator +=(int cat_lives){
        this->lives = this->lives + cat_lives;
        return *this;
    }
};

int main()
{
    Cat kitty(10);
    kitty.reportLives();
    kitty.loseLife();
    kitty.reportLives();
    (kitty += 1) += 3;
    kitty.reportLives();

}