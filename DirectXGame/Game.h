#pragma once
#include "KamataEngine.h"

#include "CameraController.h"
#include "Skydome.h"


#include "Player.h"
#include "P_DeathParticle.h"
#include "P_Bullet.h"


#include "Enemy.h"
//#include "E_DeathParticle.h"



#include "Fade.h"
#include <list>
#include <vector>
#define NOMINMAX
#include <Windows.h>
#include <algorithm>
// ゲームシーン

using namespace KamataEngine;

class Game
{
public:
	// デストラクタ
	~Game();

	// 初期化
	void Initialize();

	// 更新
	void Update();

	// 描画
	void Draw();

	// 終了フラグ
	bool finishedGAME_ = false;
	// デスフラグのgetter
	bool IsFinishedGAME() const { return finishedGAME_; } // ゲームオーバー

	// 敵を倒した場合のフラグ
	bool finishedGAME2_ = false;
	bool IsFinishedGAME2() const { return finishedGAME2_; } ////ゲームクリア

private:
	// テクスチャハンドル
	uint32_t textureHandle_ = 0;
	// 3Dモデルデータ
	KamataEngine::Model* model_ = nullptr;

	std::vector<std::vector<KamataEngine::WorldTransform*>> worldTransformBlocks_; // stdでエラーが起きたらKamataEngine::をいれる

	// デバックカメラ有効
	bool isDebugCameraActive_ = false;

	// デバックカメラ
	KamataEngine::DebugCamera* debugCamera_ = nullptr;

	// デバックカメラの生成
	// debugCamera_ = new DebugCamera();

	// ワールドトランスフォーム
	KamataEngine::WorldTransform worldTransform_;

	// カメラ
	KamataEngine::Camera camera_;

	// スプライト
	KamataEngine::Sprite* sprite_ = nullptr;

	// 3D
	// KamataEngine::Model* cube_ = nullptr;

#pragma region プレイヤー

	// プレイヤー
	Player* player_ = nullptr;
	KamataEngine::Model* modelPlayer_ = nullptr;

#pragma region プレイヤーの弾
	// 自キャラの弾
	KamataEngine::Model* modelPlayerBullet_ = nullptr;
	// 弾
	std::list<P_Bullet*> bullets_;
	// 速度
	KamataEngine::Vector3 velocity_;
	// 弾の寿命(フレーム数)
	int playerBulletLifeTime = 20; // 変更可能な左辺値にするためconstを外し型をintに変更    // スペースキーを押して弾を撃つ

#pragma endregion

	// プレイヤーの弾の生成
	P_Bullet* playerBullet_ = nullptr;
	void PlayerAttack();

	// プレイヤーのパーティクル
	P_DeathParticle* deathParticles_ = nullptr;
	KamataEngine::Model* modelParticle_ = nullptr;

	

	uint32_t PBSound_ = 0;

#pragma endregion

#pragma region 敵

	// 敵
	Enemy* enemy_ = nullptr;
	KamataEngine::Model* modelEnemy_ = nullptr;

	// 敵のパーティクル
	E_DeathParticle* enemyDeathParticles_ = nullptr;
	KamataEngine::Model* modelE_Particle_ = nullptr;

	
#pragma endregion

	

	// 天球
	Skydome* skydome_ = nullptr;
	KamataEngine::Model* modelskydome_ = nullptr;

	// マップチップフィールド
	//MapChipField* mapChipField_;

	// 表示ブロックの生成
	// void GenerateBlocks();

	// カメラコントロール
	CameraController* cameraController_ = nullptr;
	// void Initialize();
	// KamataEngine::Model* cameraModel_;

	// std::list<Enemy*> enemies_;

	// 全ての当たり判定
	void CheckAllCollisions();

	// ゲームのフェーズ(型)
	enum class Phase
	{
		kFadeIn,       // フェードイン
		kPlay,         // ゲームプレイ
		kDeath,        // プレイヤーのデス演出
		kBarrierDeath, // バリアのデス演出
		kEnemyDeath,   // 敵のデス演出
		kFadeOut,      // フェードアウト(オーバー)
		kFadeOut2,     // フェードアウト(クリア)
	};

	// ゲームの現在フェーズから開始
	Phase phase_;

	// フェーズの切り替え
	void ChangePhase();

	// フェード
	Fade* fade_ = nullptr;
};
