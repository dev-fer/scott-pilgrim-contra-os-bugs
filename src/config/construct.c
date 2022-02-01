#include "../headers.h"

Card create_card(char *urlCard, int maxFrame, int frameDelay, int frameWidth, int frameHeight, int frameStartWidth, int frameStartHeight, int frameFinishWidth, int frameFinishHeight, float cardX, float cardY, char *urlMiniCard) {
    Card c;
    c.card = al_load_bitmap(urlCard);
    verifyAllegroFunction(c.card, "image not found");
    c.maxFrame = maxFrame;
    c.currentFrame = 0;
    c.frameCount = 0;
    c.frameDelay = frameDelay;
    c.frameWidth = frameWidth;
    c.frameHeight = frameHeight;
    c.frameStartWidth = frameStartWidth;
    c.frameStartHeight = frameStartHeight;
    c.frameFinishWidth = frameFinishWidth;
    c.frameFinishHeight = frameFinishHeight;
    c.cardX = cardX;
    c.cardY = cardY;
    c.urlMiniCard = urlMiniCard;
    return c;
}

EnemyCard create_enemy_card(char *urlCard, float cardX, float cardY) {
    EnemyCard ec;
    ec.card = al_load_bitmap(urlCard);
    verifyAllegroFunction(ec.card, "image not found");
    ec.cardX = cardX;
    ec.cardY = cardY;
    return ec;
}

MiniCard create_mini_card(char *urlCard, float cardX, float cardY) {
    MiniCard mc;
    mc.card = al_load_bitmap(urlCard);
    verifyAllegroFunction(mc.card, "image not found");
    mc.cardX = cardX;
    mc.cardY = cardY;
    return mc;
}

CharacterCard create_character_card(char *urlCard, float cardX, float cardY) {
    CharacterCard cc;
    cc.card = al_load_bitmap(urlCard);
    verifyAllegroFunction(cc.card, "image not found");
    cc.cardX = cardX;
    cc.cardY = cardY;
    return cc;
}

Button create_button(char *urlButton, int maxFrame, int frameDelay, int frameWidth, int frameHeight, float buttonX, float buttonY) {
    Button b;
    b.button = al_load_bitmap(urlButton);
    verifyAllegroFunction(b.button, "image not found");
    b.maxFrame = maxFrame;
    b.currentFrame = 0;
    b.frameCount = 0;
    b.frameDelay = frameDelay;
    b.frameWidth = frameWidth;
    b.frameHeight = frameHeight;
    b.buttonX = buttonX;
    b.buttonY = buttonY;
    return b;
}
