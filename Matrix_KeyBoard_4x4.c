// � ���, �, ����� ��������, ������� ����� ���

//******************************************************************************
/*
 * @file    Matrix_KeyBoard_4x4.c
 * @author  ������ �����
 * @version 1.0
 * @date    28.07.2017
 * @brief   ������� ��� ������ � ���������� ����������� ������� 4�4. ��������� 
 *          ������������ ������� �� 8-� ������������ ������������ ��������� ����������        
 */
//******************************************************************************

#include "Matrix_KeyBoard_4x4.h"

//******************************************************************************
// ���������� ����������
FSM_State_MKB4x4 Status_MKB4x4;

// ������ �������� �������� ������� ������������ �������
uint16_t gTMR_MKB4x4[MAX_VIRT_TMR_MKB4x4];

// ������ �������� ��������� ������� ������������ �������
vTMRState_MKB4x4 gTMRState_MKB4x4[MAX_VIRT_TMR_MKB4x4];
//******************************************************************************


//******************************************************************************
// ��������� ��������� �������
void Start_vTMR_MKB4x4(uint16_t timerID);
void Stop_vTMR_MKB4x4(uint16_t timerID);
//void Reset_vTMR_MKB4x4(uint16_t timerID);
//void Pause_vTMR_MKB4x4(uint16_t timerID);
//void Release_vTMR_MKB4x4(uint16_t timerID);
uint16_t Get_vTMR_MKB4x4(uint16_t timerID);
unsigned char KeyPressDetect_MKB4x4(MKB4x4_Typedef *MKB);
//******************************************************************************


//******************************************************************************
//==============================================================================
// ������� ��� ������ � ������������ ���������

/*
 * @brief   ������� ����������� ������ "RUNNING" ������������ �������
 * @param   timerID: ����� �������, ������ �������� ���������� ��������
 * @retval  None
 */
void Start_vTMR_MKB4x4(uint16_t timerID)
{
    gTMR_MKB4x4[timerID] = 0; //                        �������� �������� �������
    gTMRState_MKB4x4[timerID] = RUNNING; //             ���������� ������ ������� "�������"
} // void START_VirtTimer__MKB_4x4 (uint16_t timerID)

/*
 * @biref   ������� ����������� ������ "STOP" ������������ ������� � ���������� 
 *          �������� �������� � ����
 * @param   timerID: ����� �������, ������ �������� ���������� ��������
 * @retval  None
 */
void Stop_vTMR_MKB4x4(uint16_t timerID)
{
    gTMRState_MKB4x4[timerID] = STOP;
    gTMR_MKB4x4[timerID] = 0; //                        �������� �������� �������
} // void STOP_VirtTimer__MKB_4x4 (uint16_t timerID)

/*
 * @biref   ������� �������� ������� ������������ ������� � ����������� 
 *          �������� "RUNNING"
 * @param   timerID: ����� �������, ������ �������� ���������� ��������
 * @retval  None
 */
//void Reset_vTMR_MKB4x4(uint16_t timerID)
//{
//    gTMR_MKB4x4[timerID] = 0; //                      �������� �������� �������
//    gTMRState_MKB4x4[timerID] = RUNNING_vTMR; //      ���������� ������ ������� "�������"
//}

/*
 * @biref   ������� ����������� ������ "PAUSE" ������������ �������
 * @param   timerID: ����� �������, ������ �������� ���������� ��������
 * @retval  None
 */
//void Pause_vTMR_MKB4x4(uint16_t timerID)
//{
//    if (gTMRState_MKB4x4[timerID] == RUNNING_vTMR)
//    {
//        gTMRState_MKB4x4[timerID] = PAUSE_vTMR;
//    }
//} // void PAUSE_VirtTimer__MKB_4x4(uint16_t timerID)

/*
 * @biref   ������� ����������� ������ "RUNNING" ������������ �������
 * @param   timerID: ����� �������, ������ �������� ���������� ��������
 * @retval  None
 */
//void Release_vTMR_MKB4x4(uint16_t timerID)
//{
//    if (gTMRState_MKB4x4[timerID] == PAUSE_vTMR)
//    {
//        gTMRState_MKB4x4[timerID] = RUNNING_vTMR;
//    }
//} // void RELEASE_VirtTimer__MKB_4x4(uint16_t timerID)

/*
 * @brief   ������� ���������� �������� �������� 
 * @param   timerID: ����� �������, �������� �������� ���������� ���������
 * @retval  �������� �������� ������������ �������
 */
