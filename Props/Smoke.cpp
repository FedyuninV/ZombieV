#include "Smoke.hpp"
#include "../GameWorld.hpp"
#include "../GameRender.hpp"

size_t Smoke::_textureID;

void Smoke::init()
{
    _textureID = GameRender::registerTexture("data/textures/smoke2.png");
}

Smoke::Smoke() :
    _vertexArray(sf::Quads, 4)
{
    _needsPhysics = false;
}

Smoke::Smoke(Vec2 pos, Vec2 vel, float angularVel, float size) :
    _ratio(0.0f),
    _ratioSpeed(4.0f),
    _size(size),
    _angularVelocity(angularVel),
    _velocity(vel),
    _isDone(false),
    _vertexArray(sf::Quads, 4)
{
    _body.setPosition(pos);
    _needsPhysics = false;

    float a(rand()%3600/10.0f);
    _angle = a*DEGRAD;
}

void Smoke::update(GameWorld& world)
{
    _ratio += _ratioSpeed*DT;
    _ratio =  _ratio>1.0f?1.0f:_ratio;
    _angle += _angularVelocity*(1.0f-_ratio);
    _body.move2D(_velocity);

    _isDone = _ratio>1.0f;
}

void Smoke::render()
{
    float ratio = _ratio+0.25;
    float sx   = ratio*_size*cos(_angle);
    float sy   = ratio*_size*sin(_angle);

    Vec2 coord(_body.getPosition());
    float x = coord.x;
    float y = coord.y;

    sf::Color color(50, 50, 50, (1.0f-_ratio)*200.0f);

    _vertexArray[0] = sf::Vertex(sf::Vector2f(x+sx, y+sy), color, sf::Vector2f(0 , 0));
    _vertexArray[1] = sf::Vertex(sf::Vector2f(x+sy, y-sx), color, sf::Vector2f(256, 0));
    _vertexArray[2] = sf::Vertex(sf::Vector2f(x-sx, y-sy), color, sf::Vector2f(256, 256));
    _vertexArray[3] = sf::Vertex(sf::Vector2f(x-sy, y+sx), color, sf::Vector2f(0  , 256));

    GameRender::addQuad(_textureID, _vertexArray, RenderLayer::RENDER);
}
