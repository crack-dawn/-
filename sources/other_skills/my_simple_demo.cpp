


/*
// lua�㺯�� ��Ҫ C++dll���ص�task �����ĳЩ���ԣ�C++��������Ҫ����lua������������ֻ�������������ϳ��ģ� lua ���� c++ ��skill Ӧ�ò���Ǻܴ�
// ���˵�����ǣ� C++dll ������һЩ ִ��������Ҫ�����ݣ� ������lua ������������Կ� 
// ��\SOM v3.4.2\Team\lua_scripts\skill ��lua�� ���� c++dll�� skill������װ��Ҳ�ͷ����˼����ؼ���Ա�����ԣ�
// ֵ��ע����ǣ�C++dll ��ѭ�����õģ��� [state_0] ������Է���״̬�£��᲻�ϵ���skill ��kickier ���� receiver ��������
// Ҳ����˵�� C++dll ��ȡ������ ÿ�ε���ʱ������ֱ������ϵ�����ʵʱˢ��
/*
   
  ���ɵ� .dll �� �� \Demo\Release Ŀ¼��
  �������ɵ� dll ʱ�� �ǵø�����
  ������������� .dll�ļ��ƶ��� �� \SOM v3.4.2\Team\user_skills ���Ŀ¼�£��ſ�����lua�������������ã�Ҳ������ demo_test.lua ���Ƶ�lua�ļ��ڵ���

  ���ڲ���demo����� lua�ű� �� �� \SOM v3.4.2\Team\lua_scripts\play\Test\Others\demo_test.lua��

  ˳��һ�ᣬ ���԰����ڲ��Ե�lua�ű����� \SOM v3.4.2\Team\lua_scripts\play\Test\Others\ Ŀ¼�£�ÿ�����ƽ̨���뵽����ģʽ�Ϳ��Կ�����Ҫ���Ե�lua�ű�

  */
 





#include "maths.h"
#include "PlayerTask.h"
#include "worldmodel.h"

#ifdef __cplusplus//�û�ע�⣻�ӿ���Ҫ��������  
extern "C"
{
#endif
	//ȫ������ һ����� C++ dll �Ľӿں����� �����dll ��̬��߱��������Ҫʵ�ֵĹ���
	__declspec(dllexport) PlayerTask player_plan(const WorldModel* model, int robot_id);

#ifdef __cplusplus
}
#endif


 

///* ��ʾ�� demo1   �����ܶ�*/   
PlayerTask player_plan(const WorldModel* model, int robot_id){

	PlayerTask task;//����task ����

	point2f we_pos(305, 10);  //�ܵ��Է�������

	task.target_pos = we_pos;

	return task;

}


























//namespace Pass_Kick{//ʵ�ز��Եó�
//	const float head_len = 7;
//	const float miss = 12;//Խ���������Խ���� �������
//	const float getangle = PI / 20; //�Ƕ�ֵ
//	const int  fast_pass = 9; //���Դ�����
//	const int get_buff = 35;//ÿ�ε�������
//}

///*��������  ������������ ball kicker receiver */
//bool is_ready_pass(const point2f& ball, const point2f& passer, const point2f& receiver){
//	float receiver_to_ball = (ball - receiver).angle();
//	float ball_to_passer = (passer - ball).angle();
//	//float distance_miss = fabs((ball - passer).length());
//	float dir_miss = fabs(receiver_to_ball - ball_to_passer);
//	//����ʸ���Ƕ�֮��С��ĳ��ֵ���ж��Ƿ���Դ���
//	bool pass = (dir_miss < 0.25);
//	return pass;
//}



