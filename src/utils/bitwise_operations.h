#ifndef BITWISE_OPERATION_H_
#define BITWISE_OPERATION_H_

#define SET_BIT(Reg,Pin) (Reg |= (1<<Pin))
#define CLEAR_BIT(Reg,Pin) (Reg &= ~(1<<Pin))
#define GET_BIT(Reg,Pin) ((Reg & (1<<Pin)) >> Pin)
#define TOGGLE_BIT(Reg,Pin) (Reg ^= (1<<Pin))

#endif