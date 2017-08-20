// И тут, я, такой коварный, написан новый код

//******************************************************************************
/*
 * @file    Matrix_KeyBoard_4x4.c
 * @author  Михаил Исаев
 * @version 1.0
 * @date    28.07.2017
 * @brief   Драйвер для работы с матричноей клавиатурой размера 4х4. Позволяет 
 *          обрабатывать нажатия на 8-х одновременно подключенных матричных клавиатуры        
 */
//******************************************************************************

#include "Matrix_KeyBoard_4x4.h"

//******************************************************************************
// Глобальные переменные
FSM_State_MKB4x4 Status_MKB4x4;

// Массив содержит значение каждого виртуального таймера
uint16_t gTMR_MKB4x4[MAX_VIRT_TMR_MKB4x4];

// Массив содержит состояния каждого виртуального таймера
vTMRState_MKB4x4 gTMRState_MKB4x4[MAX_VIRT_TMR_MKB4x4];
//******************************************************************************


//******************************************************************************
// Прототипы локальных функций
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
// Функции для работы с виртуальными таймерами

/*
 * @brief   Функция присваивает статус "RUNNING" виртуальному таймеру
 * @param   timerID: Номер таймера, статус которого необходимо изменить
 * @retval  None
 */
void Start_vTMR_MKB4x4(uint16_t timerID)
{
    gTMR_MKB4x4[timerID] = 0; //                        Обнуляем значение таймера
    gTMRState_MKB4x4[timerID] = RUNNING; //             Выставляем статус таймера "запущен"
} // void START_VirtTimer__MKB_4x4 (uint16_t timerID)

/*
 * @biref   Функция присваивает статус "STOP" виртуальному таймеру и сбрасывает 
 *          значение счетчика в ноль
 * @param   timerID: Номер таймера, статус которого необходимо изменить
 * @retval  None
 */
void Stop_vTMR_MKB4x4(uint16_t timerID)
{
    gTMRState_MKB4x4[timerID] = STOP;
    gTMR_MKB4x4[timerID] = 0; //                        Обнуляем значение таймера
} // void STOP_VirtTimer__MKB_4x4 (uint16_t timerID)

/*
 * @biref   Функция обнуляет счетчик виртуального таймера и присваивает 
 *          значение "RUNNING"
 * @param   timerID: Номер таймера, статус которого необходимо изменить
 * @retval  None
 */
//void Reset_vTMR_MKB4x4(uint16_t timerID)
//{
//    gTMR_MKB4x4[timerID] = 0; //                      Обнуляем значение таймера
//    gTMRState_MKB4x4[timerID] = RUNNING_vTMR; //      Выставляем статус таймера "запущен"
//}

/*
 * @biref   Функция присваивает статус "PAUSE" виртуальному таймеру
 * @param   timerID: Номер таймера, статус которого необходимо изменить
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
 * @biref   Функция присваивает статус "RUNNING" виртуальному таймеру
 * @param   timerID: Номер таймера, статус которого необходимо изменить
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
 * @brief   Функция возвращает значение счетчика 
 * @param   timerID: Номер таймера, значение которого необходимо прочитать
 * @retval  Значение счетчика виртуального таймера
 */
uint16_t Get_vTMR_MKB4x4(uint16_t timerID)
{
    return gTMR_MKB4x4[timerID];
} // uint16_t Get_vTMR_MKB4x4(uint16_t timerID)

/*
 * @brief   Данную функцию необходим поместить в обработчик прерывания, вызываемого по 
 *          переполнению счетчика таймера. Функция выполняет инкремент виртуального таймера если 
 *          его состояние "RUNNING"
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
 * @brief   Функция определяет какая кнопка матричной клавиатура нажата и возвращает    
 *          её значение
 * @param   MKB: указатель на структуру (см. header файл)
 * @retval  Код нажатой кнопки                 
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
 * @brief   Функция определяет какая кнопка клавиатуры нажата. Присутствует защита
 *          от дребезга, задержка перед повторным вводом символа и автоповтор ввода символа
 * @param   MKB: указатель на структуру (см. header файл)
 * @retval  Код нажатой кнопки   
 */
unsigned char ProcessKeyFSM_MKB4x4(MKB4x4_Typedef *MKB)
{
    // Вывоз функции для опроса матричной клавиатуры
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
