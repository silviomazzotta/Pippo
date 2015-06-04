#include "HelloWorldScene.h"
#include "GlobalVariable.h"
#include "SimpleAudioEngine.h"
#include "Uccello.h"
#include "Gugo.h"
#include "MenuScene.h"

USING_NS_CC;

//fonts/futura-48.fnt
const std::string TRE_FONT_CONTATORI = "font-issue1343.fnt";

//impostazione grafica sfondo
std::string TRE_PNG_MONTAGNA = "montagna.png";
std::string TRE_PNG_MONTAGNA_GIALLA = "montagna_gialla.png";
std::string TRE_PNG_PRATO = "prato.png";
std::string TRE_PNG_MURO = "muro.png";
std::string TRE_PNG_PALLINA_LABEL = "pietralabel.png";

// ***********  REGOLE GIOCO  **********
// in base allo score cambio il livelli
/*
1     -  1000 - LIVELLO1 --> solo palline e uccello
1000  -  1500 - LIVELLO2 --> ogni tanto una pallina obbliqua
2000  -  2500 - LIVELLO3 --> aggiungo Gugo


*/



Scene* HelloWorld::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = HelloWorld::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
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

    _statoDifficolta = LIVELLO1;
    ext_velocita_pall10 = 4;
    glClearColor(randomValueBetween(0.0, 0.1),randomValueBetween(0.4, 0.7),randomValueBetween(0.7, 1.0),randomValueBetween(0.5, 1.0));
    _playing = true;
    _statoGgugut = PLAY;
    setupGameOver();
    setupActions();
   // setupTest();
   // setupTest2(this);
    _uccello = Uccello::uccelloSpriteWithFile("nemico_04.png");
	 this->addChild(_uccello, 10);
	// _uccello->setPosition(Vec2(300 ,300));
	 _pallinaBlue = Sprite::create("sfera_06.png");
	_uccello->aggiungiPallina(_pallinaBlue);
	_uccello->muoviLeAli();

//aggiunto gufo
	_gugo = Gugo::gugoSpriteWithFile("gugu_01.png");
	 this->addChild(_gugo, 10);
	 _pallinaGugo = Sprite::create("sfera_06.png");
	 _gugo->aggiungiPallina(_pallinaGugo);

	 _gugo->setVisible(false);
	 _pallinaGugo->setVisible(false);




    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _screenSize = Director::getInstance()->getWinSize();

    /////////////////////////////
    // 2. add a menu item with "X" image, which is clicked to quit the program
    //    you may modify it.

    // add a "close" icon to exit the progress. it's an autorelease object
    auto closeItem = MenuItemImage::create(
                                           "CloseNormal.png",
                                           "CloseSelected.png",
                                           CC_CALLBACK_1(HelloWorld::menuCloseCallback, this));

    closeItem->setPosition(Vec2(origin.x + visibleSize.width - closeItem->getContentSize().width/2 ,
                                origin.y + closeItem->getContentSize().height/2));

    // create menu, it's an autorelease object
    auto menu = Menu::create(closeItem, NULL);
    menu->setPosition(Vec2::ZERO);
    this->addChild(menu, 11);




    _muro = Sprite::create("muro.png");
    _muro->setAnchorPoint(Vec2(0.0,  0.0));
    _muro->setPosition(Vec2(origin.x,  origin.y));
    this->addChild(_muro, 6);



	auto director = Director::getInstance();
	 Size screenSize = director->getWinSize();

/*
    _prato = Sprite::create("prato.png");
    _prato->setAnchorPoint(Vec2(0.0,  0.0));
    _prato->setPosition(Vec2(origin.x+(_muro->getContentSize().width * .70) ,  origin.y));
    this->addChild(_prato, 5);

    if(screenSize.width>(_prato->getContentSize().width+(_muro->getContentSize().width/2))){
    	_prato->setScaleX((screenSize.width/ _prato->getContentSize().width)+0.1);
    }
*/
    //TODO portare sopra
    std::vector<std::string>  NOMI_SFONDO_VECTOR;
    //we can also add a whole vector

  // NOMI_SFONDO_VECTOR.push_back("montagna.png");
  // NOMI_SFONDO_VECTOR.push_back("montagna_3.png");
  //  NOMI_SFONDO_VECTOR.push_back("montagna_5.png");

    NOMI_SFONDO_VECTOR.push_back("citta.png");
    NOMI_SFONDO_VECTOR.push_back("montagna_gialla.png");
    NOMI_SFONDO_VECTOR.push_back("montagna_viola.png");

    std::random_shuffle ( NOMI_SFONDO_VECTOR.begin(), NOMI_SFONDO_VECTOR.end() );

    _montagna = Sprite::create("sfondoUNO960640.png");
    _montagna->setAnchorPoint(Vec2(0.0,  0.0));
    _montagna->setPosition(Vec2(origin.x,  origin.y));
	this->addChild(_montagna, 4);




