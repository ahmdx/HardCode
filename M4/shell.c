void handleCommand(char*);

int main() {
  char line[100];
  char directory[512];
  char dirName[32];
  int dirIndex = 0;
  int dirEntry = 0;
  int dirSector = 0;
  //while(1) {
  // makeInterrupt21();
  interrupt(0x21, 0, "shell$ ", 0, 0);
  interrupt(0x21, 1, line, 0, 0);
  handleCommand(line);
  interrupt(0x21, 5, 0, 0, 0);
  //}
}

void handleCommand(char* input) {
  char directory[512];
  char dirName[32];
  char fileName[32];
  char lineRead[100];
  char file[13312];
  int dirIndex = 0;
  int dirEntry = 0;
  int dirSector = 1;
  //   int i = 0;
  //   int comm = 0;
  //   char* view = "view";
  //   char* execute = "execute";
  //   int checkEqual = 1;
  //   char* programName;
  //   char* fileName;
  //   char buffer[13312];

  if (input[0] == 'v' && input[1] == 'i' && input[2] == 'e' && input[3] == 'w') {
	interrupt(0x21, 0, "view", 0, 0);
  } else if (input[0] == 'e' && input[1] == 'x' && input[2] == 'e' && input[3] == 'c' && input[4] == 'u' && input[5] == 't' && input[6] == 'e') {
	interrupt(0x21, 0, "execute", 0, 0);
  } else if (input[0] == 'd' && input[1] == 'e' && input[2] == 'l' && input[3] == 'e' && input[4] == 't' && input[5] == 'e') {
	interrupt(0x21, 0, "delete", 0, 0);
  } else if (input[0] == 'c' && input[1] == 'o' && input[2] == 'p' && input[3] == 'y') {
	interrupt(0x21, 0, "copy", 0, 0);
  }
  else if (input[0] == 'd' && input[1] == 'i' && input[2] == 'r') {
	interrupt(0x21, 2, directory, 2, 0);
	while (dirIndex < 16) {
	  if (directory[dirIndex*32] != 0x00) {
		dirEntry = 0;
		while(dirEntry < 6) {
		  if (directory[dirIndex*32 + dirEntry] != 0x00) {
			dirName[dirEntry] = directory[dirIndex*32 + dirEntry];
		  } else {
			dirName[dirEntry] = 0x5F;
		  }
		  dirEntry++;
		}
// 		dirEntry = 6;
// 		while(dirEntry < 32) {
// 		  if (directory[dirIndex*32 + dirEntry] == 0x00) {
// 			break;
// 		  }
// 		  dirSector++;
// 		  dirEntry++;
// 		}
// 		interrupt(0x21, 0, 2 + '0', 0, 0);
		dirEntry = 6;
		dirName[dirEntry + 0] = 1 + '0';
		dirName[dirEntry + 0] = '\r';
		dirName[dirEntry + 1] = '\n';
		dirName[dirEntry + 2] = 0x00;
		interrupt(0x21, 0, dirName, 0, 0);
		dirSector = 0;
	  }
	  dirIndex++;
	}
  }
  //   else if (input[0] == 'c' && input[1] == 'r' && input[2] == 'e' && input[3] == 'a' && input[4] == 't' && input[5] == 'e') {
  // 	while(input[dirIndex + 7] != '\0') {
  // 	  fileName[dirIndex] = input[dirIndex + 7];
  // 	  dirIndex++;
  // 	}
  // 	interrupt(0x21, 0, "create> ",0, 0);
  // 	interrupt(0x21, 1, lineRead, 0, 0);
  // 	while(lineRead[0] != 0xd) {
  // 	  dirIndex = 0;
  // 	  while(lineRead[dirIndex] != '\0') {
  // 		file[dirEntry] = lineRead[dirIndex];
  // 		dirIndex++;
  // 		dirEntry++;
  // 	  }
  // 	  interrupt(0x21, 0, "create> ",0, 0);
  // 	  interrupt(0x21, 1, lineRead, 0, 0);
  // 	}
  // 	interrupt(0x21, 8, fileName, file, 1);
  //   }
  else {
	interrupt(0x21, 0, "Fatal: Bad command - ", 0, 0);
	interrupt(0x21, 0, input, 0, 0);
  }
  interrupt(0x21, 0, "\r", 0, 0);
  interrupt(0x21, 0, "\n", 0, 0);

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

// void dir() {
//   char directory[512];
//   char* name;
//   int dirIndex = 0;
//   int dirEntry = 0;
//   while (dirIndex < 16) {
// 	if (directory[dirIndex*32] != 0x00) {
// 	  dirEntry = 0;
// 	  while(dirEntry < 6) {
// 		name[dirEntry] = directory[dirIndex*32 + dirEntry];
// 		dirEntry++;
// 	  }
// 	  name[dirEntry] = '\r';
// 	  name[dirEntry + 1] = '\n';
// 	  printString(name);
// 	}
// 	dirIndex++;
//   }
//   //   readSector(directory, 2);
//   interrupt(0x21, 2, directory, 2, 0);
//
//   printString("Dir!");
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
