#include "Boss.h"
#include "BossBody.h"
#include "BossHead.h"
#include "BossHand.h"

bool Boss::init()
{
	if (!Enemy::init())
	{
		return true;
	}

	auto body = BossBody::create();
	this->AddParts(body);

	auto head = BossHead::create();
	head->setPosition(0, body->GetPartsSize().height* 0.5);
	this->AddParts(head);

	auto hand = BossHand::create();
	hand->InitHand(BossHand::HandDir::HandDir_Left);
	hand->setPosition(-body->GetPartsSize().width*0.5, 0);
	this->AddParts(hand);

	hand = BossHand::create();
	hand->InitHand(BossHand::HandDir::HandDir_Right);
	hand->setPosition(body->GetPartsSize().width*0.5, 0);
	this->AddParts(hand);

	this->scheduleUpdate();
	return true;
}

void Boss::update(float dt)
{

}
