#pragma once

/// <summary>
/// 모델 임시 테이블 데이터
/// </summary>
struct ModelTempTable
{
    // 고유 번호
    uint id;
    // 이름(로컬라이즈)
    wstring strName;
    // 구매 골드량
    uint64 gold;
    // 구매 골드 표시
    wstring goldDesc;
    // 모델 이미지명
    string strImage;

    ModelTempTable(uint a = -1, wstring b = L"", uint64 c = 0, wstring d = L"", string e = "")
    {
        id = a;
        strName = b;
        gold = c;
        goldDesc = d;
        strImage = e;
    }
};

/// <summary>
/// 클라이언트 모델 저장 데이터
/// </summary>
class ModelData
{
public:
    list<int> mModelList;
    int mSlotCount = 0;

    void clear()
    {
        mModelList.clear();
        mSlotCount = 0;
    }
};

typedef vector<ModelTempTable> ModelTempTableList;
extern ModelTempTableList g_ModelTempTable;
extern ModelTempTable FindModelTable(int id);

extern ModelTempTableList g_MaximModelListTable;
extern ModelTempTable FindMaximModelListTable(int id);

typedef vector<vector<ModelTempTable>> ModelSubTempTableArr;
extern ModelSubTempTableArr g_ModelSubTempTableArr;
extern ModelTempTable FindModelSubTable(int idx, int subIdx);

extern const uint64 SlotExNeedGold;