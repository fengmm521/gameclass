//
//  GameTest.cpp
//  game3
//
//  Created by 俊盟科技1 on 10/20/14.
//
//

#include "GameTest.h"
#include "strHash.h"
using namespace cocos2d;
// on "init" you need to initialize your instance
bool GameTest::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    do
    {
        tmap = TMXTiledMap::create("test/AStarTestMap.tmx");
        tmap->setPosition(Point());
        this->addChild(tmap);
        
        TMXMapInfo* mapinfo = TMXMapInfo::create("test/AStarTestMap.tmx");
        
         ValueMapIntKey tiledatMap =  mapinfo->getTileProperties();
        
        TMXLayer* layer = tmap->getLayer("ob");
        Sprite* tilsp = layer->getTileAt(cocos2d::Vec2(8,11));
       //TMXTilesetInfo* tileInfo = layer->getTileSet();
        int Gid = layer->getTileGIDAt(Vec2(8,11));
        
        ValueMap gidStrMap = tiledatMap[Gid].asValueMap();
        
        tilsp->setColor(Color3B(123,123,123));
        //this->addChild(tilsp,1);
        
        log("Gid = %d,cast = %d",Gid,gidStrMap["cast"].asInt());

    }while (0);
    return true;
}


void GameTest::onExit()
{
    
    Layer::onExit();
}
void GameTest::onEnter()
{
    Layer::onEnter();
    
}
