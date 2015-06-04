#ifndef __MENU_SCENE_H__
#define __MENU_SCENE_H__

#include "cocos2d.h"
#include "PallinaSprite.h"
#include "Uccello.h"
#include "GlobalVariable.h"
#include "Gugo.h"

using namespace cocos2d;


class MenuScene : public cocos2d::Layer
{
	//End game
    Sprite *_background_menu;
    Sprite *_gameover;
    Label *_labelRecord;
    Menu *_menuRestart;

    int _score;
    int _lives=ext_pietre_disposizione;
    Size _screenSize;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();


    // implement the "static create()" method manually
    CREATE_FUNC(MenuScene);

    void setInvisible(Node * node);
    void update (float dt) ;

    float randomValueBetween(float low, float high);
    void animationDone(Node *node);
    virtual ~MenuScene();


};

#endif // __HELLOWORLD_SCENE_H__