#define MUMEROPALLINE 5
    _palline = new Vector<PallinaSprite*>(MUMEROPALLINE);
    char strPallina[100] = {0};
    int t = 2;
    for (int i = 2; i < 10; ++i) {
        sprintf(strPallina, "sfera_%02d.png",t); //da 02 .. 05  totale 4 palline
        auto *pallina = PallinaSprite::pallinaSpriteWithFile(strPallina);
        pallina->setPunti(10);
        if(i == 4)
            pallina->setPunti(20);
        if(i == 5)
            pallina->setPunti(-20);
       //cancello pallina blue
        // if(i == 6)
        //    pallina->setPunti(111);

        pallina->setVisible(false);
        pallina->setTag(i);
        this->addChild(pallina, 9);
        _palline->pushBack(pallina);
        t= t+1;
        if (t == 6)  {
        	t = 2;
        }
    }
    //agiungo altre palline





    _pietre = new Vector<Sprite*>(20);
    for (int i = 0; i < 19; ++i) {
        auto *pietra =  Sprite::create("pietra.png");
        pietra->setVisible(false);
        this->addChild(pietra, 11);
        _pietre->pushBack(pietra);
    }


    //Gugut
    _gugutAnimato = Sprite::create("gugut_01.png");
    _gugutAnimato->setVisible(true);
    _gugutAnimato->setAnchorPoint(Vec2(0.5,  0.2));//+(_muro->getContentSize().height )+(_gugutAnimato->getContentSize().height )
    //_gugutAnimato->setPosition(Vec2(_muro->getContentSize().width/2 + origin.x, (_muro->getContentSize().height * 1.45)+ origin.y));
    _gugutAnimato->setPosition(Vec2(_muro->getContentSize().width/2 + origin.x,(_muro->getContentSize().height )+ origin.y));

    this->addChild(_gugutAnimato, 8);
   // _gugutAnimato->setAnchorPoint(Vec2(0.5,  0.5));



    _gugutAnimatoSaluta  = Sprite::create("gugutsaluta_06.png");
    _gugutAnimatoSaluta->setVisible(false);
    _gugutAnimatoSaluta->setAnchorPoint(Vec2(0.5,  0.15));
    _gugutAnimatoSaluta->setPosition(Vec2(_muro->getContentSize().width/2 + origin.x,(_muro->getContentSize().height )+ origin.y));
     this->addChild(_gugutAnimatoSaluta, 8);

    /*
     Vector<SpriteFrame*> animFrames(2);
     char str[100] = {0};
     for(int i = 1; i < 3; i++)
     {
     //sprintf(str, "Images/grossini_dance_%02d.png",i);
     sprintf(str, "gugut_%02d.png",i);
     auto frame = SpriteFrame::create(str,Rect(0,0,width_gugut,heigth_gugut));  //we assume that the sprites' dimentions are 40*40 rectangles.
     animFrames.pushBack(frame);
     }
     */
    //_gugutAnimato->runAction( _muoviGugut->clone() );


   // ******************************   HUD   ***********************************


    //TODO mettero pietra
    _labelLiv= Label::createWithBMFont(TRE_FONT_CONTATORI, "Lives");
    addChild(_labelLiv);
    _labelLiv->setPosition(_screenSize.width * .08 , _screenSize.height * .94);
    _labelLiv->setVisible(false);//metto invisibile perche ho messo pietra sotto

    //15-12-2014
    //appare in alto a sinistra ********* PALLINA *****
     _pietraLabel =  Sprite::create(TRE_PNG_PALLINA_LABEL);
    addChild(_pietraLabel,20);
    _pietraLabel->setPosition(_screenSize.width * .08 , _screenSize.height * .94);
    //_pietraLabel->setScaleX(0.5);
    //_pietraLabel->setScaleY(0.5);

     // Label  x   ---> coordinate rispetto alla pietra di sinistra
    auto per= Label::createWithBMFont(TRE_FONT_CONTATORI, "X");
    addChild(per,23);
    per->setPosition(_pietraLabel->getPositionX()+ _pietraLabel->getContentSize().width * 1.10 , _screenSize.height * .94);

    //Numero di pietre a disposizione --> posizionata rispetto a per
    _livesDisplay = Label::createWithBMFont(TRE_FONT_CONTATORI, "0");
    //_livesDisplay->setAnchorPoint(Point::ANCHOR_MIDDLE_RIGHT);
    //_livesDisplay->setPosition(_screenSize.width * .17 , _screenSize.height * .94);
    _livesDisplay->setPosition(per->getPositionX()+ 1.8*(per ->getContentSize().width)  , _screenSize.height * .94);
    this->addChild(_livesDisplay,23);
    std::ostringstream value;
    value << _lives;
    _livesDisplay->setString(value.str());



    //  **************** Label  SCORE **********************
    //  Va posizionata rispetto a LivesDisplay
     auto labelSco = Label::createWithBMFont(TRE_FONT_CONTATORI, "Score");
    addChild(labelSco,23);
    labelSco->setPosition(_livesDisplay->getPositionX()+ _livesDisplay ->getContentSize().width * 2.80  , _screenSize.height * .94);


    //  ****************   SCORE **********************
    _scoreDisplay = Label::createWithBMFont(TRE_FONT_CONTATORI, "0");
    _scoreDisplay->setAnchorPoint(Point::ANCHOR_MIDDLE_LEFT);
    _scoreDisplay->setPosition(labelSco->getPositionX()+ labelSco ->getContentSize().width * 1.10, _screenSize.height * .94);
    this->addChild(_scoreDisplay,23);


     //per finire scheduler
    //this->unschedule(schedule_selector(MyNode::TickMe));

    //create main loop
    this->schedule(schedule_selector(HelloWorld::update));

    this->schedule(schedule_selector(HelloWorld::addPalline), 2.4f);
    this->schedule(schedule_selector(HelloWorld::addUccello), 5.0f);
    this->schedule(schedule_selector(HelloWorld::addGugo), 7.0f);
    this->schedule(schedule_selector(HelloWorld::addPallineZigZag), 9.0f);


    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();

    listener->onTouchBegan = CC_CALLBACK_2(HelloWorld::onTouchBegan, this);
    //listener->onTouchMoved = CC_CALLBACK_2(HelloWorld::onTouchMoved, this);
    //  listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    //listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);

    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);

    //mi serve per inzializzare le particelle
    addParticelle();
    particelleRotFlower();
    particellePallinaNegativa();

    return true;
}

void HelloWorld::addGugo(float dt){
    if (!_playing) return;
    if (_statoDifficolta == LIVELLO1|| _statoDifficolta == LIVELLO3 || _statoDifficolta == LIVELLO5   || _statoDifficolta == LIVELLO6 || _statoDifficolta == LIVELLO8 ){
       _gugo->setColpito(false);
       _pallinaGugo->setVisible(true);
  	   _gugo->setVisible(true);

       _gugo->muoviSopraSotto();
    }


}

void HelloWorld::addUccello (float dt){
   if (!_playing) return;
   if (!(_statoDifficolta == LIVELLO4 || _statoDifficolta == LIVELLO6 ) ){
            _uccello->setColpito(false);
            _pallinaBlue->setVisible(true);
            _uccello->muoviSinistraDestraInAlto();
            cocos2d::log("HelloWorld::addUccello fine.....");
   }


}


void HelloWorld::addPallineZigZag (float dt){
    cocos2d::log("HelloWorld::addPallineZigZag  .....");
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    if (!_playing) return;
    if (_statoDifficolta == LIVELLO2 || _statoDifficolta == LIVELLO5 || _statoDifficolta == LIVELLO6 || _statoDifficolta == LIVELLO7   ){
            auto *pallina = _palline->at( _nextPallina);
            _nextPallina++;

            if ( _nextPallina >= _palline->size())
                _nextPallina = 0;
           pallina->setPosition(Vec2(visibleSize.width + origin.x,visibleSize.height * 1.3 + origin.y));
            pallina->setVisible(true);
            pallina->runAction( _muoviZigZag_1->clone() );
    }

    if (_statoDifficolta == LIVELLO1|| _statoDifficolta == LIVELLO4 || _statoDifficolta == LIVELLO4 ){
            auto *pallina = _palline->at( _nextPallina);
            _nextPallina++;

            if ( _nextPallina >= _palline->size())
                _nextPallina = 0;
            pallina->setPosition(Vec2(visibleSize.width + origin.x, visibleSize.height * 1.3 + origin.y));
            pallina->setVisible(true);
            pallina->runAction( _muoviZigZagJump->clone() );
    }

}
void HelloWorld::addPalline (float dt){
    cocos2d::log("HelloWorld::addPalline .....");
    if (!_playing) return;
    if(_statoGgugut==RUOTASINISTRA) return;
    if (_statoDifficolta == LIVELLO5)return;

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    auto *pallina = _palline->at( _nextPallina);

    _nextPallina++;

    if ( _nextPallina >= _palline->size())
        _nextPallina = 0;


    //TODO fare la y random
    float minY = visibleSize.height / 6;
    float maxY = visibleSize.height;
    float rangeY = maxY - minY;
    float randomY = (float)(arc4random() % (int)rangeY) + minY;


    if (5==pallina->getTag()){

    	randomY =  visibleSize.height * 0.8;
    }
    pallina->setPosition(Vec2(visibleSize.width + origin.x, randomY));
    pallina->setVisible(true);

    Vec2 targetPosition = Vec2(origin.x,randomY );

    float minDuration = 1.0;
    float maxDuration = 4.0;

    float rangeDuration = maxDuration - minDuration;
    float randomDuration = (float)(arc4random() % (int)rangeDuration) + minDuration;

    if(pallina->getPunti() == 10){
        CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/bombRelease.wav");
        randomDuration = ext_velocita_pall10;
    }

    auto moveToTargetPosition = MoveTo::create(randomDuration, targetPosition);

    auto actionFade = FadeOut::create(2.0f);
    auto actionFadeBack = actionFade->reverse();
   // auto seq2 = Sequence::create(moveToTargetPosition, NULL);
    //pallina->runAction(moveToTargetPosition);

    pallina->runAction(
                       Sequence::create(moveToTargetPosition,
                                        CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)),
                                        NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
                       );
    /*
    if (_statoDifficolta == LIVELLO1){
    	pallina->runAction(
                       Sequence::create(moveToTargetPosition,
                                        CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)),
                                        NULL )
                       );
    }else if (_statoDifficolta == LIVELLO2){

    	pallina->runAction( _muoviZigZag_1->clone() );
    }else if (_statoDifficolta == LIVELLO3){

    	pallina->runAction( _muoviZigZagJump->clone() );
    }else{

    	pallina->runAction( _muoviZigZagJump->clone() );
    }
    */


}

void HelloWorld::setInvisible(Node * node) {
    node->setVisible(false);
}


