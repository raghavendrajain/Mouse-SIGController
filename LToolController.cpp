#include "ControllerEvent.h"
#include "Controller.h"
#include "Logger.h"
#include <iostream>

using namespace std;

class MyController : public Controller {  
public:  
  void onInit(InitEvent &evt);  
  double onAction(ActionEvent&);
  void onRecvMsg(RecvMsgEvent &evt); 
  void onCollision(CollisionEvent &evt);   
 
private:
  bool accelerationValueRecieved;
 
};  

static double xPos = 0; 
static double yPos= 0; 


static int messageCount;
static int onActionCount;
static int flag=1;
static Vector3d pos;

void MyController::onInit(InitEvent &evt) {  

  SimObj *obj = getObj(myname());
 
}  
  
double MyController::onAction(ActionEvent &evt) {  
  //return 1.0;
  SimObj *obj = getObj(myname());
 
  double massOfTool;  
  massOfTool = obj->getMass();
  obj->getPosition(pos);
  
  return 0.00001;
      
} 

std::string msg = " ";

void MyController::onRecvMsg(RecvMsgEvent &evt)
{

  SimObj *my = getObj(myname());

  char *all_msg = (char*)evt.getMsg();
  // std::string msg;
  msg= evt.getMsg();

  LOG_MSG((msg.c_str()));


  char xPosStr[10]=" "; 
  char yPosStr[10]=" ";
  int result=0;

  result = sscanf(msg.c_str(), "%[^','],%[^',']", xPosStr, yPosStr ); 
  xPos = atof(xPosStr);
  yPos = atof(yPosStr);

  // LOG_MSG((" Position Received by Controller : %f %f ", xPos, yPos));
  //std::cout <<"xPos is" << xPos <<std::endl;

  messageCount++;
  std::cout << "The received mesage count is" << messageCount <<std::endl;

  my->setPosition(pos.x() + xPos, pos.y(), pos.z() + yPos);

}


void MyController::onCollision(CollisionEvent &evt) { 
}


extern "C" Controller * createController() {  
  return new MyController;  
}  


