#include "P_Bullet.h"
#include "KamataEngine.h"

#include"Player.h"
#include"Game.h"


#include <list>
#define NOMINMAX


using namespace KamataEngine;
using namespace MathUtility;

void P_Bullet::Initialize(KamataEngine::Model* model, Camera* camera, Player* player) {
	// NULLポイントチェック
	// assert(model);

	model_ = model;

	camera_ = camera;

	player_ = player;

	// ワールド変換データ初期化
	worldTransform_.Initialize();

	isActive_ = false;
}

void P_Bullet::Update() 
{
	if (!isActive_) {
		return;
	}

	worldTransform_.translation_ += velocity_;

	timer_ += 1.0f / 60.0f;
	if (timer_ >= kLifeTime) {
		isActive_ = false;
		return;
	}


	// アフィン変換行列
	worldTransform_.matWorld_ = MakeAffineMatrix(worldTransform_.scale_, worldTransform_.rotation_, worldTransform_.translation_);
	worldTransform_.TransferMatrix(); // プレイヤーの座標の計算
}

void P_Bullet::StartAttack() {
	if (!player_)
		return;
	isActive_ = true;
	timer_ = 0.0f;

	 const auto& rot = player_->GetRotation();

	float pitch = rot.x; // 上下
	float yaw = rot.y;   // 左右

	// Player の向き通りの forward

	KamataEngine::Vector3 forward;
	forward.x = cosf(pitch) * sinf(yaw);
	forward.y = -sinf(pitch);
	forward.z = -cosf(pitch) * cosf(yaw);

	velocity_ = forward;

	const float kSpawnOffset = 1.5f;
	worldTransform_.translation_ = player_->GetWorldPosition() + forward * kSpawnOffset;

}

void P_Bullet::Draw() 
{
	if (!isActive_) {
		return;
	}

	model_->Draw(worldTransform_, *camera_);
}

KamataEngine::Vector3 P_Bullet::GetWorldPosition() 
{
	// ワールド座標を入れる変数
	KamataEngine::Vector3 worldPos;
	// ワールド行列の平行移動成分を取得(ワールド座標)
	worldPos.x = worldTransform_.matWorld_.m[3][0];
	worldPos.y = worldTransform_.matWorld_.m[3][1];
	worldPos.z = worldTransform_.matWorld_.m[3][2];

	return worldPos;
}

void P_Bullet::SetPosition(const KamataEngine::Vector3& position) { worldTransform_.translation_ = position; }

#pragma region プレイヤーの弾と敵の衝突

AABB P_Bullet::GetAABB()
{
	KamataEngine::Vector3 worldPos = GetWorldPosition();

	AABB aabb;

	aabb.min = {worldPos.x - kWidth / 2.0f, worldPos.y - kHeight / 2.0f, worldPos.z - kWidth / 2.0f};
	aabb.max = {worldPos.x + kWidth / 2.0f, worldPos.y + kHeight / 2.0f, worldPos.z + kWidth / 2.0f};

	return aabb;
}

// 弾と敵の衝突応答
void P_Bullet::OnCollition(const Enemy* enemy) { (void)enemy; }

#pragma endregion