/* ��ʾ�� demo2   ����֮�� �������� */  //��Ƶ ����
//PlayerTask player_plan(const WorldModel* model, int robot_id) {
// 
//	PlayerTask task;
//
//	//���� worldmodel��������ȡ�ҷ������˵���������
//	const point2f& player_pos = model->get_our_player_pos(robot_id);
//
//	//���� worldmodel��������ȡ �ҷ���Ա�ĳ���
//	const float dir = model->get_our_player_dir(robot_id);
//
//	//���� worldmodel��������ȡ �����������
//	const point2f  ball_pos = model->get_ball_pos();
//
//	//�з���������������
//	const point2f& opp_goal = -FieldPoint::Goal_Center_Point;
//
//	//�������� ��-�� �õ��ĳ����� ��->�٣� ����ѧ�ϣ�1,2��-��0,0���õ��ķ��������ǣ�1,2����ͬС�죬���� ��Ա���� angle() �õ���������
//	//���� �趨 face_dir ��  ���� ���ŵķ���
//	const float& face_dir = (opp_goal - ball_pos).angle();
//
//
//	/* ����Ŀ��㳯��:  ��Ա ����  ��   */
//	task.orientate = face_dir;
//
//	/* ��Ҫ�����Ŀ�������= ���λ�� + ����ƫ�ƾ��� */		// face_dir ������ƫ�� 13����λ
//	task.target_pos = ball_pos  - Maths::vector2polar(13, face_dir);
//
//	return task; //���� task ���󣬶Խ�lua�ű��� ����
//}


///* �����ж� ������������ pos�� ball  kicker  �� dir�� kick_dir*/
bool is_getball(const point2f& ball, const point2f& kicker, const float& kick_dir) {

	static int  miss = get_ball_threshold; //�Ƿ� �õ��� ������

	bool get_ball = (ball - kicker).length() < miss && (fabs(anglemod(kick_dir - (ball - kicker).angle())) < PI / 15);

	if (get_ball) {
		return true;
	}
	else {
		return false;
	}

}

/* ��ʾ�� demo3   ���� ׼��  ����*/
//PlayerTask player_plan(const WorldModel* model, int robot_id) {
//
//	PlayerTask task;
//
//	/*��ȡ���� ���ģ� ��Ա��λ��  �����λ��  �����˳���   */
//	���� worldmodel��������ȡ�ҷ������˵���������
//	const point2f& player_pos = model->get_our_player_pos(robot_id); 
//
//	���� worldmodel��������ȡ �ҷ���Ա�ĳ���
//	const float& dir = model->get_our_player_dir(robot_id);
//
//	���� worldmodel��������ȡ �����������
//	const point2f& ball_pos = model->get_ball_pos();
//
//	
//	/*  ���� �������� �����Ĵ�Լ�ǣ� 305�� 0 �� */
//	�趨һ����������
//	point2f opp_gate_pos(300, 25);
//
//	���� �������꣬���� ���λ�� �ʵ�ƫ��-- ��ƫ�ң���ƫ�����ţ�ƫ�󣬾�ƫ������
//	if (ball_pos.y < 0)
//	{
//		opp_gate_pos.y = -opp_gate_pos.y;
//	}
//
//	 ȷ�����ŷ���
//	const float& excute_dir = (opp_gate_pos - ball_pos).angle();
//
//	/* ��Ҫ�����Ŀ�������= ���λ�� */		// Ŀ������� �� ����ƫ�� 10����λ
//	task.target_pos = ball_pos - Maths::vector2polar(10, excute_dir );
//
//	/* ����Ŀ��㳯��= ��-> ���� �ĳ���*/
//	task.orientate = excute_dir;// ��� �Ƕ�/���� Ҳ���� (opp_gate_pos - ball_pos).angle();  
//
//	����Ԥ��Ŀ��� ��� < 5����λ                            
//	if ( is_getball(ball_pos, player_pos, excute_dir) )
//	{
//		if ( (player_pos - opp_gate_pos).length() > 50    )
//			task.kickPower = 50;
//		if ((player_pos - opp_gate_pos).length() > 100)
//			task.kickPower = 75;
//		if ((player_pos - opp_gate_pos).length() > 150)
//				task.kickPower = 100;
//
//		/*��������*/
//		task.kickPower = 127;//���ȷ�Χ��Լ�� 0~ 80   90 --
//
//		/*�Ƿ�����*/
//		task.needKick = true;
//	}
//	return task; //���� task ���󣬶Խ�lua�ű��� ����
//}	
//

 
/* ��ʾ�� demo4   ���� */
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
//	const float  kicker_dir =model->get_our_player_dir(robot_id); //����Ա���� kicker
//	const point2f  kicker_pos = model->get_our_player_pos(robot_id);//����
//
//	const point2f  receiver_pos = model->get_our_player_pos(receiver_id);// receiver �ڳ��ϵ�����
//
//	const point2f   ball_pos = model->get_ball_pos(); //�������
//	//const point2f& opp_goal = -FieldPoint::Goal_Center_Point;//�з���������
//
//	const float excute_dir = (receiver_pos - ball_pos).angle();// ������
//
//	//�ж����Ƿ���С���������ϣ��������������֣�1.�ж�ball�����ľ����Ƿ�С��ĳ��ֵ��2.��ͷ����ͳ�����ʸ���Ƕ�֮��ֵ�Ƿ�С��ĳ��ֵ
//	//bool get_ball = fabs( (ball_pos - kicker_pos).length() ) < get_ball_threshold - 1.5 && (fabs(anglemod(excute_dir - (ball_pos - kicker_pos).angle())) < PI / 6);
//
//
//	//	/* ��Ҫ�����Ŀ�������= ���λ�� */		// Ŀ������� �� ����ƫ�� 10����λ
//	task.target_pos = ball_pos - Maths::vector2polar(10, (receiver_pos - ball_pos).angle());
//
//	/*ִ�� �Ĵ�����*/
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


