/*
 * PallinaSprite.cpp
 *
 *  Created on: 19/nov/2014
 *      Author: XPIN12
 */

#include "PallinaSprite.h"



bool PallinaSprite::initWithFile(const std::string& filename) {
    return cocos2d::Sprite::initWithFile(filename);
}

PallinaSprite::~PallinaSprite() {
}
PallinaSprite::PallinaSprite() {
}


//come create in Sprite
PallinaSprite* PallinaSprite::pallinaSpriteWithFile(const std::string& filename) {
    auto sprite = new PallinaSprite();
    if (sprite && sprite->initWithFile(filename)) {
        sprite->autorelease();
        return sprite;
    }
    CC_SAFE_DELETE(sprite);
    return nullptr;
}

