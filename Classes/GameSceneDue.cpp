//
//  GameSceneDue.cpp
//  gugut
//
//  Created by silviomaz on 06/01/15.
//
//
//test 

#include "GameSceneDue.h"
#include "PallinaSprite.h"

USING_NS_CC;

static const int PIETRA_TAG = 0x80;
static const int PALLINE_TAG = 0x90;

float randomValueTra(float low, float high)
{
    return (((float) random() / 0xFFFFFFFFu) * (high - low)) + low;
}

Scene* GameSceneDue::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::createWithPhysics();
    scene->getPhysicsWorld()->setDebugDrawMask( PhysicsWorld::DEBUGDRAW_ALL );
    
   // scene->getPhysicsWorld()->setGravity( Vec2( 0, 0 ) );
    scene->getPhysicsWorld()->setGravity( Vec2( 0, -100 ) );
    
    // 'layer' is an autorelease object
    auto layer = GameSceneDue::create();
    layer->SetPhysicsWorld( scene->getPhysicsWorld() );
    
    // add layer as a child to scene
    scene->addChild(layer);
    
    
    
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameSceneDue::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
     _visibleSize = Director::getInstance()->getVisibleSize();
    _origin = Director::getInstance()->getVisibleOrigin();
    
    //definisco le pallina che lancia Gugut
    _pietre = new Vector<Sprite*>(20);
    for (int i = 0; i < 19; ++i) {
        auto *pietra =  Sprite::create("pietra.png");
        pietra->setVisible(false);
        pietra->setTag(PIETRA_TAG);
 
       /* auto spriteBody = PhysicsBody::createBox( pietra->getContentSize( ), PhysicsMaterial( 0, 1, 0 ) );
        
        //spriteBody->applyImpulse( Vect( 400, 700 ) );
        
        pietra->setPhysicsBody( spriteBody );
        spriteBody->setTag(PIETRA_TAG);//Tag del PhysicsBody
        spriteBody->setCollisionBitmask(5);
        spriteBody->setContactTestBitmask(true);
        */
        this->addChild(pietra, 11);
        _pietre->pushBack(pietra);
    }
    
	#define MUMEROPALLINE 5
    _palline = new Vector<PallinaSprite*>(MUMEROPALLINE);
    char strPallina[100] = {0};
    for (int i = 2; i < 6; ++i) {
        sprintf(strPallina, "sfera_%02d.png",i); //da 02 .. 05  totale 4 palline
        auto *pallina = PallinaSprite::pallinaSpriteWithFile(strPallina);
        pallina->setVisible(true);
        pallina->setTag(i);

		if(i == 2){
		        auto spriteBody = PhysicsBody::createCircle(pallina->getContentSize().width/2,  PhysicsMaterial(1.0f, 1.0f, 0.1f));
		        spriteBody->setCollisionBitmask(3);
		        spriteBody->setContactTestBitmask(true);
		        pallina->setPhysicsBody( spriteBody );
                pallina->setPosition(Vec2( _visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y ));
                spriteBody->setTag(12);
		        pallina->setPunti(10);
		}
		if(i == 3){
			        auto spriteBody = PhysicsBody::createCircle(pallina->getContentSize().width/2,  PhysicsMaterial(0.05f, 1.0f, 0.1f));
			        spriteBody->setCollisionBitmask(3);
			        spriteBody->setContactTestBitmask(true);
			        pallina->setPhysicsBody( spriteBody );
	                pallina->setPosition(Vec2( _visibleSize.width / 3 + _origin.x, _visibleSize.height / 3 + _origin.y ));
	                spriteBody->setTag(13);
			        pallina->setPunti(10);
			}
		if(i == 4){
			        auto spriteBody = PhysicsBody::createCircle(pallina->getContentSize().width/2,  PhysicsMaterial(0.95f, 1.0f, 0.1f));
			        spriteBody->setCollisionBitmask(3);
			        spriteBody->setContactTestBitmask(true);
			        pallina->setPhysicsBody( spriteBody );
	                pallina->setPosition(Vec2( _visibleSize.width / 4 + _origin.x, _visibleSize.height / 2 + _origin.y ));
	                spriteBody->setTag(14);
			        pallina->setPunti(10);
			}
		if(i == 5){
			        auto spriteBody = PhysicsBody::createCircle(pallina->getContentSize().width/2,  PhysicsMaterial(0.05f, 0.9f, 0.9f));
			        spriteBody->setCollisionBitmask(3);
			        spriteBody->setContactTestBitmask(true);
			        pallina->setPhysicsBody( spriteBody );
	                pallina->setPosition(Vec2( _visibleSize.width * 0.8 + _origin.x, _visibleSize.height / 2 + _origin.y ));
	                spriteBody->setTag(15);
			        pallina->setPunti(10);
			}
        this->addChild(pallina, 9);
        _palline->pushBack(pallina);
        //applico forza
      //  if(i == 4)
       // 	pallina->getPhysicsBody()->applyForce( Vect(100, 78) );
       // if(i == 5)
       //        	pallina->getPhysicsBody()->applyForce( Vect(200, 78) );
    }


    
    _muro = Sprite::create("muro.png");
    _muro->setAnchorPoint(Vec2(0.0,  0.0));
    _muro->setPosition(Vec2(_origin.x,  _origin.y));
    this->addChild(_muro, 6);
    
    //Gugut
    _gugutAnimato = Sprite::create("gugut_01.png");
    _gugutAnimato->setVisible(true);
    _gugutAnimato->setAnchorPoint(Vec2(0.5,  0.2));//+(_muro->getContentSize().height )+(_gugutAnimato->getContentSize().height )
    //_gugutAnimato->setPosition(Vec2(_muro->getContentSize().width/2 + origin.x, (_muro->getContentSize().height * 1.45)+ origin.y));
    _gugutAnimato->setPosition(Vec2(_muro->getContentSize().width/2 + _origin.x,(_muro->getContentSize().height )+ _origin.y));
    
    this->addChild(_gugutAnimato, 8);
    
    
    auto edgeBody = PhysicsBody::createEdgeBox( _visibleSize, PHYSICSBODY_MATERIAL_DEFAULT, 3 );
    
    auto edgeNode = Node::create();
    edgeNode ->setPosition( Point( _visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y ) );
    edgeNode->setPhysicsBody( edgeBody );
    
    this->addChild( edgeNode );
    
 /*   {
        auto sprite = Sprite::create( "CloseNormal.png" );
        sprite->setPosition( Point( _visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y ) );
        
        auto spriteBody = PhysicsBody::createBox( sprite->getContentSize( ), PhysicsMaterial( 0, 1, 0 ) );
        spriteBody->setCollisionBitmask(1);
        spriteBody->setContactTestBitmask(true);
        
        sprite->setPhysicsBody( spriteBody );
        
        this->addChild( sprite );
    }
    
    {
        auto sprite = Sprite::create( "CloseNormal.png" );
        sprite->setPosition( Point( _visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y + 200 ) );
        
        auto spriteBody = PhysicsBody::createBox( sprite->getContentSize( ), PhysicsMaterial( 0, 1, 0 ) );
        spriteBody->setCollisionBitmask(2);
        spriteBody->setContactTestBitmask(true);
        
        sprite->setPhysicsBody( spriteBody );
        
        this->addChild( sprite );
    }
    */
    /*  {
     auto sprite2 = Sprite::create( "CloseNormal.png" );
     sprite2->setPosition( Point( visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y ) );
     
     auto spriteBody2 = PhysicsBody::createBox( sprite2->getContentSize( ), PhysicsMaterial( 0, 1, 0 ) );
     spriteBody2->setAngularVelocity(400);
     spriteBody2->setAngularDamping( 1 );
     spriteBody2->setAngularVelocityLimit(500);
     spriteBody2->setCollisionBitmask(3);
     spriteBody2->setContactTestBitmask(true);
     
     sprite2->setPhysicsBody( spriteBody2 );
     
     this->addChild( sprite2 );
     }
     */
 /*   {
        auto sprite = Sprite::create( "CloseNormal.png" );
        sprite->setPosition( Point( _visibleSize.width / 3 + _origin.x, _visibleSize.height / 2 + _origin.y ) );
        
        auto spriteBody = PhysicsBody::createBox( sprite->getContentSize( ), PhysicsMaterial( 0, 1, 0 ) );
        spriteBody->setVelocity( Vect( 100, 247 ) );
        spriteBody->setVelocityLimit( 500 );
        spriteBody->setLinearDamping( 0.5 );
        
        sprite->setPhysicsBody( spriteBody );
        
        this->addChild( sprite );
        
    }
    {
        auto sprite = Sprite::create( "CloseNormal.png" );
        sprite->setPosition( Point( _visibleSize.width / 4 + _origin.x, _visibleSize.height / 3 + _origin.y ) );
        
        auto spriteBody = PhysicsBody::createBox( sprite->getContentSize( ), PhysicsMaterial( 0, 1, 0 ) );
        
        spriteBody->applyImpulse( Vect( 400, 700 ) );
        
        sprite->setPhysicsBody( spriteBody );
        
        this->addChild( sprite );
    }
    
    */
    auto contactListener = EventListenerPhysicsContact::create();
    contactListener->onContactBegin = CC_CALLBACK_1(GameSceneDue::onContactBegin, this);
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
    
    
    /*
    _player = CCSprite::create("sfera_02.png");//creo sprite
    auto body = PhysicsBody::createCircle
    (_player->getContentSize().width / 2, PhysicsMaterial( 0, 1, 0 ) ); //creo un Physics Body
    // body->setContactTestBitmask(true);
    //body->setDynamic(true);  //Tipo dinamico
    body->setCollisionBitmask(3);
    body->setContactTestBitmask(true);
    _player->setPhysicsBody(body);  //Lo setto come proprieta del nodo
    
    _player->setPosition(Vec2(_origin.x + _visibleSize.width/6,
                              _origin.y + _visibleSize.height/2));
    
    this->addChild( _player );
    */
    
    
    auto dispatcher = Director::getInstance()->getEventDispatcher();
    auto listener = EventListenerTouchOneByOne::create();
    
    listener->onTouchBegan = CC_CALLBACK_2(GameSceneDue::onTouchBegan, this);
    listener->onTouchMoved = CC_CALLBACK_2(GameSceneDue::onTouchMoved, this);
    //  listener->onTouchMoved = CC_CALLBACK_2(GameLayer::onTouchMoved, this);
    //listener->onTouchEnded = CC_CALLBACK_2(GameLayer::onTouchEnded, this);
    
    dispatcher->addEventListenerWithSceneGraphPriority(listener, this);
    
    

    addPartcleStella(Vec2(0,0));
    
    
    Sprite* parent = Sprite::create("unpixel.png");
    parent->setTextureRect(CCRectMake(0,0, 400, 200));
    parent->setColor(ccc3(255,0, 0));
    parent->setAnchorPoint(Vec2(0,0));
    parent->setPosition(Vec2( _visibleSize.width / 2 + _origin.x, _visibleSize.height / 2 + _origin.y));
    auto edgeBody2 = PhysicsBody::createBox( parent->getContentSize( ), PHYSICSBODY_MATERIAL_DEFAULT, Vec2(0,0) );
    edgeBody2->setDynamic(false);
    parent->setPhysicsBody( edgeBody2 );
    this->addChild(parent, 20);

    return true;
}

