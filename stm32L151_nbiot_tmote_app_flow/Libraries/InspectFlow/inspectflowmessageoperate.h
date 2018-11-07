#ifndef __INSPECT_FLOW_MESSAGE_OPERATE_H
#define   __INSPECT_FLOW_MESSAGE_OPERATE_H

#include "sys.h"
#include "tmesh_algorithm.h"

#define INSPECT_FLOW_STATUS_PACK_NUM		10

typedef __packed struct
{
	SPOTCarType						FlowState;
	unsigned short						FlowCount;
	
	signed short int					magnetismX;
	signed short int					magnetismY;
	signed short int					magnetismZ;
	
	signed short int					magnetismBackX;
	signed short int					magnetismBackY;
	signed short int					magnetismBackZ;
	
	unsigned short int					magnetismDiff;
	
	unsigned int						timeCounter;
	unsigned int						unixTime;
}FlowStatusTypeDef;

/* Inspect Spot Flow Status */
typedef struct
{
	unsigned char						Front;
	unsigned char						Rear;
	FlowStatusTypeDef					FlowStatus[INSPECT_FLOW_STATUS_PACK_NUM];
}Inspect_SwapSpotFlowStatusTypeDef;

extern Inspect_SwapSpotFlowStatusTypeDef	InspectFlowStatus;

bool Inspect_Message_FlowStatusisFull(void);
bool Inspect_Message_FlowStatusisEmpty(void);

void Inspect_Message_FlowStatusEnqueue(FlowStatusTypeDef dataBuf);
bool Inspect_Message_FlowStatusDequeue(FlowStatusTypeDef* dataBuf);
void Inspect_Message_FlowStatusDequeueEx(FlowStatusTypeDef* dataBuf);
bool Inspect_Message_FlowStatusOffSet(void);
unsigned char Inspect_Message_FlowStatusRear(void);

#endif /* __INSPECT_FLOW_MESSAGE_OPERATE_H */
