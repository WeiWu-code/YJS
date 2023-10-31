#pragma once
#include "src/include/namespace.h"
#include <vector>
#include <tuple>
#include "src/item/id.h"
#include <string>

namespace YJS_NAMESPACE {
	typedef unsigned int Offset;
	typedef std::string Context;

	/*
		���Ǵ���ڵ�����Ҫ����С��λ
	*/
	struct ItemMessage {
		char character;
		Id id;
		Id origin;
		Id rightOrigin;
	};

	/*
		����һ�������Ҷ�ӽڵ㣬�κ�ʵ�ֵײ��㷨�Ŀ�������Ҫ�Դ���Ϊ���࣬
		�̳����������Լ���Ҷ�ӽڵ㡣
	*/
	class ItemListInterface {
	public:
		Context context;
		Id headId;
		Id headOrigin;
		Id endRightOrigin;

		// ItemListInterface():ItemListInterface('\0', Id(-1,-1) {}

		ItemListInterface(const ItemMessage& itemMessage)
				:context("" + itemMessage.character),
				headId(itemMessage.id),
				headOrigin(itemMessage.origin),
				endRightOrigin(itemMessage.rightOrigin){}



		virtual ~ItemListInterface() {};

	};






}