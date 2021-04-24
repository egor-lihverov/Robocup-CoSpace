////////////////////////////////////////
//
//	File : ai.c
//	CoSpace Robot
//	Version 1.0.0
//	Jan 1 2021
//	Copyright (C) 2021 CoSpace Robot. All Rights Reserved
//
//////////////////////////////////////
//
// ONLY C Code can be compiled.
//
/////////////////////////////////////

#define CsBot_AI_H//DO NOT delete this line
#ifndef CSBOT_REAL
#include <windows.h>
#include <stdio.h>
#include <math.h>
#define DLL_EXPORT extern __declspec(dllexport)
#define false 0
#define true 1
#endif
//The robot ID : six chars unique CID.
//Find it from your CoSpace Robot label or CoSpace program download GUI.
//Don't write the below line into two lines or more lines.
char AI_MyID[6] = {'1','2','3','4','5','6'};

int Duration = 0;
int SuperDuration = 0;
int bGameEnd = false;
int CurAction = -1;
int CurGame = 0;
int SuperObj_Num = 0;
int SuperObj_X = 0;
int SuperObj_Y = 0;
int Teleport = 0;
int LoadedObjects = 0;
int US_Front = 0;
int US_Left = 0;
int US_Right = 0;
int CSLeft_R = 0;
int CSLeft_G = 0;
int CSLeft_B = 0;
int CSRight_R = 0;
int CSRight_G = 0;
int CSRight_B = 0;
int PositionX = 0;
int PositionY = 0;
int TM_State = 0;
int Compass = 0;
int Time = 0;
int WheelLeft = 0;
int WheelRight = 0;
int LED_1 = 0;
int MyState = 0;
int AI_SensorNum = 13;
int AI_TeamID = 1;   //Robot Team ID. 1:Blue Ream; 2:Red Team.
int MySMS; //A integer value which you want to send to the other robot.
           //In Super Team mode, you can use this value to inform your another robot of your status.
           //In Indiviual Mode, you should keep this value to 0.  

//The following three variables save the information of the other robot.
int OtherRob_SMS; //Keep the recieved value of the other robot MySMS value.
            //In Super Team mode, this value is sent by your another robot.
            //In Indiviual Mode, this value has no meaning.
int OtherRob_PositionX;//The X coordinate of the other robot. 
int OtherRob_PositionY;//The Y coordinate of the other robot. 

//The following four variables keep the information of the last state-changed object.
int ObjState;    //The state (0: Disappear; 1:Appear.) of the last state changed object.
int ObjPositionX;//The X coordinate of the last state-changed object.
int ObjPositionY;//The Y coordinate of the last state-changed object.
int ObjDuration; //The duration(seconds) of the object maintains the current state;


int turn;

#define CsBot_AI_C//DO NOT delete this line

DLL_EXPORT void SetGameID(int GameID)
{
    CurGame = GameID;
    bGameEnd = 0;
}


DLL_EXPORT void SetTeamID(int TeamID)
{
    AI_TeamID = TeamID;
}

DLL_EXPORT int GetGameID()
{
    return CurGame;
}

//Only Used by CsBot Dance Platform
DLL_EXPORT int IsGameEnd()
{
    return bGameEnd;
}

#ifndef CSBOT_REAL

DLL_EXPORT char* GetDebugInfo()
{
    char info[3000];
    sprintf(info, "Duration=%d;SuperDuration=%d;bGameEnd=%d;CurAction=%d;CurGame=%d;SuperObj_Num=%d;SuperObj_X=%d;SuperObj_Y=%d;Teleport=%d;LoadedObjects=%d;US_Front=%d;US_Left=%d;US_Right=%d;CSLeft_R=%d;CSLeft_G=%d;CSLeft_B=%d;CSRight_R=%d;CSRight_G=%d;CSRight_B=%d;PositionX=%d;PositionY=%d;TM_State=%d;Compass=%d;Time=%d;WheelLeft=%d;WheelRight=%d;LED_1=%d;MyState=%d;",Duration,SuperDuration,bGameEnd,CurAction,CurGame,SuperObj_Num,SuperObj_X,SuperObj_Y,Teleport,LoadedObjects,US_Front,US_Left,US_Right,CSLeft_R,CSLeft_G,CSLeft_B,CSRight_R,CSRight_G,CSRight_B,PositionX,PositionY,TM_State,Compass,Time,WheelLeft,WheelRight,LED_1,MyState);
    return info;
}
 
