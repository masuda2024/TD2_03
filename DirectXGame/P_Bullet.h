#pragma once
#include "KamataEngine.h"
#include"MyMath.h"

class Enemy;

class Player;

class MapChipField;

class P_Bullet
{
	enum Corner {
		kRightBottom,
		kLeftBottom,
		kRightTop,
		kLeftTop,

		kNumCorner
	};

public:
	
	struct CollisionMapInfo {
		bool ceiling = false;
		bool landing = false;
		bool hitLeftWall = false;
		bool hitRightWall = false;
		KamataEngine::Vector3 move;
	};

	void Initialize(KamataEngine::Model* model, KamataEngine::Camera* camera, Player* player);

	void Update();

	void StartAttack();

	void Draw();

	
	 // 有効かどうか
	bool IsActive() const { return isActive_; }

	// 終了フラグ
	bool isFinished_ = false;

	// デスフラグ
	bool isPBDead_ = false;

	bool IsPBDead() const { return isPBDead_; }

	void SetMapChipField(MapChipField* mapChipField) { mapChipField_ = mapChipField; }


	// ワールド座標を取得
	KamataEngine::Vector3 GetWorldPosition();

	void SetPosition(const KamataEngine::Vector3& position);

	KamataEngine::Vector3 velocity_ = {};

	KamataEngine::Vector3 CornerPosition(const KamataEngine::Vector3& center, Corner corner);

#pragma region プレイヤーの弾と敵の衝突

	// AABBを取得
	AABB GetAABB();
	// 衝突応答
	void OnCollition(const Enemy* enemy);

#pragma endregion

	//弾の反射用

	void CheckMapCollision(CollisionMapInfo& info);

	void CheckMapCollisionUp(CollisionMapInfo& info);
	void CheckMapCollisionDown(CollisionMapInfo& info);
	void CheckMapCollisionRight(CollisionMapInfo& info);
	void CheckMapCollisionLeft(CollisionMapInfo& info);

	void CheckMapHit(CollisionMapInfo& info);


private:
	static inline const float kBlank = 0.1f;

	MapChipField* mapChipField_ = nullptr;

	// 攻撃のON/OFF
	bool isActive_ = false;

	Player* player_ = nullptr;

	// ワールド変換データ
	KamataEngine::WorldTransform worldTransform_;

	// モデル
	KamataEngine::Model* model_;

	// カメラ
	KamataEngine::Camera* camera_;

	// 速度
	KamataEngine::Vector3 Bulletvelocity_;

	float timer_ = 0.0f;
	static inline const float kLifeTime = 3.0f; 
	// 当たり判定サイズ
	static inline const float kWidth = 0.8f;
	static inline const float kHeight = 0.8f;
};
