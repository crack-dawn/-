


/*
// lua层函数 需要 C++dll返回的task 对象的某些属性，C++处理数据要快于lua，（对于这种只有两个机器人上场的， lua 或者 c++ 的skill 应该差别不是很大）
// 本人的理解是， C++dll 处理了一些 执行任务需要的数据， 传给了lua 函数，具体可以看 
// ⑥\SOM v3.4.2\Team\lua_scripts\skill 对lua层 接收 c++dll的 skill函数封装，也就访问了几个关键成员的属性，
// 值得注意的是，C++dll 是循环调用的，在 [state_0] 这个策略分配状态下，会不断调用skill 给kickier 或者 receiver 分配任务，
// 也就是说， C++dll 获取的数据 每次调用时，会根局比赛场上的数据实时刷新
/*
   
  生成的 .dll 在 ③ \Demo\Release 目录下
  调用生成的 dll 时， 记得改名，
  并将重命名后的 .dll文件移动到 ④ \SOM v3.4.2\Team\user_skills 这个目录下，才可以在lua策略中正常调用，也就是在 demo_test.lua 类似的lua文件内调用

  用于测试demo现象的 lua脚本 是 ⑤ \SOM v3.4.2\Team\lua_scripts\play\Test\Others\demo_test.lua，

  顺带一提， 可以把用于测试的lua脚本放在 \SOM v3.4.2\Team\lua_scripts\play\Test\Others\ 目录下，每次软件平台进入到测试模式就可以看到需要测试的lua脚本

  */
 





#include "maths.h"
#include "PlayerTask.h"
#include "worldmodel.h"

#ifdef __cplusplus//用户注意；接口需要如下声明  
extern "C"
{
#endif
	//全局声明 一个输出 C++ dll 的接口函数， 输出的dll 动态库具备这个函数要实现的功能
	__declspec(dllexport) PlayerTask player_plan(const WorldModel* model, int robot_id);

#ifdef __cplusplus
}
#endif


 

///* 简单示例 demo1   定点跑动*/   
PlayerTask player_plan(const WorldModel* model, int robot_id){

	PlayerTask task;//创建task 对象

	point2f we_pos(305, 10);  //跑到对方球门内

	task.target_pos = we_pos;

	return task;

}


























//namespace Pass_Kick{//实地测试得出
//	const float head_len = 7;
//	const float miss = 12;//越大接球条件越宽松 拿球距离
//	const float getangle = PI / 20; //角度值
//	const int  fast_pass = 9; //可以传球间距
//	const int get_buff = 35;//每次调整距离
//}

///*传球条件  传入三个坐标 ball kicker receiver */
//bool is_ready_pass(const point2f& ball, const point2f& passer, const point2f& receiver){
//	float receiver_to_ball = (ball - receiver).angle();
//	float ball_to_passer = (passer - ball).angle();
//	//float distance_miss = fabs((ball - passer).length());
//	float dir_miss = fabs(receiver_to_ball - ball_to_passer);
//	//两个矢量角度之差小于某个值，判断是否可以传球
//	bool pass = (dir_miss < 0.25);
//	return pass;
//}



/* 简单示例 demo2   找球之后 正对足球， */  //视频 拿球
//PlayerTask player_plan(const WorldModel* model, int robot_id) {
// 
//	PlayerTask task;
//
//	//调用 worldmodel函数，获取我方机器人的向量坐标
//	const point2f& player_pos = model->get_our_player_pos(robot_id);
//
//	//调用 worldmodel函数，获取 我方球员的朝向
//	const float dir = model->get_our_player_dir(robot_id);
//
//	//调用 worldmodel函数，获取 球的向量坐标
//	const point2f  ball_pos = model->get_ball_pos();
//
//	//敌方球门正中心坐标
//	const point2f& opp_goal = -FieldPoint::Goal_Center_Point;
//
//	//向量朝向 ①-② 得到的朝向是 ②->①， 与数学上（1,2）-（0,0）得到的方向向量是（1,2）大同小异，再用 成员函数 angle() 得到这个方向角
//	//这里 设定 face_dir 是  球朝向 球门的方向
//	const float& face_dir = (opp_goal - ball_pos).angle();
//
//
//	/* 到达目标点朝向:  队员 正对  球   */
//	task.orientate = face_dir;
//
//	/* 需要到达的目标点坐标= 球的位置 + 向量偏移距离 */		// face_dir 反方向偏移 13个单位
//	task.target_pos = ball_pos  - Maths::vector2polar(13, face_dir);
//
//	return task; //返回 task 对象，对接lua脚本层 数据
//}


