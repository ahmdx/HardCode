void handleCommand(char*);
int div(int, int);
int mod(int, int);

int main() {
  char line[100];
  //while(1) {
  // makeInterrupt21();
  interrupt(0x21, 0, "shell$ ", 0, 0);
  interrupt(0x21, 1, line, 0, 0);
  handleCommand(line);
  interrupt(0x21, 5, 0, 0, 0);
  //}
}

void handleCommand(char* input) {
  //   int i = 0;
  //   int comm = 0;
  //   char* view = "view";
  //   char* execute = "execute";
  //   int checkEqual = 1;
  //   char* programName;
  //   char* fileName;
  //   char buffer[13312];
//   char directory[512];
//   char dirName[32];
//   char secNum[2];
//   char fileName[32];
//   char lineRead[100];
//   char file[13312];
//   int dirIndex = 0;
//   int dirEntry = 0;
//   int dirSector = 1;
  char* viewFileName;
  char viewBuffer[13312];
  int v = 0;
  char* execProgramName;
  int e = 0;
//   char* deleteFileName;
//   int d = 0;

  if (input[0] == 'v' && input[1] == 'i' && input[2] == 'e' && input[3] == 'w') {
	while(v<6){
	  if(input[v+5] == "\0"){		//v+5 to skip "view "
		break;
	  }
	  viewFileName[v] = input[v+5];
	  v++;
	}
	interrupt(0x21, 3, viewFileName, viewBuffer, 0);
	interrupt(0x21, 0, viewBuffer, 0, 0);
  }else
  if (input[0] == 'e' && input[1] == 'x' && input[2] == 'e' && input[3] == 'c' && input[4] == 'u' && input[5] == 't' && input[6] == 'e') {
	while(e<6){
	  if(input[e+8] == "\0"){		//e+8 to skip "execute "
		break;
	  }
	  execProgramName[e] = input[e+8];
	  e++;
	}
	interrupt(0x21, 4, execProgramName, 0x2000, 0);
  }else
  if (input[0] == 'd' && input[1] == 'e' && input[2] == 'l' && input[3] == 'e' && input[4] == 't' && input[5] == 'e') {
    interrupt(0x21,12,input,0,0);
  }else
  if (input[0] == 'c' && input[1] == 'o' && input[2] == 'p' && input[3] == 'y') {
	interrupt(0x21,9,input,0,0);
  }else
  if (input[0] == 'd' && input[1] == 'i' && input[2] == 'r') {
	interrupt(0x21,10,0,0,0);
  }else
  if (input[0] == 'c' && input[1] == 'r' && input[2] == 'e' && input[3] == 'a' && input[4] == 't' && input[5] == 'e') {
    interrupt(0x21,11,input,0,0);
  }
  else {
	interrupt(0x21, 0, "Fatal: Bad command - ", 0, 0);
	interrupt(0x21, 0, input, 0, 0);
  }
  return;
  // interrupt(0x21, 0, "\r", 0, 0);
  // interrupt(0x21, 0, "\n", 0, 0);

  //   interrupt(0x21, 0, "\r", 0, 0);
  //   interrupt(0x21, 0, "\n", 0, 0);

  //   while(i<4){		//check if equal "view"
  // 	if(input[i] != view[i]){
  // 	  checkEqual = 0;
  // 	}
  // 	i++;
  //   }
  //   if(checkEqual == 0){
  // 	i=0;
  // 	checkEqual = 1;
  //
  // 	while(i<7){		//check if equal "execute"
  // 	  if(input[i] != execute[i]){
  // 		checkEqual = 0;
  // 	  }
  // 	  i++;
  // 	}
  // 	if(checkEqual == 0){		//bad command if not equal both
  // 	  interrupt(0x21, 0, "Bad Command: ", 0, 0);
  // 	  interrupt(0x21, 0, input, 0 ,0);
  // 	  interrupt(0x21, 0, "", 0, 0);
  //
  // 	}else{		//if equal "execute"
  // 	  i=0;
  // 	  while(i<6){
  // 		if(input[i+8] == "\0"){		//i+8 to skip "execute "
  // 		  break;
  // 		}
  // 		programName[i] = input[i+8];
  // 		i++;
  // 	  }
  // 	  interrupt(0x21, 4, programName, 0x2000, 0);
  // 	  //interrupt(0x21, 5, 0, 0, 0);
  // 	}
  //
  //   }else{
  // 	i=0;
  // 	while(i<6){
  // 	  if(input[i+5] == "\0"){		//i+5 to skip "view "
  // 		break;
  // 	  }
  // 	  fileName[i] = input[i+5];
  // 	  i++;
  // 	}
  // 	interrupt(0x21, 3, fileName, buffer, 0);
  // 	interrupt(0x21, 0, buffer, 0, 0);
  //   }
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

// EVERYTHING BELOW THIS LINE IS REDUNDANT AND DOES NOT HELP WITH THIS MILESTONE

// void viewfunc(char* input){
//   char* fileName;
//   char buffer[13312];
//   int v = 0;
//   while(v<6){
// 	if(input[v+5] == "\0"){		//v+5 to skip "view "
// 	  break;
// 	}
// 	fileName[v] = input[v+5];
// 	v++;
//   }
//   interrupt(0x21, 3, fileName, buffer, 0);
//   interrupt(0x21, 0, buffer, 0, 0);
// }

// void executefunc(char* input){
//   char* programName;
//   int e = 0;
//   while(e<6){
// 	if(input[e+8] == "\0"){		//e+8 to skip "execute "
// 	  break;
// 	}
// 	programName[e] = input[e+8];
// 	e++;
//   }
//   interrupt(0x21, 4, programName, 0x2000, 0);
// }

// int getCommand(char* input) {
//   int index = 0;
//   char* command;
//   while (input[index] != ' '  && input[index] != '\0') {
// 	command[index] = input[index];
// 	index++;
//   }
//   command[index] = 0x00;
//   if (isEqual(command, "view") != 0) {
// 	return 0;
//   } else if (isEqual(command, "execute") != 0) {
// 	return 1;
//   } else if (isEqual(command, "delete") != 0) {
// 	return 2;
//   } else if (isEqual(command, "copy") != 0) {
// 	return 3;
//   } else if (isEqual(command, "dir") != 0) {
// 	return 4;
//   } else if (isEqual(command, "create") != 0) {
// 	return 5;
//   }
//   return -1;
// }
//
// int isEqual(char* arg0, char* arg1) {
//   int index = 0;
//   int l0 = length(arg0);
//   int l1 = length(arg1);
//   if (l0 != l1)
// 	return 0;
//   while(arg0[index] != '\0') {
// 	if (arg0[index] != arg1[index])
// 	  return 0;
// 	index++;
//   }
//   return 1;
// }
//
// int length(char* arg) {
//   int length = 0;
//   int index = 0;
//   while(arg[index] != '\0') {
// 	length++;
// 	index++;
//   }
//   return length;
// }
