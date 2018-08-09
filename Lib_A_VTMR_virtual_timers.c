/**
 * @file    "Lib_A_VTMR_virtual_timers.c"
 * @author  Isaev Mickle
 * @version 1.2
 * @date    09.08.2018
 *
 * @brief   Библиотека содержит функции для работы с виртуальными таймерами.
 *          --------------------------------------------------------------------
 *          - функция, разрешающая отсчет времени;
 *          - функция, останавливающая отсчет времени;
 *          - функция, сбрасывающая значение счетчика и разрешающая отсчет времени;
 *          - функция, инкрементирующая виртуальный таймер;
 *
 *      @note   При таком способе отсчета времени инкремент виртуального таймера
 *              выполняется при вызове функции VTMR_IntProcess();
 *      @code
 *          // Объявление глобальных переменных
 *          VTMR_tmr_s myVirtTimer1CntStruct,
 *                     myVirtTimer2CntStruct;
 *          uint32_t myVirtTimer1Value,
 *                   myVirtTimer2Value;
 *
 *          int main(void)
 *          {
 *              ...
 *              // Разрешает инкремент виртуального таймера при вызове
 *              // функции VTMR_IntProcess();
 *              VTMR_StartVirtTimer(&myVirtTimer1CntStruct);
 *              VTMR_StartVirtTimer(&myVirtTimer2CntStruct);
 *              ...
 *              while(1)
 *              {
 *                  // Разрешает инкремент виртуального таймера при вызове
 *                  // функции VTMR_IntProcess() и сбрасывает значение
 *                  // счетчика в нуль - перезапуск виртуального таймера;
 *                  VTMR_RestartVirtTimer(&myVirtTimer1CntStruct);
 *                  VTMR_RestartVirtTimer(&myVirtTimer2CntStruct);
 *                  ...
 *                  // Получение количества вызова функции VTMR_IntProcess();
 *                  // (получение количества прерываний  "void TIMER_1_INTERRUPT(void)")
 *                  myVirtTimer1Value = VTMR_GetValueVirtTimer(&myVirtTimer1CntStruct);
 *                  ...
 *                  myVirtTimer2Value = VTMR_GetValueVirtTimer(&myVirtTimer2CntStruct);
 *
 *                  // Причем
 *                  myVirtTimer1Value == myVirtTimer1CntStruct.timeInterval;
 *                  myVirtTimer2Value == myVirtTimer2CntStruct.timeInterval;
 *
 *                  // Запрещает инкремент виртуального таймера при вызове
 *                  // функции VTMR_IntProcess() - остановка виртуального таймера;
 *                  VTMR_StopVirtTimer(&myVirtTimer1CntStruct);
 *                  VTMR_StopVirtTimer(&myVirtTimer2CntStruct);
 *              }
 *          }
 *
 *          void TIMER_1_INTERRUPT(void)
 *          {
 *              ...
 *              VTMR_IntProcess(&myVirtTimer1CntStruct);
 *              VTMR_IntProcess(&myVirtTimer2CntStruct);
 *          }
 *      @endcode
 *          --------------------------------------------------------------------
 *
 *
 *
 *
 *          --------------------------------------------------------------------
 *          - функция, записывающая текущее значение аппаратного счетчика в переменную
 *          - функция, выполняющая вычитание из текущего значения аппаратного счетчика
 *            значения переменной;
 *      @note   При таком способе отсчета времени библиотека не использует прерывания.
 *
 *      @code
 *          // Объявление глобальных переменных
 *          VTMR_tmr_s myVirtTimer1CntStruct,
 *                     myVirtTimer2CntStruct;
 *          uint32_t myVirtTimer1Value,
 *                   myVirtTimer2Value;
 *
 *          int main(void)
 *          {
 *              ...
 *              // Пример инициализации для микроконтроллеров PIC:
 *              // где TMR9 - указатель на старшие 16 бит аппаратного счетчика;
 *                     TMR8 - указатель на младшие 16 бит аппаратного счетчика;
 *              VTMR_InitTimerStruct(&myVirtTimer1CntStruct,
 *                                   (uint16_t*) &TMR9,
 *                                   (uint16_t*) &TMR8);
 *              VTMR_InitTimerStruct(&myVirtTimer2CntStruct,
 *                                   (uint16_t*) &TMR9,
 *                                   (uint16_t*) &TMR8);
 *
 *              // Пример инициализации для микроконтроллеров STM32;
 *              // где TIM3->CNT - указатель на старшие 16 бит аппаратного счетчика;
 *                     TIM4->CNT - указатель на младшие 16 бит аппаратного счетчика;
 *              VTMR_InitTimerStruct(&myVirtTimer1CntStruct,
 *                                   (uint16_t*) &TIM3->CNT,
 *                                   (uint16_t*) &TIM4->CNT);
 *              VTMR_InitTimerStruct(&myVirtTimer2CntStruct,
 *                                   (uint16_t*) &TIM3->CNT,
 *                                   (uint16_t*) &TIM4->CNT);
 *
 *              // Если используется только 16 битный таймер вместо 32 битного, то
 *              // в качестве указателя на старшие 16 бит аппаратного счетчика
 *              // следует передать NULL
 *              VTMR_InitTimerStruct(&myVirtTimer1CntStruct,
 *                                   (uint16_t*) NULL,
 *                                   (uint16_t*) &TIM4->CNT);
 *              VTMR_InitTimerStruct(&myVirtTimer2CntStruct,
 *                                   (uint16_t*) NULL,
 *                                   (uint16_t*) &TIM4->CNT);
 *              ...
 *              while(1)
 *              {
 *                  // Запись в переменную счетчика текущего значения
 *                  // аппаратного счетчика;
 *                  // @see VTMR_tmr_s;
 *                  VTMR_StartTimer(&myVirtTimer1CntStruct);
 *                  VTMR_StartTimer(&myVirtTimer2CntStruct);
 *                  ...
 *
 *                  // Определение разницы между текущим значением аппаратного
 *                  // счетчика и значением переменной счетчика в
 *                  // структуре myVirtTimer1CntStruct.
 *                  // В результате имеем количество тиков аппаратного счетчика
 *                  // между вызовами функций VTMR_StartTimer() и VTMR_GetTimerValue();
 *                  // @see VTMR_tmr_s;
 *                  myVirtTimer1Value = VTMR_GetTimerValue(&myVirtTimer1CntStruct);
 *                  ....
 *                  myVirtTimer2Value = VTMR_GetTimerValue(&myVirtTimer2CntStruct);
 *
 *                  // Причем
 *                  myVirtTimer1Value == myVirtTimer1CntStruct.timeInterval;
 *                  myVirtTimer2Value == myVirtTimer2CntStruct.timeInterval;
 *                  ...
 *
 *              }
 *          }
 *      @endcode
 *      ------------------------------------------------------------------------
 */