///* 拿球判定 传入三个参数 pos： ball  kicker  ， dir： kick_dir*/
bool is_getball(const point2f& ball, const point2f& kicker, const float& kick_dir) {

	static int  miss = get_ball_threshold; //是否 拿到球 最大距离

	bool get_ball = (ball - kicker).length() < miss && (fabs(anglemod(kick_dir - (ball - kicker).angle())) < PI / 15);

	if (get_ball) {
		return true;
	}
	else {
		return false;
	}

}

/* 简单示例 demo3   捡球 准备  射门*/
//PlayerTask player_plan(const WorldModel* model, int robot_id) {
//
//	PlayerTask task;
//
//	/*获取场上 信心， 球员的位置  足球的位置  机器人朝向   */
//	调用 worldmodel函数，获取我方机器人的向量坐标
//	const point2f& player_pos = model->get_our_player_pos(robot_id); 
//
//	调用 worldmodel函数，获取 我方球员的朝向
//	const float& dir = model->get_our_player_dir(robot_id);
//
//	调用 worldmodel函数，获取 球的向量坐标
//	const point2f& ball_pos = model->get_ball_pos();
//
//	
//	/*  球门 向量坐标 正中心大约是（ 305， 0 ） */
//	设定一个球门坐标
//	point2f opp_gate_pos(300, 25);
//
//	球门 向量坐标，根据 球的位置 适当偏移-- 球偏右，就偏右射门，偏左，就偏左射门
//	if (ball_pos.y < 0)
//	{
//		opp_gate_pos.y = -opp_gate_pos.y;
//	}
//
//	 确定射门方向
//	const float& excute_dir = (opp_gate_pos - ball_pos).angle();
//
//	/* 需要到达的目标点坐标= 球的位置 */		// 目标点坐标 向 方向偏移 10个单位
//	task.target_pos = ball_pos - Maths::vector2polar(10, excute_dir );
//
//	/* 到达目标点朝向= 球-> 球门 的朝向*/
//	task.orientate = excute_dir;// 这个 角度/朝向 也就是 (opp_gate_pos - ball_pos).angle();  
//
//	到达预定目标点 误差 < 5个单位                            
//	if ( is_getball(ball_pos, player_pos, excute_dir) )
//	{
//		if ( (player_pos - opp_gate_pos).length() > 50    )
//			task.kickPower = 50;
//		if ((player_pos - opp_gate_pos).length() > 100)
//			task.kickPower = 75;
//		if ((player_pos - opp_gate_pos).length() > 150)
//				task.kickPower = 100;
//
//		/*踢球力度*/
//		task.kickPower = 127;//力度范围大约是 0~ 80   90 --
//
//		/*是否踢球*/
//		task.needKick = true;
//	}
//	return task; //返回 task 对象，对接lua脚本层 数据
//}	
//

 
/* 简单示例 demo4   传球 */
//PlayerTask player_plan(const WorldModel* model, int robot_id){
//
//	PlayerTask task;
//
//	int  receiver_id = -7;
//
//	for (int i = 0; i < 6; i++)
//	{
//		if (i == robot_id || i == model->get_our_goalie())
//			continue;
//		if (model->get_our_exist_id()[i])
//			receiver_id = i;
//	}
//
// 
//	const float  kicker_dir =model->get_our_player_dir(robot_id); //传球员朝向 kicker
//	const point2f  kicker_pos = model->get_our_player_pos(robot_id);//坐标
//
//	const point2f  receiver_pos = model->get_our_player_pos(receiver_id);// receiver 在场上的坐标
//
//	const point2f   ball_pos = model->get_ball_pos(); //球的坐标
//	//const point2f& opp_goal = -FieldPoint::Goal_Center_Point;//敌方球门坐标
//
//	const float excute_dir = (receiver_pos - ball_pos).angle();// 传球方向
//
//	//判断球是否在小车控球嘴上，从两个参数着手：1.判断ball到车的距离是否小于某个值，2.车头方向和车到球矢量角度之差值是否小于某个值
//	//bool get_ball = fabs( (ball_pos - kicker_pos).length() ) < get_ball_threshold - 1.5 && (fabs(anglemod(excute_dir - (ball_pos - kicker_pos).angle())) < PI / 6);
//
//
//	//	/* 需要到达的目标点坐标= 球的位置 */		// 目标点坐标 向 方向偏移 10个单位
//	task.target_pos = ball_pos - Maths::vector2polar(10, (receiver_pos - ball_pos).angle());
//
//	/*执行 的传球方向*/
//	task.orientate = excute_dir;
//
//	if (is_getball(ball_pos, kicker_pos, kicker_dir))
//	{
//		task.needKick = true;
//		task.kickPower = 25;
//
//		task.target_pos = ball_pos - Maths::vector2polar(10, (receiver_pos - ball_pos).angle());
//		task.orientate = excute_dir;
//	}
//
//	return task;
//}
//							


