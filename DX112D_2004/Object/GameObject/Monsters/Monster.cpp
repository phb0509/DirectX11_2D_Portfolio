#include "Framework.h"

Monster::Monster() : isRight(false), isAttack(false), hp(100), isDie(false), speed(100),detectRange(400,400), isDetectedPlayer(false)
{
}

Monster::~Monster()
{

}
