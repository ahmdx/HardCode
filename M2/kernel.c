void printString(char*);

int main(){
  printString("Hello World\0");
  while(1){}
}

void printString(char* string){
  int i = 0;
  while(string[i] != '\0'){
    interrupt(0x10, 0xE*256+string[i], 0, 0, 0);
    i++;
  }
}


