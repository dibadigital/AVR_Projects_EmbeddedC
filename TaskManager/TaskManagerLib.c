
#include "TaskManagerLib.h"

#include <stdio.h>

static Task_t systemTask[TASK_MAX];

void Task_Add (uint8_t bankNumber, uint16_t mainTime, TaskFunc funcTask)
{
    systemTask[bankNumber].counterTim = 0;
    systemTask[bankNumber].MainTime = mainTime;
    systemTask[bankNumber].Job = funcTask;
    systemTask[bankNumber].Step = 0;
    systemTask[bankNumber].Active = 1;
}

void Task_ChangeStep (uint8_t bankNumber, uint8_t step)
{
    systemTask[bankNumber].Step = step; 
}

void Task_ChangeTime (uint8_t bankNumber, uint16_t newTime)
{
    systemTask[bankNumber].MainTime = newTime;
}

void Task_TimingCallback (void)
{
    uint8_t count;
    
    for (count = 0; count < TASK_MAX; count++)
    {       
        if (systemTask[count].Active && (systemTask[count].counterTim < systemTask[count].MainTime))
        {
            systemTask[count].counterTim++;
        }
    }
}

void TaskRun (void)
{
    uint8_t count;
    
    for (count = 0; count < TASK_MAX; count++)
    {       
        if (systemTask[count].Active && (systemTask[count].counterTim == systemTask[count].MainTime))
        {                  
            /* log */ 
            printf ("Task %i run.\r", count); /* Connect to the serial port because we have the putchar function in the InitHW */
       
            systemTask[count].Job (systemTask[count].Step);
            systemTask[count].counterTim = 0;
        }
    }
}