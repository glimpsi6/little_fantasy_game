#include "World/Collisions.h"
#include "Entities/Character.h"

static void projectPolygon(const std::vector<sf::Vector2f>& verts,
                           sf::Vector2f axis,
                           float& min, float& max)
{
    min = max = verts[0].x * axis.x + verts[0].y * axis.y;
    for (size_t i = 1; i < verts.size(); ++i) {
        float p = verts[i].x * axis.x + verts[i].y * axis.y;
        min = std::min(min, p);
        max = std::max(max, p);
    }
}

static std::array<sf::Vector2f, 4> aabbToVerts(const sf::FloatRect& hb)
{
    return {{
        {hb.left,             hb.top},
        {hb.left + hb.width,  hb.top},
        {hb.left + hb.width,  hb.top + hb.height},
        {hb.left,             hb.top + hb.height}
    }};
}

// возвращает true если есть пересечение; normal — ось выталкивания, depth — глубина
static bool satPolygonAABB(const std::vector<sf::Vector2f>& poly,
                           const sf::FloatRect& hb,
                           sf::Vector2f& outNormal, float& outDepth)
{
    auto boxArr = aabbToVerts(hb);
    std::vector<sf::Vector2f> box(boxArr.begin(), boxArr.end());

    float minDepth = std::numeric_limits<float>::max();
    sf::Vector2f bestAxis{};

    auto testAxis = [&](sf::Vector2f axis) -> bool {
        float len = std::sqrt(axis.x * axis.x + axis.y * axis.y);
        if (len < 1e-6f) return true; // пропускаем вырожденную ось
        axis.x /= len; axis.y /= len;

        float minA, maxA, minB, maxB;
        projectPolygon(poly, axis, minA, maxA);
        projectPolygon(box,  axis, minB, maxB);

        if (maxA < minB || maxB < minA) return false; // разделяющая ось

        float depth = std::min(maxA - minB, maxB - minA);
        if (depth < minDepth) {
            minDepth = depth;
            float centerPoly = (minA + maxA) * 0.5f;
            float centerBox  = (minB + maxB) * 0.5f;
            bestAxis = (centerBox > centerPoly) ? axis : sf::Vector2f{-axis.x, -axis.y};
        }
        return true;
    };

    // оси полигона
    for (size_t i = 0; i < poly.size(); ++i) {
        sf::Vector2f a = poly[i];
        sf::Vector2f b = poly[(i + 1) % poly.size()];
        sf::Vector2f edge{ b.x - a.x, b.y - a.y };
        sf::Vector2f axis{ -edge.y, edge.x };
        if (!testAxis(axis)) return false;
    }

    // оси AABB
    if (!testAxis({1.f, 0.f})) return false;
    if (!testAxis({0.f, 1.f})) return false;

    outNormal = bestAxis;
    outDepth  = minDepth;
    return true;
}


void Collisions::interactionWithMap(Character& ch)
{ 
    // Обработка объектов карты
    for (const auto& col : _map.getColiders()) {
        ch.setCoord(ch.getCoord()); 
        auto hb = ch.getHitbox();
        if (!hb.intersects(col.bounds)) continue;

        if (col.isPolygon) {
            sf::Vector2f normal{};
            float depth = 0.f;
            if (satPolygonAABB(col.points, hb, normal, depth)) {
                ch.getCoord().x += normal.x * depth;
                ch.getCoord().y += normal.y * depth;
            }
        } else {
            float overlapLeft   = (hb.left + hb.width)  - col.bounds.left;
            float overlapRight  = (col.bounds.left + col.bounds.width) - hb.left;
            float overlapTop    = (hb.top  + hb.height) - col.bounds.top;
            float overlapBottom = (col.bounds.top + col.bounds.height) - hb.top;

            float minX = std::min(overlapLeft, overlapRight);
            float minY = std::min(overlapTop,  overlapBottom);

            if (minX < minY) {
                if (overlapLeft < overlapRight) ch.getCoord().x -= overlapLeft;
                else                            ch.getCoord().x += overlapRight;
            } else {
                if (overlapTop < overlapBottom) ch.getCoord().y -= overlapTop;
                else                            ch.getCoord().y += overlapBottom;
            }
        }
        hb = ch.getHitbox();
    }

    // Обработка столкновений с нпс
    for (size_t i = 0; i < _map.getEntities().size(); i++) {
        if(&ch == _map.getEntities()[i].get()) continue;

        Coordinates npcCoord = _map.getEntities()[i]->getCoord();
        int npcH = _map.getEntities()[i]->getHeight();
        int npcW = _map.getEntities()[i]->getWidth();
 
        // Проверяем пересечение
        bool overlapX = (ch.getCoord().x < npcCoord.x + npcW) && (ch.getCoord().x + ch.getWidth() > npcCoord.x);
        bool overlapY = (ch.getCoord().y < npcCoord.y + npcH) && (ch.getCoord().y + ch.getHeight() > npcCoord.y);
        
        if (overlapX && overlapY)
        {
            float overlapLeft   = (ch.getCoord().x + ch.getWidth()) - npcCoord.x;
            float overlapRight  = (npcCoord.x + npcW) - ch.getCoord().x;
            float overlapTop    = (ch.getCoord().y + ch.getHeight()) - npcCoord.y;
            float overlapBottom = (npcCoord.y + npcH) - ch.getCoord().y;

            float minX = std::min(overlapLeft, overlapRight);
            float minY = std::min(overlapTop,  overlapBottom);

            if (minX < minY) {
                if (overlapLeft < overlapRight) ch.getCoord().x -= overlapLeft;
                else                            ch.getCoord().x += overlapRight;
            } else {
                if (overlapTop < overlapBottom) ch.getCoord().y -= overlapTop;
                else                            ch.getCoord().y += overlapBottom;
            }
        }
    }
}

//todo по логике надо в другое место или сделать из класса менеджера обработки карт
void Collisions::interactionPlayerWithNPC(Character& ch)
{
    for (size_t i = 0; i < _map.getEntities().size(); i++)
    {
        if(&ch == _map.getEntities()[i].get()) continue;

        Coordinates npcCoord = _map.getEntities()[i]->getCoord();
        int npcH = _map.getEntities()[i]->getHeight();
        int npcW = _map.getEntities()[i]->getWidth();

        float npc_center_x = npcCoord.x + npcW / 2;
        float npc_center_y = npcCoord.y + npcH / 2;

        float ch_center_x = ch.getCoord().x + ch.getWidth() / 2;
        float ch_center_y = ch.getCoord().y + ch.getHeight() / 2;

        if( (ch_center_x - npc_center_x < radius && npc_center_x - ch_center_x < radius) &
            (ch_center_y - npc_center_y < radius && npc_center_y - ch_center_y < radius)) {
            _map.getEntities()[i]->setEIcon(true);
        } else {
            _map.getEntities()[i]->setEIcon(false);
        }
    }
}