#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <thread>
#include <unistd.h>
#define PORT 8080

class Server {

    const uchar IP_ADDR_LEN = 16; 
    int m_max_connections;
    int m_port;
    char m_str_ip_addr[16];
    bool m_running = false;


    int server_fd, new_socket, valread;
    struct sockaddr_in address;
    int opt = 1;
    int addrlen = sizeof(address);

    public Server(char ip[], int port, int max_con) {
        strcpy(m_str_ip_addr, ip);
        m_por = port;
        m_max_connections = max_con;
    }
    
    public bool start() {
       if (m_running) 
           return false;
       // create socket connection
       //// setup address
       //// bind socket
       //// 
       // Creating socket file descriptor
       if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
       {
           perror("socket failed");
           return false;
       }
       // Forcefully attaching socket to the port 8080
       if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
                                                  &opt, sizeof(opt)))
       {
           perror("setsockopt");
           return false;
       }
       address.sin_family = AF_INET;
       address.sin_addr.s_addr = INADDR_ANY;
       address.sin_port = htons( PORT );

       // Forcefully attaching socket to the port 8080
       if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0)
       {
           perror("bind failed");
           return false;
       }
       if (listen(server_fd, m_max_connections) < 0)
       {
           perror("listen");
           return false;
       }

       // create listener thread
       thread listenerThread(handleListener);
       listenerThread.start();
       return true; 
    }
  
    public stop() {
       m_running = false; 
       // close socket connection 
    }
 
    void handlerListener() {
        while (true) {
            if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))<0) {
                perror("accept");
                exit(EXIT_FAILURE);
            } 
            Thread clientThread(handleClientConnection, new_socket);
            clientThread.start();
        }
    } 
   
    public handleClientConnection(int client_socket_fd) {
         // process client connection
         // read whole input stream
         int valread = read(client_socket_fd, buffer, 1024); 
         string str_received = new string(buffer);
         // parse http method
         string http_method = str_received.Substring(0, str_received.IndexOf(" "));
         int start = str_received.IndexOf(httpMethod) + httpMethod.Length + 1;
         int length = str_received.LastIndexOf("HTTP") - start - 1;
         string requested_url = str_received.Substring(start, length);
         IServlet servlet = ServletFactory.getServlet(requested_url);
         if (servlet != null) {
             servlet.handleHttpRequest(str_received, client_socket_fd);
         }
         else {
             sendResponse(clientSocket, "<html><head><meta 
                http-equiv=\"Content-Type\" content=\"text/html; 
                charset=utf-8\"></head><body><h2>Atasoy Simple Web 
                Server</h2><div>404 - Not 
                Found</div></body></html>");
         }
         // close client connection 
         close(client_socket_fd);
    } 
    
    public sendResponse(int client, char[] response) {
        send(client, response, strlen(response), 0);
    }

    public bool isStarted() { return m_running; }
};
