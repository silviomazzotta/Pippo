/*
 * PallinaSprite.h
 *
 *  Created on: 19/nov/2014
 *      Author: XPIN12
 *
 *
 *      GameSprite *_ball = GameSprite::gameSpriteWithFile("mallet.png");
 */

#ifndef PALLINASPRITE_H_
#define PALLINASPRITE_H_
#include "cocos2d.h"

class PallinaSprite : public cocos2d::Sprite {
public:
    PallinaSprite();
    ~PallinaSprite();

    CC_SYNTHESIZE(int, _punti, Punti);

    static PallinaSprite* pallinaSpriteWithFile(const std::string& filename);


    inline float radius() const { return getTexture()->getContentSize().width * 0.5f; }

    virtual bool initWithFile(const std::string& filename) override;
};



#endif /* PALLINASPRITE_H_ */