bool GameSceneDue::onContactBegin(cocos2d::PhysicsContact &contact)
{
	cocos2d::log("GameSceneDue::onContactBegin   ....... inizio   ");
    PhysicsBody *a = contact.getShapeA()->getBody();
    PhysicsBody *b = contact.getShapeB()->getBody();
    
    // check if the bodies have collided
  /*  if ( ( 1 == a->getCollisionBitmask() && 2 == b->getCollisionBitmask() ) || ( 2 == a->getCollisionBitmask() && 1 == b->getCollisionBitmask() ) )
    {
        CCLOG( "GameSceneDue::onContactBegin COLLISION HAS OCCURED" );
        a->applyForce( Vect(100, 78) );
        b->applyForce( Vect(100, 78) );
        b->resetForces();
    }
*/
    PhysicsBody *pallinaBody = nullptr ;
    if ( ! (3 == a->getCollisionBitmask() && 3 == b->getCollisionBitmask())){
			if (  3 == a->getCollisionBitmask() )
			   {
				  // CCLOG( "GameSceneDue::onContactBegin COLLISION HAS OCCURED" );
				   pallinaBody = contact.getShapeA()->getBody();
			   }

			if (   3 == b->getCollisionBitmask() )
			   {
					pallinaBody = contact.getShapeB()->getBody();
			   }
        
         if(pallinaBody){


        	 _emitter->setPosition(pallinaBody->getNode()->getPosition());
        	 _emitter->resetSystem();
        	 _emitter->setDuration(0.5);

			//prendo tag
			  if (12 == pallinaBody->getTag()){
			        	  cocos2d::log("GameSceneDue::onContactBegin   colpita pallina 2  ");
                    //deve variare la y
			        	 // pallinaBody->applyForce( Vect(-50, -220) );
                         pallinaBody->setVelocity(Vec2(randomValueTra(900,900),
                        		 randomValueTra(0,500)));
			    }
			  if (13 == pallinaBody->getTag()){
						        	  cocos2d::log("GameSceneDue::onContactBegin  colpita pallina 3   ");

                  pallinaBody->setVelocity(Vec2(randomValueTra(900,1900),
                		  randomValueTra(0,800)));
				}
			  if (14 == pallinaBody->getTag()){
			 						        	  cocos2d::log("GameSceneDue::onContactBegin  colpita pallina 4   ");

                  pallinaBody->setVelocity(Vec2(randomValueTra(900,1900),
                		  randomValueTra(0,800)));

			 				}
			  if (15 == pallinaBody->getTag()){
			 						        	  cocos2d::log("GameSceneDue::onContactBegin   colpita pallina 5  ");

                  pallinaBody->setVelocity(Vec2(randomValueTra(900,1900),
                		  randomValueTra(-400,800)));
			 				}
           }
        }


          if (PIETRA_TAG == a->getTag()){
        	//  cocos2d::log("GameSceneDue::onContactBegin   ....... 1  ");
              a-> getNode()->stopAllActions();
        	  a-> getNode()->setVisible(false);
              a->removeFromWorld();
              //a->setEnable(false);         	 // a->applyForce( Vect(100, 78) );
          }
          if (PIETRA_TAG == b->getTag()   ){
        	 // cocos2d::log("GameSceneDue::onContactBegin   ....... 2  ");
               b-> getNode()->stopAllActions();
        	  b-> getNode()->setVisible(false);
              b->removeFromWorld();

             // b->setEnable(false);
        	 // b->applyForce( Vect(100, 78) );
         }

         // a-> getNode()->stopAllActions();
         // b-> getNode()->stopAllActions();

         // PhysicsBody* bodyPallina = (a->getCategoryBitmask() == 0x04 || a->getCategoryBitmask() == 0x08) ? a : b;
              CCLOG("Forse megio cosi recupero i tag e poi faccio tutto" );
              auto sp = (Sprite*)contact.getShapeA()->getBody()->getNode();
              int tag = sp->getTag();
              CCLOG("onContactBegin tag di A : %d", tag);
              auto spb = (Sprite*)contact.getShapeA()->getBody()->getNode();
				int tagb = spb->getTag();
				CCLOG("onContactBegin tag di B : %d", tagb);


    return true;
}

