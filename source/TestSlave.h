
/* File generated by gen_cfile.py. Should not be modified. */

#ifndef TESTSLAVE_H
#define TESTSLAVE_H

#include "data.h"

/* Prototypes of function provided by object dictionnary */
UNS32 TestSlave_valueRangeTest (UNS8 typeValue, void * value);
const indextable * TestSlave_scanIndexOD (CO_Data *d, UNS16 wIndex, UNS32 * errorCode);

/* Master node data struct */
extern CO_Data TestSlave_Data;

typedef struct {
    UNS16 mbRegister;
    UNS16 coIndex;
    UNS8  coSubIndex;
    UNS32 coEntrySizeInShort;
    UNS16* pointer;
} modbus_mapping_t;

extern const modbus_mapping_t TestSlave_modbus_mapping[];

typedef struct {
    UNS16 svRegister;
    UNS16 coIndex;
    UNS8  coSubIndex;
    UNS32 coEntrySizeInShort;
    UNS16* pointer;
} to_be_saved_t;

extern const to_be_saved_t TestSlave_to_be_saved[];

extern UNS16 CANopen_Node_ID;		/* Mapped at index 0x2000, subindex 0x00*/
extern UNS32 CANopen_Baud_Rate;		/* Mapped at index 0x2001, subindex 0x00*/
extern UNS16 Modbus_Node_ID;		/* Mapped at index 0x2002, subindex 0x00*/
extern UNS32 Modbus_Baud_Rate;		/* Mapped at index 0x2003, subindex 0x00*/
extern UNS8 Read_Inputs_8_Bit[1];		/* Mapped at index 0x6000, subindex 0x01 - 0x01 */
extern UNS8 Read_Input_Bit_0x1_to_0x80[8];		/* Mapped at index 0x6020, subindex 0x01 - 0x08 */
extern UNS8 Write_Outputs_8_Bit[1];		/* Mapped at index 0x6200, subindex 0x01 - 0x01 */
extern UNS8 Write_Outputs_Bit_1_to_128[8];		/* Mapped at index 0x6220, subindex 0x01 - 0x08 */
extern INTEGER16 Read_Analogue_Input_16_Bit[4];		/* Mapped at index 0x6401, subindex 0x01 - 0x04 */
extern INTEGER16 Write_Analogue_Output_16_Bit[2];		/* Mapped at index 0x6411, subindex 0x01 - 0x02 */
extern REAL32 Analogue_Input_Scaling_Float[4];		/* Mapped at index 0x642F, subindex 0x01 - 0x04 */
extern UNS32 Analogue_Input_SI_unit[4];		/* Mapped at index 0x6430, subindex 0x01 - 0x04 */
extern REAL32 Analogue_Output_Scaling_Float[2];		/* Mapped at index 0x6442, subindex 0x01 - 0x02 */
extern UNS32 Analogue_Output_SI_Unit[2];		/* Mapped at index 0x6450, subindex 0x01 - 0x02 */

#endif // TESTSLAVE_H
