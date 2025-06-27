//#include "Renderer.hpp"
//
//void Renderer::render(sf::RenderWindow& window, Map& map)
//{
//    const float tileSize = 10.0f;
//    sf::RectangleShape rect(sf::Vector2f(tileSize, tileSize));
//
//    for (unsigned int y = 0; y < map.getHeight(); ++y)
//    {
//        for (unsigned int x = 0; x < map.getWidth(); ++x)
//        {
//            int tileValue = map.getTile(x, y);
//
//            if (tileValue == 0)
//                rect.setFillColor(sf::Color::White);
//            else
//                rect.setFillColor(sf::Color::Black);
//
//            rect.setPosition(sf::Vector2f(x * tileSize, y * tileSize));
//            window.draw(rect);
//        }
//    }
//}