bool  HelloWorld::onTouchBegan(Touch *touch, Event *unused_event){


    if (!_playing) return true;
    if (_lives < 1) return true;
    _gugutAnimato->runAction( _groundHit->clone() );

	   cocos2d::log("onTouchBegan.......   ");
	   Size visibleSize = Director::getInstance()->getVisibleSize();
	   Vec2 origin = Director::getInstance()->getVisibleOrigin();
	   cocos2d::log("position = (%f,%f)",touch->getLocation().x,touch->getLocation().y);

    // _player1->runAction((CCAction *) _rotateSprite->copy()->autorelease());

    auto actionTo = SkewTo::create(2, 37.2f, -37.2f);
    auto actionToBack = SkewTo::create(2, 0, 0);
    auto actionBy = SkewBy::create(2, 0.0f, -90.0f);
    auto actionBy2 = SkewBy::create(2, 45.0f, 45.0f);
    auto actionByBack = actionBy->reverse();

    Vec2  offset = Vec2(_gugutAnimato->getPosition().x-touch->getLocation().x,_gugutAnimato->getPosition().y-touch->getLocation().y );
    float   ratio     = offset.y/offset.x;
    int     targetX   = _gugutAnimato->getContentSize().width/2 +  visibleSize.width;
    int     targetY   = (targetX*ratio) + _gugutAnimato->getPosition().y;

    Vec2 targetPositionProiettileTo = Vec2(targetX,targetY);

    auto *proiettile = _pietre->at( _nextPietra);
	   // auto *proiettile = CCSprite::create("pietra.png");

    _nextPietra++;

	  	if ( _nextPietra >= _pietre->size())
            _nextPietra = 0;


	//)+(_gugutAnimato->getContentSize().height
    proiettile->setPosition(Vec2(_gugutAnimato->getPosition().x,_gugutAnimato->getPosition().y+(_gugutAnimato->getContentSize().height)*0.3));
    proiettile->setVisible(true);

    ///addChild(proiettile, 9); in ios dava problemi perche aggiunto prima

    auto moveToTargetPosition = MoveTo::create(1.2, targetPositionProiettileTo);


    auto seq2 = Sequence::create(moveToTargetPosition, NULL);

    proiettile->runAction(
                          Sequence::create(moveToTargetPosition,
                                           CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)),
                                           NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
                          );

    _lives =_lives-1;
     std::ostringstream value;
     value << _lives;
     _livesDisplay->setString(value.str());

    return true;

}
void HelloWorld::update (float dt) {
    //the main loop
    if (!_playing) return;
    cocos2d::log("HelloWorld::update .....");
    //getBoundingBox().intersectsRect
    //_player1->getBoundingBox().intersectsRect();
    controllaModificaDifficolta();
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();


    //Controllo che pallina blue ha ragginto meta schermo
    // se raggiunto la lancio   _pallinaBlue metto in stato lanciato

    //fine

    for (auto pallina : *_palline){
        if (!(pallina->isVisible()))
            continue;
        //TODO controllo urto con pallina di Gugu


        //controllo urto con gugut
        if (_gugutAnimato->getBoundingBox().intersectsRect(pallina->getBoundingBox())){
        	   //ruotaGugutSinistra(pallina);
            	gugutSaluta(pallina);
        	 //stoppa pallina e falla cadere
        	   pallina->stopAllActions();
        	   Vec2 targetPosition =Vec2(pallina->getPositionX()  ,origin.y );
        	   pallina->runAction(
        	   											Sequence::create(
        	   											RotateBy::create(0.1f,-90.0f),
        	   											MoveTo::create(1.2, targetPosition),
        	   							                RotateBy::create(0.01f,90.0f),
        	   											CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)),
        	   											NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
        	   											);

        	 //fine
        	 muoviMontagnaScoglio();
           // _gugutAnimato->runAction(_ruataGugut->clone() );
            _playing = false;
           stopGameAndMessage();
        }
        for (auto pietra : *_pietre){
            if (!(pietra->isVisible()))
                continue;

            if ((!_gugo->getColpito())){
            	  controllaPietraConPallinaBlu(pietra);
            }
           // _pallinaBlue->convert

           // [spriteA convertToWorldSpace:spriteB.position];
            //inizio da confrontare


       	   //fine

            //controllo urto ucccello e con pallinaBlue
            if ((!_uccello->getColpito())){
                  //per adesso commwnto considero solo pallina blue
            	  /* if (pietra->getBoundingBox().intersectsRect(_uccello->getBoundingBox())){
                    	   cocos2d::log("urto con uccellooo ..... decremento le lives ..");
                    	   _uccello->setColpito(true);
                       	 _lives = _lives -1;
           				std::ostringstream value;
           				value << _lives;
           				_livesDisplay->setString(value.str());
           	         }
           	         */
            	 Vec2 posizioneAssouluta =  _uccello->convertToWorldSpace(_pallinaBlue->getPosition());
			     auto pallinaBlueTemp = Sprite::create("bomba_01.png");
			     pallinaBlueTemp->setPosition(posizioneAssouluta.x, posizioneAssouluta.y);
			     pallinaBlueTemp->setContentSize(Size(_pallinaBlue->getContentSize().width, _pallinaBlue->getContentSize().height));
                    if (pietra->getBoundingBox().intersectsRect(pallinaBlueTemp->getBoundingBox())){
                                        	cocos2d::log("urto con pallinaBlueTemp ..... incremento di 4 .. ");
                                        	   _uccello->setColpito(true);
                                        	   //metto invisibile
                                        	   _pallinaBlue->setVisible(false);
                                           	 _lives = _lives +4;
                               				std::ostringstream value;
                               				value << _lives;
                               				_livesDisplay->setString(value.str());
                               				//TODO faccio fare esplosione e dico che ho guadagnato punti
                               				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/boom.wav");
                               		   /*prima era cosi funzionava
                                            Sprite * urto = Sprite::create("bomba_01.png");
                                            this->addChild(urto, 6);
                                            urto->setPosition(Vec2(pallinaBlueTemp->getPosition().x, pallinaBlueTemp->getPosition().y));

                                            urto->runAction( _explotion->clone() );
                                            */
                                            //fine
                                            //TODO
                               				_emitter_rotFlower->setPosition(Vec2(pallinaBlueTemp->getPosition().x, pallinaBlueTemp->getPosition().y));
                               				_emitter_rotFlower->resetSystem();
                               				_emitter_rotFlower->setDuration(0.5);

                                            //15-12-2014
                                            //faccio ruotare labelPietra
                                            effettoGuadagnoPietre(pallinaBlueTemp);
                          	 }
              }
             //fine
            //urto tra pallina e pietra
            if (pietra->getBoundingBox().intersectsRect(pallina->getBoundingBox())){
                //inserisco audio
                //CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("S-Damage.mp3");
                //INIZIO ESPLOSIONE
                /*	  auto *eplosioneAnimata = createEplosioneAnimata();

                 eplosioneAnimata->setPosition(Vec2(pallina->getPosition().x, pallina->getPosition().y));
                 this->addChild(eplosioneAnimata, 6);
                 Vec2 targetPosition =Vec2(pallina->getPositionX()  ,pallina->getPositionY() +24 );
                 eplosioneAnimata->runAction(
                 Sequence::create(
                 MoveTo::create(0.5, targetPosition),
                 CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)),
                 NULL)
                 );
                 */
               // Sprite * urto = Sprite::create("bomba_01.png");

                CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/boom.wav");
             //   this->addChild(urto, 6);
              //  urto->setPosition(Vec2(pallina->getPosition().x, pallina->getPosition().y));;
            //    urto->runAction( _explotion->clone() );
                //FINE



                //TODO se punti pallina == 111  lives = lives - 1 ;
                if (pallina->getPunti() == 111){
                    _lives = _lives +4;
                    std::ostringstream value;
                    value << _lives;
                    _livesDisplay->setString(value.str());

                }else{
                    _score = _score + pallina->getPunti() ;
                    std::ostringstream value;
                    value << _score;
                    _scoreDisplay->setString(value.str());

                    if(pallina->getPunti()<0){
                    	_emitter_pallinaNegativa->setPosition(Vec2(pallina->getPosition().x, pallina->getPosition().y));
                    	_emitter_pallinaNegativa->resetSystem();
                    	_emitter_pallinaNegativa->setDuration(0.3);

                    }else{
						_emitter_1->setPosition(Vec2(pallina->getPosition().x, pallina->getPosition().y));
						_emitter_1->resetSystem();
						_emitter_1->setDuration(0.3);

                    }
                }
                //TODO faccio blink di _spriteAnimato
                //_spriteAnimato->runAction(Blink::create(2, 10));
                //Todo muovo il nemico verso sotto
                pallina->stopAllActions();

                //Vec2 targetPosition =Vec2(nemico->getPositionY()  ,origin.y );
                //auto moveToTargetPosition = MoveTo::create(randomDuration, targetPosition);
                pietra->stopAllActions();
                pietra->runAction(
                                  Sequence::create(
                                                   CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)),
                                                   NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
                                  );

                pallina->stopAllActions();
                pallina->runAction(
                                   Sequence::create(
                                                    CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)),
                                                    NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
                                   );
                //nemico->setVisible(false);
            }
        }

    }

    if (_score > 1001 && _score < 1020 ) {

    }



    //controllo  fine gioco
    if(_playing == true){
			if (_lives < 1) {
				//_energy = 0;
				_playing = false;
				// muoviMontagnaScoglio();
				// andLivesGugutSalta();
			 	 muoviMontagnaScoglio();
			           // _gugutAnimato->runAction(_ruataGugut->clone() );
			            _playing = false;
			           stopGameAndMessage();

				//TODO faccio ruotare gugut
				// - cambio ancor point - ruoto verso si nistra


			   // stopGameAndMessage();
			}
    }

    controllaPietre();
    /*
    if (_lives == 4) {
        //_livesDisplay->runAction(Blink::create(1, 2));
        //_gugutAnimato->runAction(Blink::create(1, 2));
        //_gugutAnimato->setOpacity( 0 );
        auto action1 = FadeIn::create(1.0f);
        auto action1Back = action1->reverse();

        auto action2 = FadeOut::create(1.0f);
         auto action2Back = action2->reverse();
        auto action2BackReverse = action2Back->reverse();
        auto action2BackReverseReverse = action2BackReverse->reverse();
        auto action3 = Blink::create(2, 10);
        //if(!(_statoGgugut == BLINK))
        //	_gugutAnimato->runAction(action3);
        //_statoGgugut = BLINK;
        //_gugutAnimato->setUserData("on");
        //_gugutAnimato->setOpacity(122);
        if(!(_statoGgugut == BLINK)) {
            _statoGgugut = BLINK;
            _labelLiv->runAction( Sequence::create( action3,
                                                   CallFunc::create(
                                                                    // lambda
                                                                    [&](){
                                                                        //auto s = Director::getInstance()->getWinSize();
                                                                        //auto label = Label::createWithTTF("called:lambda callback", "fonts/Marker Felt.ttf", 16.0f);
                                                                        //label->setPosition(Vec2( s.width/4*1,s.height/2-40));
                                                                        //this->addChild(label,14);
                                                                        _statoGgugut = PLAY;
                                                                    }  ),
                                                   NULL));
        }

    }else{

        _statoGgugut = PLAY;
    }
    */
}

