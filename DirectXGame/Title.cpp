#include "Title.h"
#include "KamataEngine.h"

using namespace KamataEngine;

void Title::Initialize()
{
	
	// カメラの初期化
	camera_.Initialize();
	// ワールド変換の初期化
	worldTransform_.Initialize();
	
	// フェード
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);
}

void Title::Update() 
{

	switch (phase_)
	{
	case Phase::kMain:

		// タイトルシーンの終了条件
		if (Input::GetInstance()->TriggerKey(DIK_SPACE))
		{

			//Audio::GetInstance()->PlayWave(Botan_);
			// フェードアウト開始
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
			finishedTitle_ = true;
		}
		if (Input::GetInstance()->TriggerKey(DIK_T))
		{
			//Audio::GetInstance()->PlayWave(Botan_);
			// フェードアウト開始
			phase_ = Phase::kFadeOut;
			fade_->Start(Fade::Status::FadeOut, 1.0f);
			finishedTitle2_ = true;
		}
		break;
	case Phase::kFadeIn:
		// フェード
		fade_->Update();
		if (fade_->IsFinished()) 
		{
			phase_ = Phase::kMain;
		}
		break;
	case Phase::kFadeOut:
		// フェード
		fade_->Update();
		if (fade_->IsFinished()) 
		{
			finishedTitle_ = true;
		} else 
		{
			finishedTitle2_ = true;
		}
		break;
	}
}

void Title::Draw() 
{
	// DirectXCommonインスタンスの取得
	//DirectXCommon* dxCommon = DirectXCommon::GetInstance();

	

	//Sprite::PreDraw();

	//titleSprite_->Draw();

	//Sprite::PostDraw();

	// フェード
	fade_->Draw();
}

Title::~Title() 
{

	//  フェード
	delete fade_;
	// タイトルのスプライト
	//delete titleSprite_;
}