/**
  *********************************************************************************************************
  * @file    inspectflowmessageoperate.c
  * @author  Movebroad -- KK
  * @version V1.0
  * @date    2018-11-07
  * @brief   
  *********************************************************************************************************
  * @attention
  *
  *
  *
  *********************************************************************************************************
  */

#include "inspectflowmessageoperate.h"
#include "platform_config.h"
#include "platform_map.h"

Inspect_SwapSpotFlowStatusTypeDef			InspectFlowStatus;

/**********************************************************************************************************
 @Function			bool Inspect_Message_FlowStatusisFull(void)
 @Description			Inspect_Message_FlowStatusisFull
 @Input				void
 @Return				true							: 已满
					false						: 未满
**********************************************************************************************************/
bool Inspect_Message_FlowStatusisFull(void)
{
	bool MessageState;
	
	if ((InspectFlowStatus.Rear + 1) % INSPECT_FLOW_STATUS_PACK_NUM == InspectFlowStatus.Front) {
		MessageState = true;
	}
	else {
		MessageState = false;
	}
	
	return MessageState;
}

/**********************************************************************************************************
 @Function			bool Inspect_Message_FlowStatusisEmpty(void)
 @Description			Inspect_Message_FlowStatusisEmpty
 @Input				void
 @Return				true							: 已空
					false						: 未空
**********************************************************************************************************/
bool Inspect_Message_FlowStatusisEmpty(void)
{
	bool MessageState;
	
	if (InspectFlowStatus.Front == InspectFlowStatus.Rear) {
		MessageState = true;
	}
	else {
		MessageState = false;
	}
	
	return MessageState;
}


/**********************************************************************************************************
 @Function			void Inspect_Message_FlowStatusEnqueue(FlowStatusTypeDef dataBuf)
 @Description			Inspect_Message_FlowStatusEnqueue
 @Input				dataBuf	 		 				: 需写入数据
 @Return				void
**********************************************************************************************************/
void Inspect_Message_FlowStatusEnqueue(FlowStatusTypeDef dataBuf)
{
	InspectFlowStatus.Rear = (InspectFlowStatus.Rear + 1) % INSPECT_FLOW_STATUS_PACK_NUM;								//队尾偏移1
	
	InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].FlowState				= dataBuf.FlowState;
	InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].FlowCount				= dataBuf.FlowCount;
	
	InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].magnetismX				= dataBuf.magnetismX;
	InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].magnetismY				= dataBuf.magnetismY;
	InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].magnetismZ				= dataBuf.magnetismZ;
	InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].magnetismBackX			= dataBuf.magnetismBackX;
	InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].magnetismBackY			= dataBuf.magnetismBackY;
	InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].magnetismBackZ			= dataBuf.magnetismBackZ;
	InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].magnetismDiff			= dataBuf.magnetismDiff;
	
	InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].detectMode				= dataBuf.detectMode;
	InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].carinThreshhold			= dataBuf.carinThreshhold;
	InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].caroutThreshhold			= dataBuf.caroutThreshhold;
	InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].recalibrationOvertime		= dataBuf.recalibrationOvertime;
	InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].waitSendHeartbeatMin		= dataBuf.waitSendHeartbeatMin;
	
	InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].timeCounter				= dataBuf.timeCounter;
	InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].unixTime				= dataBuf.unixTime;
	
	if (Inspect_Message_FlowStatusisFull() == true) {																//队列已满
		InspectFlowStatus.Front = (InspectFlowStatus.Front + 1) % INSPECT_FLOW_STATUS_PACK_NUM;							//队头偏移1
	}
}