//stoppo il game e mostro messaggio
//void HelloWorld::stopGameAndMessageOLd()

/*
 void stopGameAndMessageOLd()
 {
 Size visibleSize = Director::getInstance()->getVisibleSize();
 Vec2 origin = Director::getInstance()->getVisibleOrigin();
 _playing = false;


 auto label = Label::createWithBMFont("fonts/futura-48.fnt","End Game");
 label->setPosition(Vec2(origin.x + visibleSize.width/2,
 origin.y + visibleSize.height/2 ));
 this->addChild(label, 8);

 //TODO stoppo le action delle palline
 for (auto sprite : *_palline){
 sprite->stopAllActions();
 sprite->setVisible(false);
 }
 for (auto sprite : *_pietre){
 sprite->stopAllActions();
 sprite->setVisible(false);
 }


	auto restartLabel = Label::createWithBMFont("fonts/futura-48.fnt", "Restart Game");
	auto restartItem = MenuItemLabel::create(restartLabel, CC_CALLBACK_1(HelloWorld::restartTapped, this));
	//restartItem->setScale(0.1F);
	restartItem->setPosition(Vec2(origin.x + visibleSize.width/2,
 origin.y + visibleSize.height/3 ));

	auto *menu = Menu::create(restartItem, NULL);
	menu->setPosition(Point::ZERO);
	this->addChild(menu, 9);

	int record = CCUserDefault::sharedUserDefault( )->getIntegerForKey( "RECORD" );
	//if((record == nullptr) || (_score>record) ){
	if(_score>record) {
 record =_score;
 CCUserDefault::sharedUserDefault()->setIntegerForKey("RECORD",record);

 CCUserDefault::sharedUserDefault()->flush();
 }

	auto labelRecord = Label::createWithBMFont("fonts/futura-48.fnt", "0");
	labelRecord->setPosition(Vec2(origin.x + visibleSize.width/2,
 origin.y + visibleSize.height/1.5 ));
	this->addChild(labelRecord,10);
	std::ostringstream value;
	value << record;
	labelRecord->setString("Record "+value.str());
 cocos2d::log("background_menu_end.png kkk .....");
	auto background_menu = Sprite::create("backgroundmenuend.png");
	this->addChild(background_menu, 7);
	background_menu->setPosition(Vec2(origin.x + visibleSize.width/2,
 origin.y + visibleSize.height/2 ));

 cocos2d::log("background_menu_end.png kkk ppp.....");



 this->unscheduleUpdate();

 }
 */
//stoppo il game e mostro messaggio
/*
 void HelloWorld::stopGameAndMessage()
 {
 Size visibleSize = Director::getInstance()->getVisibleSize();
 Vec2 origin = Director::getInstance()->getVisibleOrigin();
 _playing = false;




 //TODO stoppo le action delle palline
 for (auto sprite : *_palline){
 sprite->stopAllActions();
 sprite->setVisible(false);
 }
 for (auto sprite : *_pietre){
 sprite->stopAllActions();
 sprite->setVisible(false);
 }


	int record = CCUserDefault::sharedUserDefault( )->getIntegerForKey( "RECORD" );
	//if((record == nullptr) || (_score>record) ){
	if(_score>record) {
 record =_score;
 CCUserDefault::sharedUserDefault()->setIntegerForKey("RECORD",record);

 CCUserDefault::sharedUserDefault()->flush();
 }



	auto background_menu = Sprite::create("backgroundmenuend.png");
	this->addChild(background_menu, 7);
	background_menu->setPosition(Vec2(origin.x + visibleSize.width/2,
 origin.y + visibleSize.height/2 ));

	auto gameover = Sprite::create("gameoverbutton.png");
	this->addChild(gameover, 8);
	gameover->setPosition(Vec2(origin.x + visibleSize.width/2,
 (background_menu->getContentSize().height * 0.30)+ origin.y + (background_menu->getPositionY())));


	auto labelRecord = Label::createWithBMFont("fonts/futura-48.fnt", "0");

	//auto labelRecord = Label::createWithBMFont("font-issue1343.fnt", "0");
	labelRecord->setPosition(Vec2(origin.x + visibleSize.width/2,
 origin.y +background_menu->getPositionY() ));
	this->addChild(labelRecord,8);
	std::ostringstream value;
	value << record;
	labelRecord->setString("Record "+value.str());


 //	auto menuTitle =
 //	MenuItemImage::create("gameoverbutton.png",
 //	"gameoverbutton.png");

	auto retryItem =
	MenuItemImage::create("startagainbutton.png",
	"startagainbutton.png",
	CC_CALLBACK_1(HelloWorld::restartTapped, this));

	//auto mainMenuItem =
	//MenuItemImage::create("GameOverScreen/Menu_Button.png",
	//"GameOverScreen/Menu_Button(Click).png",
	//CC_CALLBACK_1(GameOver::GoToMainMenuScene, this));

	auto menu = Menu::create( retryItem,
	NULL);
 // menu->alignItemsVerticallyWithPadding(visibleSize.height / 4);
 menu->setPosition(Vec2(origin.x + visibleSize.width/2,
 origin.y +background_menu->getPositionY() - (background_menu->getContentSize().height * 0.30)));
	this->addChild(menu, 8);





 this->unscheduleUpdate();

 }
*/
//stoppo il game e mostro messaggio


