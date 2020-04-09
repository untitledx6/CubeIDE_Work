#include "wifi.h"

void Server_Init(void) {
	HAL_Delay(50);
	printf("AT+RST\r\n");
	HAL_Delay(300);
	printf("AT+CWMODE=2\r\n");
	HAL_Delay(100);
	printf("AT+CIPMUX=1\r\n");
	HAL_Delay(100);
	printf("AT+CIPSERVER=1,8080\r\n");
	HAL_Delay(100);
	printf("AT+CIPSTO=0\r\n");
	HAL_Delay(100);
}

void Client_Init(void) {
	HAL_Delay(50);
	printf("AT+RST\r\n");
	HAL_Delay(300);
	printf("AT+CWMODE=1\r\n");
	HAL_Delay(50);
	printf("AT+CWJAP=\"untitledx6\",\"./text.out\"\r\n");
	HAL_Delay(5000);
	printf("AT+CIPMUX=0\r\n");
	HAL_Delay(100);
	printf("AT+CIPSTART=\"TCP\",\"172.20.10.6\",1347\r\n");
	HAL_Delay(100);
	printf("AT+CIPMODE=1\r\n");
	HAL_Delay(100);
	printf("AT+CIPSEND\r\n");
	HAL_Delay(100);

}
void Client_SentTo_Server(uint8_t *Str) {

	printf("%s\r\n", Str);

}

void Server_SentTo_Client(uint8_t *Str) {
	HAL_Delay(50);
	printf("AT+CIPSEND=0,%d\r\n", Strlen(Str) + 2);
	HAL_Delay(50);
	printf("%s\r\n", Str);
	HAL_Delay(50);
}

 uint8_t Strlen(uint8_t *s) {
	 for(uint8_t i = 0; i < 256; i++) {
		 if(s[i] == '\0') {
			 return i;
		 }
	 }
 }
 void Strcpy(uint8_t *s1, uint8_t *s2) {
	 uint8_t i;
	 for(i = 0; s2[i] != '\0'; i++) {
		 s1[i] = s2[i];
	 }
	 s1[i] = '\0';
 }
uint8_t Strcmp(uint8_t *s1, uint8_t *s2) {
	uint8_t i;
		 for(i = 0; s2[i] != '\0'; i++) {
			 if(s1[i] != s2[i]) {
				 return 0;
			 }
		 }
		 if(s1[i] == '\0') {
			 return 1;
		 }
		 return 0;
}
