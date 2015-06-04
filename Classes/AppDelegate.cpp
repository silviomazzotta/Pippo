#include "AppDelegate.h"
#include "HelloWorldScene.h"
#include "GlobalVariable.h"
#include "GameSceneDue.h"
#include "MenuScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLView::create("My Game");
        director->setOpenGLView(glview);
    }

    Size screenSize = director->getWinSize();

  //  Size designSize = Size(2048, 1536);
    //  glview->setDesignResolutionSize(designSize.width, designSize.height, ResolutionPolicy::EXACT_FIT);
    // 1
    // aggiunto per il multiresolution
    Size designSize = Size(480,320);
    Size resourceSize = Size(960,640);
    // 2
  /*  director->setContentScaleFactor(resourceSize.height / designSize.height);
    director->getOpenGLView()->setDesignResolutionSize(
    designSize.width, designSize.height, ResolutionPolicy::FIXED_HEIGHT);
    */
    director->setContentScaleFactor(resourceSize.width / designSize.width);
    director->getOpenGLView()->setDesignResolutionSize(
    designSize.width, designSize.height, ResolutionPolicy::FIXED_WIDTH);





    FileUtils::getInstance()->setSearchPaths({"iphone"});
    width_gugut=94;
    heigth_gugut=180;
    width_esplosione=190;
    heigth_esplosione=190;
    width_uccello=80;
    heigth_uccello=60;
    width_gugutsaluta=152;
    heigth_gugutsaluta=180;
/*
     width_gugut=126;
    heigth_gugut=240;
    width_esplosione=300;
    heigth_esplosione=300;
    width_uccello=130;
    heigth_uccello=98;
    width_gugutsaluta=203;
    heigth_gugutsaluta=240;
*/

     //  ...... FINE   ....

    /*

  if (screenSize.height > 1280) {
       FileUtils::getInstance()->setSearchPaths({"ipadhd"});
       width_gugut=193;
       heigth_gugut=367;
       width_esplosione=480;
       heigth_esplosione=480;
       width_uccello=280;
       heigth_uccello=211;
       width_gugutsaluta=310;
       heigth_gugutsaluta=367;

    } else if (screenSize.height > 639) {
       FileUtils::getInstance()->setSearchPaths({"ipad"});
       width_gugut=126;
       heigth_gugut=240;
       width_esplosione=300;
       heigth_esplosione=300;
       width_uccello=130;
       heigth_uccello=98;
       width_gugutsaluta=203;
       heigth_gugutsaluta=240;

    } else {
       FileUtils::getInstance()->setSearchPaths({"iphone"});
       width_gugut=63;
       heigth_gugut=120;
       width_esplosione=190;
       heigth_esplosione=190;
       width_uccello=80;
       heigth_uccello=60;
       width_gugutsaluta=102;
       heigth_gugutsaluta=120;

    }
*/

 //    director->setContentScaleFactor(screenSize.height/designSize.height);

    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);

    // create a scene. it's an autorelease object
    auto scene = MenuScene::createScene();

    //auto scene = GameSceneDue::createScene();

    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
    // SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
    // SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
