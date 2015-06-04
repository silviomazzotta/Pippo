/*
 * PallinaSprite.cpp
 *
 *  Created on: 19/nov/2014
 *      Author: XPIN12
 */

#include "Uccello.h"
#include "GlobalVariable.h"
USING_NS_CC;


bool Uccello::initWithFile(const std::string& filename) {
    return cocos2d::Sprite::initWithFile(filename);
}

Uccello::~Uccello() {
}
Uccello::Uccello() {
}


//come create in Sprite
Uccello* Uccello::uccelloSpriteWithFile(const std::string& filename) {
	cocos2d::log("Uccello::uccelloSpriteWithFile .....");
    auto sprite = new Uccello();
    if (sprite && sprite->initWithFile(filename)) {
	    sprite->setVisible(false);
	    sprite->setColpito(false);
	    sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


void Uccello::aggiungiPallina(const std::string& filename){
	 Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	
	_pallina = Sprite::create(filename);
	this->addChild(_pallina, 5);
	_pallina->setAnchorPoint(Vec2(0,0));
	_pallina->setPosition(Vec2(0,0));
	_pallina->setVisible(false);

	
}
void Uccello::aggiungiPallina(Sprite * node){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	cocos2d::log("Uccello::aggiungiPallina .....");

	this->addChild(node, 5);
	node->setAnchorPoint(Vec2(0,0));
	node->setPosition(Vec2(this->getContentSize().width*0.2,-node->getContentSize().height*0.85));


}

void Uccello::faiVolare (){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto moveToTargetPosition = MoveTo::create(1, Vec2(0,0));


	    this->runAction(
	                       Sequence::create(moveToTargetPosition,
	                                        CallFuncN::create(CC_CALLBACK_1(Uccello::setInvisible, this)),
	                                        NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
	                       );


}

void Uccello::faiCaderePallina(Node * node){
	
	//rendo invisibile la pallina che ha  uccello
	//ne creo altra che ha un move to verso sotto
	_pallina->setVisible(false);
	
	//creo nuova pallina che cade
	auto pallinaCheCade = Sprite::create("pallinaUccello.png");
	pallinaCheCade->setPosition(_pallina->getPosition());
	node->addChild(pallinaCheCade, 15);
	
	
    auto moveToTargetPosition = MoveTo::create(1, Vec2(0,0));

    
    pallinaCheCade->runAction(
                       Sequence::create(moveToTargetPosition,
                                        CallFuncN::create(CC_CALLBACK_1(Uccello::setInvisible, this)),
                                        NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
                       );
	

}

void Uccello::muovi(){
	   Size visibleSize = Director::getInstance()->getVisibleSize();
	    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	  //TODO fare la y random
	    float minY = visibleSize.height / 6;
	    float maxY = visibleSize.height;
	    float rangeY = maxY - minY;
	    float randomY = (float)(arc4random() % (int)rangeY) + minY;



	    this->setPosition(Vec2(visibleSize.width + origin.x, randomY));
	    this->setVisible(true);

	    Vec2 targetPosition = Vec2(origin.x,randomY );

	    float minDuration = 2.0;
	    float maxDuration = 4.0;

	    float rangeDuration = maxDuration - minDuration;
	    float randomDuration = (float)(arc4random() % (int)rangeDuration) + minDuration;

	

	    auto moveToTargetPosition = MoveTo::create(randomDuration, targetPosition);

    
         this->runAction(
                       Sequence::create(moveToTargetPosition,
                                        CallFuncN::create(CC_CALLBACK_1(Uccello::setInvisible, this)),
                                        NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
                       );
	

}


void Uccello::muoviSinistraDestraInAlto(){
	    Size visibleSize = Director::getInstance()->getVisibleSize();
	    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	  //TODO fare la y random
	    float minY = visibleSize.height * 0.7;
	    float maxY = visibleSize.height* 0.9;
	    float rangeY = maxY - minY;
	    float randomY = (float)(arc4random() % (int)rangeY) + minY;


        //posiziono a sinistra con y random
	    this->setPosition(Vec2(visibleSize.width + origin.x, randomY));
	    this->setVisible(true);

	    Vec2 targetPosition = Vec2(origin.x,randomY );

	    float minDuration = 2.0;
	    float maxDuration = 4.0;

	    float rangeDuration = maxDuration - minDuration;
	    float randomDuration = (float)(arc4random() % (int)rangeDuration) + minDuration;



	    auto moveToTargetPosition = MoveTo::create(randomDuration, targetPosition);
        this->runAction(
                    Sequence::create(moveToTargetPosition,
                                     CallFuncN::create(CC_CALLBACK_1(Uccello::setInvisible, this)),
                                     NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
                    );


}


void Uccello::muoviLeAli(){

	Size designSize = Size(480,320);
	Size resourceSize = Size(960,640);
	float ratio_scale = resourceSize.width / designSize.width ;

	    Vector<SpriteFrame*> uccelloFrames(3);
		char str[100] = {0};
		for(int i = 3; i < 6 ;i++)
		{
			//sprintf(str, "Images/grossini_dance_%02d.png",i);
			sprintf(str, "nemico_%02d.png",i);
			auto frame = SpriteFrame::create(str,Rect(0,0,width_uccello/ratio_scale,heigth_uccello/ratio_scale));  //we assume that the sprites' dimentions are 40*40 rectangles.
		     uccelloFrames.pushBack(frame);
		}

		auto animationUcc = Animation::createWithSpriteFrames(uccelloFrames, 0.2f);

		this->runAction( RepeatForever::create( Animate::create(animationUcc) ) );

}
void Uccello::setInvisible(Node * node) {
    node->setVisible(false);
}
