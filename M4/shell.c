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
	char* delete = "delete";
	char* copy = "copy";
	char* dir = "dir";
	char* create = "create";
	int checkEqual = 1;
	char* programName;
	char* fileName1;
	char* fileName2;
	char buffer[13312];
	
	while(i<4){		//check if equal "view"
	  if(input[i] != view[i]){
	    checkEqual = 0;
	  }
	  i++;
	}
	if(checkEqual == 1){		//if equal "view"
	  i=0;
	  while(i<6){
	    if(input[i+5] == "\0"){		//i+5 to skip "view "
	      break;
	    }
	    fileName1[i] = input[i+5];
	    i++;
	  }
	 interrupt(0x21, 3, fileName1, buffer, 0);
	 interrupt(0x21, 0, buffer, 0, 0);
	}
	
	  checkEqual = 1;
	  i = 0;
      while(i<7){		//check if equal "execute"
	  if(input[i] != execute[i]){
	    checkEqual = 0;
	      }
	    i++;
	    }
      if(checkEqual == 1){		//if equal "execute"
	   i=0
	while(i<6){
	  if(input[i+8] == "\0"){		//i+8 to skip "execute "
	     break;
	   }
	   programName[i] = input[i+8];
	   i++;
	  }
	  interrupt(0x21, 4, programName, 0x2000, 0);
	  //interrupt(0x21, 5, 0, 0, 0);
	}
	 
	 checkEqual = 1;
	 i = 0;
      while(i<6){      //check if equal "delete"
	  if(input[i] != delete[i]){
	    checkEqual = 0;
	  }  
	   i++;
	    }
      
      if(checkEqual == 1){		//if equal "delete"
	  i=0;
	  while(i<6){
	    if(input[i+7] == "\0"){		//i+7 to skip "delete"
	      break;
	    }
	    fileName1[i] = input[i+7];
	    i++;
	  }
	 interrupt(0x21, 7, fileName1, 0, 0);
		
	}
	    checkEqual = 1;
	    i = 0;
      while(i<4){      //check if equal "copy"
	  if(input[i] != copy[i]){
	    checkEqual = 0;
	  }  
	   i++;
	    }
      if(checkEqual == 1){
	  i=0;
	  while(i<6){
	    if(input[i+5] == "\0"){		//i+7 to skip "copy"
	      break;
	    }
	    fileName1[i] = input[i+5];
	    i++;
	  }
	  int count = i + 6;
	  i = 0;
	  while(i<6){
	    if(input[count] == "\0"){
	      break;
	    }
	    fileName2[i] = input[count];
	    i++
	    count++
	  }
	interrupt(0x21, 3, fileName1, buffer, 0);
	interrupt(0x21, 8, fileName2, buffer, 1);
		
	}
	
	checkEqual = 1;
	i = 0;
	
	while(i<3){ //check if equal "dir"
	  if(input[i] != dir[i]){
	    checkEqual = 0;
	  }
	  i++;
	}
	
	if(checkEqual == 1){		//if equal "dir"
	  
	}
	
	checkEqual = 1;
	i = 0;
	
	while(i<6){ //check if equal "create"
	  if(input[i] != create[i]){
	    checkEqual = 0;
	  }
	  i++;
	}
	
	if(checkEqual == 1){		//if equal "create"
	  
	}
	
	if(checkEqual == 0){		//bad command if not equal both
	  interrupt(0x21, 0, "Bad Command: ", 0, 0);
	  interrupt(0x21, 0, input, 0 ,0);
	  interrupt(0x21, 0, "", 0, 0);
}