void HelloWorld::stopGameAndMessage()
{
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();
    _playing = false;




    //TODO stoppo le action delle palline
  //  for (auto sprite : *_palline){
   //     sprite->stopAllActions();
       // sprite->setVisible(false);
  //  }

	_uccello->stopAllActions();
	_pallinaBlue->stopAllActions();

	_uccello->setVisible(false);
	_pallinaBlue->setVisible(false);



	for (auto sprite : *_pietre){
        sprite->stopAllActions();
        sprite->setVisible(false);
    }

    //_background_menu->setOpacity( 0 );
    _background_menu->setPosition(Vec2(origin.x + visibleSize.width+ _background_menu->getContentSize().width,
                                      origin.y + visibleSize.height/2 ));

    _background_menu->setVisible(true);

    auto action3 = Blink::create(1, 1);
    auto actionTo = SkewTo::create(2, 0.f, 2.f);
    auto rotateTo = RotateTo::create(2, 61.0f);
    auto actionScaleTo = ScaleTo::create(2, -0.44f, 0.47f);

    auto actionScaleToBack = ScaleTo::create(2, 1.0f, 1.0f);
    auto rotateToBack = RotateTo::create(2, 0);
    auto actionToBack = SkewTo::create(2, 0, 0);


    auto actionTo2 = MoveTo::create(0.5, Vec2(origin.x + visibleSize.width/2,
                                            origin.y + visibleSize.height/2 ));


    _background_menu->runAction( Sequence::create(DelayTime::create(1.5), actionTo2,
                                                  CallFunc::create(
                                                                   // lambda
                                                                   [&](){
                                                                       _menuRestart->setVisible(true);

                                                                       _gameover->setVisible(true);
                                                                       _labelRecord->setVisible(true);

                                                                       int record = CCUserDefault::sharedUserDefault( )->getIntegerForKey( "RECORD" );
                                                                       //if((record == nullptr) || (_score>record) ){
                                                                       if(_score>record) {
                                                                           record =_score;
                                                                           CCUserDefault::sharedUserDefault()->setIntegerForKey("RECORD",record);

                                                                           CCUserDefault::sharedUserDefault()->flush();
                                                                       }
                                                                       std::ostringstream value;
                                                                       value << record;
                                                                       _labelRecord->setString("Record "+value.str());




                                                                   }  ),
                                                  NULL));


    this->unscheduleUpdate();

}




void HelloWorld::restartTapped(Ref* pSender) {


    auto scene = MenuScene::createScene();
    Director::getInstance( )->replaceScene( TransitionFade::create( 0.5, scene ) );
    scene->scheduleUpdate();

}


Sprite* HelloWorld::createEplosioneAnimata(){
	Size designSize = Size(480,320);
	Size resourceSize = Size(960,640);
	float ratio_scale = resourceSize.width / designSize.width ;

    Sprite * _nemicoAnimato = Sprite::create("bomba_01.png");//446x438
    Vector<SpriteFrame*> animFrames(5);
    char str[100] = {0};
    for(int i = 1; i < 6; i++)
    {
        //sprintf(str, "Images/grossini_dance_%02d.png",i);
        sprintf(str, "bomba_%02d.png",i);
        auto frame = SpriteFrame::create(str,Rect(0,0,width_esplosione/ratio_scale,heigth_esplosione/ratio_scale)); //we assume that the sprites' dimentions are 40*40 rectangles.
        animFrames.pushBack(frame);
    }

    auto animation = Animation::createWithSpriteFrames(animFrames, 0.2f);
    _nemicoAnimato->runAction( RepeatForever::create( Animate::create(animation) ) );
    return _nemicoAnimato;
}

void HelloWorld::setupActions()
{

	//  width_gugut=33;
	 //   heigth_gugut=60;

	 Size designSize = Size(480,320);
	 Size resourceSize = Size(960,640);
	      // 2
	    /*  director->setContentScaleFactor(resourceSize.height / designSize.height);
	      director->getOpenGLView()->setDesignResolutionSize(
	      designSize.width, designSize.height, ResolutionPolicy::FIXED_HEIGHT);
	      */
	//      director->setContentScaleFactor(resourceSize.width / designSize.width);
	float ratio_scale = resourceSize.width / designSize.width ;


	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vector<SpriteFrame*> animFrames(2);
    char str[100] = {0};
    for(int i = 1; i < 3; i++)
    {
        sprintf(str, "gugut_%02d.png",i);
        auto frame = SpriteFrame::create(str,Rect(origin.x,  origin.y,width_gugut/ratio_scale,heigth_gugut/ratio_scale));  //we assume that the sprites' dimentions are 40*40 rectangles.
        animFrames.pushBack(frame);
    }
    // auto animate = Animate::create(animation);
    // sprite->runAction(animate);
    auto animation1 =  Animation::createWithSpriteFrames(animFrames, 0.2f);
	   _muoviGugut = RepeatForever::create( Animate::create(animation1)) ;
	   _muoviGugut->retain();
    //Animation* animation = Animation::createWithSpriteFrames(animFrames, 0.3f);
    //_muoviGugut->runAction( _muoviGugut->Clone() );

    Animation *animation = Animation::create();

    std::ostringstream name;
    for (int i = 1; i <3; i++) {
        sprintf(str, "gugut_%02d.png",i);
        auto frame1 = SpriteFrame::create(str,Rect(origin.x,  origin.y,width_gugut/ratio_scale,heigth_gugut/ratio_scale));  //we assume that the sprites' dimentions are 40*40 rectangles.
        animation->addSpriteFrame(frame1);
    }
    animation->setDelayPerUnit(1.0 / 10.0);
    animation->setRestoreOriginalFrame(true);
    _groundHit = Sequence::create(
                                  Animate::create(animation),
                                  CallFuncN::create(CC_CALLBACK_1(HelloWorld::animationDone, this)),
                                  NULL);
    _groundHit->retain();

    //Gugut saluta Inizio
    Vector<SpriteFrame*> animFramesSaluta(3);
    char str2[100] = {0};
    for(int i = 3; i < 7; i++)
    {
        sprintf(str2, "gugutsaluta_%02d.png",i);
        auto frame = SpriteFrame::create(str2,Rect(origin.x,  origin.y,width_gugutsaluta/ratio_scale,heigth_gugutsaluta/ratio_scale));  //we assume that the sprites' dimentions are 40*40 rectangles.
        animFramesSaluta.pushBack(frame);
    }
    // auto animate = Animate::create(animation);
    // sprite->runAction(animate);
    Animation *animationSaluta =  Animation::createWithSpriteFrames(animFramesSaluta, 0.2f);
    animationSaluta->setDelayPerUnit(1.0 / 10.0);
    animationSaluta->setRestoreOriginalFrame(true);
	 //  _muoviGugutSaluta = RepeatForever::create( Animate::create(animationSaluta)) ;

	   _muoviGugutSaluta = Sequence::create(
			   	   	   	   	   	   	   	   Animate::create(animationSaluta),
	                                    CallFuncN::create(CC_CALLBACK_1(HelloWorld::animationDone, this)),
	                                    NULL);


	   _muoviGugutSaluta->retain();
	//Gugut saluta fine

    // hit meteor or health animation
	   animation = Animation::create();
	   for (int i = 1; i < 7; i++) {
           name.str("");
           name << "bomba_0" << i << ".png";
           auto frame = SpriteFrame::create(name.str(),Rect(origin.x,  origin.y,width_esplosione/ratio_scale,heigth_esplosione/ratio_scale));
           animation->addSpriteFrame(frame);
       }
	   animation->setDelayPerUnit(0.5 / 7.0);
	   animation->setRestoreOriginalFrame(true);
	   _explotion = Sequence::create(Animate::create(animation),
                                     CallFuncN::create(CC_CALLBACK_1(HelloWorld::animationDone, this)),
                                     CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)),
                                     NULL);
	   _explotion->retain();

    //Ruota gugut
    auto actionTo = RotateTo::create(2, 180, 180);
    auto actionToBack = RotateTo::create(2, 0, 0);
    auto actionBy = RotateBy::create(2, 0.0f, 360);
    auto actionByBack = actionBy->reverse();

    auto actionBy2 = RotateBy::create(2, 360, 0);
    auto actionBy2Back = actionBy2->reverse();

    _ruataGugut = Sequence::create(
                                   actionBy, actionByBack,
                                   CallFuncN::create(CC_CALLBACK_1(HelloWorld::animationDone, this)),
                                   NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
    ;
    _ruataGugut->retain();

    //INIZIO _muoviZigZag_1
    float randomDuration = 3.0;
    Size visibleSize = Director::getInstance()->getVisibleSize();
 //   Vec2 origin = Director::getInstance()->getVisibleOrigin();
    Vec2 targetPosition_1 = Vec2(visibleSize.width/2 + origin.x,origin.y );
    auto moveToTargetPosition_1 = MoveTo::create(0.8, targetPosition_1);


    Vec2 targetPosition_2 = Vec2(origin.x,origin.y+visibleSize.height/2  );

    auto moveToTargetPosition_2 = MoveTo::create(1.5, targetPosition_2);


    _muoviZigZag_1  = Sequence::create(
    		moveToTargetPosition_1, moveToTargetPosition_2,
            CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)),
            NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/);

    _muoviZigZag_1->retain();



    auto actionJumpZigZag = JumpTo::create(2.7, targetPosition_1, 275, 6);

    _muoviZigZagJump= Sequence::create(
    		moveToTargetPosition_1, actionJumpZigZag, moveToTargetPosition_2,
            CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)),
            NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/);

    _muoviZigZagJump->retain();



    //FINE_muoviZigZag_1

}


