#include "mbed.h"
#define div_2 7812
#define div_4 3906
#define div_8 1953

DigitalIn sel(D10);
DigitalIn up(D11);
DigitalIn down(D12);
AnalogOut aout(PA_4);
AnalogIn ain(A0);

int main()
{
    float ADCdata[128];
    int div = div_2;
    int up_last, down_last;
    int j = 0;
    int cnt = 0;
    int temp = 0;
    int num = 1;
    int a = 1;

    printf("2Hz\r\n");
    while (sel == 0) {
        if (up == 1 && up_last == 0) {
            if (div == div_2) {
                div = div_4;
                num = 2;
                a = 3;
                printf("4Hz\r\n");
            } else if (div == div_4) {
                div = div_8;
                num = 4;
                a = 7;
                printf("8Hz\r\n");
            } else {
                div = div_8;
                num = 4;
                a = 7;
            }
        } 
        if (down == 1 && down_last == 0) {
            if (div == div_8) {
                div = div_4;
                num = 2;
                a = 3;
                printf("4Hz\r\n");
            } else if (div == div_4) {
                div = div_2;
                num = 1;
                a = 1;
                printf("2Hz\r\n");
            } else {
                div = div_2;
                num = 1;
                a = 1;
            }
        }
        up_last = up;
        down_last = down;
        ThisThread::sleep_for(10ms);
    }
    ThisThread::sleep_for(1s);
    printf("\r\n");
    while (1) {
        for (float i = 0.0f; i < 1.0f; i += 0.16666f) {
            aout = i;
            if (cnt <= num * 128) cnt++;
            if (j < 128 && cnt % num == 0) {
                ADCdata[j++] = ain;
            }
            wait_us(div);
        }
        for (int i = 0; i < 45; i++) {
            if (cnt <= num * 128) cnt++;
            if (j < 128 && cnt % num == 0) {
                ADCdata[j++] = ain;
            }
            wait_us(div);
        }
        for (float i = 1.0f; i > 0.0f; i -= 0.07692f) {
            aout = i;
            if (cnt <= num * 128) cnt++;
            if (j < 128 && cnt % num == 0) {
                ADCdata[j++] = ain;
            }
            wait_us(div);
        }
        if (temp == a) {
            for (int k = 0; k < 128; k++) {
                printf("%f\r\n", ADCdata[k]);
            }
        }
        temp++;
    }
}