//******************************************************************************
// Секция include: здесь подключается заголовочный файл к модулю
#include "Lib_A_VTMR_virtual_timers.h"
//******************************************************************************


//******************************************************************************
//==============================================================================
// Глобальные переменные
//==============================================================================


//==============================================================================
// Локальные переменные
//==============================================================================
//******************************************************************************


//******************************************************************************
// Секция прототипов локальных функций
//******************************************************************************


//******************************************************************************
// Секция описания функций (сначала глобальных, потом локальных)

void
VTMR_RestartVirtTimer (
	VTMR_tmr_s *vTMR)
{
	vTMR->state = VTMR_RUNNING;
	vTMR->timeInterval = 0;
}

void
VTMR_StopVirtTimer (
	VTMR_tmr_s *vTMR)
{
	vTMR->state = VTMR_STOP;
}

void
VTMR_StartVirtTimer (
	VTMR_tmr_s *vTMR)
{
	vTMR->state = VTMR_RUNNING;
}

uint32_t
VTMR_GetValueVirtTimer (
	VTMR_tmr_s *vTMR)
{
	return vTMR->timeInterval;
}

void
VTMR_IntProcess (
	VTMR_tmr_s *vTMR)
{
	if (vTMR->state == VTMR_RUNNING)
	{
		vTMR->timeInterval++;
	}
}

/* ################################################################## */
/* <Функции виртуальных таймеров, привязанных к аппаратному счетчику> */
/* ################################################################## */

/**
 * @brief   Функция сбрасывает в нуль виртуальный таймер
 * @param[in]   *vTMR:  Указатель на структуру виртуального таймера
 * @return None
 */
void
VTMR_StartTimer(
	VTMR_tmr_s *pVTMR)
{
	/* Если режим работы таймера 32-х битный */
	if (pVTMR->pHighCntReg != NULL)
	{
		uint32_t highCnt = (uint32_t) * pVTMR->pHighCntReg,
				 lowCnt = (uint32_t) * pVTMR->pLowCntReg;

		pVTMR->cnt =
			(((highCnt << 16) & 0xFFFF0000)
			 | (lowCnt & 0x0000FFFF));
	}
	/* Иначе, если режим работы таймера 16-ти битный */
	else
	{
		pVTMR->cnt = (uint32_t) * pVTMR->pLowCntReg;
	}
}