void HelloWorld::setupGameOver()
{
    bool VISIBILITA = false;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    _background_menu = Sprite::create("backgroundmenuend.png");
    _background_menu->setVisible(VISIBILITA);
    this->addChild(_background_menu, 7);

    _background_menu->setPosition(Vec2(origin.x + visibleSize.width/2,
                                      origin.y + visibleSize.height/2 ));


    _gameover = Sprite::create("gameoverbutton.png");
    _gameover->setVisible(VISIBILITA);
    this->addChild(_gameover, 8);
    _gameover->setPosition(Vec2(origin.x + visibleSize.width/2,
                                (_background_menu->getContentSize().height * 0.30)+ origin.y + (_background_menu->getPositionY())));



 //   _labelRecord = Label::createWithBMFont("font-issue1343.fnt", "0");
     _labelRecord = Label::createWithBMFont("fonts/futura-48.fnt", "0");

    _labelRecord->setVisible(VISIBILITA);
    _labelRecord->setPosition(Vec2(origin.x + visibleSize.width/2,
                                   origin.y +_background_menu->getPositionY() ));
    this->addChild(_labelRecord,8);



    auto retryItem =
    MenuItemImage::create("startagainbutton.png",
                          "startagainbutton.png",
                          CC_CALLBACK_1(HelloWorld::restartTapped, this));

    _menuRestart = Menu::create( retryItem,
                                NULL);
    _menuRestart->setPosition(Vec2(origin.x + visibleSize.width/2,
                                   origin.y +_background_menu->getPositionY() - (_background_menu->getContentSize().height * 0.30)));
    _menuRestart->setVisible(VISIBILITA);
    this->addChild(_menuRestart, 8);

    _menuRestart->setPosition(Vec2(origin.x + visibleSize.width/2,
                           origin.y +_background_menu->getPositionY() - (_background_menu->getContentSize().height * 0.30)));




}


void HelloWorld::setupTest()
{

    bool VISIBILITA = false;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* parent = Sprite::create("unpixel.png");
    parent->setTextureRect(CCRectMake(0,0, 400, 400));
    parent->setColor(ccc3(255,0, 0));
    parent->setAnchorPoint(Vec2(0,0));
    this->addChild(parent, 20);

    parent->setPosition(Vec2(origin.x + visibleSize.width/2,
                                       origin.y + visibleSize.height/2 ));


    Sprite* cildren = Sprite::create("unpixel.png");
    cildren->setColor(ccc3(0,  255, 0));
    cildren->setTextureRect(CCRectMake(0,0, 70, 70));
    cildren->setColor(ccc3(0, 255, 0));
    cildren->setAnchorPoint(Vec2(0,0));
    cildren->setPosition(Vec2(parent->getContentSize().width*0.20,0));
    parent->addChild(cildren, 20);





     auto moveToTargetPosition = MoveTo::create(10, Vec2(500,500));

    parent->runAction(moveToTargetPosition);

}
void HelloWorld::setupTest2(HelloWorld *seStesso){

    bool VISIBILITA = false;
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

    Sprite* parent = Sprite::create("unpixel.png");
    parent->setTextureRect(CCRectMake(0,0, 400, 400));
    parent->setColor(ccc3(255,0, 0));
    parent->setAnchorPoint(Vec2(0,0));
    seStesso->addChild(parent, 20);

    parent->setPosition(Vec2(origin.x + visibleSize.width/2,
                             origin.y + visibleSize.height/2 ));


    Sprite* cildren = Sprite::create("unpixel.png");
    cildren->setColor(ccc3(0,  255, 0));
    cildren->setTextureRect(CCRectMake(0,0, 70, 70));
    cildren->setColor(ccc3(0, 255, 0));
    cildren->setAnchorPoint(Vec2(0,0));
    cildren->setPosition(Vec2(parent->getContentSize().width*0.20,0));
    parent->addChild(cildren, 20);

    auto moveToTargetPosition = MoveTo::create(10, Vec2(500,500));

    parent->runAction(moveToTargetPosition);



}

void HelloWorld::ruotaGugutSinistra(PallinaSprite* pallinaSprite){

	 _gugutAnimato->stopAllActions();
	   for (auto sprite : *_palline){
		   if(pallinaSprite->getTag()!=sprite->getTag()){
	             sprite->setVisible(false);
		   }
	    }

	   _statoGgugut = RUOTASINISTRA;

	Size visibleSize = Director::getInstance()->getVisibleSize();
	  Vec2 origin = Director::getInstance()->getVisibleOrigin();
	//_gugutAnimato->runAction(RotateTo::create(1,-90));
	   auto actionJump = JumpTo::create(0.7, Vec2(_muro->getContentSize().width*0.6 + origin.x, (_muro->getContentSize().height * 1.45)+ origin.y), 275, 2);

	// auto actionFadeBack = actionFade->reverse();
	    auto seq2 = Sequence::create(actionJump,CallFunc::create(
                // lambda
							[&](){

	    					   Vec2 origin = Director::getInstance()->getVisibleOrigin();

	    					//	_gugutAnimato->setAnchorPoint(Vec2(0, 0));
	    						//_gugutAnimato->setPosition(Vec2(_muro->getContentSize().width + origin.x, (_muro->getContentSize().height * 1.0)+ origin.y));
	    						// auto ruotaSinistra = RotateTo::create(0.7,-90);
	    						// _gugutAnimato->runAction(ruotaSinistra);

							}  )
	    						, NULL);





	    _gugutAnimato->runAction(seq2);
}
void HelloWorld::andLivesGugutSalta(){
	_statoGgugut = RUOTASINISTRA;
	   Size visibleSize = Director::getInstance()->getVisibleSize();
	  Vec2 origin = Director::getInstance()->getVisibleOrigin();
	  _gugutAnimato->stopAllActions();
	   auto actionJump = JumpTo::create(0.4, Vec2(_muro->getContentSize().width*0.8 + origin.x, (_muro->getContentSize().height * 1.45)+ origin.y), 275, 2);

	    auto seq2 = Sequence::create(actionJump,CallFunc::create(
                // lambda
							[&](){

	    					   Vec2 origin = Director::getInstance()->getVisibleOrigin();

	    						_gugutAnimato->setAnchorPoint(Vec2(0, 0));
	    						_gugutAnimato->setPosition(Vec2(_muro->getContentSize().width + origin.x, (_muro->getContentSize().height * 1.0)+ origin.y));
	    						 auto ruotaSinistra = RotateTo::create(0.7,-90);
	    						 _gugutAnimato->runAction(ruotaSinistra);

							}  )
	    						, NULL);





	    _gugutAnimato->runAction(seq2);
}


