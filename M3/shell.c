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
	interrupt(0x21, 0, "Bad Command: ", 0, 0);
	interrupt(0x21, 0, input, 0 ,0);
	interrupt(0x21, 0, "", 0, 0);
}