/* 简单示例 demo6 ， 7   */
/* demo6   找球 +  射门 找球时稍加调整   */  //视频 点球
//PlayerTask player_plan(const WorldModel* model, int robot_id){
//
//	PlayerTask task;
//
//		int  receiver_id = -7;
//	
//		for (int i = 0; i < 6; i++)
//		{
//			if (i == robot_id || i == model->get_our_goalie())
//				continue;
//			if (model->get_our_exist_id()[i])
//				receiver_id = i;
//		}
//
//	const point2f& ball = model->get_ball_pos();
//	const point2f& runner = model->get_our_player_pos(robot_id);
//	const float kicker_dir = model->get_our_player_dir(robot_id);
//
//	const point2f& receiver = model->get_our_player_pos(receiver_id);
//
//	//传球时
//	/* point2f pos = receiver; */
//
//	//射门时
//	point2f pos(300, 25);
//	pos.y = ball.y > 0 ? pos.y : -pos.y;
//
//	float pos_to_ball = (ball - pos).angle();
//
//	//判断小车已经可以传球了
//	if (is_ready_pass(ball, runner, pos)){
//		static int distance = Pass_Kick::fast_pass;
//
//		task.target_pos = ball + Maths::vector2polar(distance, pos_to_ball);
//		task.orientate = (pos - ball).angle();
//		task.needCb = true;
//
//		if (is_getball(ball, runner, kicker_dir))
//		{
//			task.needKick = true;
//			task.kickPower = 100;  //[0, 126]
//			task.needCb = false;
//		}
//	}
//	else{//距离球较远时，不断靠近
//		task.target_pos = ball + Maths::vector2polar(BALL_SIZE / 2 + MAX_ROBOT_SIZE + 15, pos_to_ball);
//		if (ball.y>0){//球在y轴正向
//			if (runner.y < ball.y){
//				task.target_pos.x = runner.x;
//				task.target_pos.y = runner.y + Pass_Kick::get_buff;
//			}
//			else{
//				task.target_pos = ball + Maths::vector2polar(BALL_SIZE / 2 + MAX_ROBOT_SIZE + 15, pos_to_ball);
//			}
//		}
//		else{//球在y轴负向
//			if (runner.y>ball.y){
//				task.target_pos.x = runner.x;
//				task.target_pos.y = runner.y - Pass_Kick::get_buff;
//			}
//			else{
//				task.target_pos = ball + Maths::vector2polar(BALL_SIZE / 2 + MAX_ROBOT_SIZE + 15, pos_to_ball);
//			}
//		}
//		task.orientate = (pos - ball).angle();
//	}
//
//	if (task.needCb == true){
//		task.target_pos = ball + Maths::vector2polar(Pass_Kick::fast_pass, pos_to_ball);
//		task.orientate = (pos - ball).angle();
//		task.needCb = true;
//		if (is_getball(ball, runner, kicker_dir))
//				{
//					task.needKick = true;
//					task.kickPower = 120;
//					task.needCb = false;
//				}
//	}
//
//	return task;
//}
/* demo7   找球 +  传球 找球时稍加调整   */  //视频 传球
//PlayerTask player_plan(const WorldModel* model, int robot_id){
//
//	PlayerTask task;
//
//		int  receiver_id = -7;
//	
//		for (int i = 0; i < 6; i++)
//		{
//			if (i == robot_id || i == model->get_our_goalie())
//				continue;
//			if (model->get_our_exist_id()[i])
//				receiver_id = i;
//		}
//
//	const point2f& ball = model->get_ball_pos();
//	const point2f& runner = model->get_our_player_pos(robot_id);
//	const float kicker_dir = model->get_our_player_dir(robot_id);
//
//	const point2f& receiver = model->get_our_player_pos(receiver_id);
//
//	//传球时
//	point2f pos = receiver; 
//
//	//射门时
//	/*point2f pos(300, 25);
//	pos.y = ball.y > 0 ? pos.y : -pos.y;;*/
//
//	float pos_to_ball = (ball - pos).angle();
//	
//
//	//判断小车已经可以传球了
//	if (is_ready_pass(ball, runner, pos)){
//		static int distance=Pass_Kick::fast_pass;
//		
//		task.target_pos = ball + Maths::vector2polar( distance, pos_to_ball);
//		task.orientate = (pos - ball).angle();
//		task.needCb = true;
//
//		if (is_getball(ball, runner, kicker_dir))
//		{
//			task.needKick = true;
//			task.kickPower = 25;
//			task.needCb = false;
//		}
//	}
//	else{//距离球较远时，不断靠近
//		task.target_pos = ball + Maths::vector2polar(BALL_SIZE / 2 + MAX_ROBOT_SIZE + 15, pos_to_ball);
//		if (ball.y>0){//球在y轴正向
//			if (runner.y < ball.y){
//				task.target_pos.x = runner.x;
//				task.target_pos.y = runner.y + Pass_Kick::get_buff;
//			}
//			else{
//				task.target_pos = ball + Maths::vector2polar(BALL_SIZE / 2 + MAX_ROBOT_SIZE + 15, pos_to_ball);
//			}
//		}
//		else{//球在y轴负向
//			if (runner.y>ball.y){
//				task.target_pos.x = runner.x;
//				task.target_pos.y = runner.y - Pass_Kick::get_buff;
//			}
//			else{
//				task.target_pos = ball + Maths::vector2polar(BALL_SIZE / 2 + MAX_ROBOT_SIZE + 15, pos_to_ball);
//			}
//		}
//		task.orientate = (pos - ball).angle();
//	}
//
//	return task;
//}



/*官方C++ demo 给出的方法，稍作修改可以参考使用， 直接调用会出现不明错误  仅拿官方给出的demo_method作为参考*/
//#include "demo_method\GetBall.h"
//#include "demo_method\Shoot.h"
//#include "demo_method\PenaltyKick.h"
//#include "demo_method\GotoPos.h"
//#include "demo_method\Shoot.h"
//#include "demo_method\goalie.h"
//#include   "demo_method\GotoPos.h"
/* 简单示例 demo5   少部分可行  调用官方的 C++ 方法  ，
   如果含有这一类 const point2f& ball = worldModel::getInstance()->get_ball_pos();不可行
   使用指针  	  const point2f& player_pos = model->get_our_player_pos(robot_id); 可以运行
   可是官方给的方法全是 前者， 所以 官方给的方法也就当 参考看吧，需要的话复制一段
*/
//PlayerTask player_plan(const WorldModel* model, int robot_id) {
//
//	PlayerTask task;
//	
//	GotoPos gotopos;
//
//  task= gotoPos::getInstance()->plan(250, 70, 0);
//
//	return  task;
//}	