/* ��ʾ�� demo6 �� 7   */
/* demo6   ���� +  ���� ����ʱ�Լӵ���   */  //��Ƶ ����
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
//	//����ʱ
//	/* point2f pos = receiver; */
//
//	//����ʱ
//	point2f pos(300, 25);
//	pos.y = ball.y > 0 ? pos.y : -pos.y;
//
//	float pos_to_ball = (ball - pos).angle();
//
//	//�ж�С���Ѿ����Դ�����
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
//	else{//�������Զʱ�����Ͽ���
//		task.target_pos = ball + Maths::vector2polar(BALL_SIZE / 2 + MAX_ROBOT_SIZE + 15, pos_to_ball);
//		if (ball.y>0){//����y������
//			if (runner.y < ball.y){
//				task.target_pos.x = runner.x;
//				task.target_pos.y = runner.y + Pass_Kick::get_buff;
//			}
//			else{
//				task.target_pos = ball + Maths::vector2polar(BALL_SIZE / 2 + MAX_ROBOT_SIZE + 15, pos_to_ball);
//			}
//		}
//		else{//����y�Ḻ��
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
/* demo7   ���� +  ���� ����ʱ�Լӵ���   */  //��Ƶ ����
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
//	//����ʱ
//	point2f pos = receiver; 
//
//	//����ʱ
//	/*point2f pos(300, 25);
//	pos.y = ball.y > 0 ? pos.y : -pos.y;;*/
//
//	float pos_to_ball = (ball - pos).angle();
//	
//
//	//�ж�С���Ѿ����Դ�����
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
//	else{//�������Զʱ�����Ͽ���
//		task.target_pos = ball + Maths::vector2polar(BALL_SIZE / 2 + MAX_ROBOT_SIZE + 15, pos_to_ball);
//		if (ball.y>0){//����y������
//			if (runner.y < ball.y){
//				task.target_pos.x = runner.x;
//				task.target_pos.y = runner.y + Pass_Kick::get_buff;
//			}
//			else{
//				task.target_pos = ball + Maths::vector2polar(BALL_SIZE / 2 + MAX_ROBOT_SIZE + 15, pos_to_ball);
//			}
//		}
//		else{//����y�Ḻ��
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



/*�ٷ�C++ demo �����ķ����������޸Ŀ��Բο�ʹ�ã� ֱ�ӵ��û���ֲ�������  ���ùٷ�������demo_method��Ϊ�ο�*/
//#include "demo_method\GetBall.h"
//#include "demo_method\Shoot.h"
//#include "demo_method\PenaltyKick.h"
//#include "demo_method\GotoPos.h"
//#include "demo_method\Shoot.h"
//#include "demo_method\goalie.h"
//#include   "demo_method\GotoPos.h"
/* ��ʾ�� demo5   �ٲ��ֿ���  ���ùٷ��� C++ ����  ��
   ���������һ�� const point2f& ball = worldModel::getInstance()->get_ball_pos();������
   ʹ��ָ��  	  const point2f& player_pos = model->get_our_player_pos(robot_id); ��������
   ���ǹٷ����ķ���ȫ�� ǰ�ߣ� ���� �ٷ����ķ���Ҳ�͵� �ο����ɣ���Ҫ�Ļ�����һ��
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
