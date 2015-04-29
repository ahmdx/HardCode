void handleCommand(char*);
int getCommand(char*);
int length(char*);
void printString(char*);
void printCharacter(char*);

int main() {
  char line[100];
  while(1) {
	// makeInterrupt21();
	interrupt(0x21, 0, "shell$ ", 0, 0);
	interrupt(0x21, 1, line, 0, 0);
	handleCommand(line);
  }
}

void handleCommand(char* input) {
  int i = 0;
  int comm = 0;
  //   char* view = "view";
  //   char* execute = "execute";
  //   int checkEqual = 1;
  //   char* programName;
  //   char* fileName;
  //   char buffer[13312];
  comm = getCommand(input);
  switch (comm){
	case 0:	//view
	  // 	  printString("view!");
	  interrupt(0x21, 0, "view!", 0, 0);
	  break;
	case 1:	//execute
	  interrupt(0x21, 0, "execute!", 0, 0);
	  break;
	case 2:
	  interrupt(0x21, 0, "delete!", 0, 0);
	  break;
	case 3:
	  interrupt(0x21, 0, "copy!", 0, 0);
	  break;
	case 4:	//dir
	  interrupt(0x21, 0, "dir!", 0, 0);
	  break;
	case 5:
	  interrupt(0x21, 0, "create!", 0, 0);
	  break;
	default:
	  interrupt(0x21, 0, "Fatal: Bad command.", 0, 0);break;
  }

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

int getCommand(char* input) {
  int index = 0;
  char* command;
  while (input[index] != ' '  && input[index] != '\0') {
	command[index] = input[index];
	index++;
  }
  command[index] = 0x00;
  if (isEqual(command, "view") != 0) {
	return 0;
  } else if (isEqual(command, "execute") != 0) {
	return 1;
  } else if (isEqual(command, "delete") != 0) {
	return 2;
  } else if (isEqual(command, "copy") != 0) {
	return 3;
  } else if (isEqual(command, "dir") != 0) {
	return 4;
  } else if (isEqual(command, "create") != 0) {
	return 5;
  }
  return -1;
}

int isEqual(char* arg0, char* arg1) {
  int index = 0;
  int l0 = length(arg0);
  int l1 = length(arg1);
  if (l0 != l1)
	return 0;
  while(arg0[index] != '\0') {
	if (arg0[index] != arg1[index])
	  return 0;
	index++;
  }
  return 1;
}

int length(char* arg) {
  int length = 0;
  int index = 0;
  while(arg[index] != '\0') {
	length++;
	index++;
  }
  return length;
}

// void printCharacter(char character){
//   interrupt(0x10, 0xE*256+character, 0, 0, 0);
// }
//
void printString(char* string) {
  //   int i = 0;
  //   while(string[i] != '\0'){
  // 	printCharacter(string[i]);
  // 	i++;
  //   }
  //   printCharacter(0xd);
  //   printCharacter(0xa);
  interrupt(0x21, 0, string, 0, 0);
}
