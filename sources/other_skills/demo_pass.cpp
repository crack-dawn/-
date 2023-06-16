#include "my.h"

#pragma comment(lib, "worldmodel_lib.lib")

//用户注意；接口需要如下声明
extern "C" _declspec(dllexport) PlayerTask player_plan(const WorldModel *model, int robot_id); //绿色部分为声明函数 player_plan

// 传球 
PlayerTask player_plan(const WorldModel *model, int robot_id)
{
	PlayerTask task;

	
	const point2f &ball = model->get_ball_pos(); //足球坐标
	point2f goal; 		//目标点坐标  可以是 球门 也可以是 某个队员， 但是传球力度需要 精调整
	int my_kick_power; //传球力度
	int receiver_id = GetReceverID(model, robot_id);
	const point2f receiverPos = model->get_our_player_pos(receiver_id); //接球队员 坐标

	goal = receiverPos;
	const float toGoalDir = DIR((goal - ball).angle()); //足球到目标的方向
	const float toGoalDist = (goal - ball).length();	//足球到目标点的距离
	my_kick_power = SetPassPower(toGoalDist); // 这里也可以写一个 阶跃函数分段 什么的， 更加精细

 

	static int i = 0; //静态标志 确认 踢球角度及状态
	static int nearBall = false; //接近placePos？
	static const float circleR = 35; //绕行调整半径
	const point2f &playerPos = model->get_our_player_pos(robot_id); //球员坐标
	const float &robot_dir = model->get_our_player_dir(robot_id); //球员朝向
	float g2b = DIR((ball - goal).angle());//目标到球的方
	float b2g = DIR(Reverse_Dir(g2b));//球到目标的方向
	float r2b = DIR((ball - playerPos).angle());//队员朝向足球的方向
	float b2r = DIR((playerPos - ball).angle()); //足球朝向队员的方向
	float toBallDist = DIR((playerPos - ball).length());//球员到足球的距离



	const point2f &firstPos = ball + Maths::vector2polar(circleR - 2, b2r);//远距离 应该达到圆周上的位置
	const point2f &placePos = ball - Maths::vector2polar(circleR - 2, toGoalDir);//圆周上 适合切入 kickPos的位置
	float toPlaceposDist = (playerPos - placePos).length();//到切入点距离 
	const point2f &kickPos = ball - Maths::vector2polar(MAX_ROBOT_SIZE - 2, toGoalDir);//射门 应该达到的 kickPos
	float toKickPosDist = (playerPos - kickPos).length();//到射门点 距离


	


		if (toBallDist > circleR) //距离未到达足够近, 车向球靠近 去往 直线距离圆周上最近的一点
		{
			if (ball.X() < 300 && ball.X() > -300 && ball.Y() < 200 && ball.Y() > -200) //球在图像中时，保存球的位置
			{
				//车跑向球

				/*精调整 细节*/
				task.orientate = b2r + PI;
				task.target_pos = ball + Maths::vector2polar(circleR - 1, RunToCircleDir(b2r, b2g));

				/*粗略*/
				/*task.orientate = r2b;
				task.target_pos = firstPos;*/
			}
		}

		/* 绕圆周 不断逼近 placePos */
		else if (toBallDist < circleR + 5 && toBallDist > circleR - 12)
		{
			task.target_pos = ball + Maths::vector2polar(circleR - 1, RunOnCircleDir(b2r, b2g, PI / 5)); // +顺时针 || -逆时针 
			task.orientate = r2b;

			if (toPlaceposDist < 12 || toKickPosDist < 12) // 接近切入点
			{
				nearBall = 1;
				task.target_pos = kickPos;
				task.orientate = toGoalDir;
				task.needCb = true;
			}
		}

		/*逼近踢球点*/
		if (nearBall)
		{
			task.target_pos = kickPos;
			task.orientate = toGoalDir;
			task.needCb = true;
		}

		/* 最后的踢球 */
		if (toKickPosDist < MAX_ROBOT_SIZE+4)  //从 placePos附近 逼近kickPos ，准备射球
		{
			task.target_pos = kickPos;
			task.orientate = toGoalDir;
			task.needCb = true;
			if (fabs(r2b - toGoalDir) < PI /6 && toBallDist < MAX_ROBOT_SIZE+3)
			{
				task.needCb = false;
				task.needKick = true;
				task.kickPower = my_kick_power;
			}
		}


		//bool start_action = (BallSpeed(0, 1) < 2) ? true : false;
		//if (start_action == false)
		//{
		//	task.target_pos =   ball + Maths::vector2polar(35, b2r);
		//}
	

	return task;
}