void HelloWorld::gugutSaluta(PallinaSprite* pallinaSprite){
   	_statoGgugut = RUOTASINISTRA;
	   Size visibleSize = Director::getInstance()->getVisibleSize();
	  Vec2 origin = Director::getInstance()->getVisibleOrigin();
	  _gugutAnimato->stopAllActions();
	  // auto actionJump = JumpTo::create(0.4, Vec2(_muro->getContentSize().width*0.7 + origin.x, (_muro->getContentSize().height * 1.45)+ origin.y), 30, 2);
	  // auto action1 = Blink::create(2, 10);
	   auto actionBlink = Blink::create(0.2, 2);

	   //   _tamara->runAction( action1);
	    //  _kathia->runAction(action2);

	   auto seq2 = Sequence::create(actionBlink,CallFunc::create(
                // lambda
							[&](){

	    	                   _gugutAnimato->setVisible(false);
	    	                   _gugutAnimatoSaluta->setVisible(true);
	    					   Vec2 origin = Director::getInstance()->getVisibleOrigin();

	    						//_gugutAnimato->setAnchorPoint(Vec2(0, 0));
	    						//_gugutAnimato->setPosition(Vec2(_muro->getContentSize().width/2 + origin.x, (_muro->getContentSize().height * 1.0)+ origin.y));
	    						// auto ruotaSinistra = RotateTo::create(0.7,-90);
	    						 _gugutAnimatoSaluta->runAction(_muoviGugutSaluta->clone() );

							}  )
	    						, NULL);





	    _gugutAnimato->runAction(seq2);
}

void HelloWorld::muoviMontagnaScoglio(){

	 auto actionJumpMuro = JumpTo::create(0.3, _muro->getPosition(), -10, 1);
    _muro->runAction(actionJumpMuro);
	 auto actionJumpMontagna = JumpTo::create(0.3, _montagna->getPosition(), -10, 1);
	 _montagna->runAction(actionJumpMontagna);
	// auto actionJumpProto = JumpTo::create(0.3, _prato->getPosition(), -10, 1);
	// _prato->runAction(actionJumpProto);


}

HelloWorld::~HelloWorld()
{
    CC_SAFE_RELEASE(_muoviGugut);
    CC_SAFE_RELEASE(_groundHit);
    CC_SAFE_RELEASE(_explotion);
    CC_SAFE_RELEASE(_muoviGugutSaluta);
     CC_SAFE_RELEASE(_muoviZigZag_1);

}
void HelloWorld::animationDone(Node *node)
{
    node->stopAllActions();
}
void HelloWorld::effettoGuadagnoPietre(Node *node)
{
	//muovo le pietre vero pietre dispay contatore
	//auto action2 = Blink::create(2, 5);
	//_pietraLabel->runAction(action2);
	//prendere posizione pietra
   	auto *pietra =  Sprite::create("pietra.png");
    pietra->setPosition(Vec2(node->getPosition().x, node->getPosition().y));
    this->addChild(pietra, 20);
    pietra->runAction(
   										Sequence::create(
   										MoveTo::create(0.3, Vec2(_pietraLabel->getPosition().x, _pietraLabel->getPosition().y)),
   						                CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)),


   										NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
   										);
   	auto *pietra2 =  Sprite::create("pietra.png");
    pietra2->setPosition(Vec2(node->getPosition().x, node->getPosition().y));
    this->addChild(pietra2, 20);
    pietra2->runAction(
   										Sequence::create(
   										MoveTo::create(0.5, Vec2(_pietraLabel->getPosition().x, _pietraLabel->getPosition().y)),
   						                CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)),


   										NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
   										);
   	auto *pietra3 =  Sprite::create("pietra.png");
    pietra3->setPosition(Vec2(node->getPosition().x, node->getPosition().y));
    this->addChild(pietra3, 20);
    pietra3->runAction(
   										Sequence::create(
   										MoveTo::create(0.6, Vec2(_pietraLabel->getPosition().x, _pietraLabel->getPosition().y)),
   						                CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)),


   										NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
   										);
   	auto *pietra4 =  Sprite::create("pietra.png");
    pietra4->setPosition(Vec2(node->getPosition().x, node->getPosition().y));
    this->addChild(pietra4, 20);
    pietra4->runAction(
   										Sequence::create(
   										MoveTo::create(0.7, Vec2(_pietraLabel->getPosition().x, _pietraLabel->getPosition().y)),
   						                CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)),


   										NULL /* DO NOT FORGET TO TERMINATE WITH NULL (unexpected in C++)*/)
   										);

    _emitter_rotFlower->setPosition(Vec2(_pietraLabel->getPosition().x, _pietraLabel->getPosition().y));
    _emitter_rotFlower->resetSystem();
    _emitter_rotFlower->setDuration(0.5);


}
void HelloWorld::controllaModificaDifficolta()
{

	//controlla il livello difficolta il punteggio
    if(_score>7240){
		ext_velocita_pall10 = 1.3;
		_statoDifficolta = LIVELLO9;
	}else if(_score>6220){
		ext_velocita_pall10 = 1.4;
		_statoDifficolta = LIVELLO8;
	}else if(_score>5900){
		ext_velocita_pall10 = 1.7;
		_statoDifficolta = LIVELLO7;
	}else if(_score>3050){
		ext_velocita_pall10 = 1.9;
		_statoDifficolta = LIVELLO6;
	}else if(_score>2400){
		ext_velocita_pall10 = 2.0;
		_statoDifficolta = LIVELLO5;
	}else if(_score>1200){
		ext_velocita_pall10 = 2.4;
		_statoDifficolta = LIVELLO4;
	}else if(_score>700){
		ext_velocita_pall10 = 3.2;
		_statoDifficolta = LIVELLO3;
	}else if(_score>300){
		ext_velocita_pall10 = 4.2;
		_statoDifficolta = LIVELLO2;
	}



}
void HelloWorld::controllaPietre()
{

	if (_lives == 6) {

		   auto action1 = FadeIn::create(1.0f);
	        auto action1Back = action1->reverse();

	        auto action2 = FadeOut::create(1.0f);
	         auto action2Back = action2->reverse();
	        auto action2BackReverse = action2Back->reverse();
	        auto action2BackReverseReverse = action2BackReverse->reverse();
	        auto action3 = Blink::create(2, 10);
	        auto actionBy2 = ScaleBy::create(0.5f, 5.0f, 1.0f);
	        auto actionTint = TintTo::create(2, 255, 0, 255);

	        if(!(_statoGgugut == BLINK)) {
	            _statoGgugut = BLINK;
	            auto *pietra =  Sprite::create("pietra.png");
	            pietra->setPosition(_screenSize.width * .08 , _screenSize.height * .94);
	            pietra->setVisible(true);
	            this->addChild(pietra, 10);
	            //actionBy2, actionBy2->reverse(),actionBy2, actionBy2->reverse()
	            pietra->runAction( Sequence::create( action3,
	            										CallFuncN::create(CC_CALLBACK_1(HelloWorld::setInvisible, this)),
	            										CallFuncN::create(CC_CALLBACK_1(HelloWorld::animationDone, this)),
	                                                   CallFunc::create(
	                                                                    // lambda
	                                                                    [&](){

	                                                                          _statoGgugut = PLAY;
	                                                                    }  ),
	                                                   NULL));
	        }

	    }else{

	        _statoGgugut = PLAY;
	    }



}
float HelloWorld::randomValueBetween(float low, float high)
{
    return (((float) random() / 0xFFFFFFFFu) * (high - low)) + low;
}
void HelloWorld::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
    MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}


