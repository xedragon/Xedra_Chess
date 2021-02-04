using System;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

namespace Data
{
    public class CardDefine
    {
        /// <summary> 
        /// id
        /// </summary>
        [PrimaryKey] [AutoIncrement] public int id  { get; set; }

        /// <summary> 
        /// 卡牌id
        /// </summary>
        public int card_id;

        /// <summary> 
        /// 说明
        /// </summary>
        public string desc;

        /// <summary> 
        /// 图片说明
        /// </summary>
        public string image;

        /// <summary> 
        /// 卡牌类型
        /// </summary>
        public int card_type;

        /// <summary> 
        /// 属性
        /// </summary>
        public int card_attribute;

        /// <summary> 
        /// 点数
        /// </summary>
        public int card_point;

        /// <summary> 
        /// 中文名
        /// </summary>
        public string card_name;

        /// <summary> 
        /// 配置张数
        /// </summary>
        public int card_num;

    }
}