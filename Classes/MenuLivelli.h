
#ifndef MenuLivelli_H_
#define MenuLivelli_H_


#pragma once
#include "cocos2d.h"
using namespace cocos2d;

class HelloWorldScene;

class MenuLivelli : public CCLayer
{
private:
	CCLabelBMFont* scoreLabel;
	//Sprite* _endMenu;

    Sprite *_background_menu;
    Sprite *_gameover;
    Label *_labelRecord;
    Menu *_menuRestart;
    int _score=0;




public:
	MenuLivelli(void);
	~MenuLivelli(void);

	CCMenu* pauseMenu;
	CCMenu* resumeMenu;

	CCSize visibleSize;


	void updateScore(int score);

	void pauseGame(CCObject* pSender);
	void resumeGame(CCObject* pSender);

	void setupGameOver();
	void restartTapped(Ref* pSender) ;
	void faiVedereEndGameMenu();
	void setScore(int score);

	void startScena_1(Ref* pSender);
	void startScena_2(Ref* pSender);
	void startScena_3(Ref* pSender);

};


#endif