void GameSceneDue::onTouchMoved(cocos2d::Touch *touch, cocos2d::Event *event)
{
    
  //  _player->setPosition(Vec2(_player->getPositionX()+touch->getDelta().x, _player->getPositionY()+touch->getDelta().y));
    
    // _player->setPosition(Vec2(0,0));

	 // _boom->setPosition(_rocket->getPosition());
	//  _boom->resetSystem();
	 // _boom->setDuration(1);
    
}


bool  GameSceneDue::onTouchBegan(Touch *touch, Event *unused_event){
    
    
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
   
    proiettile->setPosition(Vec2(_gugutAnimato->getPosition().x,_gugutAnimato->getPosition().y+(_gugutAnimato->getContentSize().height)*0.3));
    proiettile->setVisible(true);
    
    auto spriteBody = PhysicsBody::createBox( proiettile->getContentSize( ), PhysicsMaterial( 0, 1, 0 ) );
    
    //spriteBody->applyImpulse( Vect( 400, 700 ) );
    
    proiettile->setPhysicsBody( spriteBody );
    spriteBody->setTag(PIETRA_TAG);//Tag del PhysicsBody
    spriteBody->setCollisionBitmask(5);
    spriteBody->setContactTestBitmask(true);
    
    spriteBody->setVelocity(targetPositionProiettileTo);

    
    ///addChild(proiettile, 9); in ios dava problemi perche aggiunto prima
    
 /*   auto moveToTargetPosition = MoveTo::create(1.2, targetPositionProiettileTo);
    
    
    auto seq2 = Sequence::create(moveToTargetPosition, NULL);
    
    proiettile->runAction(
                          Sequence::create(moveToTargetPosition,
                                           CallFuncN::create(CC_CALLBACK_1(GameSceneDue::setInvisible, this)),
                                           NULL )
                          );
    
   */
    
    return true;
    
}

