#include "Controller.h"
#include"Input.h"
#include"Camera.h"

Controller::Controller()
{
}

Controller::~Controller()
{
}

void Controller::Initialize()
{
	transform.position_ = { 1,1,1 };
}

void Controller::Update()
{
	if (Input::IsKey(DIK_W)) {
		transform.position_.z -= 0.01;
	}
	if (Input::IsKey(DIK_S)) {
		transform.position_.z += 0.01;
	}
	if (Input::IsKey(DIK_A)) {
		transform.position_.x += 0.01;
	}
	if (Input::IsKey(DIK_D)) {
		transform.position_.x -= 0.01;
	}

	Camera::SetPosition( { 0+transform.position_.x, 10, 10+transform.position_.z, 0 } );
	Camera::SetTarget(XMLoadFloat3(&transform.position_));
}

void Controller::Draw()
{
}

void Controller::Release()
{
}
