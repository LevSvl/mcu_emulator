#ifndef SIGNAL_H
#define SIGNAL_H

typedef unsigned char signal_t;

#define SIGNAL_INPUT        extern signal_t
#define SIGNAL_OUTPUT       signal_t
#define SIGNAL_INOUT        extern signal_t
#define SIGNAL_INTERNAL     signal_t
#define SIGNAL_T            signal_t

#endif // SIGNAL_H
