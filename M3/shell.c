void handleCommand(char*);

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
	char* view = "view";
	char* execute = "execute";
	int checkEqual = 1;
	char* programName;
	char* fileName;
	char buffer[13312];
	
	while(i<4){		//check if equal "view"
	  if(input[i] != view[i]){
	    checkEqual = 0;
	  }
	  i++;
	}
	if(checkEqual == 0){
	  i=0;
	  checkEqual = 1;
	  
	  while(i<7){		//check if equal "execute"
	  if(input[i] != execute[i]){
	    checkEqual = 0;
	  }
	  i++;
	  }
	if(checkEqual == 0){		//bad command if not equal both
	  interrupt(0x21, 0, "Bad Command: ", 0, 0);
	  interrupt(0x21, 0, input, 0 ,0);
	  interrupt(0x21, 0, "", 0, 0);

	}else{		//if equal "execute"
	  i=0;
	  while(i<6){
	   if(input[i+8] == "\0"){		//i+8 to skip "execute "
	     break;
	   }
	   programName[i] = input[i+8];
	   i++;
	  }
	  interrupt(0x21, 4, programName, 0x2000, 0);
	}
	
	}else{
	  i=0;
	  while(i<6){
	    if(input[i+5] == "\0"){		//i+5 to skip "view "
	      break;
	    }
	    fileName[i] = input[i+5];
	    i++;
	  }
	 interrupt(0x21, 3, fileName, buffer, 0);
	 interrupt(0x21, 0, buffer, 0, 0);
	}	
	
}