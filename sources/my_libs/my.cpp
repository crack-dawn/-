
#include "my.h"
/*
1. 足球机器人长度 角度坐标系 是 atanf2 , （-PI, PI],
2. X轴正方向为 中点->对方球门的位置， 顺时针转动 90°，为y轴正方向
*/
/*-----------------------------------------------------------------------------------*/


const float BallSpeed(int current, int  pastcnt)//不能称之为速度，只能说是单位帧数内移动的距离
{
	//int cnt = pastcnt - current;
	Ball ball_;
	float speed = 0;
	const point2f &ballPos = ball_.get_pos(current); // param 表示 前param 帧的足球位置，0 表示当前时刻足球位置 ； 可以用此计算足球的速度 ；摄像头拍摄 30帧/秒 左右 或是  
	const point2f &ballPosPast = ball_.get_pos(pastcnt);
	speed = (ballPos - ballPosPast).length();
	return speed;
}
const float BallMoveDir(int current, int  pastcnt) //球位移的方向
{
	//int cnt = pastcnt - current;
	Ball ball_;
	float dir;
	const point2f &ballPos = ball_.get_pos(current); // param 表示 前param 帧的足球位置，0 表示当前时刻足球位置 ； 可以用此计算足球的速度 ；摄像头拍摄 30帧/秒 左右 或是  
	const point2f &ballPosPast = ball_.get_pos(pastcnt);
	dir = (ballPos - ballPosPast).angle();
	return dir;
}


//根据距离改  最好不要超过35
// 100之内 《= 20
// 150之内 《= 25
// 200     《= 30
float SetPassPower(float dist)
{
	float power = 14;
	if (dist > 100) power++;
	if (dist > 150) power++;
	if (dist > 190) power++;
	if (dist > 240) power++;

	return power;
}


// 获取对面守门球员 ID序号
int GetOppGoalieID(const WorldModel *model, int robot_id)
{
	int oppGoalieID = -100;

	oppGoalieID = model->get_opp_goalie();

	if (oppGoalieID >= 1 && oppGoalieID <= 12)
	{
		return oppGoalieID;
	}
	else
	{
		return -100; // wrong  没有守门员
	}
}
// 获取对面守门球员位置
const point2f GetOppGoaliePos(const WorldModel *model, int robot_id)
{
	point2f oppGoaliePos = { 300, 0 };
	int oppGoalieID = GetOppGoalieID(model, robot_id);
	if (oppGoalieID != -100)
	{
		oppGoaliePos = model->get_opp_player_pos(oppGoalieID);
	}
	return oppGoaliePos;
}


// 获取射门方向
const float KickDir(point2f goalpos, point2f ballpos, point2f oppGoaliePos)
{
	// 根据球的位置判定偏向
	goalpos.y = ballpos.y > 0 ? abs(goalpos.y) : -abs(goalpos.y);

	// 根据守门员判定偏向
	if (oppGoaliePos.x != 300 && oppGoaliePos.y != 0)
	{
		if (oppGoaliePos.y >= 0)
		{
			goalpos.y = -abs(goalpos.y);
		}
	}
	return DIR((goalpos - ballpos).angle()); // 射门方向
}

/*获取我方接球队员 ID*/
int GetReceverID(const WorldModel *model, int robot_id){
	int  receiver_id = -100;

	for (int i = 0; i < 6; i++)
	{
		if (i == robot_id || i == model->get_our_goalie())
			continue;
		if (model->get_our_exist_id()[i])
			receiver_id = i;
	}
	return receiver_id;
}



//限定大小阈值
float my_limite(float x, float max, float min)
{
	if (x - max> 0)
	{
		x = max;
	}
	else if (min - x > 0)
	{
		x = min;
	}
	return x;
}


//atan2f 超越PI 与 -PI  时重新更新，化为【-PI, PI角度】 
float atan2fCorrect(float dir)
{
	float result = dir;
	if (result > PI)
	{
		return (result - PI - PI);
	}
	else if (result < -PI)
	{
		return (result + PI + PI);
	}
	else
	{
		return result;
	}
}


/*atan2f  角度 转化为 【0 ， 2 PI】 角度*/
float DIR(float d)
{
	d = (d >= 0 ? d : (d + PI + PI));
	return d;
}

/*绕圆周 转动时 每次转移时调整的 弧度/角度 */
/* 转动需要的 角度 ， 球->球员， 球->目标点, 转动角【 18°  ， 60°】， 36°较好*/
float RunOnCircleDir(float b2r, float b2g, float DetAngle)
{
	//   我为蓝方视角
	if (DetAngle > 0.33*PI || DetAngle < 0.1*PI)
	{
		DetAngle = PI / 5;
	}
	//DetAngle= my_limite( DetAngle, 0.33*PI, 0.1*PI );

	float dir;
	if (b2r >= b2g && fabs(b2r - b2g) <= PI)
	{
		dir = b2r + DetAngle; //顺时针
	}
	else if (b2r < b2g && fabs(b2r - b2g) <= PI)
	{
		dir = b2r - DetAngle; //逆时针
	}
	else if (b2r >= b2g && fabs(b2r - b2g) >= PI)
	{
		dir = b2r - DetAngle;
	}
	else if (b2r < b2g && fabs(b2r - b2g) > PI)
	{
		dir = b2r + DetAngle;
	}
	return dir;
}


//atanf2 角度反转
float Reverse_Dir(float dir)
{
	if (dir >= 0)
	{
		dir -= PI;
	}
	else
	{
		dir += PI;
	}
	return dir;
}


/* 跑向圆周时 应该到达的 位置角度值 */
/* 转动需要的 角度 ， 球->球员， 球->目标点*/
float RunToCircleDir(float b2r, float b2g)
{
	//   我为蓝方视角
	//不需要调整 直接跑过去
	if (fabs(b2r - b2g) >= 0.60*PI && fabs(b2r - b2g) <= 1.40 * PI)
	{
		return b2r;
	}

	//需要调                                      
	if (b2r > b2g && fabs(b2r - b2g) < 0.60 * PI)//
	{
		return b2g + PI - 0.4*PI;
	}
	else if (b2r < b2g && fabs(b2r - b2g) < 0.60 * PI)
	{
		return b2g + PI + 0.4*PI;
	}

	else if (b2r > b2g && fabs(b2r - b2g) > 1.40 * PI)//
	{
		return b2g + PI + 0.4*PI;
	}
	else if (b2r < b2g && fabs(b2r - b2g) > 1.40 * PI)
	{
		return b2g + PI - 0.4*PI;
	}

	else {
		return b2r;
	}

}
 
