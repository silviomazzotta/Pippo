#ifndef __SECONDA_SCENE_H__
#define __SECONDA_SCENE_H__

#include "cocos2d.h"
#include "PallinaSprite.h"
#include "Uccello.h"
#include "GlobalVariable.h"
#include "Gugo.h"
#include "HelloWorldScene.h"

using namespace cocos2d;

//enum StatoGugut {PLAY, BLINK, NOPLAY,RUOTASINISTRA};
//enum StatoDifficolta {LIVELLO1, LIVELLO2, LIVELLO3,LIVELLO4,LIVELLO5,LIVELLO6,LIVELLO7,LIVELLO8,LIVELLO9};

;

class SecondaScene : public cocos2d::Layer
{
	//uccello inizio
	//ogni 10 secondi faccio apparire un uccello
	Uccello *_uccello;
	Sprite *_pallinaBlue;
    //
    Gugo *_gugo;
    Sprite *_pallinaGugo;


    Vector<PallinaSprite*> *_palline;
    int _nextPallina=0;

  //  Vector<PallinaSprite*> *_pallineZigZag;
  //  int _nextPallinaZigZag=0;

    Sprite *_gugutAnimato;
    Sprite *_gugutAnimatoSaluta;
    //Vector<SpriteFrame*> _vettoreFramesGugut;
    StatoGugut _statoGgugut = PLAY;
    StatoDifficolta _statoDifficolta = LIVELLO1;

    Sprite *_muro;
    Sprite *_montagna;
    Sprite *_prato;

    //End game
    Sprite *_background_menu;
    Sprite *_gameover;
    Label *_labelRecord;
    Menu *_menuRestart;
    //fine


    Vector<Sprite*> *_pietre;
    int _nextPietra=0;

    Sprite *_pietraLabel;
    //int _nextNemico=0;
    Label *_scoreDisplay;
    Label *_livesDisplay;
    Label *_labelLiv;
    int _score;
    int _lives=ext_pietre_disposizione;
    Size _screenSize;
    bool _playing = false;
    bool _urtoPallina = false;
    //bool _rotateSun = false;
    Action* _muoviGugut;
    Action* _groundHit;
    Action* _explotion;
    Action* _ruataGugut;
    Action* _muoviGugutSaluta;
    Action* _muoviZigZag_1;
    Action* _muoviZigZagJump;

    //particelle
    ParticleSystem * _emitter_1;
    ParticleSystem * _emitter_rotFlower;
    ParticleSystem * _emitter_pallinaNegativa;

public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();

    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

    // implement the "static create()" method manually
    CREATE_FUNC(SecondaScene);

    void addPalline (float dt) ;
    void addPallineZigZag (float dt);
    void addGugo(float dt);
    void setInvisible(Node * node);
    bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* event);
    void update (float dt) ;
    void stopGameAndMessage();
    void restartTapped(Ref* pSender);
    float randomValueBetween(float low, float high);
    Sprite* createEplosioneAnimata();
    void setupActions(void);
    void setupGameOver(void);
    void setupTest(void);

    void ruotaGugutSinistra(PallinaSprite* pallinaSprite);
    void andLivesGugutSalta();
    void muoviMontagnaScoglio();
    void gugutSaluta(PallinaSprite* pallinaSprite);
    void animationDone(Node *node);
    virtual ~SecondaScene();
    //uccello
    void addUccello (float dt) ;
    //fine
    //15-12-2014
    void effettoGuadagnoPietre(Node *node);
    void controllaModificaDifficolta();
    void controllaPietre();
    void addParticelle() ;
    void particelleRotFlower();
    void particellePallinaNegativa();
    void controllaPietraConPallinaBlu(Node *pietra);
};

#endif // __HELLOWORLD_SCENE_H__
