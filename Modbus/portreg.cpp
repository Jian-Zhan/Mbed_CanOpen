#include "mb.h"
#include "mbport.h"

//    MB_ENOREG,                  /*!< illegal register address. */
//    MB_EINVAL,                  /*!< illegal argument. */

eMBErrorCode
readOD( USHORT usIndex, UCHAR * pucRegBuffer, USHORT usNRegs )
{
    const indextable *odEntry;
    UNS32 errorCode;
    ODCallback_t *CallbackList;
    UNS8 subIndex;
    UNS32 subIndexSizeInByte, subIndexSizeInShort, odSizeInShort = 0;

    odEntry = scanIndexOD (d, wIndex, &errorCode, &CallbackList);
    if (errorCode != OD_SUCCESSFUL) {
        return MB_ENOREG;
    }

    odSizeInShort = 0;
    for (subIndex = 0; subIndex < odEntry->nSubCount; subIndex++) {
        if (odEntry->pSubindex[subIndex].bAccessType & WO) {
            // If a subindex is not readable
            accessDictionaryError(usIndex, subIndex, 0, 0, OD_READ_NOT_ALLOWED);
            return MB_ENOREG;
        }

        subIndexSizeInByte = odEntry->pSubindex[subIndex].size;
        subIndexSizeInShort = (subIndexSizeInByte / 2) + (subIndexSizeInByte % 2);
        odSizeInShort += subIndexSizeInShort;
    }

    if (odSizeInShort != usNRegs) {
        return MB_EINVAL;
    }

    for (subIndex = 0; subIndex < odEntry->nSubCount; subIndex++) {
    }
}

eMBErrorCode
writeOD( USHORT usIndex, UCHAR * pucRegBuffer, USHORT usNRegs )
{
    // TODO
    return MB_EINVAL;
}

// Only accept reading/writing holding registors. The usAddress is OD index of CO_Data, and
// usNRegs must match OD size. subIndexes of an OD entry will be padded to 16-bits.
eMBErrorCode
eMBRegHoldingCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs, eMBRegisterMode eMode )
{
    eMBErrorCode    eStatus = MB_ENOERR;
    int             iRegIndex;

    if (eMode == MB_REG_READ) {
        eStatus = readOD(usAddress, pucRegBuffer, usNRegs);
    }
    else if (eMode == MB_REG_WRITE) {
        eStatus = writeOD(usAddress, pucRegBuffer, usNRegs);
    }

    return eStatus;
}

eMBErrorCode
eMBRegInputCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNRegs )
{
    return MB_ENOREG;
}

eMBErrorCode
eMBRegCoilsCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNCoils,
               eMBRegisterMode eMode )
{
    return MB_ENOREG;
}

eMBErrorCode
eMBRegDiscreteCB( UCHAR * pucRegBuffer, USHORT usAddress, USHORT usNDiscrete )
{
    return MB_ENOREG;
}

