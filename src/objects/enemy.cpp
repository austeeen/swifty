#include "enemy.hpp"

Enemy::Enemy(const GameObjectAsset ast):
    KinematicObject(ast)
{}
void Enemy::setUp()
{
    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->build();
    }

    this->cmpnt<Animator>()->setState(cur_state);
    this->cmpnt<Physics2D>()->setState(cur_state);

    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->setUp();
    }
}
void Enemy::update(const float dt)
{
    this->cmpnt<Animator>()->update(dt);
    this->cmpnt<Physics2D>()->update(dt);
}
void Enemy::lateUpdate()
{
    ObjectState next = this->cmpnt<Physics2D>()->nextState();
    if (next != cur_state) {
        cur_state = next;
        this->cmpnt<Animator>()->setState(cur_state);
        this->cmpnt<Physics2D>()->setState(cur_state);
    }
}
void Enemy::render(sf::RenderWindow &window)
{
    for (auto [cmpnt_t, cmpnt] : cmpts) {
        cmpnt->render(window);
    }
}
