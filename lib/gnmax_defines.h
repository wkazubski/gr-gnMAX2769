#ifndef GNMAX_DEFINES_H_
#define GNMAX_DEFINES_H_

typedef struct GNMAX_CPX
{
    short int i;    //!< Real value
    short int q;    //!< Imaginary value
} GNMAX_CPX;

//#define GN3S_SAMPS_MS  (2048) //!< All incoming signals are resampled to this sampling frequency
#define GNMAX_SAMPS_5MS (40919) // 5MS at fs=8.1838e6
//!< FIFO structure for linked list?
/*----------------------------------------------------------------------------------------------*/
/*! \ingroup STRUCTS
 *  @brief linked list structure for circular FIFO buffer */
typedef struct gnmax_ms_packet {

    gnmax_ms_packet *next;
    int count;                       //!< Number of packets
    GNMAX_CPX data[GNMAX_SAMPS_5MS]; //!< Payload size

} gnmax_ms_packet;
/*----------------------------------------------------------------------------------------------*/

typedef struct gnmax_variables {

    int mode;
    int bias;
    int ant;
    int freq;
    int bw;
    int zeroif;

} gnmax_variables;
/*----------------------------------------------------------------------------------------------*/

#endif //GNMAX_DEFINES_H_
