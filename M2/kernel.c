char readCharacter();
void readString(char*);
void printString(char*);
void printCharacter(char*);
void readSector(char*, int);
int div(int, int);
int mod(int, int);
void handleInterrupt21(int, int , int, int);

// interrupt(I_NUM, AX, BX, CX, DX)
// AX = AH*256+AL

int main() {
  // char line[80]; // TASK 2
  // char buffer[512]; // TASK 3
  // printString("Hello World"); //TASK 1
  // printCharacter(0xd); // TASK 1
  // printCharacter(0xa); // TASK 1
  // printString("Enter a line: "); // TASK 2
  // readString(line); // TASK 2
  // printString("Echo: "); // TASK 2
  // printString(line); // TASK 2
  // readSector(buffer, 30); // TASK 3
  // printString(buffer); // TASK 3
   char line[80]; // TASK 5
   makeInterrupt21(); // TASK 5
   interrupt(0x21,1,line,0,0); // TASK 5
   interrupt(0x21,0,line,0,0); // TASK 5
 

  while(1){}
}

// TASK 1

void printCharacter(char character){
  interrupt(0x10, 0xE*256+character, 0, 0, 0);
}

void printString(char* string) {
  int i = 0;
  while(string[i] != '\0'){
    printCharacter(string[i]);
    i++;
  }
}

// TASK 2

void readString(char* string) {
  char enter = 0xd;
  char backspace = 0x8;
  char carriageReturn = 0xd;
  char linefeed = 0xa;
  char end = 0x0;

  char letter = readCharacter();

  int i = 0;
  while(letter != enter){
    if (letter == backspace){
      if (i > 0) {
        printCharacter(backspace);
        printCharacter(end);
        printCharacter(backspace);
        i--;
      }
    } else {
      string[i] = letter;
      printCharacter(string[i]);
      i++;
    }
    letter = readCharacter();
  }
  string[i] = carriageReturn;
  string[++i] = linefeed;
  string[++i] = end;
  printCharacter(carriageReturn);
  printCharacter(linefeed);
}

char readCharacter(){
  interrupt(0x16, 0, 0, 0, 0);
}

// TASK 3
void readSector(char* buffer, int sector){
  int relsector = mod(sector,18) + 1;
  int head = mod(div(sector,18),2);
  int track = div(sector,36);
  int cx = track*256+relsector;
  int dx = head*256;
  interrupt(0x13, 2*256+1, buffer, cx, dx);
}

int div(int x, int y){
  int count = 0;
  while(y<x){
    x = x-y;
    count++;
  }
  return count;
}

int mod(int x, int y){
  while(y<x){
    x = x-y;
  }
  return x;
}

// TASK 4/5
void handleInterrupt21(int ax, int bx, int cx, int dx){
  if(ax==0){
  printString(bx);
  }else{
    if(ax==1){
    readString(bx);
    }else{
      if(ax==2){
      readSector(bx,cx);
      }else{
	if(ax>=3){
	printString("ERROR INVALID AX VALUE");
	}
      }
    }
  }
}