#include "Image.h"

namespace Image
{
    std::vector<ImageData*> _datas;

    void Initialize()
    {
        AllRelease();
    }

    int Load(std::string fileName)
    {
        ImageData* pData = new ImageData;

        bool isExist = false;

        for (int i = 0; i < _datas.size(); i++) {
            if (_datas[i] != nullptr && _datas[i]->fileName == fileName) {
                pData->pSprite = _datas[i]->pSprite;
                isExist = true;
                break;
            }
        }
        
        if (isExist == false) {
            pData->pSprite = new Sprite();
            if (FAILED(pData->pSprite->Load(fileName))) {
                SAFE_DELETE(pData->pSprite);
                SAFE_DELETE(pData);
                return -1;
            }
            pData->fileName = fileName;
        }

        for (int i = 0; i < _datas.size(); i++) {
            if (_datas[i] == nullptr) {
                _datas[i] = pData;
                return i;
            }
        }

        _datas.push_back(pData);

        int handle = (int)_datas.size() - 1;

        ResetRect(handle);

        return handle;

    }

    void Draw(int handle)
    {
        if (handle < 0 || handle >= _datas.size() || _datas[handle] == nullptr)
        {
            return;
        }
        _datas[handle]->transform.Calculation();
        _datas[handle]->pSprite->Draw(_datas[handle]->transform);
    }

    void Release(int handle)
    {
        if (handle < 0 || handle >= _datas.size())
        {
            return;
        }

        //同じモデルを他でも使っていないか
        bool isExist = false;
        for (int i = 0; i < _datas.size(); i++)
        {
            //すでに開いている場合
            if (_datas[i] != nullptr && i != handle && _datas[i]->pSprite == _datas[handle]->pSprite)
            {
                isExist = true;
                break;
            }
        }

        //使ってなければモデル解放
        if (isExist == false)
        {
            SAFE_DELETE(_datas[handle]->pSprite);
        }

        SAFE_DELETE(_datas[handle]);
    }

    void AllRelease()
    {
        for (int i = 0; i < _datas.size(); i++)
        {
            Release(i);
        }
        _datas.clear();
    }

    void ResetRect(int handle)
    {
       /* if (handle < 0 || handle >= _datas.size())
        {
            return;
        }

        XMFLOAT3 size = _datas[handle]->pSprite->GetTextureSize();

        _datas[handle]->rect.left = 0;
        _datas[handle]->rect.top = 0;
        _datas[handle]->rect.right = (long)size.x;
        _datas[handle]->rect.bottom = (long)size.y;*/
    }

    void SetRect(int handle, int x, int y, int width, int height)
    {
        if (handle < 0 || handle >= _datas.size())
        {
            return;
        }

        _datas[handle]->rect.left = x;
        _datas[handle]->rect.top = y;
        _datas[handle]->rect.right = width;
        _datas[handle]->rect.bottom = height;
    }

    void SetTransform(int handle, Transform& transform)
    {
        if (handle < 0 || handle >= _datas.size())
        {
            return;
        }

        _datas[handle]->transform = transform;
    }

    XMMATRIX GetMatrix(int handle)
    {
        if (handle < 0 || handle >= _datas.size())
        {
            return XMMatrixIdentity();
        }
        return _datas[handle]->transform.GetWorldMatrix();
    }
}


