#include "Transform.h"

Transform::Transform()
    :position_(XMVectorZero()),rotate_(XMVectorZero()),scale_(XMVectorSet(1,1,1,1))
     ,matTranslate_(XMMatrixIdentity()),matRotate_(XMMatrixIdentity()),matScale_(XMMatrixIdentity())
{
}

Transform::~Transform()
{
}

void Transform::Calclation()
{
    //SRTÇÃèáî‘Ç≈Ç©ÇØÇÈ
     float tx = XMVectorGetX(position_);
     float ty = XMVectorGetY(position_);
     float tz = XMVectorGetZ(position_);
     matTranslate_ = XMMatrixTranslation(tx, ty, tz);

     float tmp_rx = XMVectorGetX(rotate_);
     float tmp_ry = XMVectorGetY(rotate_);
     float tmp_rz = XMVectorGetZ(rotate_);
     //Z*X*YÇÃèáî‘Ç≈çsóÒÇÇ©ÇØÇÈÇ∆DirectXÇÃâÒì]Ç…Ç»ÇÈÇÊ
     XMMATRIX rx = XMMatrixRotationX(tmp_rx);
     XMMATRIX ry = XMMatrixRotationX(tmp_ry);
     XMMATRIX rz = XMMatrixRotationX(tmp_rz);
     matRotate_ = rz * rx * ry;

     float sx = XMVectorGetX(scale_);
     float sy = XMVectorGetY(scale_);
     float sz = XMVectorGetZ(scale_);
     matScale_ = XMMatrixScaling(sx, sy, sx);
}

XMMATRIX Transform::GetWorldMatrix()
{
    return matScale_ * matRotate_ * matTranslate_;
}
