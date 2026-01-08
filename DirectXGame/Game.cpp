#include "Game.h"
#include "MyMath.h"
#include "CameraController.h"
#include "Fade.h"

#include "Player.h"
#include "P_Bullet.h"

#include "Enemy.h"



using namespace KamataEngine;

#pragma region
#pragma endregion

void GameScene::Initialize() {
#pragma region

#pragma endregion

	
	
	// デバックカメラの生成
	debugCamera_ = new DebugCamera(100, 200);

	// スカイドーム
	modelskydome_ = Model::CreateFromOBJ("SkyDome", true);

#pragma region プレイヤー

	// playerHPのスプライト
	playerhpHandle_ = TextureManager::Load("hp.png");
	playerhpSprite_ = KamataEngine::Sprite::Create(playerhpHandle_, {0, 680});

	_playerhpHandle_ = TextureManager::Load("hp_.png");
	_playerhpSprite_ = KamataEngine::Sprite::Create(_playerhpHandle_, {0, 680});

	// プレイヤー
	modelPlayer_ = Model::CreateFromOBJ("player", true);

	// プレイヤーの弾
	modelPlayerBullet_ = Model::CreateFromOBJ("bullet", true);
	// パーティクルの3Dモデルデータの生成
	model_P_Particle_ = Model::CreateFromOBJ("deathParticle", true);

	// プレイヤーの生成
	player_ = new Player();

	// プレイヤーの座標を指定
	KamataEngine::Vector3 playerPosition = {-10, 1, 0};
	player_->Initialize(modelPlayer_, &camera_, playerPosition);

	// プレイヤーの弾
	playerBullet_ = new PlayerBullet();
	playerBullet_->Initialize(modelPlayerBullet_, &camera_, playerPosition, velocity_);

	// プレイヤーのデスパーティクル
	P_Particles_ = new PlayerDeathParticle();
	P_Particles_->Initialize(model_P_Particle_, &camera_, playerPosition);

#pragma endregion

#pragma region 敵

	// enemyHPのスプライト
	enemyhpHandle_ = TextureManager::Load("Ehp.png");
	enemyhpSprite_ = KamataEngine::Sprite::Create(enemyhpHandle_, {1050, 0});

	_enemyhpHandle_ = TextureManager::Load("Ehp_.png");
	_enemyhpSprite_ = KamataEngine::Sprite::Create(_enemyhpHandle_, {1050, 0});

	// 敵の3Dモデル
	modelEnemy_ = Model::CreateFromOBJ("enemy", true);
	// 敵の弾
	modelEnemyBullet_ = Model::CreateFromOBJ("E_bullet", true);

	model_E_Particle_ = Model::CreateFromOBJ("E_deathParticle", true);

	// 敵の生成
	enemy_ = new Enemy();
	// 敵の座標
	KamataEngine::Vector3 enemyPosition = {35, 5, 0};
	enemy_->Initialize(modelEnemy_, &camera_, enemyPosition);

	// 敵の弾
	enemyBullet_ = new EnemyBullet();
	enemyBullet_->Initialize(modelEnemyBullet_, &camera_, enemyPosition, EnemyBulletVelocity_);

	// 敵のデスパーティクル
	E_Particles_ = new EnemyDeathParticle();
	E_Particles_->Initialize(model_E_Particle_, &camera_, enemyPosition);

#pragma endregion

	// ワールドトランスフォームの初期化
	worldTransform_.Initialize();

	// カメラの初期化
	camera_.Initialize();

	// スカイドームの生成
	skydome_ = new Skydome();
	skydome_->Initialize(modelskydome_, textureHandle_, &camera_);

	// カメラコントローラの初期化
	cameraController_ = new CameraController;
	cameraController_->Initialize();
	cameraController_->SetTarget(player_);
	cameraController_->Reset();

	CameraController::Rect cameraArea = {12.0f, 100 - 12.0f, 6.0f, 6.0f};
	cameraController_->SetMovableArea(cameraArea);

	// フェーズインから開始
	phase_ = Phase::kFadeIn;

	// フェード
	fade_ = new Fade();
	fade_->Initialize();
	fade_->Start(Fade::Status::FadeIn, 1.0f);
}