uint16_t Get_vTMR_MKB4x4(uint16_t timerID)
{
    return gTMR_MKB4x4[timerID];
} // uint16_t Get_vTMR_MKB4x4(uint16_t timerID)

/*
 * @brief   ������ ������� ��������� ��������� � ���������� ����������, ����������� �� 
 *          ������������ �������� �������. ������� ��������� ��������� ������������ ������� ���� 
 *          ��� ��������� "RUNNING"
 * @param   None
 * @retval  None
 */
void IntProcess_vTMR_MKB4x4(void)
{
    uint8_t i = 0;
    
    for (i = 0; i < MAX_VIRT_TMR_MKB4x4; i++)
    {
        if (gTMRState_MKB4x4[i] == RUNNING)
        {
            gTMR_MKB4x4[i]++;
        }
    }
} // void PROCESS_VirtTimer__MKB_4x4(void)
//==============================================================================


//==============================================================================

/*
 * @brief   ������� ���������� ����� ������ ��������� ���������� ������ � ����������    
 *          � ��������
 * @param   MKB: ��������� �� ��������� (��. header ����)
 * @retval  ��� ������� ������                 
 */
unsigned char KeyPressDetect_MKB4x4(MKB4x4_Typedef *MKB)
{
    for (MKB->rows = 0; MKB->rows < 4; MKB->rows++)
    {
        MKB->pOutReSet[MKB->rows](); //           
        for (MKB->cols = 0; MKB->cols < 4; MKB->cols++)
        {
            if (MKB->pIn[MKB->cols]() == 0)
            {
                MKB->pOutSet[MKB->rows](); //      
                return MKB->keyCodeArr[MKB->rows][MKB->cols];
            }
        }
        MKB->pOutSet[MKB->rows](); //             
    }
    return 0;
} // unsigned char KeyPressDetect_MKB4x4(InOut_MKB4x4_Typedef *PORT)

/*
 * @brief   ������� ���������� ����� ������ ���������� ������. ������������ ������
 *          �� ��������, �������� ����� ��������� ������ ������� � ���������� ����� �������
 * @param   MKB: ��������� �� ��������� (��. header ����)
 * @retval  ��� ������� ������   
 */
unsigned char ProcessKeyFSM_MKB4x4(MKB4x4_Typedef *MKB)
{
    // ����� ������� ��� ������ ��������� ����������
    MKB->keyCode = KeyPressDetect_MKB4x4(MKB);

    switch (MKB->status)
    {
    case NOT_PRESS:
        if (MKB->keyCode != 0)
        {
            MKB->_keyCode = MKB->keyCode;
            Start_vTMR_MKB4x4(MKB->id_TMR);
            Status_MKB4x4 = DEBONCE;
        }
        break;

    case DEBONCE:
        if (Get_vTMR_MKB4x4(MKB->id_TMR) >= DEBOUNCE_MKB4x4)
        {
            MKB->status = PRESS;
        }
        break;

    case PRESS:
        if (MKB->keyCode == MKB->_keyCode)
        {
            Start_vTMR_MKB4x4(MKB->id_TMR);
            MKB->status = FIRST_DELAY;
            return MKB->keyCode;
        }
        else
        {
            MKB->status = NOT_PRESS;
            MKB->_keyCode = 0;
            Stop_vTMR_MKB4x4(MKB->id_TMR);
        }
        break;

    case FIRST_DELAY:
        if (MKB->keyCode == MKB->_keyCode)
        {
            if (Get_vTMR_MKB4x4(MKB->id_TMR) >= FIRST_DELAY_MKB4x4)
            {
                Start_vTMR_MKB4x4(MKB->id_TMR);
                MKB->status = AUTO_REPEAT;
                return MKB->keyCode;
            }
        }
        else
        {
            MKB->status = NOT_PRESS;
            Stop_vTMR_MKB4x4(MKB->id_TMR);
            MKB->_keyCode = 0;
        }
        break;

    case AUTO_REPEAT:
        if (MKB->keyCode == MKB->_keyCode)
        {
            if (Get_vTMR_MKB4x4(MKB->id_TMR) >= AUTO_REPEAT_MKB4x4)
            {
                Start_vTMR_MKB4x4(MKB->id_TMR);
                return MKB->keyCode;
            }
        }
        else
        {
            MKB->status = NOT_PRESS;
            MKB->_keyCode = 0;
            Stop_vTMR_MKB4x4(MKB->id_TMR);
        }
        break;
    }
    return 0;
} // unsigned char ProcessKeyFSM_MKB4x4(InOut_MKB4x4_Typedef *MKB4x4)
//==============================================================================
//******************************************************************************
