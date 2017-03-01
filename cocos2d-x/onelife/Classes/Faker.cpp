#include "Faker.h"
#include "FakerParts.h"
#include "FakerFiniteState.h"

#define FAKER_SHEEP_MAX_COUNT 10


bool Faker::init()
{
	if (!Enemy::init())
	{
		return false;
	}

	//LifeParts의 FaceType 추출
	int lifePartsFace = RandomHelper::random_int(
		(int)FakerSheep::FaceType::Face_1, (int)FakerSheep::FaceType::Face_5);
	//그외 FaceType 저장
	vector<int> faces;
	for (int i = (int)FakerSheep::FaceType::Face_1; i < (int)FakerSheep::FaceType::Face_5 + 1; i++)
	{
		if (i != lifePartsFace)
		{
			faces.push_back(i);
		}
	}

	//추출한 FaceType데이터로 Parts생성
	auto lifeParts = FakerSheep::create();
	//lifeParts->GetSprite()->setColor(Color3B::RED);
	lifeParts->SetFace((FakerSheep::FaceType)lifePartsFace);
	this->AddParts(LIFEPARTS_KEY, lifeParts, true);
	
	int faceIndex;
	FakerSheep * fakeParts = nullptr;
	for (int i = 0; i < FAKER_SHEEP_MAX_COUNT; i++)
	{
		fakeParts = FakerSheep::create();
		faceIndex = RandomHelper::random_int(0, (int)faces.size() - 1);
		fakeParts->SetFace((FakerSheep::FaceType)faces[faceIndex]);
		fakeParts->OnHidePosition();
		this->AddParts(i, fakeParts);
	}

	this->AddState(Faker::State::State_Idle, FakerIdleState::Create(this));
	this->AddState(Faker::State::State_ShowLife, FakerShowLifeState::Create(this));
	this->AddState(Faker::State::State_AllHide, FakerAllHide::Create(this));
	this->AddState(Faker::State::State_AllSideShow, FakerAllSideShow::Create(this));

	this->ChangeState(Faker::State::State_Idle);


	return true;
}


void Faker::OnActivate(bool isActive)
{
	this->GetState(Faker::State::State_Idle)->SetActive(isActive);
}
