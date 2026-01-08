#include "Player.h"

#include"KamataEngine.h"
#include"Game.h"
#include"cassert"
#include<numbers>
#include<algorithm>
#include<list>
#define NOMINMAX



using namespace KamataEngine;
using namespace MathUtility;



void Player::Initialize(Model* model, Camera* camera, KamataEngine::Vector3& position) 
{
	// NULLポイントチェック
	assert(model);

	model_ = model;

	// textureHandle_ = textureHandle;

	worldTransform_.translation_ = position;

	camera_ = camera;

	worldTransform_.rotation_.y = std::numbers::pi_v<float> / 2.0f;

	worldTransform_.Initialize();
}

void Player::Update()
{

	// 7.旋回制御
	AnimateTurn();

	// キャラクターの移動ベクトル
	//Vector3 move = {0, 0, 0};
	// キャラクターの移動速度
	//const float kCharacterSpeed = 0.2f;

	//Vector3 acceleration = {};

	// --- メンバ変数を更新 ---
	angle_ = worldTransform_.rotation_.x;
	cosValue_ = std::cos(angle_);
	sinValue_ = std::sin(angle_);

	constexpr float kTurnSpeed = 0.09f;
	worldTransform_.rotation_.x += kTurnSpeed;
	if (worldTransform_.rotation_.x > 6.2831853f) 
	{
		worldTransform_.rotation_.x -= 6.2831853f;
	}

	//// 押した方向で移動ベクトルを変更(左右)
	//if (Input::GetInstance()->PushKey(DIK_A)) 
	//{
	//	move.x -= kCharacterSpeed;
	//} else if (Input::GetInstance()->PushKey(DIK_D))
	//{
	//	move.x += kCharacterSpeed;
	//	if (velocity_.x < 0.0f) 
	//	{
	//		// 速度と逆方向に入力中は急ブレーキ
	//		velocity_.x *= (1.0f - kAttenuation);
	//	}
	//	acceleration.x += kAccleration;
	//	if (lrDirection_ != LRDirection::kRight)
	//	{
	//		lrDirection_ = LRDirection::kRight;
	//		// 旋回開始時の角度を記録する
	//		trunFirstRotationY_ = worldTransform_.rotation_.y;
	//		// 旋回タイマーに時間を設定する
	//		trunTimer_ = kTimeTurn;
	//	}
	//}
	//// 押した方向で移動ベクトルを変更(上下)
	//if (Input::GetInstance()->PushKey(DIK_W))
	//{
	//	move.y += kCharacterSpeed;
	//} else if (Input::GetInstance()->PushKey(DIK_S)) 
	//{
	//	move.y -= kCharacterSpeed;
	//}

	// 座標移動(ベクトルの加算)
	//worldTransform_.translation_ += move;

	// アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix(); // プレイヤーの座標の計算
}

// プレイヤーの描画(敵当たったら非表示になる)
void Player::Draw()
{
	if (isDead_) 
	{
		return;
	}

	model_->Draw(worldTransform_, *camera_);
}

// 7.旋回制御
void Player::AnimateTurn() 
{
	// 旋回制御
	if (trunTimer_ > 0.0f) 
	{
		trunTimer_ -= 1.0f / 60.0f;

		// 左右の自キャラ角度テーブル
		float destinationRotationYTable[] = {std::numbers::pi_v<float> / 2.0f, std::numbers::pi_v<float> * 3.0f / 2.0f};
		// 状態に応じた角度を取得する
		float destinationRotationY = destinationRotationYTable[static_cast<uint32_t>(lrDirection_)];
		// 自キャラの角度を設定する
		worldTransform_.rotation_.y = EaseInOut(destinationRotationY, trunFirstRotationY_, trunTimer_ / kTimeTurn);
	}
}

Player::~Player() {}

#pragma region プレイヤーの弾と敵の衝突

KamataEngine::Vector3 Player::CornerPosition(const KamataEngine::Vector3& center, Corner corner)
{
	KamataEngine::Vector3 offsetTable[kNumCorner] =
	{
	    {+kWidth / 2.0f, -kHeight / 2.0f, 0}, //  kRightBottom
	    {-kWidth / 2.0f, -kHeight / 2.0f, 0}, //  kLeftBottom
	    {+kWidth / 2.0f, +kHeight / 2.0f, 0}, //  kRightTop
	    {-kWidth / 2.0f, +kHeight / 2.0f, 0}  //  kLeftTop
	};

	return center + offsetTable[static_cast<uint32_t>(corner)];
}

KamataEngine::Vector3 Player::GetWorldPosition() 
{
	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

#pragma endregion