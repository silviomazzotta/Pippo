//
//  GameSceneDue.h
//  gugut
//
//  Created by silviomaz on 06/01/15.
//
//

#ifndef __gugut__GameSceneDue__
#define __gugut__GameSceneDue__

#include <stdio.h>

#include <stdio.h>

#include "cocos2d.h"
#include "PallinaSprite.h"

using namespace cocos2d;

class GameSceneDue : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();
    
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameSceneDue);
    
    void onTouchMoved(Touch*, Event*);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    bool onContactBegin( cocos2d::PhysicsContact &contact );
    
    void setInvisible(Node * node);
    
    void addPalline (float dt);

    void addPartcleStella(Vec2 posizione) ;

    
private:
    Size _visibleSize;
    Vec2 _origin;

    cocos2d::PhysicsWorld *sceneWorld;
    

    void SetPhysicsWorld( cocos2d::PhysicsWorld *world ) { sceneWorld = world; };
    
    
    CCSprite * _player;
    
    
    Sprite *_gugutAnimato;
    
    Sprite *_muro;
    
    
    Vector<Sprite*> *_pietre;
    int _nextPietra=0;
    
    Vector<PallinaSprite*> *_palline;
    int _nextPallina=0;


    ParticleSystem *_boom;
    ParticleSystem * _emitter;

};



#endif /* defined(__gugut__GameSceneDue__) */
