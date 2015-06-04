/*
 * PallinaSprite.h
 *
 *  Created on: 19/nov/2014
 *      Author: XPIN12
 *
 *
 *      Uccello *_uccello = Uccello::gameSpriteWithFile("mallet.png");
 */

#ifndef UCCELLO_H_
#define UCCELLO_H_
#include "cocos2d.h"

class Uccello : public cocos2d::Sprite {
	Sprite *_pallina;
	bool _urtato = false;
	

public:
    Uccello();
    ~Uccello();

    CC_SYNTHESIZE(int, _punti, Punti);
    CC_SYNTHESIZE(bool, _colpito, Colpito);

    static Uccello* uccelloSpriteWithFile(const std::string& filename);


    inline float radius() const { return getTexture()->getContentSize().width * 0.5f; }

    virtual bool initWithFile(const std::string& filename) override;
    
    void aggiungiPallina(const std::string& filename);
    void aggiungiPallina(Sprite * node);
    void faiCaderePallina(Node * node);
    void faiVolare();
    void setInvisible(Node * node);
    void muovi();
    void muoviSinistraDestraInAlto();
    void muoviLeAli();

};



#endif /* PALLINASPRITE_H_ */
