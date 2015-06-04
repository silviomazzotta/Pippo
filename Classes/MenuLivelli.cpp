/*
 * MenuLivelli.cpp
 *
 *  Created on: 23/feb/2015
 *      Author: XPIN12
 */


#include "MenuLivelli.h"

#include "SecondaScene.h"
#include "TerzaScene.h"
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
//#include "Utility.h"

std::string PNG_SCENA_1 = "sfondo260_173_uno.png";
std::string PNG_SCENA_2 = "sfondo260_173_due.png";
std::string PNG_SCENA_3 = "sfondo260_173_tre.png";
std::string PNG_LUCCHETT_ON = "lucchetto_on.png";
std::string PNG_LUCCHETT_OF = "lucchetto_of.png";



 Sprite* creareSprite(Color3B colore,Vec2 posizione,Size dimensione ,bool visibilita ){
	 Sprite *temp = Sprite::create("unpixel.png");
	 	 temp->setTextureRect(CCRectMake(0,0, dimensione.width * 0.80, dimensione.height * 0.8));
	 	 temp->setColor(colore);
	 	 temp->setVisible(visibilita);
	 	 temp->setPosition(posizione);
	 return temp ;

 }
MenuLivelli::MenuLivelli()
{
    int PLAYER_LEVEL = 1;

	visibleSize = CCDirector::sharedDirector()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto schena_1 = MenuItemImage::create(
    										PNG_SCENA_1,
    										PNG_SCENA_1,
                                           CC_CALLBACK_1(MenuLivelli::startScena_1, this));

   // schena_1->setPosition(Vec2(origin.x + visibleSize.width/4,
    //		 origin.y + visibleSize.height*0.5));
    float position_1 = 80 ;
    schena_1->setPosition(Vec2(position_1 ,  origin.y + visibleSize.height/2));
    auto menu_schena_1 = Menu::create(schena_1, NULL);
   // menu_schena_1->setPosition(Vec2(origin.x + 90.00 ,
	//            origin.y + visibleSize.height*0.5));
    menu_schena_1->setPosition(Vec2::ZERO);
    this->addChild(menu_schena_1, 11);

    float dim_PNG_SCENA = menu_schena_1->getContentSize().width;


    // LUCCHETTO  1

    auto lucchetto_1 = Sprite::create(PNG_LUCCHETT_ON);
    this->addChild(lucchetto_1, 12);
	lucchetto_1->setAnchorPoint(Vec2(0,0));
	lucchetto_1->setPosition(Vec2(position_1 ,  origin.y + visibleSize.height/2));

    // FINE LCCH


    //  SCENA 2


    auto schena_2 = MenuItemImage::create(
    										PNG_SCENA_2,
    										PNG_SCENA_2,
                                           CC_CALLBACK_1(MenuLivelli::startScena_2, this));

    schena_2->setPosition(Vec2(origin.x+visibleSize.width/2 ,  origin.y + visibleSize.height/2));

    auto menu_schena_2 = Menu::create(schena_2, NULL);
    menu_schena_2->setPosition(Vec2::ZERO);
    this->addChild(menu_schena_2, 11);



    if( PLAYER_LEVEL = 2 or PLAYER_LEVEL = 3 ){
        auto lucchetto_2 = Sprite::create(PNG_LUCCHETT_ON);

	else{
        auto lucchetto_2 = Sprite::create(PNG_LUCCHETT_OF);
     }
	this->addChild(lucchetto_2, 12);
	lucchetto_2->setAnchorPoint(Vec2(0,0));
	lucchetto_2->setPosition(Vec2(origin.x+visibleSize.width/2 ,  origin.y + visibleSize.height/2));


    //  SCENA 3


    auto schena_3 = MenuItemImage::create(
    										PNG_SCENA_3,
    										PNG_SCENA_3,
                                           CC_CALLBACK_1(MenuLivelli::startScena_3, this));
    float position_3 = 400 ;

    schena_3->setPosition(Vec2(position_3 ,  origin.y + visibleSize.height/2));

    auto menu_schena_3 = Menu::create(schena_3, NULL);
     menu_schena_3->setPosition(Vec2::ZERO);
    this->addChild(menu_schena_3, 11);



    if(  PLAYER_LEVEL = 3 ){
        auto lucchetto_3 = Sprite::create(PNG_LUCCHETT_ON);

	else{
        auto lucchetto_3 = Sprite::create(PNG_LUCCHETT_OF);
     }
	this->addChild(lucchetto_3, 12);
	lucchetto_3->setAnchorPoint(Vec2(0,0));
	lucchetto_3->setPosition(Vec2(position_3 ,  origin.y + visibleSize.height/2));


}

MenuLivelli::~MenuLivelli(void)
{

}

void MenuLivelli::pauseGame(CCObject* pSender)
{
/*	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pop.wav");

	HelloWorld* helloWorld = (HelloWorld*)this->getParent();

	if(!helloWorld->projectileLayer->gameOver)
	{
		pauseMenu->setTouchEnabled(false);

		CCMenuItemImage* resumeItem = CCMenuItemImage::create("_bookgame_UI__resume.png",
														  "_bookgame_UI__resume.png", this,
														  menu_selector(MenuLivelli::resumeGame));

		resumeItem->setPosition(ccp(visibleSize.width * 0.5 ,
								visibleSize.height* 0.5));


		resumeMenu = CCMenu::create(resumeItem, NULL);
		resumeMenu->setPosition(CCPointZero);
		this->addChild(resumeMenu);

		helloWorld->gamePaused();
	}

 */
}

void MenuLivelli::resumeGame(CCObject* pSender)
{
	/*CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pop.wav");

	pauseMenu->setTouchEnabled(true);
	this->removeChild(resumeMenu);

	HelloWorld* helloWorld = (HelloWorld*)this->getParent();
	helloWorld->gameResumed();
     */
}

void MenuLivelli::updateScore(int score)
{
	char scoreTxt[100];
	//sprintf(scoreTxt, "Score: %d", score);
	sprintf(scoreTxt, "%d", score);
	scoreLabel->setString(scoreTxt);
}


void MenuLivelli::setupGameOver()
{
    bool VISIBILITA = false;
   // Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    _background_menu = Sprite::create("unpixel.png");
    _background_menu->setTextureRect(CCRectMake(0,0, visibleSize.width * 0.80, visibleSize.height * 0.8));
    _background_menu->setColor(ccc3(255,255, 0));
    _background_menu->setPosition(Vec2(origin.x + visibleSize.width/2,
                                       origin.y + visibleSize.height/2 ));



    _background_menu->setOpacity(0);
    this->addChild(_background_menu, 37);




    auto puntiRealizzati = Label::createWithBMFont("fonts/futura-48.fnt", "Restart Game");

    auto restartLabel = Label::createWithBMFont("fonts/futura-48.fnt", "Restart Game");
	auto restartItem = MenuItemLabel::create(restartLabel, CC_CALLBACK_1(MenuLivelli::restartTapped, this));
	//restartItem->setScale(0.1F);

	_menuRestart = Menu::create(restartItem, NULL);
	_menuRestart->setPosition(Vec2(origin.x + visibleSize.width/2 ,
	            origin.y + visibleSize.height*0.3));



	_menuRestart->setVisible(VISIBILITA);
		this->addChild(_menuRestart, 47);




}

void MenuLivelli::restartTapped(Ref* pSender) {
//	Director::getInstance()->replaceScene
//			(TransitionZoomFlipX::create(0.5, ScrollerTest::createScene()));
	// reschedule
	//this->scheduleUpdate();

 //  auto scene = GameScene::createScene();

  //  Director::getInstance( )->replaceScene( TransitionFade::create( 0.5, scene ) );
  //   scene->scheduleUpdate();

}

void MenuLivelli::faiVedereEndGameMenu(){

	_background_menu->setVisible(true);
	_menuRestart->setVisible(true);
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto totolal_point = Label::createWithBMFont("fonts/font-issue1343.fnt", "");
	totolal_point->setPosition(Vec2(origin.x + (visibleSize.width/2) ,
	 	            origin.y + visibleSize.height*0.7 ));

	char scoreTxt[100];
	//sprintf(scoreTxt, "Score: %d", score);
	sprintf(scoreTxt, "Score : %d", _score);
	totolal_point->setString(scoreTxt);

	 this->addChild(totolal_point, 97);

	 //***************     START RECORD    ******************************
	 auto label_Record = Label::createWithBMFont("fonts/font-issue1343.fnt", "");
	 	  label_Record->setPosition(Vec2(origin.x + (visibleSize.width/2) ,
	 	 	            origin.y + visibleSize.height*0.5 ));
	 this->addChild(label_Record, 97);

	 int record = CCUserDefault::sharedUserDefault( )->getIntegerForKey( "RECORD" );
	 //if((record == nullptr) || (_score>record) ){
	 if(_score>record) {
	    record =_score;
	    CCUserDefault::sharedUserDefault()->setIntegerForKey("RECORD",record);

	    CCUserDefault::sharedUserDefault()->flush();
	 }
	 std::ostringstream value;
	 value << record;
	 label_Record->setString("Record : "+value.str());
	 //***************     END RECORD    ******************************

	 scoreLabel->setVisible(false);
}

void MenuLivelli::setScore(int score){

  _score = score;
}


//Vado alla scena 1
void MenuLivelli::startScena_1(Ref* pSender) {
   auto scene = HelloWorld::createScene();

    Director::getInstance( )->replaceScene( TransitionFade::create( 0.5, scene ) );
     scene->scheduleUpdate();

}

void MenuLivelli::startScena_2(Ref* pSender) {
   auto scene = SecondaScene::createScene();

    Director::getInstance( )->replaceScene( TransitionFade::create( 0.5, scene ) );
     scene->scheduleUpdate();

}

void MenuLivelli::startScena_3(Ref* pSender) {
   auto scene = TerzaScene::createScene();

    Director::getInstance( )->replaceScene( TransitionFade::create( 0.5, scene ) );
     scene->scheduleUpdate();

}



