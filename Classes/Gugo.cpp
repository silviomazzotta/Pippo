/*
 * Gugo.cpp
 *
 *  Created on: 15/gen/2015
 *      Author: XPIN12
 */

#include "Gugo.h"

#include "GlobalVariable.h"
USING_NS_CC;


bool Gugo::initWithFile(const std::string& filename) {
    return cocos2d::Sprite::initWithFile(filename);
}

Gugo::~Gugo() {
}

Gugo::Gugo() {
	  _visibleSize = Director::getInstance()->getVisibleSize();
		_origin = Director::getInstance()->getVisibleOrigin();
}



//come create in Sprite
Gugo* Gugo::gugoSpriteWithFile(const std::string& filename) {
	cocos2d::log("Gugo::GugoSpriteWithFile .....");
    auto sprite = new Gugo();
    if (sprite && sprite->initWithFile(filename)) {
	    sprite->setVisible(false);
	    sprite->setColpito(false);
	    sprite->autorelease();

        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}


void Gugo::aggiungiPallina(const std::string& filename){
	 Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	_pallina = Sprite::create(filename);
	this->addChild(_pallina, 5);
	_pallina->setAnchorPoint(Vec2(0,0));
	_pallina->setPosition(Vec2(0,0));
	_pallina->setVisible(false);


}
void Gugo::aggiungiPallina(Sprite * node){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	cocos2d::log("Gugo::aggiungiPallina .....");

	this->addChild(node, 5);
	node->setAnchorPoint(Vec2(0,0));
	node->setPosition(Vec2(this->getContentSize().width*0.2,-node->getContentSize().height*0.85));


}

void Gugo::faiVolare (){
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
	auto moveToTargetPosition = MoveTo::create(1, Vec2(0,0));


	    this->runAction(
	                       Sequence::create(moveToTargetPosition,
	                                        CallFuncN::create(CC_CALLBACK_1(Gugo::setInvisible, this)),
	                                        NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
	                       );


}

void Gugo::faiCaderePallina(Node * node){

	//rendo invisibile la pallina che ha  Gugo
	//ne creo altra che ha un move to verso sotto
	_pallina->setVisible(false);

	//creo nuova pallina che cade
	auto pallinaCheCade = Sprite::create("pallinaUccello.png");
	pallinaCheCade->setPosition(_pallina->getPosition());
	node->addChild(pallinaCheCade, 15);


    auto moveToTargetPosition = MoveTo::create(1, Vec2(0,0));


    pallinaCheCade->runAction(
                       Sequence::create(moveToTargetPosition,
                                        CallFuncN::create(CC_CALLBACK_1(Gugo::setInvisible, this)),
                                        NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
                       );


}

void Gugo::muovi(){
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
                                        CallFuncN::create(CC_CALLBACK_1(Gugo::setInvisible, this)),
                                        NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
                       );


}

//da sopra a meta schermo e poi risale
void Gugo::muoviSopraSotto(){


        float minXGugoSopra = 0.5;
	    float maxXGugoSopra = 0.8;
        float rangeXGugo = maxXGugoSopra - minXGugoSopra;
	    float randomXGugo = (float)(arc4random() % (int)rangeXGugo) + minXGugoSopra;

        this->setPosition(Vec2(_visibleSize.width*randomXGugo+ _origin.x, _visibleSize.height + 280+ _origin.y));
	    this->setVisible(true);
	    Vec2 targetPositionScende = (Vec2(_visibleSize.width*randomXGugo + _origin.x, _visibleSize.height*0.7 + _origin.y));

	    Vec2 targetPositionSale = (Vec2(_visibleSize.width*randomXGugo + _origin.x, _visibleSize.height +_origin.y+ 280));

	    float minDuration = 2.0;
	    float maxDuration = 4.0;

	    float rangeDuration = maxDuration - minDuration;
	    float randomDuration = (float)(arc4random() % (int)rangeDuration) + minDuration;

	    auto moveToPositionScende = MoveTo::create(randomDuration, targetPositionScende);

	    auto moveToPositionRisale = MoveTo::create(randomDuration, targetPositionSale);
        this->runAction(
                Sequence::create(moveToPositionScende,moveToPositionRisale,
                                 CallFuncN::create(CC_CALLBACK_1(Gugo::setInvisible, this)),
                                 NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
                );

}
void Gugo::muoviSinistraDestraInAlto(){
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
                                     CallFuncN::create(CC_CALLBACK_1(Gugo::setInvisible, this)),
                                     NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
                    );


}


void Gugo::muoviLeAli(){
	    Vector<SpriteFrame*> uccelloFrames(3);
		char str[100] = {0};
		for(int i = 3; i < 6 ;i++)
		{
			//sprintf(str, "Images/grossini_dance_%02d.png",i);
			sprintf(str, "nemico_%02d.png",i);
			auto frame = SpriteFrame::create(str,Rect(0,0,width_uccello,heigth_uccello));  //we assume that the sprites' dimentions are 40*40 rectangles.
		     uccelloFrames.pushBack(frame);
		}

		auto animationUcc = Animation::createWithSpriteFrames(uccelloFrames, 0.2f);

		this->runAction( RepeatForever::create( Animate::create(animationUcc) ) );

}
void Gugo::setInvisible(Node * node) {
    node->setVisible(false);
}
