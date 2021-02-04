#ifndef _CH2OSENSOR_H_
#define _CH2OSENSOR_H_

#include <string.h>
#include <stdint.h>

class CH2OSensor {
    private:
        bool checkSum();
        char *sendData(char *comm);
        char *_res = NULL;
    public:
        CH2OSensor();
        void init(int txPin, int rxPin, int baudrate, int uart_number);
        float getConcentration();
        ~CH2OSensor();
};

#endif