#include "MenuScene.h"
#include "GlobalVariable.h"
#include "SimpleAudioEngine.h"
#include "Uccello.h"
#include "Gugo.h"
#include "MenuLivelli.h"

USING_NS_CC;



// ***********  REGOLE GIOCO  **********
// in base allo score cambio il livelli
/*
1     -  1000 - LIVELLO1 --> solo palline e uccello
1000  -  1500 - LIVELLO2 --> ogni tanto una pallina obbliqua
2000  -  2500 - LIVELLO3 --> aggiungo Gugo


*/



Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }


    //   T getRandomObject() const
    //NOMI_SFONDO_VECTOR.push_back("montagna_4.png")

    // Posso fare così per lo sfondo
    //auto background = LayerColor::create(Color4B(40,40,40,255));
    //addChild(background);

    glClearColor(randomValueBetween(0.0, 0.1),randomValueBetween(0.4, 0.7),randomValueBetween(0.7, 1.0),randomValueBetween(0.5, 1.0));
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _screenSize = Director::getInstance()->getWinSize();


    //aggingo il menu
    auto menu_scene = new MenuLivelli();
    this->addChild(menu_scene, 100);


    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.








    return true;
}



void MenuScene::setInvisible(Node * node) {
    node->setVisible(false);
}


void MenuScene::update (float dt) {

}


//stoppo il game e mostro messaggio






MenuScene::~MenuScene()
{

}
void MenuScene::animationDone(Node *node)
{
    node->stopAllActions();
}

float MenuScene::randomValueBetween(float low, float high)
{
    return (((float) random() / 0xFFFFFFFFu) * (high - low)) + low;
}