/**
 * @brief   Функция вычисляет временной интервал между вызовами функции
 *          "VTMR_StartTimer()" и "VTMR_GetTimerValue()"
 * @param[in,out]   *pVTMR: Указатель на структуру виртуального таймера
 * @return  Временной интервал между вызовами функций "VTMR_StartTimer" и
 *          "VTMR_GetTimerValue" в тиках аппаратного счетчика
 */
uint32_t
VTMR_GetTimerValue(
	VTMR_tmr_s *pVTMR)
{
	/* Если режим работы таймера 32-х битный */
	if (pVTMR->pHighCntReg != NULL)
	{
		uint32_t highCnt = (uint32_t) * pVTMR->pHighCntReg,
				 lowCnt = (uint32_t) * pVTMR->pLowCntReg;

		uint32_t cnt32Bit =
			(((highCnt << 16) & 0xFFFF0000)
			 | (lowCnt & 0x0000FFFF)) - pVTMR->cnt;

		/* Если было обнуление аппаратного счетчика */
		if (pVTMR->cnt >= cnt32Bit)
		{
			pVTMR->timeInterval =
				VTMR_32BIT_CNT_MAX_VAL - pVTMR->cnt + cnt32Bit;
		}
		else
		{
			pVTMR->timeInterval =
				cnt32Bit - pVTMR->cnt;
		}
	}
	/* Иначе, если режим работы таймера 16-ти битный */
	else
	{
		/* Если было обнуление аппаратного счетчика */
		if (pVTMR->cnt >= *pVTMR->pLowCntReg)
		{
			pVTMR->timeInterval =
				(((uint32_t) ((VTMR_16BIT_CNT_MAX_VAL - (uint16_t) pVTMR->cnt) + (uint16_t) * pVTMR->pLowCntReg)) & 0x0000FFFF);
		}
		else
		{
			pVTMR->timeInterval =
				(((uint32_t) ((uint16_t) * pVTMR->pLowCntReg - (uint16_t) pVTMR->cnt)) & 0x0000FFFF);
		}
	}
	return pVTMR->timeInterval;
}

/**
 * @brief   Функция вычисляет максимальный временной интервал между вызовами функции
 *          "VTMR_StartTimer()" и "VTMR_GetTimerValue()"
 * @param[in,out]   *pVTMR: Указатель на структуру виртуального таймера
 * @return  Наибольший временной интервал между вызовами функций "VTMR_StartTimer" и
 *          "VTMR_GetTimerValue" в тиках аппаратного счетчика
 */
uint32_t
VTMR_GetMaxTimerValue(
	VTMR_tmr_s *pVTMR)
{
	VTMR_GetTimerValue(pVTMR);

	// Если новое значение временного интервала больше предыдущего:
	if (pVTMR->timeInterval > pVTMR->timeIntervalMax)
	{
		pVTMR->timeIntervalMax = pVTMR->timeInterval;
	}
	return  pVTMR->timeIntervalMax;
}

/**
 * @brief   Функция инициализирует структуру виртуального таймера
 * @param[in]   *pVTMR: Указатель на структуру виртуального таймера
 * @param[in]   *pHighCntReg:   Указатель на старшие 16 бит аппаратного счетчика
 *  @note   Если разрядность таймера 16 бит (вместо 32 бит), то вместо указателя
 *          на старшие 16 бит аппаратного счетчика необходимо передать NULL
 * @param[in]   *pLowCntReg:    Указатель на младшие 16 бит аппаратного счетчика
 * @return  None
 */
void
VTMR_InitTimerStruct(
	VTMR_tmr_s *pVTMR,
	const uint16_t * const pHighCntReg,
	const uint16_t * const pLowCntReg)
{
	pVTMR->pHighCntReg = pHighCntReg;
	pVTMR->pLowCntReg = pLowCntReg;
	pVTMR->cnt = 0;
	pVTMR->timeInterval = 0;
	pVTMR->timeIntervalMax = 0;
}
//******************************************************************************


////////////////////////////////////////////////////////////////////////////////
// END OF FILE
////////////////////////////////////////////////////////////////////////////////
