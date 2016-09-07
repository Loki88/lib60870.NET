/*
 *  Copyright 2016 MZ Automation GmbH
 *
 *  This file is part of lib60870-C
 *
 *  lib60870-C is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  lib60870-C is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with lib60870-C.  If not, see <http://www.gnu.org/licenses/>.
 *
 *  See COPYING file for the complete license text.
 */

#ifndef SRC_INC_INFORMATION_OBJECTS_H_
#define SRC_INC_INFORMATION_OBJECTS_H_

#ifdef __cplusplus
extern "C" {
#endif


typedef uint8_t QualityDescriptor;

#define IEC60870_QUALITY_GOOD        0
#define IEC60870_QUALITY_OVERFLOW    0x01
#define IEC60870_QUALITY_BLOCKED     0x10
#define IEC60870_QUALITY_SUBSTITUTED 0x20
#define IEC60870_QUALITY_NON_TOPICAL 0x40
#define IEC60870_QUALITY_INVALID     0x80

typedef uint8_t SetpointCommandQualifier;

typedef enum  {
    IEC60870_DOUBLE_POINT_INTERMEDIATE = 0,
    IEC60870_DOUBLE_POINT_OFF = 1,
    IEC60870_DOUBLE_POINT_ON = 2,
    IEC60870_DOUBLE_POINT_INDETERMINATE = 3
} DoublePointValue;

typedef enum {
    IEC60870_STEP_LOWER = 1,
    IEC60870_STEP_HIGHER = 2
} StepCommandValue;

/************************************************
 * InformationObject
 ************************************************/

typedef struct sInformationObject* InformationObject;

/**
 * \brief return the size in memory of a generic InformationObject instance
 *
 * This function can be used to determine the required memory for malloc
 */
int
InformationObject_getMaxSizeInMemory(void);

int
InformationObject_getObjectAddress(InformationObject self);

/**
 * \brief Destroy object - free all related resources
 *
 * This is a virtual function that calls the destructor from the implementation class
 *
 * \self the InformationObject instance
 */
void
InformationObject_destroy(InformationObject self);

/************************************************
 * SinglePointInformation (:InformationObject)
 ************************************************/

typedef struct sSinglePointInformation* SinglePointInformation;

SinglePointInformation
SinglePointInformation_create(SinglePointInformation self, int ioa, bool value,
        QualityDescriptor quality);

bool
SinglePointInformation_getValue(SinglePointInformation self);

QualityDescriptor
SinglePointInformation_getQuality(SinglePointInformation self);

void
SinglePointInformation_destroy(SinglePointInformation self);

/********************************************************
 *  SinglePointWithCP24Time2a (:SinglePointInformation)
 ********************************************************/

typedef struct sSinglePointWithCP24Time2a* SinglePointWithCP24Time2a;

SinglePointWithCP24Time2a
SinglePointWithCP24Time2a_create(SinglePointWithCP24Time2a self, int ioa, bool value,
        QualityDescriptor quality, CP24Time2a timestamp);

void
SinglePointWithCP24Time2a_destroy(SinglePointWithCP24Time2a self);

CP24Time2a
SinglePointWithCP24Time2a_getTimestamp(SinglePointWithCP24Time2a self);

/********************************************************
 *  SinglePointWithCP56Time2a (:SinglePointInformation)
 ********************************************************/

typedef struct sSinglePointWithCP56Time2a* SinglePointWithCP56Time2a;

SinglePointWithCP56Time2a
SinglePointWithCP56Time2a_create(SinglePointWithCP56Time2a self, int ioa, bool value,
        QualityDescriptor quality, CP56Time2a timestamp);

void
SinglePointWithCP56Time2a_destroy(SinglePointWithCP56Time2a self);

CP56Time2a
SinglePointWithCP56Time2a_getTimestamp(SinglePointWithCP56Time2a self);


/************************************************
 * DoublePointInformation (:InformationObject)
 ************************************************/

typedef struct sDoublePointInformation* DoublePointInformation;

void
DoublePointInformation_destroy(DoublePointInformation self);

DoublePointInformation
DoublePointInformation_create(DoublePointInformation self, int ioa, DoublePointValue value,
        QualityDescriptor quality);

DoublePointValue
DoublePointInformation_getValue(DoublePointInformation self);

QualityDescriptor
DoublePointInformation_getQuality(DoublePointInformation self);

/********************************************************
 *  DoublePointWithCP24Time2a (:DoublePointInformation)
 ********************************************************/

typedef struct sDoublePointWithCP24Time2a* DoublePointWithCP24Time2a;

void
DoublePointWithCP24Time2a_destroy(DoublePointWithCP24Time2a self);

DoublePointWithCP24Time2a
DoublePointWithCP24Time2a_create(DoublePointWithCP24Time2a self, int ioa, DoublePointValue value,
        QualityDescriptor quality, CP24Time2a timestamp);

CP24Time2a
DoublePointWithCP24Time2a_getTimestamp(DoublePointWithCP24Time2a self);

/********************************************************
 *  DoublePointWithCP56Time2a (:DoublePointInformation)
 ********************************************************/

typedef struct sDoublePointWithCP56Time2a* DoublePointWithCP56Time2a;

DoublePointWithCP56Time2a
DoublePointWithCP56Time2a_create(DoublePointWithCP56Time2a self, int ioa, DoublePointValue value,
        QualityDescriptor quality, CP56Time2a timestamp);

void
DoublePointWithCP56Time2a_destroy(DoublePointWithCP56Time2a self);

CP56Time2a
DoublePointWithCP56Time2a_getTimestamp(DoublePointWithCP56Time2a self);

/************************************************
 * StepPositionInformation (:InformationObject)
 ************************************************/

typedef struct sStepPositionInformation* StepPositionInformation;

/**
* \brief Create a new instance of StepPositionInformation information object
*
* \param self Reference to an existing instance to reuse, if NULL a new instance will we dynamically allocated
* \param ioa Information object address
* \param value Step position (range -64 ... +63)
* \param isTransient true if position is transient, false otherwise
* \param quality quality descriptor (according to IEC 60870-5-101:2003 7.2.6.3)
*
* \return Reference to the new instance
*/
StepPositionInformation
StepPositionInformation_create(StepPositionInformation self, int ioa, int value, bool isTransient,
        QualityDescriptor quality);

void
StepPositionInformation_destroy(StepPositionInformation self);

int
StepPositionInformation_getObjectAddress(StepPositionInformation self);

/**
 * \brief Step position (range -64 ... +63)
 */
int
StepPositionInformation_getValue(StepPositionInformation self);

bool
StepPositionInformation_isTransient(StepPositionInformation self);

QualityDescriptor
StepPositionInformation_getQuality(StepPositionInformation self);

/*********************************************************
 * StepPositionWithCP24Time2a (:StepPositionInformation)
 *********************************************************/

typedef struct sStepPositionWithCP24Time2a* StepPositionWithCP24Time2a;

void
StepPositionWithCP24Time2a_destroy(StepPositionWithCP24Time2a self);

StepPositionWithCP24Time2a
StepPositionWithCP24Time2a_create(StepPositionWithCP24Time2a self, int ioa, int value, bool isTransient,
        QualityDescriptor quality, CP24Time2a timestamp);

CP24Time2a
StepPositionWithCP24Time2a_getTimestamp(StepPositionWithCP24Time2a self);


/*********************************************************
 * StepPositionWithCP56Time2a (:StepPositionInformation)
 *********************************************************/

typedef struct sStepPositionWithCP56Time2a* StepPositionWithCP56Time2a;

void
StepPositionWithCP56Time2a_destroy(StepPositionWithCP56Time2a self);

StepPositionWithCP56Time2a
StepPositionWithCP56Time2a_create(StepPositionWithCP56Time2a self, int ioa, int value, bool isTransient,
        QualityDescriptor quality, CP56Time2a timestamp);

CP56Time2a
StepPositionWithCP56Time2a_getTimestamp(StepPositionWithCP56Time2a self);

/**********************************************
 * BitString32 (:InformationObject)
 **********************************************/

typedef struct sBitString32* BitString32;

void
BitString32_destroy(BitString32 self);

BitString32
BitString32_create(BitString32 self, int ioa, uint32_t value);

uint32_t
BitString32_getValue(BitString32 self);

QualityDescriptor
BitString32_getQuality(BitString32 self);

/**********************************************
 * Bitstring32WithCP24Time2a (:BitString32)
 **********************************************/

typedef struct sBitstring32WithCP24Time2a* Bitstring32WithCP24Time2a;

void
Bitstring32WithCP24Time2a_destroy(Bitstring32WithCP24Time2a self);

Bitstring32WithCP24Time2a
Bitstring32WithCP24Time2a_create(Bitstring32WithCP24Time2a self, int ioa, uint32_t value, CP24Time2a timestamp);

CP24Time2a
Bitstring32WithCP24Time2a_getTimestamp(Bitstring32WithCP24Time2a self);

/**********************************************
 * Bitstring32WithCP56Time2a (:BitString32)
 **********************************************/

typedef struct sBitstring32WithCP56Time2a* Bitstring32WithCP56Time2a;

void
Bitstring32WithCP56Time2a_destroy(Bitstring32WithCP56Time2a self);

Bitstring32WithCP56Time2a
Bitstring32WithCP56Time2a_create(Bitstring32WithCP56Time2a self, int ioa, uint32_t value, CP56Time2a timestamp);

CP56Time2a
Bitstring32WithCP56Time2a_getTimestamp(Bitstring32WithCP56Time2a self);

/**********************************************
 * MeasuredValueNormalized
 **********************************************/

typedef struct sMeasuredValueNormalized* MeasuredValueNormalized;

void
MeasuredValueNormalized_destroy(MeasuredValueNormalized self);

MeasuredValueNormalized
MeasuredValueNormalized_create(MeasuredValueNormalized self, int ioa, float value, QualityDescriptor quality);

float
MeasuredValueNormalized_getValue(MeasuredValueNormalized self);

void
MeasuredValueNormalized_setValue(MeasuredValueNormalized self, float value);

QualityDescriptor
MeasuredValueNormalized_getQuality(MeasuredValueNormalized self);

/***********************************************************************
 * MeasuredValueNormalizedWithCP24Time2a : MeasuredValueNormalized
 ***********************************************************************/

typedef struct sMeasuredValueNormalizedWithCP24Time2a* MeasuredValueNormalizedWithCP24Time2a;

void
MeasuredValueNormalizedWithCP24Time2a_destroy(MeasuredValueNormalizedWithCP24Time2a self);

MeasuredValueNormalizedWithCP24Time2a
MeasuredValueNormalizedWithCP24Time2a_create(MeasuredValueNormalizedWithCP24Time2a self, int ioa,
            float value, QualityDescriptor quality, CP24Time2a timestamp);

CP24Time2a
MeasuredValueNormalizedWithCP24Time2a_getTimestamp(MeasuredValueNormalizedWithCP24Time2a self);

void
MeasuredValueNormalizedWithCP24Time2a_setTimestamp(MeasuredValueNormalizedWithCP24Time2a self, CP24Time2a value);

/***********************************************************************
 * MeasuredValueNormalizedWithCP56Time2a : MeasuredValueNormalized
 ***********************************************************************/

typedef struct sMeasuredValueNormalizedWithCP56Time2a* MeasuredValueNormalizedWithCP56Time2a;

void
MeasuredValueNormalizedWithCP56Time2a_destroy(MeasuredValueNormalizedWithCP56Time2a self);

MeasuredValueNormalizedWithCP56Time2a
MeasuredValueNormalizedWithCP56Time2a_create(MeasuredValueNormalizedWithCP56Time2a self, int ioa,
            float value, QualityDescriptor quality, CP56Time2a timestamp);

CP56Time2a
MeasuredValueNormalizedWithCP56Time2a_getTimestamp(MeasuredValueNormalizedWithCP56Time2a self);

void
MeasuredValueNormalizedWithCP56Time2a_setTimestamp(MeasuredValueNormalizedWithCP56Time2a self, CP56Time2a value);


/*******************************************
 * MeasuredValueScaled : InformationObject
 *******************************************/

typedef struct sMeasuredValueScaled* MeasuredValueScaled;

/**
 * \brief Create a new instance of MeasuredValueScaled information object
 *
 * \param self Reference to an existing instance to reuse, if NULL a new instance will we dynamically allocated
 * \param ioa Information object address
 * \param value scaled value (range -32768 - 32767)
 * \param quality quality descriptor (according to IEC 60870-5-101:2003 7.2.6.3)
 *
 * \return Reference to the new instance
 */
MeasuredValueScaled
MeasuredValueScaled_create(MeasuredValueScaled self, int ioa, int value, QualityDescriptor quality);

void
MeasuredValueScaled_destroy(MeasuredValueScaled self);

int
MeasuredValueScaled_getValue(MeasuredValueScaled self);

void
MeasuredValueScaled_setValue(MeasuredValueScaled self, int value);

QualityDescriptor
MeasuredValueScaled_getQuality(MeasuredValueScaled self);

void
MeasuredValueScaled_setQuality(MeasuredValueScaled self, QualityDescriptor quality);

/***********************************************************************
 * MeasuredValueScaledWithCP24Time2a : MeasuredValueScaled
 ***********************************************************************/

typedef struct sMeasuredValueScaledWithCP24Time2a* MeasuredValueScaledWithCP24Time2a;

void
MeasuredValueScaledWithCP24Time2a_destroy(MeasuredValueScaledWithCP24Time2a self);

MeasuredValueScaledWithCP24Time2a
MeasuredValueScaledWithCP24Time2a_create(MeasuredValueScaledWithCP24Time2a self, int ioa,
        int value, QualityDescriptor quality, CP24Time2a timestamp);

CP24Time2a
MeasuredValueScaledWithCP24Time2a_getTimestamp(MeasuredValueScaledWithCP24Time2a self);

void
MeasuredValueScaledWithCP24Time2a_setTimestamp(MeasuredValueScaledWithCP24Time2a self, CP24Time2a value);

/***********************************************************************
 * MeasuredValueScaledWithCP56Time2a : MeasuredValueScaled
 ***********************************************************************/

typedef struct sMeasuredValueScaledWithCP56Time2a* MeasuredValueScaledWithCP56Time2a;

void
MeasuredValueScaledWithCP56Time2a_destroy(MeasuredValueScaledWithCP56Time2a self);

MeasuredValueScaledWithCP56Time2a
MeasuredValueScaledWithCP56Time2a_create(MeasuredValueScaledWithCP56Time2a self, int ioa,
        int value, QualityDescriptor quality, CP56Time2a timestamp);

CP56Time2a
MeasuredValueScaledWithCP56Time2a_getTimestamp(MeasuredValueScaledWithCP56Time2a self);

void
MeasuredValueScaledWithCP56Time2a_setTimestamp(MeasuredValueScaledWithCP56Time2a self, CP56Time2a value);

/*******************************************
 * MeasuredValueShort : InformationObject
 *******************************************/

typedef struct sMeasuredValueShort* MeasuredValueShort;

void
MeasuredValueShort_destroy(MeasuredValueShort self);

MeasuredValueShort
MeasuredValueShort_create(MeasuredValueShort self, int ioa, float value, QualityDescriptor quality);

float
MeasuredValueShort_getValue(MeasuredValueShort self);

void
MeasuredValueShort_setValue(MeasuredValueShort self, float value);

QualityDescriptor
MeasuredValueShort_getQuality(MeasuredValueShort self);

/***********************************************************************
 * MeasuredValueShortWithCP24Time2a : MeasuredValueShort
 ***********************************************************************/

typedef struct sMeasuredValueShortWithCP24Time2a* MeasuredValueShortWithCP24Time2a;

void
MeasuredValueShortWithCP24Time2a_destroy(MeasuredValueShortWithCP24Time2a self);

MeasuredValueShortWithCP24Time2a
MeasuredValueShortWithCP24Time2a_create(MeasuredValueShortWithCP24Time2a self, int ioa,
        float value, QualityDescriptor quality, CP24Time2a timestamp);

CP24Time2a
MeasuredValueShortWithCP24Time2a_getTimestamp(MeasuredValueShortWithCP24Time2a self);

void
MeasuredValueShortWithCP24Time2a_setTimestamp(MeasuredValueShortWithCP24Time2a self,
        CP24Time2a value);

/***********************************************************************
 * MeasuredValueShortWithCP56Time2a : MeasuredValueShort
 ***********************************************************************/

typedef struct sMeasuredValueShortWithCP56Time2a* MeasuredValueShortWithCP56Time2a;

void
MeasuredValueShortWithCP56Time2a_destroy(MeasuredValueShortWithCP56Time2a self);

MeasuredValueShortWithCP56Time2a
MeasuredValueShortWithCP56Time2a_create(MeasuredValueShortWithCP56Time2a self, int ioa,
        float value, QualityDescriptor quality, CP56Time2a timestamp);

CP56Time2a
MeasuredValueShortWithCP56Time2a_getTimestamp(MeasuredValueShortWithCP56Time2a self);

void
MeasuredValueShortWithCP56Time2a_setTimestamp(MeasuredValueShortWithCP56Time2a self,
        CP56Time2a value);

/*******************************************
 * IntegratedTotals : InformationObject
 *******************************************/

typedef struct sIntegratedTotals* IntegratedTotals;

void
IntegratedTotals_destroy(IntegratedTotals self);

/**
 * \brief Create a new instance of IntegratedTotals information object
 *
 * For message type: M_IT_NA_1 (15)
 *
 * \param self Reference to an existing instance to reuse, if NULL a new instance will we dynamically allocated
 * \param ioa Information object address
 * \param value binary counter reading value and state
 *
 * \return Reference to the new instance
 */
IntegratedTotals
IntegratedTotals_create(IntegratedTotals self, int ioa, BinaryCounterReading value);

BinaryCounterReading
IntegratedTotals_getBCR(IntegratedTotals self);

void
IntegratedTotals_setBCR(IntegratedTotals self, BinaryCounterReading value);

/***********************************************************************
 * IntegratedTotalsWithCP24Time2a : IntegratedTotals
 ***********************************************************************/

typedef struct sIntegratedTotalsWithCP24Time2a* IntegratedTotalsWithCP24Time2a;

/**
 * \brief Create a new instance of IntegratedTotalsWithCP24Time2a information object
 *
 * For message type: M_IT_TA_1 (16)
 *
 * \param self Reference to an existing instance to reuse, if NULL a new instance will we dynamically allocated
 * \param ioa Information object address
 * \param value binary counter reading value and state
 * \param timestamp timestamp of the reading
 *
 * \return Reference to the new instance
 */
IntegratedTotalsWithCP24Time2a
IntegratedTotalsWithCP24Time2a_create(IntegratedTotalsWithCP24Time2a self, int ioa,
        BinaryCounterReading value, CP24Time2a timestamp);

void
IntegratedTotalsWithCP24Time2a_destroy(IntegratedTotalsWithCP24Time2a self);

CP24Time2a
IntegratedTotalsWithCP24Time2a_getTimestamp(IntegratedTotalsWithCP24Time2a self);

void
IntegratedTotalsWithCP24Time2a_setTimestamp(IntegratedTotalsWithCP24Time2a self,
        CP24Time2a value);

/***********************************************************************
 * IntegratedTotalsWithCP56Time2a : IntegratedTotals
 ***********************************************************************/

typedef struct sIntegratedTotalsWithCP56Time2a* IntegratedTotalsWithCP56Time2a;

/**
 * \brief Create a new instance of IntegratedTotalsWithCP56Time2a information object
 *
 * For message type: M_IT_TB_1 (37)
 *
 * \param self Reference to an existing instance to reuse, if NULL a new instance will we dynamically allocated
 * \param ioa Information object address
 * \param value binary counter reading value and state
 * \param timestamp timestamp of the reading
 *
 * \return Reference to the new instance
 */
IntegratedTotalsWithCP56Time2a
IntegratedTotalsWithCP56Time2a_create(IntegratedTotalsWithCP56Time2a self, int ioa,
        BinaryCounterReading value, CP56Time2a timestamp);

void
IntegratedTotalsWithCP56Time2a_destroy(IntegratedTotalsWithCP56Time2a self);

CP56Time2a
IntegratedTotalsWithCP56Time2a_getTimestamp(IntegratedTotalsWithCP56Time2a self);

void
IntegratedTotalsWithCP56Time2a_setTimestamp(IntegratedTotalsWithCP56Time2a self,
        CP56Time2a value);


/*******************************************
 * SingleCommand
 *******************************************/

typedef struct sSingleCommand* SingleCommand;

SingleCommand
SingleCommand_create(SingleCommand self, int ioa, bool command, bool selectCommand, int qu);

void
SingleCommand_destroy(SingleCommand self);

int
SingleCommand_getQU(SingleCommand self);

bool
SingleCommand_getState(SingleCommand self);

bool
SingleCommand_isSelect(SingleCommand self);

/***********************************************************************
 * SingleCommandWithCP56Time2a : SingleCommand
 ***********************************************************************/

typedef struct sSingleCommandWithCP56Time2a* SingleCommandWithCP56Time2a;

void
SingleCommandWithCP56Time2a_destroy(SingleCommandWithCP56Time2a self);

SingleCommandWithCP56Time2a
SingleCommandWithCP56Time2a_create(SingleCommandWithCP56Time2a self, int ioa, bool command, bool selectCommand, int qu, CP56Time2a timestamp);

CP56Time2a
SingleCommandWithCP56Time2a_getTimestamp(SingleCommandWithCP56Time2a self);

/*******************************************
 * DoubleCommand : InformationObject
 *******************************************/

typedef struct sDoubleCommand* DoubleCommand;

void
DoubleCommand_destroy(DoubleCommand self);

DoubleCommand
DoubleCommand_create(DoubleCommand self, int ioa, int command, bool selectCommand, int qu);

int
DoubleCommand_getQU(DoubleCommand self);

int
DoubleCommand_getState(DoubleCommand self);

bool
DoubleCommand_isSelect(DoubleCommand self);

/*******************************************
 * StepCommand : InformationObject
 *******************************************/

typedef struct sStepCommand* StepCommand;

void
StepCommand_destroy(StepCommand self);

StepCommand
StepCommand_create(StepCommand self, int ioa, int command, bool selectCommand, int qu);

int
StepCommand_getQU(StepCommand self);

int
StepCommand_getState(StepCommand self);

bool
StepCommand_isSelect(StepCommand self);

/*************************************************
 * SetpointCommandNormalized : InformationObject
 ************************************************/

typedef struct sSetpointCommandNormalized* SetpointCommandNormalized;

void
SetpointCommandNormalized_destroy(SetpointCommandNormalized self);

SetpointCommandNormalized
SetpointCommandNormalized_create(SetpointCommandNormalized self, int ioa, float value, bool selectCommand, int ql);

float
SetpointCommandNormalized_getValue(SetpointCommandNormalized self);

int
SetPointCommandNormalized_getQL(SetpointCommandNormalized self);

bool
SetpointCommandNormalized_isSelect(SetpointCommandNormalized self);

/*************************************************
 * SetpointCommandScaled : InformationObject
 ************************************************/

typedef struct sSetpointCommandScaled* SetpointCommandScaled;

void
SetpointCommandScaled_destroy(SetpointCommandScaled self);

SetpointCommandScaled
SetpointCommandScaled_create(SetpointCommandScaled self, int ioa, float value, bool selectCommand, int ql);

int
SetpointCommandScaled_getValue(SetpointCommandScaled self);

int
SetpointCommandScaled_getQL(SetpointCommandScaled self);

bool
SetpointCommandScaled_isSelect(SetpointCommandScaled self);

/*************************************************
 * SetpointCommandShort: InformationObject
 ************************************************/

typedef struct sSetpointCommandShort* SetpointCommandShort;

void
SetpointCommandShort_destroy(SetpointCommandShort self);

SetpointCommandShort
SetpointCommandShort_create(SetpointCommandShort self, int ioa, float value, bool selectCommand, int ql);

float
SetpointCommandShort_getValue(SetpointCommandShort self);

int
SetpointCommandShort_getQL(SetpointCommandShort self);

bool
SetpointCommandShort_isSelect(SetpointCommandShort self);

/*************************************************
 * Bitstring32Command : InformationObject
 ************************************************/

typedef struct sBitstring32Command* Bitstring32Command;

Bitstring32Command
Bitstring32Command_create(Bitstring32Command self, int ioa, uint32_t value);

void
Bitstring32Command_destroy(Bitstring32Command self);

uint32_t
Bitstring32Command_getValue(Bitstring32Command self);

/*************************************************
 * InterrogationCommand : InformationObject
 ************************************************/

typedef struct sInterrogationCommand* InterrogationCommand;

InterrogationCommand
InterrogationCommand_create(InterrogationCommand self, int ioa, uint8_t qoi);

void
InterrogationCommand_destroy(InterrogationCommand self);

uint8_t
InterrogationCommand_getQOI(InterrogationCommand self);

/*************************************************
 * ReadCommand : InformationObject
 ************************************************/

typedef struct sReadCommand* ReadCommand;

ReadCommand
ReadCommand_create(ReadCommand self, int ioa);

void
ReadCommand_destroy(ReadCommand self);

/***************************************************
 * ClockSynchronizationCommand : InformationObject
 **************************************************/

typedef struct sClockSynchronizationCommand* ClockSynchronizationCommand;

ClockSynchronizationCommand
ClockSynchronizationCommand_create(ClockSynchronizationCommand self, int ioa);

void
ClockSynchronizationCommand_destroy(ClockSynchronizationCommand self);

CP56Time2a
ClockSynchronizationCommand_getTime(ClockSynchronizationCommand self);

#ifdef __cplusplus
}
#endif

#endif /* SRC_INC_INFORMATION_OBJECTS_H_ */
