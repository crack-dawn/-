#ifndef my_H
#define MY_H


#include "maths.h"
#include "worldmodel.h"
#include "PlayerTask.h"


/*
1. 足球机器人长度 角度坐标系 是 atanf2 , （-PI, PI],
2. X轴正方向为 中点->对方球门的位置， 顺时针转动 90°，为y轴正方向
*/


/* 自定义函数 */

float my_limite(float x, float max, float min);//限定大小阈值

float atan2fCorrect(float dir);//atan2f 超越PI 与 -PI  时重新更新




float DIR(float d);/*atan2f  角度 转化为 【0 ， 2 PI】 角度*/

//DIR之前角度
//---对方球门-----
//       |
//       |
//       0
//       |
//       |
//(-90)--|---(90)-
//       |
//       |
//      180
//       |
//    我方球门

/*---对方球门-----
//       |
//       |
//       0
//       |
//       |
/(270)---|-----90
//       |
//       |
//       180
//       |
//    我方球门     */





int GetReceverID(const WorldModel *model, int robot_id);/*获取我方接球队员 ID*/

float RunOnCircleDir(float b2r, float b2g, float DetAngle);/*绕圆周 转动时 每次转移时调整的 弧度/角度 || 参数：  球->球员， 球->目标点  旋转弧度*/

float RunToCircleDir(float b2r, float b2g);/* 跑向圆周时 应该到达的 位置角度值 ||参数：  球->球员， 球->目标点  */

float Reverse_Dir(float dir);			   // atanf2 角度反转
// float SetKickPower(float dist， param..... param... ); // 根据距离 等 综合出 合适的 传球力度

int GetOppGoalieID(const WorldModel *model, int robot_id);

const point2f GetOppGoaliePos(const WorldModel *model, int robot_id);

//当前时刻 填0 ， 过去帧数填5，表示用这五帧内走过的距离  //比赛摄像头  60Hz 传图
const float KickDir(point2f goalpos, point2f ballpos, point2f oppGoaliePos);


const float BallSpeed(int current, int  pastcnt);//不能称之为速度，只能说是单位帧数内移动的距离

const float BallMoveDir(int current, int  pastcnt); //球位移的方向


float SetPassPower(float dist);


#endif