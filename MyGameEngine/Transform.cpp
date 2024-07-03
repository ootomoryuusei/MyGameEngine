#include "Transform.h"

Transform::Transform()
    :position_({ 0,0,0 }), rotate_({ 0,0,0 }), scale_({ 1, 1, 1 })
     ,matTranslate_(XMMatrixIdentity()),matRotate_(XMMatrixIdentity()),matScale_(XMMatrixIdentity())
{
}

Transform::~Transform()
{
}

void Transform::Calculation()
{
     matTranslate_ = XMMatrixTranslation(position_.x,position_.y,position_.z);

     //Z*X*Y�̏��Ԃōs����������DirectX�̉�]�ɂȂ��
     XMMATRIX rx = XMMatrixRotationX(XMConvertToRadians(rotate_.x));
     XMMATRIX ry = XMMatrixRotationY(XMConvertToRadians(rotate_.y));
     XMMATRIX rz = XMMatrixRotationZ(XMConvertToRadians(rotate_.z));
     matRotate_ = rz * rx * ry;

     matScale_ = XMMatrixScaling(scale_.x,scale_.y,scale_.z);
}

XMMATRIX Transform::GetWorldMatrix()
{
    return matScale_ * matRotate_ * matTranslate_; //SRT�����߂�
}
