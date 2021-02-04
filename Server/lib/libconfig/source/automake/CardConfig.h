#pragma once
#include <vector>
#include "Global.h"

class CardDefine
{
public:
 	/// <summary> 
 	/// id
	/// </summary>
	int id;
 	/// <summary> 
 	/// 卡牌id
	/// </summary>
	int card_id;
 	/// <summary> 
 	/// 说明
	/// </summary>
	const char* desc;
 	/// <summary> 
 	/// 图片说明
	/// </summary>
	const char* image;
 	/// <summary> 
 	/// 卡牌类型
	/// </summary>
	int card_type;
 	/// <summary> 
 	/// 属性
	/// </summary>
	int card_attribute;
 	/// <summary> 
 	/// 点数
	/// </summary>
	int card_point;
 	/// <summary> 
 	/// 中文名
	/// </summary>
	const char* card_name;
 	/// <summary> 
 	/// 配置张数
	/// </summary>
	int card_num;
};