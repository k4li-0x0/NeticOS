#include "codes.h"
#include "../display/vga.h"
#include <stdio.h>
#include <stdbool.h>
#define uint8_t unsigned short

bool isascii(int c){
  return c >= 0 && c<128;
}

uint8_t kybrd_ctrl_read_status(){
  return inb(KYBRD_CTRL_STATS_REG);
}

void kybrd_ctrl_send_cmd (uint8_t cmd) {
  while (1)
    if ( (kybrd_ctrl_read_status () & KYBRD_CTRL_STATS_MASK_IN_BUF) == 0)
      break;
  outb(KYBRD_CTRL_CMD_REG, cmd);
}

uint8_t kybrd_enc_read_buf () {
  return inb(KYBRD_ENC_INPUT_BUF);
}

void kybrd_enc_send_cmd (uint8_t cmd) {
  while (1)
    if ( (kybrd_ctrl_read_status () & KYBRD_CTRL_STATS_MASK_IN_BUF) == 0)
      break;
  outb(KYBRD_ENC_CMD_REG, cmd);
}

char getchar(){              
    uint8_t code = 0;
    uint8_t key = 0;
    while(1){
      if (kybrd_ctrl_read_status () & KYBRD_CTRL_STATS_MASK_OUT_BUF) {
        code = kybrd_enc_read_buf ();
        if(code <= 0x58){ //is in range??
          key = _kkybrd_scancode_std [code];
          break;
        }
      }
    }
    return key;
}

void getline(char* string, int len){
  uint8_t i=0;
  int flag = 0;
  char temp = 0;
  memset(string,0,len);
  while(i<255 && temp != 0x0D) {
    temp = getchar();
    if(isascii(temp) && temp != 0x0D) {
      if(temp == 0x08) {
        GlobalVga->ClearChar();
        i--;
      }else{
      GlobalVga->PutChar(temp);
      string[i] = temp;
      i++;}
    }
  }
  string[i] = 0x0A;
}