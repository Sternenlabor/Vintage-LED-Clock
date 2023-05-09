# Vintage-LED-Clock
# WiFi configuration
SSID and credentials are kept in a separate file which is not included in GIT repository.   
Create file *credentials.h* in *src* folder and add SSID and WiFi password.   
e.g.:

    #ifndef _CREDENTIALS_H_
    #define _CREDENTIALS_H_

    const char cstrSSID[] = "MyNetwork";
    const char cstrPWD[] = "secret";
    const char cstrHostname[] = "Vintage-LED-Clock";

    #endif /* _CREDENTIALS_H_ */