DLL_EXPORT char* GetTeamName()
{
     return " ";
}

DLL_EXPORT int GetCurAction()
{
    return CurAction;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT int GetTeleport()
{
    return Teleport;
}

//Only Used by CsBot Rescue Platform
DLL_EXPORT void SetSuperObj(int X, int Y, int num)
{
    SuperObj_X = X;
    SuperObj_Y = Y;
    SuperObj_Num = num;
}
//Only Used by CsBot Rescue Platform
DLL_EXPORT void GetSuperObj(int *X, int *Y, int *num)
{
    *X = SuperObj_X;
    *Y = SuperObj_Y;
    *num = SuperObj_Num;
}
//Used by CoSpace Rescue Simulation. 
///Called each time frame by simulator to update the other robot information.
DLL_EXPORT void UpdateRobInfo(int sms, int X, int Y)
{
	OtherRob_SMS = sms;
	OtherRob_PositionX = X;
	OtherRob_PositionY = Y;
}

//Used by CsBot Rescue Platform
DLL_EXPORT void UpdateObjectInfo(int X, int Y, int state, int duration)
{
	ObjState = state;
	ObjPositionX = X;
	ObjPositionY = Y;
	ObjDuration = duration;
}
DLL_EXPORT int GetMySMS()
{
	return MySMS;
}

#endif ////CSBOT_REAL

DLL_EXPORT void SetDataAI(volatile int* packet, volatile int *AI_IN)
{

    int sum = 0;

    US_Front = AI_IN[0]; packet[0] = US_Front; sum += US_Front;
    US_Left = AI_IN[1]; packet[1] = US_Left; sum += US_Left;
    US_Right = AI_IN[2]; packet[2] = US_Right; sum += US_Right;
    CSLeft_R = AI_IN[3]; packet[3] = CSLeft_R; sum += CSLeft_R;
    CSLeft_G = AI_IN[4]; packet[4] = CSLeft_G; sum += CSLeft_G;
    CSLeft_B = AI_IN[5]; packet[5] = CSLeft_B; sum += CSLeft_B;
    CSRight_R = AI_IN[6]; packet[6] = CSRight_R; sum += CSRight_R;
    CSRight_G = AI_IN[7]; packet[7] = CSRight_G; sum += CSRight_G;
    CSRight_B = AI_IN[8]; packet[8] = CSRight_B; sum += CSRight_B;
    PositionX = AI_IN[9]; packet[9] = PositionX; sum += PositionX;
    PositionY = AI_IN[10]; packet[10] = PositionY; sum += PositionY;
    TM_State = AI_IN[11]; packet[11] = TM_State; sum += TM_State;
    Compass = AI_IN[12]; packet[12] = Compass; sum += Compass;
    Time = AI_IN[13]; packet[13] = Time; sum += Time;
    packet[14] = sum;

}
DLL_EXPORT void GetCommand(int *AI_OUT)
{
    AI_OUT[0] = WheelLeft;
    AI_OUT[1] = WheelRight;
    AI_OUT[2] = LED_1;
    AI_OUT[3] = MyState;
}
void Game0()
{

    if(Duration>0)
    {
        Duration--;
    }
	else if (LoadedObjects > 0 && CSLeft_R >= 230 && CSLeft_R <= 255 && CSLeft_G >= 230 && CSLeft_G <= 255 && CSLeft_B >=0 && CSLeft_B <= 10 &&
		CSRight_R >= 230 && CSRight_R <= 255 && CSRight_G >= 230 && CSRight_G <= 255 && CSRight_B >=0 && CSRight_B <= 10){
			Duration = 2;
			CurAction = 1;
		}
    else if(LoadedObjects > 0 && CSLeft_R >= 230 && CSLeft_R <= 255 && CSLeft_G >= 230 && CSLeft_G <= 255 && CSLeft_B >=0 && CSLeft_B <= 10)
	{
    	Duration = 1;
        CurAction = 2;
	}
	else if (LoadedObjects > 0 && CSRight_R >= 230 && CSRight_R <= 255 && CSRight_G >= 230 && CSRight_G <= 255 && CSRight_B >=0 && CSRight_B <= 10){
		Duration = 1;
        CurAction = 3;
	}
	
	else if ((((CSLeft_R >= 200 && CSLeft_R <= 255 && CSLeft_G >= 0 && CSLeft_G <= 50 && CSLeft_B >= 0 &&
               CSLeft_B <= 50)
              ||
              (CSRight_R >= 200 && CSRight_R <= 255 && CSRight_G >= 0 && CSRight_G <= 50 && CSRight_B >= 0 &&
               CSRight_B <= 50))

             ||

             //cyan//
             ((CSLeft_R >= 0 && CSLeft_R <= 50 && CSLeft_G >= 220 && CSLeft_G <= 255 && CSLeft_B >= 220 &&
               CSLeft_B <= 255)
              ||
              (CSRight_R >= 0 && CSRight_R <= 50 && CSRight_G >= 220 && CSRight_G <= 255 && CSRight_B >= 220 &&
               CSRight_B <= 255))

             ||


             //black//
             ((CSLeft_R >= 0 && CSLeft_R <= 50 && CSLeft_G >= 0 && CSLeft_G <= 50 && CSLeft_B >= 0 && CSLeft_B <= 50)
              ||
              (CSRight_R >= 0 && CSRight_R <= 50 && CSRight_G >= 0 && CSRight_G <= 50 && CSRight_B >= 0 &&
               CSRight_B <= 50)))


            &&
            (LoadedObjects < 6)
            )
		{
			Duration = 50;
			CurAction = 4;
		}
	else if (LoadedObjects > 2 && ((CSLeft_R >= 230 && CSLeft_R <= 255 && CSLeft_G >= 135 && CSLeft_G <= 150 && CSLeft_B >= 0 && CSLeft_B <= 20)
              ||
              (CSRight_R >= 230 && CSRight_R <= 255 && CSRight_G >= 135 && CSRight_G <= 150 && CSRight_B >= 0 &&
               CSRight_B <= 20)))
	{
		Duration = 100;
		CurAction = 5;
	}
	
	else if (US_Front >= 0 && US_Front <= 10){
		Duration = 2;
		CurAction = 17;
		turn = (rand()) % 2;
	}
	else if (US_Left >= 0 && US_Left <= 12 && US_Right>= 0 && US_Right <= 12 && US_Front >= 20){
		Duration = 5;
		CurAction = 16;
	}
	else if (US_Left >= 0 && US_Left <= 6){
		Duration = 1;
		CurAction = 18;
	}
	else if (US_Right>= 0 && US_Right <= 6){
		Duration = 1;
		CurAction = 19;
	}
	else{
		CurAction = 20;
	}
    switch(CurAction)
    {
    	case 0:
    		WheelLeft=0;
            WheelRight=0;
            break;
        case 1:
            WheelLeft=-50;
            WheelRight=20;
            LED_1=0;
            break;
        case 2:
        	WheelLeft=50;
            WheelRight=20;
            LED_1 = 0;
            break;
        case 3:
        	WheelLeft=20;
            WheelRight=50;
            LED_1=0;
            break;
        case 4:
        	WheelLeft = 0;
            WheelRight = 0;
            LED_1 = 1;
            MyState = 0;
            if (Duration == 1) LoadedObjects++;
            if (LoadedObjects == 6) MyState = 1;
            break;
        case 5:
        	if (! (CSLeft_R >= 230 && CSLeft_R <= 255 && CSLeft_G >= 135 && CSLeft_G <= 150 && CSLeft_B >= 0 && CSLeft_B <= 20))
			{
        		WheelRight = -10;
        		WheelLeft = 60;
			}
			else if(! (CSRight_R >= 230 && CSRight_R <= 255 && CSRight_G >= 135 && CSRight_G <= 150 && CSRight_B >= 0 &&
               CSRight_B <= 20))
			{
				WheelRight = 60;
            	WheelLeft = -10;
			}
			else if (Duration > 90){
				WheelLeft = 30;
				WheelRight = 30;
			} 
			else{
				WheelLeft = 0;
	            WheelRight = 0;
	        	LED_1 = 2;
	            if (Duration == 1) 
				{
					MyState = 0;
					LoadedObjects = 0;
				}
			}
            
            break;
            
        case 16:
			WheelLeft = 30;
        	WheelRight = 30;
        	LED_1=0;
            break;
        
        case 17:
        	if(MyState == 1){
        		WheelLeft = -30;

                WheelRight = 30;
        		/*if (Compass < 30 || Compass > 350) {
                    WheelLeft = -30;

                    WheelRight = 30;

                } else {
                	WheelLeft = 30;

                    WheelRight = -30;
                    

                }
        		*/
			}
        	else if (US_Left >= 0 && US_Left <= 7 && turn == 0){
        		WheelLeft = 30;
        		WheelRight = -30;
        		Duration++;
			}
			else if (US_Right >= 0 && US_Right <= 7 && turn == 1){
				WheelLeft = -30;
        		WheelRight = 30;
        		Duration++;
			}
			else{
				if(turn == 1){
					WheelLeft = -30;
        			WheelRight = 30;
				}
				else{
					WheelLeft = 30;
        			WheelRight = -30;
				}
				
			}
			LED_1=0;
            break;
            
        	
        case 18:
        	WheelLeft = 20;
        	WheelRight = -20;
        	LED_1=0;
            break;
        	
        case 19:
        	WheelLeft = -20;
        	WheelRight = 20;
        	LED_1=0;
            break;
        	
        case 20:
        	
            WheelLeft=45;
            WheelRight=45;
            LED_1=0;
            break;
        
        default:
        	WheelLeft=0;
            WheelRight=0;
            break;
    }

}

/*void Game1(){
	
    if(Duration>0)
    {
        Duration--;
    }
	else if (LoadedObjects > 0 && CSLeft_R >= 230 && CSLeft_R <= 255 && CSLeft_G >= 230 && CSLeft_G <= 255 && CSLeft_B >=0 && CSLeft_B <= 10 &&
		CSRight_R >= 230 && CSRight_R <= 255 && CSRight_G >= 230 && CSRight_G <= 255 && CSRight_B >=0 && CSRight_B <= 10){
			Duration = 2;
			CurAction = 1;
		}
    else if(LoadedObjects > 0 && CSLeft_R >= 230 && CSLeft_R <= 255 && CSLeft_G >= 230 && CSLeft_G <= 255 && CSLeft_B >=0 && CSLeft_B <= 10)
	{
    	Duration = 1;
        CurAction = 2;
	}
	else if (LoadedObjects > 0 && CSRight_R >= 230 && CSRight_R <= 255 && CSRight_G >= 230 && CSRight_G <= 255 && CSRight_B >=0 && CSRight_B <= 10){
		Duration = 1;
        CurAction = 3;
	}
	
	else if ((((CSLeft_R >= 200 && CSLeft_R <= 255 && CSLeft_G >= 0 && CSLeft_G <= 50 && CSLeft_B >= 0 &&
               CSLeft_B <= 50)
              ||
              (CSRight_R >= 200 && CSRight_R <= 255 && CSRight_G >= 0 && CSRight_G <= 50 && CSRight_B >= 0 &&
               CSRight_B <= 50))

             ||

             //cyan//
             ((CSLeft_R >= 0 && CSLeft_R <= 50 && CSLeft_G >= 220 && CSLeft_G <= 255 && CSLeft_B >= 220 &&
               CSLeft_B <= 255)
              ||
              (CSRight_R >= 0 && CSRight_R <= 50 && CSRight_G >= 220 && CSRight_G <= 255 && CSRight_B >= 220 &&
               CSRight_B <= 255))

             ||


             //black//
             ((CSLeft_R >= 0 && CSLeft_R <= 50 && CSLeft_G >= 0 && CSLeft_G <= 50 && CSLeft_B >= 0 && CSLeft_B <= 50)
              ||
              (CSRight_R >= 0 && CSRight_R <= 50 && CSRight_G >= 0 && CSRight_G <= 50 && CSRight_B >= 0 &&
               CSRight_B <= 50)))


            &&
            (LoadedObjects < 6)
            )
		{
			Duration = 50;
			CurAction = 4;
		}
	else if (LoadedObjects > 2 && ((CSLeft_R >= 230 && CSLeft_R <= 255 && CSLeft_G >= 135 && CSLeft_G <= 150 && CSLeft_B >= 0 && CSLeft_B <= 20)
              ||
              (CSRight_R >= 230 && CSRight_R <= 255 && CSRight_G >= 135 && CSRight_G <= 150 && CSRight_B >= 0 &&
               CSRight_B <= 20)))
	{
		Duration = 100;
		CurAction = 5;
	}
	
	else if (US_Front >= 0 && US_Front <= 10){
		Duration = 2;
		CurAction = 17;
		turn = (rand()) % 2;
	}
	else if (US_Left >= 0 && US_Left <= 15 && US_Right>= 0 && US_Right <= 15){
		Duration = 5;
		CurAction = 16;
	}
	else if (US_Left >= 0 && US_Left <= 5){
		Duration = 1;
		CurAction = 18;
	}
	else if (US_Right>= 0 && US_Right <= 5){
		Duration = 1;
		CurAction = 19;
	}
	else{
		CurAction = 20;
	}
    switch(CurAction)
    {
    	case 0:
    		WheelLeft=0;
            WheelRight=0;
            break;
        case 1:
            WheelLeft=-50;
            WheelRight=20;
            LED_1=0;
            break;
        case 2:
        	WheelLeft=50;
            WheelRight=20;
            LED_1 = 0;
            break;
        case 3:
        	WheelLeft=20;
            WheelRight=50;
            LED_1=0;
            break;
        case 4:
        	WheelLeft = 0;
            WheelRight = 0;
            LED_1 = 1;
            MyState = 0;
            if (Duration == 1) LoadedObjects++;
            if (LoadedObjects == 6) MyState = 1;
            break;
        case 5:
        	if (! (CSLeft_R >= 230 && CSLeft_R <= 255 && CSLeft_G >= 135 && CSLeft_G <= 150 && CSLeft_B >= 0 && CSLeft_B <= 20))
			{
        		WheelRight = -10;
        		WheelLeft = 60;
			}
			else if(! (CSRight_R >= 230 && CSRight_R <= 255 && CSRight_G >= 135 && CSRight_G <= 150 && CSRight_B >= 0 &&
               CSRight_B <= 20))
			{
				WheelRight = 60;
            	WheelLeft = -10;
			}
			else if (Duration > 90){
				WheelLeft = 30;
				WheelRight = 30;
			} 
			else{
				WheelLeft = 0;
	            WheelRight = 0;
	        	LED_1 = 2;
	            if (Duration == 1) 
				{
					MyState = 0;
					LoadedObjects = 0;
				}
			}
            
            break;
            
        case 16:
			WheelLeft = 30;
        	WheelRight = 30;
        	LED_1=0;
            break;
        
        case 17:
        	if(MyState == 1){
        		WheelLeft = -30;

                WheelRight = 30;
        		/*if (Compass < 30 || Compass > 350) {
                    WheelLeft = -30;

                    WheelRight = 30;

                } else {
                	WheelLeft = 30;

                    WheelRight = -30;
                    

                }
       
			}
        	else if (US_Left >= 0 && US_Left <= 7 && turn == 0){
        		WheelLeft = 30;
        		WheelRight = -30;
        		Duration++;
			}
			else if (US_Right >= 0 && US_Right <= 7 && turn == 1){
				WheelLeft = -30;
        		WheelRight = 30;
        		Duration++;
			}
			else{
				if(turn == 1){
					WheelLeft = -30;
        			WheelRight = 30;
				}
				else{
					WheelLeft = 30;
        			WheelRight = -30;
				}
				
			}
			LED_1=0;
            break;
            
        	
        case 18:
        	WheelLeft = 20;
        	WheelRight = -20;
        	LED_1=0;
            break;
        	
        case 19:
        	WheelLeft = -20;
        	WheelRight = 20;
        	LED_1=0;
            break;
        	
        case 20:
        	
            WheelLeft=45;
            WheelRight=45;
            LED_1=0;
            break;
        
        default:
        	WheelLeft=0;
            WheelRight=0;
            break;
    }
}*/

DLL_EXPORT void OnTimer()
{
    switch (CurGame)
    {
        case 9:
            break;
        case 10:
            WheelLeft=0;
            WheelRight=0;
            LED_1=0;
            MyState=0;
            break;
        case 0:
            Game0();
            break;
//		case 1:
//            Game1();
//            break;            
        default:
            break;
    }
}

