#pragma once
#include <string>
#include <deque>
#include <map>
#include <vector>
#include <iostream>
#include "src/item/id.h"
#include "src/struct/YStruct.h"
using namespace std;
using namespace YJS_NAMESPACE;

namespace YJS_NAMESPACE {

class AVLNode; //ǰ������

class CharacterInfo {
private:
    //YATA�㷨��Ҫ������
    Id leftOriginId;
    //YATA�㷨��Ҫ������
    Id rightOriginId;
    //�Ƿ�ɾ���ı�ǣ�Ϊtrue��Ϊ��ɾ������ɾ����Ϊfalse��δ��ɾ��
    bool isDeleted;

public:
    CharacterInfo() {
        isDeleted = false;
    }
    CharacterInfo(const ItemMessage &message) {
        this->leftOriginId = message.origin;
        this->rightOriginId = message.rightOrigin;
        this->isDeleted = false;
    }
    Id getLeftOriginId()  const {return leftOriginId;}
    Id getRightOriginId() const {return rightOriginId;}
    bool getisDeleted()     const {return isDeleted;}
    void setDeleted(bool isDeleted) {this->isDeleted = isDeleted;}
};

class AVLNode : public ItemListInterface {
public:
    //����3ֻ��Ϊ�˷�����ԣ���������Ϊ8��10��16��������
    static int SPACE_SIZE; //�����ʼ��
    //�ýڵ��ʼԪ�ص�Id�������Ƿ�ɾ��
    // Id gid;
    //���ڴ洢ʵ�ʵ��ַ����ݣ���С�ݶ�Ϊ10
    // vector<char> text; 
    //���ڼ�¼ÿ���ַ�����Ϣ���Ƿ�ɾ����ԭʼǰ����ԭʼ���
    vector<CharacterInfo> informations;
    //�ýڵ����ڵĸ߶ȣ�����AVL����ƽ��
    int height;
    //�����кϷ����ݵĴ�С
    int validDataSize;
    //���������е����ݴ�С����������ɾ��������
    int allDataSize;

    //�Ըýڵ�Ϊ���ڵ��������Чֵ�ĸ���!!���ڸ���pos�Խڵ��������
    int treeSize;
    //��ڵ�
    AVLNode *left;
    //�ҽڵ�
    AVLNode *right;
    //�ڵ�ĸ�ָ��
    AVLNode *parent;
    //�ͻ��˴��������ݡ�����YATA�㷨����һ���ַ���ǰ��
    // Id headOrigin;
    //�ͻ��˴��������ݡ�����YATA�㷨�����һ���ַ��������Ƿ񱻱��ɾ�����ĺ�̣������Ƿ�ɾ��
    // Id endRightOrigin;

public:
    int getTreeSize()       const {return treeSize;}
    int getValidDataSize()  const {return validDataSize;}
    int getAllDataSize()    const {return allDataSize;}
    int getHeight()         const {return height;}
    string getText()        const {return context;}
    AVLNode* getLeft()      const {return left;}
    AVLNode* getRight()     const {return right;}

    void setTreeSize(int treeSize)              {this->treeSize = treeSize;}
    void setValidDataSize(int validDataSize)    {this->validDataSize = validDataSize;}
    void setId(Id gid)                          {this->headOrigin = gid;}
    void setHeight(int height)                  {this->height = height;}

    AVLNode();
    AVLNode(const ItemMessage &message);
    AVLNode(const vector<ItemMessage> &message);
    AVLNode(const Id &gid, char character);

    bool isDeleted(int offset);
    /**
     * �ӿڴ�����
     * ���ܻ������ѭ��
     * @param validIndex ��ʾδ��ɾ���Ľڵ㣬��0��ʼ����
     * @return
     */
    ItemPtr getValidByIndex(int validIndex);
    bool deleteCharacterByOffset(int offset);
    Id getIdByOffset(int offset);
    int getIdCounterByOffset(int offset);
    bool insertCharacter(int offset, const ItemMessage &message);

    /**
     * �ڽڵ����ʱ�����������ð�ȫ�ķ�ʽ,����[offset, SPACE_SIZE]�������.
     * @param offset ����Ϊ5�������±�Ϊ0���±�Ϊ4�Ľڵ�
     */
    void frontSplit(int offset);

    /**
     * ��ȡһ���ڵ���ӽڵ㣬�������뵽���ṹ��������̳�height��size������
     * ���ұգ���0��ʼ����
     * @param begin
     * @param end
     * @return
     */
    AVLNode* subAVLNode(int begin, int end);

};

class AVLTree : public YInterface {
private:
    //��������ͷ�ڵ㣬�ο��������ʵ��
    AVLNode* virtualRoot;
    AVLNode* root;
    //��δʹ�ã���������
    // map<Id, ItemPtr> gidToItemPtr;
public:
    AVLTree();
    AVLNode* getRoot() const;

    int getHeight(AVLNode* node) const;
    int getTreeSize(AVLNode* node) const;
    int getAllDataSize(AVLNode* node) const;
    int getValidDataSize(AVLNode* node) const;
    int getBalance(AVLNode* node) const;

    //�ѹ���ί�и����к���
    virtual ItemPtr begin() const override;
    virtual ItemPtr end() const override;
    virtual void insertItem(Index index, ItemMessage itemMsg) override;
    virtual void deleteItem(Index index) override;
    virtual ItemPtr getItemByPos(Index index) const override;
    virtual ItemPtr successor(ItemPtr itemPtr) const override;
    virtual ItemPtr predecessor(ItemPtr itemPtr) const override;
    virtual Id getId(ItemPtr itemPtr) const override;

    ItemPtr _begin() const;
    ItemPtr _end() const;

    void insertByPos(int pos, const ItemMessage &message);
    void deleteByPos(int pos);

    AVLNode* leftRotation(AVLNode* node);
    AVLNode* rightRotation(AVLNode* node);

    ItemPtr getItemPtrByPos(int pos) const; 
    AVLNode* getNodeByPos(AVLNode* node, int pos) const;
    int getValidIndexByPos(AVLNode* node, int pos) const;

    ItemPtr _successor(const ItemPtr &nodeOffset) const;
    ItemPtr _predecessor(const ItemPtr &nodeOffset) const;


    AVLNode* getSuccessorNode(AVLNode* node) const;
    AVLNode* getPredecessorNode(AVLNode* node) const;
    AVLNode* getNextInsertPosNode(AVLNode* node) const;
    AVLNode* getPreInsertPos(AVLNode* node) const;
    Id      getIdByItemPtr(ItemPtr nodeOffset) const;

    //����ʱ�鿴���ṹ
    void draw(AVLNode* root, AVLNode* flag);
    vector<vector<string>> levelOrder(AVLNode* root, AVLNode* flag);

private:
    void update(AVLNode* node);
    void fullRebalance(AVLNode* node);
    AVLNode* rebalance(AVLNode* node, AVLNode* parent);
};

}