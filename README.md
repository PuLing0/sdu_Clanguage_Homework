# 火车票务管理系统/火车票购票系统 ver1.1

> ### 开发环境：
> 
> Qt 5.9.0 <br>
> Qt Creator 4.3.0 

## 目录
- ### [1. 系统介绍](#1)<br>
    - [系统功能](#1-系统功能)
    - [系统用户](#2-系统用户)
    - [使用场景](#3-使用场景)
- ### [2. 概要设计](#2)<br>
    - [软件层次结构图](#软件层次结构图)
    - [设计数据类型](#涉及数据类型)
    - [数据流图](#数据流图)
    - [流程图](#流程图)
- ### [3. 详细设计](#3)<br>
    - [函数接口](#函数接口)
    - [调用关系](#调用关系)
- ### [4. 总结](#4)<br>

<p id="1"></p>

## 系统介绍

### 1. 系统功能 
- 登录界面：用户登录、管理员登录、注册用户、修改用户密码
- 用户界面：
- 1. 购票查询界面：票据查询（按各标签排序）、购票、改签
- 2. 个人中心界面：已购买票据查询、改签、退票
- 管理员界面：
- 1. 车票列表、用户列表界面：按车站、日期查询车票，按用户名查询车票
- 2. 增加车次、更改车次、添加用户窗口

### 2. 系统用户
管理员、旅客

### 3. 使用场景
用于火车站购票、后台管理票据

<p id="2"></p>

## 概要设计

### 软件层次结构图
<img src="https://raw.githubusercontent.com/PuLing0/sdu_Clanguage_Homework/master/Image/%E8%BD%AF%E4%BB%B6%E5%B1%82%E6%AC%A1%E5%9B%BE.png" alt="图片alt" title="软件层次结构图">

### 涉及数据类型
```
class ticket
{
public:
    ticket();
    QString id;//列车号
    QString beginpoint;//始发地
    QString endpoint;//终点站
    QString beginDay; //发车日期
    QString endDay; //到站日期
    QString begintime;//发车时间
    QString endtime;//到站时间
    int amount;//车票数
    double price;//车票价格
};
class user
{
public:
    QString account;//用户账号
    QString password;//用户密码
    bool gender;//用户性别，1是男性，2是女性
    QString name;//用户名
    bool Over_Power;//用户权限，1是管理员，2是普通用户
    QList<ticket> tickets;
};

```

### 数据流图
#### 0层数据流图
<img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/0%E5%B1%82%E6%95%B0%E6%8D%AE%E6%B5%81%E5%9B%BE.png" alt="sd" title="0层数据流图">

#### 1层数据流图
<img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/1%E5%B1%82%E6%95%B0%E6%8D%AE%E6%B5%81%E5%9B%BE-%E7%94%A8%E6%88%B7.png" alt="sd" title="1层数据流图-用户">

#### 2层数据流图
<img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/2%E5%B1%82%E6%95%B0%E6%8D%AE%E6%B5%81%E5%9B%BE-%E4%B8%AA%E4%BA%BA%E4%B8%AD%E5%BF%83.png" alt="sd" title="2层数据流图-个人中心">

### 流程图
#### 用户界面流程图
<img src="https://github.com/PuLing0/sdu_Clanguage_Homework/raw/master/Image/%E7%94%A8%E6%88%B7%E7%95%8C%E9%9D%A2%E6%B5%81%E7%A8%8B%E5%9B%BE.png" alt="sd" title="用户界面流程图">

<p id="3"></p>

## 详细设计

### 函数接口

```

```

### 调用关系
<p id="4"></p>

## 总结
