
char readCharacter();
void readString(char*);
void printString(char*);
void printCharacter(char*);
void readSector(char*, int);
void readFile(char*,char*);
int div(int, int);
int mod(int, int);
void handleInterrupt21(int, int , int, int);
void executeProgram(char*, int);
void terminate();
void writeSector(char*, int);
void deleteFile(char*);

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
  // char line[80]; // TASK 5
  // makeInterrupt21(); // TASK 5
  // interrupt(0x21,1,line,0,0); // TASK 5
  // interrupt(0x21,0,line,0,0); // TASK 5
   char buffer[13312]; // STEP 1
   makeInterrupt21(); // STEP 1
  // interrupt(0x21, 3, "messag", buffer, 0); /*read the file into buffer*/ // STEP 1
  // interrupt(0x21, 0, buffer, 0, 0); /*print out the file*/ // STEP 1
  // readFile("messag",buffer);
  // printString(buffer);
  // makeInterrupt21(); // STEP 2, 3 & 4
  // interrupt(0x21, 4, "tstprg", 0x2000, 0); // STEP 2 & 3
  // interrupt(0x21, 5, 0, 0, 0); // STEP 3
  // interrupt(0x21, 4, "shell", 0x2000, 0); //STEP 4 & 5
   
   interrupt(0x21, 7, "messag", 0, 0); //delete messag
   interrupt(0x21, 3, "messag", buffer, 0); // try to read messag
   interrupt(0x21, 0, buffer, 0, 0); //print out the contents of buffer
  while(1);
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
  switch (ax){
    case 0:
      printString(bx);break;
    case 1:
      readString(bx);break;
    case 2:
      readSector(bx,cx);break;
    case 3:
      readFile(bx,cx);break;
    case 4:
      executeProgram(bx, cx);break;
    case 5:
      terminate();break;
    case 6:
      writeSector(bx,cx);break;
    case 7:
      deleteFile(bx);break;
    default:
      printString("Fatal: Invalid AX value");
  }
}

// M3-STEP 1
void readFile(char* fileName,char* buffer){
  int sectorNameCount = 0;
  int loadCount;
  char load[512];
  readSector(load,2);
  
  while(sectorNameCount<16){   //loop 16 times to check all 16 sector names
    int sectorCharCount = 0;
    int check = 1;
    loadCount = sectorNameCount*32;
    while(sectorCharCount<6){ //loop on the sector name char by char
      if(fileName[sectorCharCount] != load[loadCount]){
        check = 0;
      }
      sectorCharCount++;
      loadCount++;
    }
    if(check != 0){ //if sector name and file name are equal, break from the loop
      break;
    }
    sectorNameCount++;
  }

  if(sectorNameCount==16){  //if looped over all sectors and name was never equal return
    return;

  }
  else{
    int fileEntryCount = 0;
    int bufferCount;
    int tempCount;
    while(fileEntryCount<26){ //read all sectors into temp which is then copied into buffer
      char temp[512];
      readSector(temp,load[loadCount]);   //load[loadCount] is a char but it should be an int
      bufferCount = fileEntryCount*512;   //"add 512 to the buffer address every time you call readSector"
      tempCount = 0;
      
      while(tempCount<512){ //copy temp to buffer
        buffer[bufferCount]=temp[tempCount];
        bufferCount++;
        tempCount++;
      }
      fileEntryCount++;
      loadCount++;
    }
  }
}
// M3-STEP 2
void executeProgram(char* name, int segment) {
  char buffer[13312];
  int i = -1;
  readFile(name, buffer);
  while (i++ < 13312) {
    putInMemory(segment, 0x0000 + i, buffer[i]);
  }
  launchProgram(segment);
}
// M3-STEP 3
void terminate() {
  // while(1);
  interrupt(0x21, 4, "shell", 0x2000, 0);
}
//M4-STEP 1
void writeSector(char* buffer, int sector){
  int relsector = mod(sector,18) + 1;
  int head = mod(div(sector,18),2);
  int track = div(sector,36);
  int cx = track*256+relsector;
  int dx = head*256;
  interrupt(0x13, 3*256+1, buffer, cx, dx);
}
//M4-STEP 2
void deleteFile(char* name){
  char map[512];
  char directory[512];
  int sectorNameCount;
  int loadCount;
  readSector(map,1);
  readSector(directory,2);
  
  while(sectorNameCount<16){   //loop 16 times to check all 16 sector names
    int sectorCharCount = 0;
    int check = 1;
    loadCount = sectorNameCount*32;
    while(sectorCharCount<6){ //loop on the sector name char by char
      if(name[sectorCharCount] != directory[loadCount]){
        check = 0;
      }
      sectorCharCount++;
      loadCount++;
    }
    if(check != 0){ //if sector name and file name are equal, break from the loop
      break;
    }
    sectorNameCount++;
  }
  if(sectorNameCount==16){  //if looped over all sectors and name was never equal return
    return;
  }else{
    int fileEntryCount = 0;
    int bufferCount;
    int tempCount;
    directory[loadCount-6] = 0; // Set the first byte of the file name to 0x00.
    while(fileEntryCount<26){ //read all sectors into temp which is then copied into buffer
      if(directory[loadCount] != 0){
      map[directory[loadCount]] = 0; //  For each sector, set the corresponding Map byte to 0x00.
      }
      fileEntryCount++;
      loadCount++;
    }
  }
  //Write the character arrays holding the Directory and Map back to their appropriate sectors.
  writeSector(directory,2);
  writeSector(map,1);
}