void GameSceneDue::setInvisible(Node * node) {
    node->setVisible(false);
}


void GameSceneDue::addPartcleStella(Vec2 posizione) {

	        _boom = ParticleSystemQuad::createWithTotalParticles(900);
	        _boom->setTexture(Director::getInstance()->getTextureCache()->addImage("gugut_01.png"));

	        //The code below we can use both in 2.x and 3.x
	        _boom->setDuration(-1);
	        _boom->setGravity(Point(0, -240));  // in Cocos2d-x-2.x CCPoint(0, -240) is used
	        _boom->setAngle(90);
	        _boom->setAngleVar(360);
	        _boom->setRadialAccel(50);
	        _boom->setRadialAccelVar(0);
	        _boom->setTangentialAccel(30);
	        _boom->setTangentialAccelVar(0);
	        _boom->setPosition(Point(_visibleSize.width / 2 , _visibleSize.width / 2 ));
	        _boom->setPosVar(Point(400, 0));
	        _boom->setLife(4);
	        _boom->setLifeVar(2);
	        _boom->setStartSpin(30);
	        _boom->setStartSpinVar(60);
	        _boom->setEndSpin(60);
	        _boom->setEndSpinVar(60);
	        _boom->setStartColor(Color4F(255,255,255,1));
	        _boom->setStartColorVar(Color4F(0,0,0,0));
	        _boom->setEndColor(Color4F(255, 255, 255, 1));
	        _boom->setEndColorVar(Color4F(0, 0, 0, 0));
	        _boom->setStartSize(30);
	        _boom->setStartSizeVar(0);
	        _boom->setEndSize(20.0f);
	        _boom->setEndSizeVar(0);
	        _boom->setEmissionRate(100);
	        _boom->stopSystem();
	        addChild(_boom,10);



	       _emitter = ParticleSystemQuad::createWithTotalParticles(300);
	        _emitter->retain();

	        addChild(_emitter, 15);
	        ////_emitter->release();    // win32 : Remove this line
	        _emitter->setTexture( Director::getInstance()->getTextureCache()->addImage("star.png") );

	        // duration
	        _emitter->setDuration(-1);

	        // gravity
	        _emitter->setGravity(Vec2::ZERO);

	        // angle
	        _emitter->setAngle(90);
	        _emitter->setAngleVar(360);

	        // speed of particles
	        _emitter->setSpeed(160);
	        _emitter->setSpeedVar(20);

	        // radial
	        _emitter->setRadialAccel(-120);
	        _emitter->setRadialAccelVar(0);

	        // tagential
	        _emitter->setTangentialAccel(30);
	        _emitter->setTangentialAccelVar(0);

	        // emitter position
	        _emitter->setPosition( Vec2(160,240) );
	        _emitter->setPosVar(Vec2::ZERO);

	        // life of particles
	        _emitter->setLife(3);
	        _emitter->setLifeVar(1);

	        // spin of particles
	        _emitter->setStartSpin(0);
	        _emitter->setStartSpinVar(0);
	        _emitter->setEndSpin(0);
	        _emitter->setEndSpinVar(2000);

	        // color of particles
	        Color4F startColor(0.5f, 0.5f, 0.5f, 1.0f);
	        _emitter->setStartColor(startColor);

	        Color4F startColorVar(0.5f, 0.5f, 0.5f, 1.0f);
	        _emitter->setStartColorVar(startColorVar);

	        Color4F endColor(0.1f, 0.1f, 0.1f, 0.2f);
	        _emitter->setEndColor(endColor);

	        Color4F endColorVar(0.1f, 0.1f, 0.1f, 0.2f);
	        _emitter->setEndColorVar(endColorVar);

	        // size, in pixels
	        _emitter->setStartSize(30.0f);
	        _emitter->setStartSizeVar(00.0f);
	        _emitter->setEndSize(ParticleSystem::START_SIZE_EQUAL_TO_END_SIZE);

	        // emits per second
	        _emitter->setEmissionRate(_emitter->getTotalParticles()/_emitter->getLife());

	        // additive
	        _emitter->setBlendAdditive(false);
	        _emitter->setPosition(Point(_visibleSize.width / 2 , _visibleSize.height / 2 ));
	        _emitter->stopSystem();




}

void GameSceneDue::addPalline (float dt){
    cocos2d::log("GameSceneDue::addPalline .....");



    auto *pallina = _palline->at( _nextPallina);

    _nextPallina++;

    if ( _nextPallina >= _palline->size())
        _nextPallina = 0;



}