void HelloWorld::addParticelle() {
	         _emitter_1 = ParticleSystemQuad::createWithTotalParticles(300);
	        _emitter_1->retain();

	        addChild(_emitter_1, 15);
	        ////_emitter_1->release();    // win32 : Remove this line
	        _emitter_1->setTexture( Director::getInstance()->getTextureCache()->addImage("star.png") );

	        // duration
	        _emitter_1->setDuration(-1);

	        // gravity
	        _emitter_1->setGravity(Vec2::ZERO);

	        // angle
	        _emitter_1->setAngle(90);
	        _emitter_1->setAngleVar(360);

	        // speed of particles
	        _emitter_1->setSpeed(160);
	        _emitter_1->setSpeedVar(20);

	        // radial
	        _emitter_1->setRadialAccel(-120);
	        _emitter_1->setRadialAccelVar(0);

	        // tagential
	        _emitter_1->setTangentialAccel(30);
	        _emitter_1->setTangentialAccelVar(0);

	        // emitter position
	        _emitter_1->setPosition( Vec2(160,240) );
	        _emitter_1->setPosVar(Vec2::ZERO);

	        // life of particles
	        _emitter_1->setLife(3);
	        _emitter_1->setLifeVar(1);

	        // spin of particles
	        _emitter_1->setStartSpin(0);
	        _emitter_1->setStartSpinVar(0);
	        _emitter_1->setEndSpin(0);
	        _emitter_1->setEndSpinVar(2000);

	        // color of particles
	        Color4F startColor(0.5f, 0.5f, 0.5f, 1.0f);
	        _emitter_1->setStartColor(startColor);

	        Color4F startColorVar(0.5f, 0.5f, 0.5f, 1.0f);
	        _emitter_1->setStartColorVar(startColorVar);

	        Color4F endColor(0.1f, 0.1f, 0.1f, 0.2f);
	        _emitter_1->setEndColor(endColor);

	        Color4F endColorVar(0.1f, 0.1f, 0.1f, 0.2f);
	        _emitter_1->setEndColorVar(endColorVar);

	        // size, in pixels
	        _emitter_1->setStartSize(30.0f);
	        _emitter_1->setStartSizeVar(00.0f);
	        _emitter_1->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);

	        // emits per second
	        _emitter_1->setEmissionRate(_emitter_1->getTotalParticles()/_emitter_1->getLife());

	        // additive
	        _emitter_1->setBlendAdditive(false);
	       // _emitter_1->setPosition(Point(_visibleSize.width / 2 , _visibleSize.height / 2 ));
	        _emitter_1->stopSystem();

}


void HelloWorld::particelleRotFlower()
{

	 _emitter_rotFlower = ParticleSystemQuad::createWithTotalParticles(50);
	    _emitter_rotFlower->retain();
	    addChild(_emitter_rotFlower, 26);
	    _emitter_rotFlower->setTexture( Director::getInstance()->getTextureCache()->addImage("stars3.png") );
	    _emitter_rotFlower->setDuration(-1);

	     // gravity
	     _emitter_rotFlower->setGravity(Vec2::ZERO);

	     // angle
	     _emitter_rotFlower->setAngle(90);
	     _emitter_rotFlower->setAngleVar(360);

	     // speed of particles
	     _emitter_rotFlower->setSpeed(160);
	     _emitter_rotFlower->setSpeedVar(20);

	     // radial
	     _emitter_rotFlower->setRadialAccel(-120);
	     _emitter_rotFlower->setRadialAccelVar(0);

	     // tagential
	     _emitter_rotFlower->setTangentialAccel(30);
	     _emitter_rotFlower->setTangentialAccelVar(0);

	     // emitter position
	     _emitter_rotFlower->setPosition( Vec2(160,240) );
	     _emitter_rotFlower->setPosVar(Vec2::ZERO);

	     // life of particles
	     _emitter_rotFlower->setLife(4);
	     _emitter_rotFlower->setLifeVar(1);

	     // spin of particles
	     _emitter_rotFlower->setStartSpin(0);
	     _emitter_rotFlower->setStartSizeVar(0);
	     _emitter_rotFlower->setEndSpin(0);
	     _emitter_rotFlower->setEndSpinVar(0);

	     // color of particles
	     Color4F startColor(0.5f, 0.5f, 0.5f, 1.0f);
	     _emitter_rotFlower->setStartColor(startColor);

	     Color4F startColorVar(0.5f, 0.5f, 0.5f, 1.0f);
	     _emitter_rotFlower->setStartColorVar(startColorVar);

	     Color4F endColor(0.1f, 0.1f, 0.1f, 0.2f);
	     _emitter_rotFlower->setEndColor(endColor);

	     Color4F endColorVar(0.1f, 0.1f, 0.1f, 0.2f);
	     _emitter_rotFlower->setEndColorVar(endColorVar);

	     // size, in pixels
	     _emitter_rotFlower->setStartSize(80.0f);
	     _emitter_rotFlower->setStartSizeVar(40.0f);
	     _emitter_rotFlower->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);

	     // emits per second
	     _emitter_rotFlower->setEmissionRate(_emitter_rotFlower->getTotalParticles()/_emitter_rotFlower->getLife());

	     // additive
	     _emitter_rotFlower->setBlendAdditive(true);
	    _emitter_rotFlower->stopSystem();
}
void HelloWorld::particellePallinaNegativa()
{

	_emitter_pallinaNegativa = ParticleFire::create();
	_emitter_pallinaNegativa->retain();
	addChild(_emitter_pallinaNegativa, 30);
	_emitter_pallinaNegativa->setTexture( Director::getInstance()->getTextureCache()->addImage("fire.png") );
	//	  _emitter->setTexture( Director::getInstance()->getTextureCache()->addImage(s_fire) );//.pvr");
	_emitter_pallinaNegativa->stopSystem();

}

void HelloWorld::controllaPietraConPallinaBlu(Node *pietra)
{
                 Vec2 posizioneAssouluta = _gugo->convertToWorldSpace(_pallinaGugo->getPosition());
			     auto pallinaBlueTemp = Sprite::create("bomba_01.png");
			     pallinaBlueTemp->setPosition(posizioneAssouluta.x, posizioneAssouluta.y);
			     pallinaBlueTemp->setContentSize(Size(_pallinaBlue->getContentSize().width, _pallinaBlue->getContentSize().height));
                    if (pietra->getBoundingBox().intersectsRect(pallinaBlueTemp->getBoundingBox())){
                                        	cocos2d::log("urto con pallinaBlueTemp ..... incremento di 4 .. ");
                                        	_gugo->setColpito(true);
                                        	   //metto invisibile
                                        	 _pallinaGugo->setVisible(false);
                                           	 _lives = _lives +4;
                               				std::ostringstream value;
                               				value << _lives;
                               				_livesDisplay->setString(value.str());
                               				//TODO faccio fare esplosione e dico che ho guadagnato punti
                               				CocosDenshion::SimpleAudioEngine::getInstance()->playEffect("sounds/boom.wav");

                               				_emitter_rotFlower->setPosition(Vec2(pallinaBlueTemp->getPosition().x, pallinaBlueTemp->getPosition().y));
                               				_emitter_rotFlower->resetSystem();
                               				_emitter_rotFlower->setDuration(0.5);

                                            //15-12-2014
                                            //faccio ruotare labelPietra
                                            effettoGuadagnoPietre(pallinaBlueTemp);
                          	 }


}
