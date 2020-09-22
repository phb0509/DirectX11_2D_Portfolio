#include "Framework.h"

Monster::Monster() : isRight(false), isAttack(false), hp(0), isDie(false), speed(100),detectRange(600,400), attackRange(200,200),isDetectedPlayer(false), 
		isDetectedPlayerInAttackRange(false),onDamageStateCheckTime(0.0f), maxSlipMove(0.0f), hitRecovery(0.1f)
{
}

Monster::~Monster()
{

}
