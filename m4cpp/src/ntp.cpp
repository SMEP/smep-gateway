/******************************************************************************
 * Project Headers
 *****************************************************************************/
#include "ntp.h"
#include "string.h"

/******************************************************************************
 * System Headers
 *****************************************************************************/



/******************************************************************************
 * Preprocessor Directives and Macros
 *****************************************************************************/


/******************************************************************************
 * Class Member Function Definitions
 *****************************************************************************/
void Timestamp::ReverseEndian(void) {
    ReverseEndianInt(seconds);
    ReverseEndianInt(fraction);
}

time_t Timestamp::to_time_t(void) {
    return (seconds - ((70 * 365 + 17) * 86400))&0x7fffffff;
}

void NTPMessage::ReverseEndian(void) {
    ref.ReverseEndian();
    orig.ReverseEndian();
    rx.ReverseEndian();
    tx.ReverseEndian();
}

int NTPMessage::recv() {
    ReverseEndian();
    return 0;
}

int NTPMessage::sendto() {
    ReverseEndian();


    return 0;
}

void NTPMessage::clear() {
    memset(this, 0, sizeof(*this));
}
