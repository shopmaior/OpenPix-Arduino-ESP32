
#ifndef OpenPix_h
#define OpenPix_h
 
#include <Arduino.h>

class OpenPix
{
    public:
        OpenPix(char* appID, char* rootCA=NULL);
        String generateUniqueID();
        String pixCreateChargeInsecure(int value);
        String pixPaymentStatusInsecure(String correlationID);
    
    private:
        char* _openPixAppID;
        char* _rootCA;
};
 
#endif