/**********************************************************************************************************
 @Function			bool Inspect_Message_FlowStatusDequeue(FlowStatusTypeDef* dataBuf)
 @Description			Inspect_Message_FlowStatusDequeue
 @Input				dataBuf	 		 				: 需读出数据地址
 @Return				true								: 未空
					false							: 已空
**********************************************************************************************************/
bool Inspect_Message_FlowStatusDequeue(FlowStatusTypeDef* dataBuf)
{
	bool MessageState;
	unsigned char front;
	
	if (Inspect_Message_FlowStatusisEmpty() == true) {															//队列已空
		MessageState = false;
	}
	else {																								//队列未空
		front = (InspectFlowStatus.Front + 1) % INSPECT_FLOW_STATUS_PACK_NUM;											//队头偏移1
		
		dataBuf->FlowState				= InspectFlowStatus.FlowStatus[front].FlowState;
		dataBuf->FlowCount				= InspectFlowStatus.FlowStatus[front].FlowCount;
		
		dataBuf->magnetismX				= InspectFlowStatus.FlowStatus[front].magnetismX;
		dataBuf->magnetismY				= InspectFlowStatus.FlowStatus[front].magnetismY;
		dataBuf->magnetismZ				= InspectFlowStatus.FlowStatus[front].magnetismZ;
		dataBuf->magnetismBackX			= InspectFlowStatus.FlowStatus[front].magnetismBackX;
		dataBuf->magnetismBackY			= InspectFlowStatus.FlowStatus[front].magnetismBackY;
		dataBuf->magnetismBackZ			= InspectFlowStatus.FlowStatus[front].magnetismBackZ;
		dataBuf->magnetismDiff			= InspectFlowStatus.FlowStatus[front].magnetismDiff;
		
		dataBuf->detectMode				= InspectFlowStatus.FlowStatus[front].detectMode;
		dataBuf->carinThreshhold			= InspectFlowStatus.FlowStatus[front].carinThreshhold;
		dataBuf->caroutThreshhold		= InspectFlowStatus.FlowStatus[front].caroutThreshhold;
		dataBuf->recalibrationOvertime	= InspectFlowStatus.FlowStatus[front].recalibrationOvertime;
		dataBuf->waitSendHeartbeatMin		= InspectFlowStatus.FlowStatus[front].waitSendHeartbeatMin;
		
		dataBuf->timeCounter			= InspectFlowStatus.FlowStatus[front].timeCounter;
		dataBuf->unixTime				= InspectFlowStatus.FlowStatus[front].unixTime;
		
		MessageState = true;
	}
	
	return MessageState;
}

/**********************************************************************************************************
 @Function			void Inspect_Message_FlowStatusDequeueEx(FlowStatusTypeDef* dataBuf)
 @Description			Inspect_Message_FlowStatusDequeueEx
 @Input				dataBuf	 		 				: 需读出数据地址
 @Return				void
**********************************************************************************************************/
void Inspect_Message_FlowStatusDequeueEx(FlowStatusTypeDef* dataBuf)
{
	dataBuf->FlowState					= InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].FlowState;
	dataBuf->FlowCount					= InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].FlowCount;
	
	dataBuf->magnetismX					= InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].magnetismX;
	dataBuf->magnetismY					= InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].magnetismY;
	dataBuf->magnetismZ					= InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].magnetismZ;
	dataBuf->magnetismBackX				= InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].magnetismBackX;
	dataBuf->magnetismBackY				= InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].magnetismBackY;
	dataBuf->magnetismBackZ				= InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].magnetismBackZ;
	dataBuf->magnetismDiff				= InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].magnetismDiff;
	
	dataBuf->detectMode					= InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].detectMode;
	dataBuf->carinThreshhold				= InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].carinThreshhold;
	dataBuf->caroutThreshhold			= InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].caroutThreshhold;
	dataBuf->recalibrationOvertime		= InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].recalibrationOvertime;
	dataBuf->waitSendHeartbeatMin			= InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].waitSendHeartbeatMin;
	
	dataBuf->timeCounter				= InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].timeCounter;
	dataBuf->unixTime					= InspectFlowStatus.FlowStatus[InspectFlowStatus.Rear].unixTime;
}

/**********************************************************************************************************
 @Function			bool Inspect_Message_FlowStatusOffSet(void)
 @Description			Inspect_Message_FlowStatusOffSet
 @Input				void
 @Return				true							: 未空
					false						: 已空
**********************************************************************************************************/
bool Inspect_Message_FlowStatusOffSet(void)
{
	bool MessageState;
	
	if (Inspect_Message_FlowStatusisEmpty() == true) {															//队列已空
		MessageState = false;
	}
	else {																								//队列未空
		InspectFlowStatus.Front = (InspectFlowStatus.Front + 1) % INSPECT_FLOW_STATUS_PACK_NUM;
		MessageState = true;
	}
	
	return MessageState;
}

/**********************************************************************************************************
 @Function			unsigned char Inspect_Message_FlowStatusRear(void)
 @Description			Inspect_Message_FlowStatusRear
 @Input				void
 @Return				队尾值
**********************************************************************************************************/
unsigned char Inspect_Message_FlowStatusRear(void)
{
	return InspectFlowStatus.Rear;
}

/********************************************** END OF FLEE **********************************************/
